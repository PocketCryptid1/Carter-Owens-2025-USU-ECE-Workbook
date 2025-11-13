#ifndef FLOORPLAN
#define FLOORPLAN

#include "module.h"

#include <string>
#include <vector>
using namespace std;

/**
 * @file floorplan.h
 * @brief Simple floorplanning helper that evaluates the area (cost) of a
 *        normalized polish expression (NPE) using a basic rotation search.
 */
class floorplan
{
    public:
        /**
         * List of modules (pointers owned by caller in this simple project).
         * Each module should have a unique integer id for lookup when parsing
         * the NPE string.
         */
        vector<module*> modules;

        /**
         * @brief Compute the placement cost (area) for a given NPE string.
         *
         * The NPE is a postfix expression where operands are module ids
         * (digits 0-9 or letters a..l mapped to ids 10..21) and operators are
         * 'H' (horizontal cut) and 'V' (vertical cut). The function evaluates
         * the expression using a stack and considers both rotations for each
         * child (original and swapped width/height) to choose the minimum
         * enclosing rectangle area for each internal node.
         *
         * @param NPE Normalized Polish Expression string (postfix)
         * @return area of the root bounding rectangle, or -1.0 on error
         */
        double cost(string NPE);

        /**
         * Default constructor: initializes empty modules list.
         */
        floorplan();
};

#endif