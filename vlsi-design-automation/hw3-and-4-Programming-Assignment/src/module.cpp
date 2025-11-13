#include "module.h"

#include <cmath>

using namespace std;

/**
 * @file module.cpp
 * @brief Implementation of the module constructor which derives width/height
 *        from area and aspect ratio for leaf modules.
 */

module::module(int id, double area, double aspect_ratio, modType type){
    // Initialize members
    this->id = id;
    this->area = area;
    this->aspect_ratio = aspect_ratio;
    this->type = type;

    // Derive geometry from area and aspect ratio. For LEAF nodes the provided
    // aspect_ratio should be > 0. For internal nodes callers may overwrite
    // width/height after construction.
    this->width = sqrt(area * aspect_ratio);
    this->height = sqrt(area / aspect_ratio);
}
