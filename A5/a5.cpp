// File: a5.cpp
// Isaac
// Rezey
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

std::string comp(std::string prosName, int prosCount, std::string currName, int &highCount);

int main(int argc, char* argv[]) {

	// Correcting user's faulty inputs
	if (argc != 2){
		std::cout << "Incorrect inputs.  Use as ./a5 filename" << std::endl;
		return -1;
	}

	// Initialize dictionary / file reading
	std::map<std::string, int> dict;
	std::ifstream file(argv[1]);
	std::string textLine;

	// Populate the dictionary
	while (not file.eof()) {
		textLine = "";
		std::getline(file, textLine);

		// Decouple the key / value
		for (unsigned i = 0; i < textLine.size(); i++){
			// Find the space
			if (textLine[i] == ' '){
				// Cut them key and value around it
				std::string key = textLine.substr(0, i);
				int value = stoi(textLine.substr(i+1));
				dict[key] = value;
				break;
			}
		}
	}
	file.close();
	
	// Process inputs
	int lowerBound = 0;
	std::string allNames;
	std::vector<std::string> nameVec;
	getline(std::cin, allNames);

	for (unsigned i = 0; i < allNames.size(); i++){
		if (allNames[i] == ' '){
			nameVec.push_back(allNames.substr(lowerBound, i-lowerBound));
			i++;
			lowerBound = i;
		}
	}
	nameVec.push_back(allNames.substr(lowerBound));

	// Spell-checking process
	char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (auto it = nameVec.begin(); it != nameVec.end(); it++){
		// Check if name is in the dictionary
		auto exactMatch = dict.find(*it);
		if (exactMatch != dict.end()){
			std::cout << *it << " " << exactMatch->second << std::endl;
			exactMatch->second++;
		} else {
			// Check if name is off by one
			int highCount = 0;
			std::string currName = *it;
			std::string predName;
			
			// Deletion:
			for (unsigned i = 0; i < currName.size(); i++){
				currName.erase(i, 1);
				auto key = dict.find(currName);
				if (key != dict.end()){
					predName = comp(key->first, key->second, predName, highCount);
				}
				currName = *it;
			}

			// Replacement:
			for (unsigned i = 0; i < currName.size(); i++){
				for (int j = 0; j < 27; j++){
					currName[i] = alpha[j];
					auto key = dict.find(currName);
					if (key != dict.end()){
						predName = comp(key->first, key->second, predName, highCount);
					}
				}
				currName = *it;
			}

			// Addition:
			for (unsigned i = 0; i < currName.size()+1; i++){
				currName.insert(i, "A");
				for (int j = 0; j < 27; j++){
					currName[i] = alpha[j];
					auto key = dict.find(currName);
					if (key != dict.end()){
						predName = comp(key->first, key->second, predName, highCount);
					}
				}
				currName = *it;
			}

			if (highCount != 0){
				std::cout << predName << " " << highCount << std::endl;
			} else {
				// It's a unique, unknown element - add it in!
				std::cout << "-" << std::endl;
				dict[*it] = 1;
			}
		}
	}

	// Output final dictionary
	std::cout << "-----" << std::endl;
	for (auto it = dict.begin(); it != dict.end(); it++){
		std::cout << it->first << " " << it->second << std::endl;
	}

}

std::string comp(std::string prosName, int prosCount, std::string currName, int &highCount){
	if (prosCount > highCount){
		highCount = prosCount;
		return prosName;
	} else if (prosCount == highCount){
		if (std::lexicographical_compare(prosName.begin(), prosName.end(), currName.begin(), currName.end())){
			highCount = prosCount;
			return prosName;
		}
	}
	return currName;
}
