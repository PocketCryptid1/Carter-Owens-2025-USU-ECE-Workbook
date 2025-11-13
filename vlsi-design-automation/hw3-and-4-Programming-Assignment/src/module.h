#ifndef MODULE
#define MODULE

/**
 * @file module.h
 * @brief Represents a rectangular module used by the floorplanner.
 */

/**
 * Types of module nodes used in the slicing tree / NPE evaluation.
 * H: horizontal cut (children stacked vertically)
 * V: vertical cut (children placed side-by-side)
 * LEAF: input module with specified area and aspect ratio
 */
enum modType { 
    H, 
    V, 
    LEAF 
};

/**
 * @class module
 * @brief Holds geometric properties and identity for a module.
 *
 * For leaf modules the constructor computes width/height from area and
 * aspect_ratio using:
 *   width = sqrt(area * aspect_ratio)
 *   height = sqrt(area / aspect_ratio)
 */
class module {
    public:
        modType type;        ///< Node type (H, V, or LEAF)
        int id;              ///< Numeric id used when parsing NPE (0..)
        double area;         ///< Module area (leaf) or summed area (internal)
        double aspect_ratio; ///< Width/height ratio (for leaves)
        double width;        ///< Computed width
        double height;       ///< Computed height

        /**
         * @brief Construct a module node.
         * @param id Integer identifier
         * @param area Area for the module
         * @param aspect_ratio Desired width/height ratio
         * @param type Node type (LEAF for input modules)
         */
        module(int id, double area, double aspect_ratio, modType type);
};

#endif