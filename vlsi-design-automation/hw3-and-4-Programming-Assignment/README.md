# HW3 Programming Assignment - Floorplanner

This small C++ project evaluates the area (cost) of normalized polish expressions (NPE) for a set of rectangular modules. The implementation performs a simple rotation search at each internal node to pick the minimum enclosing rectangle.

## Build

From the `src/` directory run:

```bash
make
```

## Run

Provide an input file where each line is:

```
<id> <area> <aspect_ratio>
```

`<id>` is a single character: `0`..`9` or `a`..`l` (letters map to ids 10..21).

Example:

```bash
./floorplan src/sample_input.txt
```

## Clean

to clean all object files and compiled binary run:

```bash
make clean
```

## Notes

- The `cost()` method in `floorplan` parses NPE strings and tries both rotations for each child when combining with `H` or `V` operators to minimize the area of each internal node.
- Source files contain Doxygen-style comments for the public APIs and important algorithms.