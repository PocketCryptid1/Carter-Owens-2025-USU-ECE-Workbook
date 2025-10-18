#include "floorplan.h"
#include <iostream>
#include <stack>

using namespace std;

floorplan::floorplan(){
    // Initialize the floorplan
    modules = vector<module*>();
}

double floorplan::cost(string NPE) {
    stack<module*> stk;
    for (char c : NPE) {
        if (c == 'H' || c == 'V') {
            if (stk.size() < 2) {
                cerr << "Error: Not enough modules on stack for operation " << c << endl;
                return -1.0;
            }
            module* right = stk.top(); 
            stk.pop();
            module* left = stk.top(); 
            stk.pop();

            // Consider all rotation combinations
            double min_area = 1e18;
            double best_width = 0, best_height = 0;

            // Four combinations: (orig, orig), (orig, rot), (rot, orig), (rot, rot)
            double left_w[2] = {left->width, left->height};
            double left_h[2] = {left->height, left->width};
            double right_w[2] = {right->width, right->height};
            double right_h[2] = {right->height, right->width};

            for (int l_rot = 0; l_rot < 2; ++l_rot) {
                for (int r_rot = 0; r_rot < 2; ++r_rot) {
                    double w, h;
                    if (c == 'H') {
                        w = max(left_w[l_rot], right_w[r_rot]);
                        h = left_h[l_rot] + right_h[r_rot];
                    } else {
                        w = left_w[l_rot] + right_w[r_rot];
                        h = max(left_h[l_rot], right_h[r_rot]);
                    }
                    double area = w * h;
                    if (area < min_area) {
                        min_area = area;
                        best_width = w;
                        best_height = h;
                    }
                }
            }
            
            module* parent = new module(-1, left->area + right->area, 0.0, (c == 'H') ? H : V);
            parent->width = best_width;
            parent->height = best_height;
            stk.push(parent);
            
        } else if (isdigit(c) || isalpha(c)) {
            int id = -1;
            if (isdigit(c)) {
                id = c - '0';
            } else {
                id = c - 'a' + 10;
            }
            
            for (int i = 0; i < (int)modules.size(); i++) {
                if (modules[i]->id == id) {
                    module* mod = modules[i];
                    stk.push(mod);
                }
            }
        }
    }
    module* root = stk.top();
    return root->width * root->height;
}