#ifndef A3_HPP
#define A3_HPP

#include "Maze.hpp"
#include <math.h>
#include <iostream>

// Used for easily comparing values in our loop
int surr[] = {1, 0, 0, 1, -1, 0, 0, -1};

int distance(Maze& maze, int sx, int sy, int fx, int fy) {
	// GOAL: Find the distance of the shortest solution path

	// Mark our current tile as explored
	maze.mark(sx, sy);

	// Initialize our minimum path length
	// In case we hit a dead end, we want to ensure we don't return an arbitrary number
	// So we use our largest possible number, minus 1 (since we return minPath + 1)
	int minPath = 2137483647;
	// NOTE: INT_MAX returned an error when used

	// Call all valid directions
	for (int i = 0; i < 8; i = i + 2){

		int x = sx + surr[std::abs(i)];
		int y = sy + surr[std::abs(i)+1];
		// Check if we've reached our base case
		if (x == fx and y == fy){
			// We're adjacent to the solution! Move back up
			maze.unmark(sx, sy); // Unmark our current tile
			return 1;
		}

		// Checking the space is open to explore / unmarked
		if (maze.is_open(x, y) and not maze.is_visited(x, y)){

			// Make the recursive call
			int temp = distance(maze, x, y, fx, fy);
			
			// Check if this is a new shortest path
			if (temp < minPath){
				minPath = temp;
			}

		}
	}	

	// Unmark our tile (In case we blocked a shortest path!
	maze.unmark(sx, sy);

	// Return it back!
	return minPath + 1;

} // distance

#endif // A3_HPP
