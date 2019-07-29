#ifndef A3_HPP
#define A3_HPP

#include "Maze.hpp"
#include <math.h>
#include <vector>

int distance(Maze& maze, int sx, int sy, int fx, int fy) {
	// GOAL: Find the distance of the shortest solution path

	// Using a three-deep array
	// [d][s][p] -> 
	// 	[d]:	Depth / Layer
	// 	[s]:	Selected state
	// 	[p]:	[0]: x, [1]: y
	
	// Creating data structure to expand
	std::vector<std::vector<int*>> states;
	states.push_back({});
	states[0].push_back({});
	states[0][0] = new int[2];

	// Populating initial properties
	states[0][0][0] = sx;
	states[0][0][1] = sy;

	// Initializing current state
	int maxD = 0;

	int safety_c = 0;

	while (safety_c < 10000){
		safety_c++;
		maxD++;
		states.push_back({});

		// std::cout << "Exploring layer " << maxD << std::endl;

		// Completely explore a layer
		for (unsigned s = 0; s < states[maxD-1].size(); s++){
			
			// Variables to simplify expressions
			int curX = states[maxD-1][s][0];
			int curY = states[maxD-1][s][1];
			int surr[] = {curX + 1, curY, curX - 1, curY, curX, curY + 1, curX, curY - 1};

			// std::cout << "\tExploring from: " << curX << ", " << curY << std::endl;

			// Check all surrounding tiles as needed
			for (int i = 0; i < 8; i = i + 2){

				if (maze.is_open(surr[i], surr[i+1]) and not maze.is_visited(surr[i], surr[i+1])){

					// std::cout << "\t\tFound open space: " << surr[i] << ", " << surr[i+1] << std::endl;

					// Create if it's the solution
					if (surr[i] == fx and surr[i+1] == fy){
					
						// Deconstruct...
						for (unsigned d = 0; d < states.size(); d++){
							for (unsigned s = 0; s < states[d].size(); s++){
								delete[] states[d][s];
							}
						}

						// Return the solution
						return maxD;
					}

					// Mark it as visited
					maze.mark(surr[i], surr[i+1]);

					// Setting up storage
					states[maxD].push_back({});
					int s_index = states[maxD].size() - 1;
					states[maxD][s_index] = new int[2];

					// Storing properties
					states[maxD][s_index][0] = surr[i];
					states[maxD][s_index][1] = surr[i+1];

				}
			}	
		}

	}

	// Deconstructor
	for (unsigned d = 0; d < states.size(); d++){
		for (unsigned s = 0; s < states[d].size(); s++){
			delete[] states[d][s];
		}
	}

	return -1;
} // distance

#endif // A3_HPP
