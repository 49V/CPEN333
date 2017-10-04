#ifndef COUNTWORDS
#define COUNTWORDS

#include <iostream>
#include <string>
#include "countWords.cpp"

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
int countWords(const std::string& line, int startIndex);


#endif