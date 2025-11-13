#include "floorplan.h"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @file floorplan.cpp
 * @brief Implements floorplan cost evaluation by parsing an NPE and combining
 *        modules with H/V operators using an exhaustive rotation algorithm.
 *
 * Instead of greedily choosing rotations at each internal node, this
 * implementation computes the set of nondominated (width,height) pairs for
 * each subtree (the Pareto frontier). When combining two subtrees we form
 * all combinations of candidate pairs and then prune dominated pairs to keep
 * complexity manageable.
 */

floorplan::floorplan(){
    // Initialize the floorplan container (empty by default)
    modules = vector<module*>();
}

// Small helper type for candidate rectangle sizes
struct Rect { double w; double h; };

// Return true if a dominates b (a.width <= b.width && a.height <= b.height) and
// at least one strict.
static bool dominates(const Rect &a, const Rect &b) {
    return (a.w <= b.w && a.h <= b.h) && (a.w < b.w || a.h < b.h);
}

// Prune dominated rectangles from the candidate list (keep Pareto frontier).
static void prune(vector<Rect> &candidates) {
    // Sort by width asc, then height asc
    sort(candidates.begin(), candidates.end(), [](const Rect &x, const Rect &y){
        if (x.w != y.w) return x.w < y.w;
        return x.h < y.h;
    });
    vector<Rect> kept;
    for (const auto &r : candidates) {
        // if any kept element dominates r, skip r
        bool skip = false;
        for (const auto &k : kept) {
            if (dominates(k, r)) { skip = true; break; }
        }
        if (!skip) kept.push_back(r);
    }
    candidates.swap(kept);
}

double floorplan::cost(string NPE) {
    // Stack of candidate lists for partial results while evaluating NPE.
    stack<vector<Rect>> stk;

    for (char c : NPE) {
        if (c == 'H' || c == 'V') {
            if (stk.size() < 2) {
                // Malformed expression: not enough operands for operator
                return -1.0;
            }
            auto right_candidates = stk.top(); stk.pop();
            auto left_candidates = stk.top(); stk.pop();

            vector<Rect> combined;
            combined.reserve(left_candidates.size() * right_candidates.size());

            for (const auto &L : left_candidates) {
                for (const auto &R : right_candidates) {
                    Rect out;
                    if (c == 'H') {
                        // Horizontal cut: widths align (take max), heights add
                        out.w = max(L.w, R.w);
                        out.h = L.h + R.h;
                    } else {
                        // Vertical cut: heights align (take max), widths add
                        out.w = L.w + R.w;
                        out.h = max(L.h, R.h);
                    }
                    combined.push_back(out);
                }
            }

            // Prune dominated candidates to keep frontier small
            prune(combined);
            stk.push(std::move(combined));

        } else if (isdigit(c) || isalpha(c)) {
            int id = -1;
            if (isdigit(c)) id = c - '0';
            else id = c - 'a' + 10;

            // Find module with matching id
            module* found = nullptr;
            for (auto mod : modules) if (mod->id == id) { found = mod; break; }
            if (!found) {
                // module id not present in modules list
                return -1.0;
            }

            // Leaf has two candidate rotations if rotation yields different dims
            vector<Rect> leaf_candidates;
            Rect r1 { found->width, found->height };
            Rect r2 { found->height, found->width };
            leaf_candidates.push_back(r1);
            if (!(r1.w == r2.w && r1.h == r2.h)) leaf_candidates.push_back(r2);
            // prune in case both identical
            prune(leaf_candidates);
            stk.push(std::move(leaf_candidates));
        }
    }

    if (stk.empty()) { cerr << "Error: empty NPE evaluation stack" << endl; return -1.0; }
    auto root_candidates = stk.top();

    // Find minimum area among root candidates
    double min_area = 1e300;
    for (const auto &r : root_candidates) {
        double area = r.w * r.h;
        if (area < min_area) min_area = area;
    }

    return min_area;
}