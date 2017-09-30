#ifndef WORDCOUNT
#define WORDCOUNT

#include <string>

/**
* CPEN 333 Lab 3
* Author : Moshe Lawlor
*/

/**
* Counts the number of words, separated by spaces in a line.
* @param line String in which to count words 
* @param startIndex Starting index to search for wrods
* @return Number of words in the line
*/
int word_count(const std::string& line, int start_idx);


#endif