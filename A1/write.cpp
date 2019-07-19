// Write a new chain of DNA

#include <fstream>
#include <iostream>

int main (int argc, char* argv[]){
	std::ofstream myfile ("foo.txt");
	
	char units [4] = {'A', 'C', 'G', 'T'};
	int length = atoi(argv[1]);
	// Randomly fill with desired number of DNA units
	for (int i = 0; i < length; i++) {
		myfile << units[rand() % 4]; 
	}

	// Close file when finished
	myfile.close();
	std::cout << "File written!" << std::endl;
	return 0;
}
