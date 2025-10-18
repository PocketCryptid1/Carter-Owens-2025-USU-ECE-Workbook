
#include "module.h"
#include "floorplan.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    floorplan fp;
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        char id;
        double area, aspect_ratio;
        if (!(iss >> id >> area >> aspect_ratio)) { break; }
        if (isdigit(id)) {
            id = id - '0';
        } else {
            id = id - 'a' + 10;
        }
        int id_int = static_cast<int>(id);
        module* mod = new module(id_int, area, aspect_ratio, LEAF);
        fp.modules.push_back(mod);
    }
    infile.close();

    string NPE = "12V3V4V5V6V7V8V9VaVbVcVdVeVfVgViVjVkVlV";
    double cost = fp.cost(NPE);
    cout << "NPE: " << NPE << "\t Cost: " << cost << endl;

    NPE = "12H3H4H5H6H7H8H9HaHbHcHdHeHfHgHiHjHkHlH";
    cost = fp.cost(NPE);
    cout << "NPE: " << NPE << "\t Cost: " << cost << endl;

    NPE = "213546H7VHVa8V9HcVHgHibdHkVHfeHVlHVjHVH";
    cost = fp.cost(NPE);
    cout << "NPE: " << NPE << "\t Cost: " << cost << endl;

    // Clean up allocated modules
    for (auto mod : fp.modules) {
        delete mod;
    }

    return 0;
}