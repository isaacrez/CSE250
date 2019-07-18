// File: a1.cpp
// Isaac
// Rezey
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

// Load relevant libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
// #include <chrono>

// Load helper functions
int findIndex(const std::string& elem, const int offset, const int powersFour[]);
int findOffset(int k);
double findDNAVal(char unit);

int main(int argc, char* argv[]){
	// INPUTS
	// 	argv[1]: Filename to be processed
	// 	argv[2]: K-mer length processed
	//	argv[3]: Threshold count for relevance

	// RUNTIME
	// 	Used to determine runtime of the function
	// auto start = std::chrono::high_resolution_clock::now();

	// Open the file
	std::ifstream myfile;
	myfile.open(argv[1]);

	// Read file's contents
	std::string dnaChain;
        getline(myfile, dnaChain);

	// Initial output formatting
	int k = atoi(argv[2]);
	int threshold = atoi(argv[3]);
	int chainLen = dnaChain.size();

	// Count the number of A, C, G, and T
	std::string baseCode = "ACGT";
	int count[4] {0};

	for (int i = 0; i < chainLen; i++){
		count[(int) findDNAVal(dnaChain[i])-1]++;
	}

	std::cout << "0 " << k << " " << chainLen << std::endl;
	std::cout << "1";
	
	for (int i = 0; i < 4; i++){
		std::cout << " " << count[i]; 
	}

	std::cout << std::endl;
	
	// Determine if K-mer processing is feasible
	// Is feasible
	if (k <= (int) dnaChain.size())
	{
		// Make the array able to house either the max number of
		// kmers the chain can create, or the number of unique kmers
		// of k length - whichever is smaller.
		int storSize = pow(4.0, k);

		std::string *kmers = new std::string[storSize];	// String of the unique kmer
		int *repeats = new int[storSize];		// Number of the unique kmer
		int offset = findOffset(k);

		int powFour[k];
		for (int i = 0; i < k; i++){
			powFour[i] = pow(4, i);
		}

		// Initialize the array to zero's
		for (int i = 0; i < storSize; i++){
			repeats[i] = 0;
		}

		// Generate list of all kmers present
		for (int i = 0; i < chainLen - k + 1; i++){

			// Find the index for the current kmer
			int ID = findIndex(dnaChain.substr(i, k), offset, powFour);
		
			// Update it's count
			repeats[ID]++;

			// If this is a new Kmer, add it's value to the chain.
			if (repeats[ID] == 1){
				kmers[ID] = dnaChain.substr(i, k);
			}
			
			// std::cout << dnaChain.substr(i, k) << std::endl;
		 	// std::cout << "\t" << ID << " - " << kmers[ID] << ": " << repeats[ID] << std::endl;
		}

		// Print our output
		for (int i = 0; i < storSize; i++) {
			if (repeats[i] >= threshold) {
				std::cout << kmers[i] << " " << repeats[i] << std::endl;
			}
		}

		// Clean up memory
		delete [] kmers;
		delete [] repeats;

	}
	// Is not feasible
	else
       	{
		std::cout << "error" << std::endl;
	}

	// Close the file
	myfile.close();

	// RUNTIME
	// auto stop = std::chrono::high_resolution_clock::now();
	// auto dur = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
	// std::cout << "Runtime (ms): " << dur.count() << std::endl;

}

int findIndex(const std::string& elem, const int offset, const int powersFour[]){
	int index = -offset;
	for (int i = 0; i < (int) elem.size(); i++) {
		index = index + findDNAVal(elem[i]) * powersFour[i];
	}
	return index;
}

int findOffset(int k){
	int offset = 0;
	for (int i = 0; i < k; i++){
		offset = offset + pow(4, i);
	}
	return offset;
}

double findDNAVal(char unit){
	switch (unit)
	{
		case 'A':
			return 1;
		case 'C':
			return 2;
		case 'G':
			return 3;
		case 'T':
			return 4;
	}
	return -1; // Error!
}
