// File: a2.hpp
// Isaac 
// Rezey
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A2_HPP
#define A2_HPP

#include <algorithm>
#include <list>
#include <vector>

// REMOVE THIS
#include <iostream>

class key_value_sequences {
public:

	std::list< std::vector<int> > ext;

	// Determine the number of elements inserted for a particular key
	int size(int key) const {

		// Check through our entire exterior list
		for (std::list< std::vector<int> >::const_iterator it = ext.begin(); it != ext.end(); it++){

			std::vector<int> curVec = *it;
		
			// Check if first element is key	
			if (curVec[0] == key){
				return curVec.size()-1;
			}
			
		}

		// If it wasn't encountered - then just return zip!
		return 0;
	};

	// Given a particular key, find all corresponding values
	const int* data(int key) const{

		// Check through our entire exterior list
		for (std::list< std::vector<int> >::const_iterator it = ext.begin(); it != ext.end(); it++){

			// Check if the first value is the key
			std::vector<int> curVec = *it;
			if (*curVec.begin() == key){

				// Format the output to be returned
				// std::vector<int> output;
				// output.reserve(curVec.size()-1);

				// for (std::vector<int>::const_iterator i = curVec.begin(); i != curVec.end(); i++){
				//	output.push_back(*i);
				// }
				
				return curVec.data() + 1;
			}
		}
		return 0;
	};

	// Insert a value linked to a particular key
	void insert(int key, int value){

		// Check through our entire exterior list
		for (std::list<std::vector<int>>::iterator it = ext.begin(); it != ext.end(); it++){
			
			// Check if the first value is the desired key
			std::vector<int> curVec = *it;
			if (*curVec.begin() == key){
				
				curVec.push_back(value);
				std::cout << "Added " << curVec.back() << " to " << key << std::endl;
				return;
			}

		}

		// This key isn't in our system yet!
		std::vector<int> curVec;
		curVec.push_back(key);
		curVec.push_back(value);
		ext.push_back(curVec);

		std::cout << "Added " << curVec.back() << " to " << key << std::endl;
	};

};

#endif
