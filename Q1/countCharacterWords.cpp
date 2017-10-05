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
 * Checks if the line specifies a character's dialogue, returning
 * the startIndex of the start of the dialogue.  If the
 * line specifies a new character is speaking, then extracts the
 * character's name.
 *
 * Assumptions: (doesn't have to be perfect)
 *     Line that starts with exactly two spaces has
 *       CHARACTER. <dialogue>
 *     Line that starts with exactly four spaces
 *       continues the dialogue of previous character
 *
 * @param line line to check
 * @param character extracted character name if new character,
 *        otherwise leaves character unmodified
 * @return startIndex of start of dialogue if a dialogue line,
 *      -1 if not a dialogue line
 */
int isDialogueLine(const std::string& line, std::string& character) {

  // new character
  if (line.length() >= 3 && line[0] == ' '
      && line[1] == ' ' && line[2] != ' ') {
    // extract character name

    int start_startIndex = 2;
    int end_startIndex = 3;
    while (end_startIndex <= line.length() && line[end_startIndex-1] != '.') {
      ++end_startIndex;
    }

    // no name found
    if (end_startIndex >= line.length()) {
      return 0;
    }

    // extract character's name
    character = line.substr(start_startIndex, end_startIndex-start_startIndex-1);
    return end_startIndex;
  }

  // previous character
  if (line.length() >= 5 && line[0] == ' '
      && line[1] == ' ' && line[2] == ' '
      && line[3] == ' ' && line[4] != ' ') {
    // continuation
    return 4;
  }

  return 0;
}

/**
 * Reads a file to count the number of words each actor speaks.
 *
 * @param filename file to open
 * @param mutex mutex for protected access to the shared wordCounts map
 * @param wordCounts a shared map from character -> word count
 */
void countCharacterWords(const std::string& filename,
                           std::mutex& mutex,
                           std::map<std::string,int>& wordCounts) {

  std::string line;  // for storing each line read from the file
  std::ifstream file (filename);
  
  // read contents of file if open
  if (file.is_open()) {
  
    std::string character = "";  // empty character to start

    // line by line
    while ( std::getline (file,line) ) {

      int startIndex = isDialogueLine(line, character);
      if (startIndex > 0 && !character.empty()) {

        int nwords = countWords(line, startIndex);
		
        // wordCounts is the only shared resource between threads. Need to protect it
		std::lock_guard<std::mutex> lock(mutex);
				
		// Adds a character if it doesn't exist, otherwise increments the characters word count
		auto exists = wordCounts.find(character);
		
		if(exists == wordCounts.end()){

					wordCounts.insert({character, nwords});
					
				}
				
		else{
			
					wordCounts[character] += nwords;
					
				}
				
        
      } 
	  
	  else {
        character = "";  // reset character
      }

    }
    file.close();  // close file
  }

}

/**
 * Comparator, orders by number decreasing, then by name
 * @param p1 first pair
 * @param p2 second pair
 * @return true if p1 should come before p2, false otherwise
 */
bool compareWordCount(std::pair<std::string,int>& pair1, std::pair<std::string,int>& pair2) {

  return (pair1.second > pair2.second) || ((pair1.first > pair2.first) && (pair1.second > pair2.second));
  
};

/**
 * Sorts characters in descending order by word count
 *
 * @param wordCounts a map of character -> word count
 * @return sorted vector of {character, word count} pairs
 */
std::vector<std::pair<std::string,int>> sortCharactersByWordCount(
    const std::map<std::string,int>& wordCounts) {

  std::vector<std::pair<std::string,int>> out;
  out.reserve(wordCounts.size());   // reserve memory for efficiency

  // sort characters by words descending
  for (const auto& pair : wordCounts) {
    out.push_back(pair);
  }
  std::sort(out.begin(), out.end(), compareWordCount);

  return out;
}

int main() {

  // map and mutex for thread safety
  std::mutex mutex;
  std::map<std::string,int> wordCounts;
  std::vector<std::thread> threads;
  
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

  // Create a thread for each file
  for(int i = 0; i < fileNames.size(); ++i){
	threads.push_back(std::thread(countCharacterWords, std::ref(fileNames[i]), std::ref(mutex), std::ref(wordCounts)));
  }
  
  // Wait for all threads to finish
  for(int i = 0; i < threads.size(); ++i){
	  threads[i].join();
  }
  
  auto sortedWordCounts = sortCharactersByWordCount(wordCounts);

  // results
  for (const auto& entry : sortedWordCounts) {
    std::cout << entry.first << ", " << entry.second << std::endl;
  }

  std::cout << std::endl << "Press ENTER to continue..." << std::endl;
  std::cin.get();

  return 0;
}
