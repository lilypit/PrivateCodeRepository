//hw1q5.cpp 

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


void reverseSentence(std::string sentence, int charLen, std::string *reversedSentence);

int main (int argc, char* argv[]) {
	
	int charLen = 0;
	std::string reverseHold = "";
	std::string* reversedSentence = &reverseHold; // we cannot initialize this pointer as NULL since we're going to be adding to it.
	std::string charHold = ""; 
	std::string sentence = ""; 
	std::stringstream ss;

	std::ifstream readFile;
	readFile.open(argv[1]); //opens the file in the argument
    
    getline(readFile, charHold);
    getline(readFile, sentence); // get the sentence for getline to read

    ss << charHold; // need to parse the first line

    while (!ss.fail()) {
    	ss >> charLen;
    }

    readFile.close(); 
    
    reverseSentence(sentence, charLen, reversedSentence); 
}


void reverseSentence(std::string sentence, int charLen, std::string *reversedSentence) {

   if (charLen == 0) { 
    	std::cout << *reversedSentence << std::endl;
   }
   else { 
    	*reversedSentence = *reversedSentence + sentence[charLen - 1]; 
    	charLen = charLen - 1; 
    	reverseSentence(sentence, charLen, reversedSentence); 
  	 }


}
