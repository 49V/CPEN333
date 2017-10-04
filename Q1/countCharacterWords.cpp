#include <map>
#include <string>
#include <mutex>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

#include "countWords.h"

/**
* Checks if the line specifies the character's dialogue, returning the index of 
* the start of the dialogue. If the line specifies a new character is speaking, 
* then extracts the character's name.
*
* Assumptions : (doesn't have to be perfect)
* - A line that starts with exactly two spaces has "CHARACTER. <dialogue>"
* - A line that starts with exactly four spcaes contains the dialogue of 
*   previous character
*
* @param line Line to check
* @param character Extracted character name if new character, otherwise leaves 
*                  character unmodified
* @return index The index of the start of dialogue if a dialogue line, otherwise
*               -1
*/
int isDialogueLine(const std::string& line, std::string& character){
	
	// If it is a new character line
	if(line.length() >= 3 && line[0] == ' ' && line[1] == ' ' && line[2] != ' '){
		
		// Extract character name	
		int startIndex = 2;
		int endIndex = 3;
		
		// We want to keep going until we encounter a '.'
		while(endIndex <= line.length() && line[endIndex - 1] != '.'){
			
			++endIndex;
		
		}
	
		// If no name is found
		if(endIndex >= line.length()){
		
			return 0;
		
		}
	
		// Extract the character's name
		character = line.substr(startIndex, endIndex - startIndex - 1);
		return endIndex;
	
	}
	
	// If it is a previous character
	if(line.length() >= 5 && line[0] == ' ' && line[1] == ' ' && line[2] == ' '
	   && line[3] == ' ' && line[4] != ' '){
		   
		   // Continuation
		   return 4;
		   
	   }
	
	return 0;
}

/**
* Reads a file to count the number of words each actor speaks.
*
* @param fileName File to open
* @param mutex Mutex For protected access to the shared wordCounts map
* @param wordCounts A shared map from character -> word count
*/
void countCharacterWords(const std::string& fileName, std::mutex& mutex, 
                         std::map<std::string, int>& wordCounts){
							 
	//------------------------
	// IMPLEMENT THREAD SAFETY
	//------------------------
	
	// For storing each line read from the file
	std::string line; 
	std::ifstream file(fileName);
	
	//Read contents of file if open
	if(file.is_open()){
		
		// Empty character to start
		std::string character = "";

		//Read line by line
		while(std::getline(file, line)){
			
			int index = isDialogueLine(line, character);
			
			// If we have a character
			if(index > 0 && !character.empty()){
			
				int numberOfWords = countWords(line, index);
				
				// Add character if it doesn't exist, otherwise increment count
				
				//----------------
				//Add word count information to the mapp
				//----------------
			
			}

			// Reset character
			else{
				
				character = "";
				
			}
			
			file.close();
			
		}
		
	}
	
}

/**
* Comparator, that orders number of words in descending order, then 
* alphabetically by name
* @param pair1 First pair
* @param pair2 Second pair
* @return true If "pair1" should come before "pair2", false otherwise 
*/
bool compareWordCount(std::pair<std::string, int>& pair1, std::pair<std::string, int>& pair2){
	
	// Implement Logic
	
	return false;
}

/**
* Sorts character in descending order based on word count
*
* @param wordCounts A map of character -> wordCount
* @return sorted vector of {character, wordCount} pairs
*/
std::vector< std::pair<std::string, int> > sortCharactersByWordCount(
	const std::map<std::string, int>& wordCounts){
	
	// Creates our output vector and reserves memory
	std::vector< std::pair<std::string, int> > out;
	out.reserve(wordCounts.size());
	
	// Sort characters in descending order based upon the wordCount
	for(const auto& pair : wordCounts){
		out.push_back(pair);
	}
	
	std::sort(out.begin(), out.end(), compareWordCount);
	
	return out;
	
}

int main() {
	
	// map and mutex for thread safety
	std::mutex mutex;
	std::map<std::string,int> wordCounts;

	std::vector<std::string> fileNames = {
      "data/shakespeare_antony_cleopatra.txt",
      "data/shakespeare_hamlet.txt",
      "data/shakespeare_julius_caesar.txt",
      "data/shakespeare_king_lear.txt",
      "data/shakespeare_macbeth.txt",
      "data/shakespeare_merchant_of_venice.txt",
      "data/shakespeare_midsummer_nights_dream.txt",
      "data/shakespeare_much_ado.txt",
      "data/shakespeare_othello.txt",
      "data/shakespeare_romeo_and_juliet.txt",
	};

  //=============================================================
  // YOUR IMPLEMENTATION HERE TO COUNT WORDS IN MULTIPLE THREADS
  //=============================================================

	auto sortedWordCounts = sortCharactersByWordCount(wordCounts);

	// results
	for (const auto& entry : sortedWordCounts) {
		std::cout << entry.first << ", " << entry.second << std::endl;
	}

	std::cout << std::endl << "Press ENTER to continue..." << std::endl;
	std::cin.get();
	
	return 0;
}