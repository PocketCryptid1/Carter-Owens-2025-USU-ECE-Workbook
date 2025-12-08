# Part B

## What is the purpose of each of the 3 stages in this routing algorithm? How are they different from each other? How do they work together as a flow?

### Initial Routing

    creates an acceptable first pass to improve with heuristic techniques

### Rip up and Re-Route(RRR)

    iteratavely removes illegal or poorly optimized nets and re-places them 

### Greedy Improvement

    individually refine each net one by one

## How does SimpleGR build a framework to allow the 3 stages? (Think high-level, it should be brief)

global grid, net list, congestion map, and cost model
each stage implements the same API
cost functions, rip‑up criteria, and local moves are configurable
