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

#include <queue>
#include <list>
#include <cmath>
#include <iostream>

void printHelper(std::ostream& os, bnode<symbol>* root, std::string ID);
void print_dictionary(std::ostream& os, bnode<symbol>* root);

// IMPLEMENT YOUR FUNCTION huffman_tree
template <typename Iter>
bnode<symbol>* huffman_tree(Iter first, Iter last){

	std::priority_queue<symbol, std::vector<symbol>> myHeap;

	// Store everything into bnodes & push into queue
	for (; first != last; first++){
		myHeap.push(*first);
	}

	// Convert heap into a sorted list of bnodes
	std::list<bnode<symbol>*> sortedList;
	while (not myHeap.empty()){
		// Set up new node
		bnode<symbol>* bin = new bnode<symbol>;
		bin->value = myHeap.top();
		myHeap.pop();
		
		// Insert into our list
		sortedList.push_front(bin);
	}

	// Convert our sortedList into a tree
	while (sortedList.size() > 1){

		// Condense two nodes into a new bnode
		bnode<symbol>* bin = new bnode<symbol>;
		bin->left = sortedList.front();
		sortedList.pop_front();
		bin->right = sortedList.front();
		sortedList.pop_front();

		bin->value.count = bin->right->value.count + bin->left->value.count;
		if (bin->left->value.value < bin->right->value.value){
			bin->value.value = bin->left->value.value;
		} else {
			bin->value.value = bin->right->value.value;
		}

		// Insert our new bnode back into the list
		bool notInserted = true;
		for (auto it = sortedList.begin(); it != sortedList.end() ; it++){
			if (bin->value < (*it)->value){
				sortedList.insert(it, bin);
				notInserted = false;
				break;
			}
		}

		// Catch for when the node deserves to be thrown in the back 
		if (notInserted){
			sortedList.push_back(bin);
		}

		// DEBUGGING
		// std::cout << "New node: " << bin->left->value.value << "-" << bin->right->value.value << std::endl;
		// print_dictionary(std::cout, bin);

		// DEBUGGING
		// Print our list to confirm it's changing appropriately
		// std::cout << "New list:\n";
		// for (auto it = sortedList.begin(); it != sortedList.end(); it++){
		// 	std::cout << "\t" << (*it)->value.value << ": " << (*it)->value.count << std::endl;
		// }

	}

	return sortedList.front();
}

// Outputs the Huffman Encoding for the given tree
void print_dictionary(std::ostream& os, bnode<symbol>* root){
	printHelper(os, root, "");
}

void printHelper(std::ostream& os, bnode<symbol>* root, std::string ID){
	if (root->left == nullptr and root->right == nullptr){
		os << root->value.value << " " << ID << std::endl;
		return;
	}
	if (root->left != nullptr){
		printHelper(os, root->left, ID + '0');
	}
	if (root->right != nullptr){
		printHelper(os, root->right, ID + '1');
	}
}

// Memory clean-up
void release_tree(bnode<symbol>* root){
	// Reached base case: Leaf node
	if (root->left == nullptr and root->right == nullptr){
		delete root;
	} else {
	// Recursive case - call it's node's, then delete this node
		release_tree(root->left);
		release_tree(root->right);
		delete root;
	}
}

#endif // A4_HPP
