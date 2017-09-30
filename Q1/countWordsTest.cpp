#include "countWords.cpp"
#include "countWords.h"
#include <exception>
#include <iostream>

/**
* CPEN 333 Lab 3
* Author : Moshe Lawlor
*/


/**
* This class is created for the purpose to throw special exceptions for our 
* different unit test failures.
*/
class UnitTestException : public std::exception{
	std::string line;
	int expected, result, startIndex; 
	
	public:
	
	/**
	* UnitTestException Constructor
	* Puts together our unit test based upon our test cases, results, and 
	* expected results.
	* @param line Line in which to search for words
	* @param startIndex Starting index in line to search for words
	* @param result Number of words in the line
	* @param expected Expected answer
	*/
	UnitTestException(const std::string& line, int startIndex, int result,
					  int expected){
	
		this->line = line;
		this->startIndex = startIndex;
		this->result = result;
		this->expected = expected;
		
	}
	
	/**
	* what() method
	* Returns an error message with regards to the exception thrown
	*/
	const char* what(){
		
		return "Unit test failed";
		
	}

	/**
	* info() method
	* Creates a string that contains all the test parameters and results
	*/
	std::string info(){
		
		std::string out;
		out.append("line: ");
		out.append(line);
		out.append(", startIndex: ");
		out.append(std::to_string(startIndex));
		out.append(", result: ");
		out.append(std::to_string(result));
		out.append(", expected: ");
		out.append(std::to_string(expected));
		
		return out;
	}
	
};

/**
* countWordsTester() method
* This method tests word count for the given line and starting index
* @param line Line in which to search for words
* @param startIndex Starting index in line to search for words
* @param expected Expected answer
* @throws UnitTestException If the test fails
*/
void countWordsTester(const std::string& line, int startIndex, int expected){
	
	int result = countWords(line, startIndex);
	
	// If not what we expect, throw an error
	if(result != expected){
		throw UnitTestException(line, startIndex, result, expected);
	}
	
}

int main(){

	// Test cases for varying our strings
	std::string test1 = "Echoes of past events nudge the tiller on my present course"; 
	std::string test2 = "Echoes of past events nudge the tiller on my present course ";
	std::string test3 = " Echoes of past events nudge the tiller on my present course";
	std::string test4 = "";
	std::string test5 = "  "; 
	std::string test6 = "Beans";
	
	int startIndex = 0;
	
	int expected1 = 11;
	int expected2 = 11;
	int expected3 = 11;
	int expected4 = 0;
	int expected5 = 0;
	int expected6 = 1;
	
	// Test cases for varying our indices
	std::string test7 = " six five four three two one ";
	
	int testIndex1 = 0;
	int testIndex2 = 4;
	int testIndex3 = 9;
	int testIndex4 = 14;
	int testIndex5 = 20;
	int testIndex6 = 24;
	int testIndex7 = 28;

	int expectedIndex1 = 6;
	int expectedIndex2 = 5;
	int expectedIndex3 = 4;
	int expectedIndex4 = 3;
	int expectedIndex5 = 2;
	int expectedIndex6 = 1;
	int expectedIndex7 = 0;
	
	try{
		// Testing Cases where we vary the string
		countWordsTester(test1, startIndex, expected1);
		countWordsTester(test2, startIndex, expected2);
		countWordsTester(test3, startIndex, expected3);
		countWordsTester(test4, startIndex, expected4);
		countWordsTester(test5, startIndex, expected5);
		countWordsTester(test6, startIndex, expected6);
		
		// Testing cases where we vary the indices
		countWordsTester(test7, testIndex1, expectedIndex1);
		countWordsTester(test7, testIndex2, expectedIndex2);
		countWordsTester(test7, testIndex3, expectedIndex3);
		countWordsTester(test7, testIndex4, expectedIndex4);
		countWordsTester(test7, testIndex5, expectedIndex5);
		countWordsTester(test7, testIndex6, expectedIndex6);
		countWordsTester(test7, testIndex7, expectedIndex7);
		
	}catch(UnitTestException &ute){
		std::cout << ute.info() << std::endl;
	}
	
	std::cout << "Finished" << std::endl;
}