# Graph Search AI Algorithms

This repository contains C++ implementations of **15 graph search algorithms** widely used in Artificial Intelligence and pathfinding.  
The focus is on demonstrating a variety of AI search techniques — from exhaustive uninformed methods to heuristic-driven, informed approaches.

---

## Algorithms Included

1. **British Museum Search (Brute Force Search)**  
   Explores the entire search space exhaustively, without using any heuristics. It checks every possible option until the goal is found. While it always finds a solution if one exists, it is often extremely resource-intensive.

2. **Depth-First Search (DFS)**  
   Proceeds down a single branch as far as possible before backtracking. DFS is memory-efficient but can get stuck in deep branches and doesn’t always return the shortest path.

3. **Breadth-First Search (BFS)**  
   Expands nodes level by level, visiting all neighbors before moving to the next depth. BFS guarantees the shortest path in unweighted graphs when all edge costs are equal.

4. **DFS + BFS Hybrid**  
   Integrates depth-first exploration with breadth-first coverage, aiming to combine DFS’s speed in certain cases with BFS’s systematic completeness.

5. **DFS with History**  
   An improved DFS that keeps a record of visited nodes to prevent cycles and duplicate state exploration, making it more efficient in graphs with loops.

6. **BFS with History**  
   Functions like BFS but avoids revisiting nodes by storing visited states, reducing unnecessary expansions and improving performance.

7. **Hill Climbing Search**  
   A heuristic-driven local search that moves toward better neighboring states. Fast and simple, but susceptible to getting trapped in local optima or flat plateaus.

8. **Beam Search**  
   A heuristic search that keeps only a fixed number of top candidates (beam width) at each depth, sacrificing completeness for speed and reduced memory usage.

9. **Hill Climbing with History**  
   An enhanced Hill Climbing approach that remembers visited states to prevent cycling, increasing the chances of escaping local traps.

10. **Beam Search with History**  
    Combines beam search with visited-state tracking to improve robustness and avoid redundant exploration.

11. **Oracle Search**  
    An idealized approach assuming perfect knowledge of the optimal path or heuristic, mainly used as a benchmark to compare other algorithms.

12. **Branch and Bound**  
    A systematic method that prunes any path whose cost exceeds the best known so far, enabling efficient search for optimal solutions in weighted graphs.

13. **Branch and Bound with Cost and Estimated Heuristics**  
    Enhances branch and bound with heuristic cost estimates to guide pruning and speed up the search while keeping results optimal.

14. **Branch and Bound + Cost + History**  
    Adds visited-state tracking to branch and bound with cost and heuristic, avoiding repeated work and improving efficiency.

15. **A Star**  
    Combines uniform-cost search with heuristics to quickly find the lowest-cost path. A* remains optimal when using an admissible and consistent heuristic.

---

## Usage

1. Clone the repository:  
   ```bash
   git clone https://github.com/Sreemanth-coder/AI_Search_Algorithms_CPP.git
   cd AI_Search_Algorithms_CPP
