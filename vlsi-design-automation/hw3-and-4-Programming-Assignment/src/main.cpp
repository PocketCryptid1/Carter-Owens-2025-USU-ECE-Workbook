#include "module.h"
#include "floorplan.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * @file main.cpp
 * @brief Small driver that reads module definitions from a text file and
 *        evaluates a few hard-coded NPEs, printing their computed cost.
 *
 * Input file format (each line):
 *   <id> <area> <aspect_ratio>
 * where <id> is a single character: '0'..'9' or 'a'..'l' (mapped to ids 10..21).
 */

int main(int argc, char** argv) {

    // parameters

    // comenting out unused parameters to avoid compiler warnings
    // double chipratio = 2.0;      // unused in this simple area-only cost
    int nmoves = 10;             // attempts per temperature
    double ratio = 0.85;         // temperature reduction factor
    double t0_input = -1.0;      // initial temperature input
    double lambdatf = 0.005;     // when temp < lambdatf * t0, set ratio to 0.1
    int iseed = 3;               // RNG seed
    double P = 0.99;             // initial acceptance probability for t0 calc
    double epsilon = 0.001;      // stopping temperature threshold

    // Random engine
    std::mt19937 rng(static_cast<unsigned int>(iseed));
    std::uniform_real_distribution<double> uni01(0.0, 1.0);

    // Read modules from input file
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

        // Convert character id to integer id used by the floorplan modules list.
        if (isdigit(id)) {
            id = id - '0';
        } else {
            id = id - 'a' + 10;
        }
        int id_int = static_cast<int>(id);

        // Create leaf module and add to the floorplan modules collection.
        module* mod = new module(id_int, area, aspect_ratio, LEAF);
        fp.modules.push_back(mod);
    }
    infile.close();

    // Build a vector of operands from the modules list
    int n = static_cast<int>(fp.modules.size());
    if (n == 0) {
        cerr << "No modules loaded from input file." << endl;
        return 1;
    }
    vector<char> operands;
    operands.reserve(n);
    for (auto mod : fp.modules) {
        int id = mod->id;
        char ch;
        if (id < 10) ch = static_cast<char>('0' + id);
        else ch = static_cast<char>('a' + (id - 10));
        operands.push_back(ch);
    }

    // Helper: create an initial left-deep NPE: "abV cV dV ..." (all vertical)
    auto build_initial_npe = [&](const vector<char> &ops) {
        string expr;
        for (char c : ops) expr.push_back(c);
        // append n-1 'V' operators to make a valid postfix left-deep tree
        for (int i = 0; i < (int)ops.size() - 1; ++i) expr.push_back('V');
        return expr;
    };

    // Build initial topology and evaluate initial cost
    string currentNPE = build_initial_npe(operands);
    double currentCost = fp.cost(currentNPE);
    if (currentCost < 0) {
        cerr << "Error evaluating initial NPE." << endl;
        return 1;
    }
    string bestNPE = currentNPE;
    double bestCost = currentCost;

    cout << "Initial topology: " << currentNPE << "\n";
    cout << "Initial cost: " << currentCost << "\n";

    // Collect operand/operator indices for fast neighbor moves
    auto operand_indices = [&](const string &expr) {
        vector<int> idx;
        for (int i = 0; i < (int)expr.size(); ++i) if (isalnum(static_cast<unsigned char>(expr[i]))) idx.push_back(i);
        return idx;
    };
    auto operator_indices = [&](const string &expr) {
        vector<int> idx;
        for (int i = 0; i < (int)expr.size(); ++i) if (expr[i] == 'H' || expr[i] == 'V') idx.push_back(i);
        return idx;
    };

    // If t0_input is negative, compute t0 from sampling nmoves random moves
    double t0 = t0_input;
    if (t0_input < 0.0) {
        // sample random moves to compute average positive delta
        double acc = 0.0;
        int count = 0;
        string npe_sample = currentNPE;
        auto op_idx = operand_indices(npe_sample);
        auto oper_idx = operator_indices(npe_sample);
        for (int i = 0; i < nmoves; ++i) {
            // choose a random move: 0 swap operands, 1 flip operator
            if (!op_idx.empty() && (oper_idx.empty() || (rng() & 1))) {
                // swap two operands
                int a = std::uniform_int_distribution<int>(0, (int)op_idx.size()-1)(rng);
                int b = std::uniform_int_distribution<int>(0, (int)op_idx.size()-1)(rng);
                std::swap(npe_sample[op_idx[a]], npe_sample[op_idx[b]]);
            } else if (!oper_idx.empty()) {
                int k = std::uniform_int_distribution<int>(0, (int)oper_idx.size()-1)(rng);
                npe_sample[oper_idx[k]] = (npe_sample[oper_idx[k]] == 'H') ? 'V' : 'H';
            }
            double cost_new = fp.cost(npe_sample);
            double delta = cost_new - currentCost;
            if (delta > 0) { acc += delta; ++count; }
        }
        double avgPosDelta = (count > 0) ? (acc / count) : 1.0;
        // t0 chosen so that exp(-avgPosDelta / t0) = P  => t0 = -avgPosDelta / ln(P)
        t0 = -avgPosDelta / std::log(P);
        if (!(t0 > 0)) t0 = 1.0; // fallback
    }

    double T = t0;

    // Simulated annealing main loop
    int iter = 0;
    while (T > epsilon) {
        for (int m = 0; m < nmoves; ++m) {
            ++iter;
            // prepare indices for current expression
            auto op_idx = operand_indices(currentNPE);
            auto oper_idx = operator_indices(currentNPE);

            string candidate = currentNPE;

            // Choose random move type: 0 swap operands, 1 flip operator
            int moveType = 0;
            if (op_idx.empty()) moveType = 1;
            else if (oper_idx.empty()) moveType = 0;
            else moveType = std::uniform_int_distribution<int>(0,1)(rng);

            if (moveType == 0 && op_idx.size() >= 2) {
                int a = std::uniform_int_distribution<int>(0, (int)op_idx.size()-1)(rng);
                int b = std::uniform_int_distribution<int>(0, (int)op_idx.size()-1)(rng);
                std::swap(candidate[op_idx[a]], candidate[op_idx[b]]);
            } else if (moveType == 1 && !oper_idx.empty()) {
                int k = std::uniform_int_distribution<int>(0, (int)oper_idx.size()-1)(rng);
                candidate[oper_idx[k]] = (candidate[oper_idx[k]] == 'H') ? 'V' : 'H';
            }

            double candidateCost = fp.cost(candidate);
            if (candidateCost < 0) continue; // invalid neighbor; skip

            double delta = candidateCost - currentCost;
            bool accept = false;
            if (delta <= 0) accept = true;
            else {
                double prob = std::exp(-delta / T);
                if (uni01(rng) < prob) accept = true;
            }

            if (accept) {
                currentNPE = candidate;
                currentCost = candidateCost;
                if (currentCost < bestCost) {
                    bestCost = currentCost;
                    bestNPE = currentNPE;
                }
            }
        }

        // update temperature
        if (T < lambdatf * t0) ratio = 0.1;
        T *= ratio;
    }

    cout << "\n===== ANNEALING COMPLETE =====\n";
    cout << "Final topology: " << bestNPE << "\n";
    cout << "Final cost: " << bestCost << "\n";

    // Clean up allocated modules
    for (auto mod : fp.modules) {
        delete mod;
    }

    return 0;
}