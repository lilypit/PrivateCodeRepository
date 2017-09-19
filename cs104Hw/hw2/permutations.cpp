#include <iostream>
#include <string>
using std::string;
using std::endl;
using std::cout;



void helperPerm(string input, string remainingCharacters) {
	string tempInput;
	string tempremainingCharacters;
 
	if (input.compare("") == 0) { //base case, if we found that there is nothing in the input, we're done. 
		cout << remainingCharacters << endl; //there's nothing there, print out the permutation
		return;
	}

	for (unsigned int i = 0; i < input.length(); i++) {  //iterate through the input until it's length is found.
		tempremainingCharacters = remainingCharacters; //create temperorary variables for each one.
		tempInput = input; 
		tempremainingCharacters = tempremainingCharacters + tempInput[i]; //the temp variable shoould equal that + the input
		tempInput.erase(i,1);
		helperPerm(tempInput, tempremainingCharacters);
	}
}

void permutations(string input) {
	string charHolder = "";
	helperPerm(input, charHolder);
}


