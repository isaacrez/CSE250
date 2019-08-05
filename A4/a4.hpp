// File: a4.hpp
// Isaac
// Rezey
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A4_HPP
#define A4_HPP

#include <ostream>
#include "symbol.hpp"

#include <vector>
#include <cmath>
#include <iostream>

// NOTES:
// 	bnode has the following properties:
// 		T: 	the stored value
// 		right:	the right child
// 		left:	the left child

// 	Iter appears to be a standard vector iterator.

// 	symbol has the following properties:
// 		value:	Character of the symbol
// 		count:	Occurences of this symbol

void printVector(std::vector<bnode<symbol>>::iterator first, std::vector<bnode<symbol>>::iterator last);
void print_recur(std::ostream& os, bnode<symbol>* root, std::string ID);

template <typename Iter>
bnode<symbol>* huffman_tree(Iter first, Iter last){
	// Goal:	Generate the huffman tree, from a vector of characters
	// Inputs:	Vector of symbols, with proper counts

	// Sort provided list from least-to-greatest
	std::vector<bnode<symbol>> sortedList = mergeSort(first, last);

	for (unsigned i = 0; i < sortedList.size(); i++){
		sortedList[i].left = nullptr;
		sortedList[i].right = nullptr;
	}

	while (sortedList.size() > 1) {
		// Create placeholder bin
		bnode<symbol>* bin;
		
		// DEBUGGING
		printVector(sortedList.begin(), sortedList.end());
		std::cout << "Compacting a node..." << std::endl;
		bin->value.value = 'T';

		// Populate bin appropriately
		bin->left = &sortedList.back();
		sortedList.pop_back();
		bin->right = &sortedList.back();
		sortedList.pop_back();
		bin->value.count = bin->left->value.count + bin->right->value.count;
	
		std::cout << "Combining the following nodes: " << bin->left->value.value << " & " << bin->right->value.value << std::endl;

		// Store it back in the vector, in proper order
		bool added = false;
		for (std::vector<bnode<symbol>*>::iterator it = sortedList.end() - 1; it != sortedList.begin() - 1; it--){
			if (it->value.count >= bin->value.count){
				sortedList.insert(it+1, bin);
				added = true;
				break;
			}
		}

		// Catch for when the inserted element is the largest in the vector
		if (not added){
			sortedList.insert(sortedList.begin(), bin);
		}
	}

	return &sortedList.front();

}

// DEBUGGING
void printVector(std::vector<bnode<symbol>>::iterator first, std::vector<bnode<symbol>>::iterator last){
	std::cout << "Current vector:" << std::endl;
	for (; first != last; first++){
		std::cout << "\t" << first->value.value << ": " << first->value.count << std::endl;
	}
}

// Mergesort Method
// 	Used to organize elements to easily generate Huffman tree.
template<typename Iter>
std::vector<bnode<symbol>> mergeSort(Iter first, Iter last){

	std::vector<bnode<symbol>> list(first, last);
	// Recursion:	Lists greater than two elements
	if (list.size() > 2){

		// Split our list and call again
		int cutoff = std::ceil(list.size()/2);
		std::vector<bnode<symbol>> sublist_1 = mergeSort(list.begin(), list.begin() + cutoff);
		std::vector<bnode<symbol>> sublist_2 = mergeSort(list.begin() + cutoff, list.end());

		std::vector<bnode<symbol>> sortedList;

		// Combine our sublists
		std::vector<bnode<symbol>>::iterator it_1 = sublist_1.begin();
		std::vector<bnode<symbol>>::iterator it_2 = sublist_2.begin();

		while (it_1 != sublist_1.end() and it_2 != sublist_2.end()){
			if (it_1->value.count < it_2->value.count){
				sortedList.push_back(*it_2);
				it_2++;
			} else {
				sortedList.push_back(*it_1);
				it_1++;
			}
		}

		// Account for leftovers
		while (it_1 != sublist_1.end()){
			sortedList.push_back(*it_1);
			it_1++;
		}
		while (it_2 != sublist_2.end()){
			sortedList.push_back(*it_2);
			it_2++;
		}

		return sortedList;

	}
	// Base case 1:	One element list
	else if (list.size() == 1)
       	{
		return list;
	}
	// Base case 2:	Two element list
	else
	{
		// Check if the elements need to be swapped
		if (list[0].value.count < list[1].value.count){
			bnode<symbol> temp = list[1];
			list[1] = list[0];
			list[0] = temp;
		}
		return list;
	}
}

// IMPLEMENT YOUR FUNCTION print_dictionary
void print_dictionary(std::ostream& os, bnode<symbol>* root){
	// Goal:	Output the heap display, as desired
	// Method:	DFS	
	
//	print_recur(os, root, "");
}

void print_recur(std::ostream& os, bnode<symbol>* root, std::string ID){

	bool gate = true;
	std::cout << root->value.value << " " << ID << std::endl;

	if (ID.length() > 5){
		return;
	}

	// Check if this is an intermediate node
	if (root->left != nullptr){
		std::string left_ID = ID;
		left_ID.push_back('0');

		print_recur(os, root->left, left_ID);
		gate = false;
	}

	if (root->right != nullptr){
		std::string right_ID = ID;
		right_ID.push_back('1');

		print_recur(os, root->right, right_ID);
		gate = false;
	}

	// Output if it is NOT an intermediate node
	if (gate) {
		std::cout << root->value.value << " " << ID << std::endl;
	}
	
}

// IMPLEMENT YOUR FUNCTION release_tree
void release_tree(bnode<symbol>* root){
	// Goal:	Deconstruct the tree
	// Method:	DFS
}

#endif // A4_HPP
