/**
* CPEN 333 Lab 3
* Author : Moshe Lawlor
*/

#ifndef COUNTCPP
#define COUNTCPP

int countWords(const std::string& line, int startIndex){
	
	int letterCount = 0;
	int wordCount = 0;
	
	for(int i = startIndex; i < line.size(); ++i ){

		if(line[i] != ' '){
			++letterCount;
		}
		
		else if(line[i] == ' ' && letterCount > 0){
			++wordCount;
			letterCount = 0;
		}
		
		else if(line[i] == ' ' && letterCount == 0){
			// Do Nothing
		}
		
		// This is used to test if my logic is correct. This statement should 
		// never be entered
		else{
			std::cout << "ERROR: Your logic is incorrect" << std::endl;
		}
	
	}
	
	// In the case that our string isn't ended by a space
	if(letterCount > 0){
		++wordCount;
	}

	
	return wordCount;
}

/*
int main(){
	
	std::string testString = "";
	int startIndex = 0;
	
	int wordCount = countWords(testString, startIndex);
	
	std::cout << "Word Count: " << wordCount << std::endl;
	
	return 0;
}
*/

#endif