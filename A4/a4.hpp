// File: a4.hpp
// First Name
// Last Name
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A4_HPP
#define A4_HPP

#include <ostream>
#include "symbol.hpp"

// MAKE SURE TO UPDATE YOUR INFORMATION IN THE HEADER OF THIS FILE
// IMPLEMENT ALL REQUIRED FUNCTIONS BELOW
// YOU ARE NOT ALLOWED TO ALTER ANY INTERFACE
// INSIDE A FUNCTION YOU CAN DO WHATEVER YOU LIKE

// IMPLEMENT YOUR FUNCTION huffman_tree
template <typename Iter>
bnode<symbol>* huffman_tree(Iter first, Iter last);

// IMPLEMENT YOUR FUNCTION print_dictionary
void print_dictionary(std::ostream& os, bnode<symbol>* root);

// IMPLEMENT YOUR FUNCTION release_tree
void release_tree(bnode<symbol>* root);

#endif // A6_HPP
