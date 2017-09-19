//g++ -g -std=c++11 -Wall _LLDeque.cpp -o hw3q5
//valgrind --tool=memcheck --leak-check=yes --suppressions=/home/student/gcc.supp ./_LLDeque

#include <string>
#include "_LLDeque.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char*argv[]) {
	LLDeque List1;
	LLDeque List2;
	int counter = 0; 

	ifstream myFile;
	myFile.open(argv[1]);
	string line;
	while (getline(myFile, line)) {
		stringstream ss(line);
		int number; 
		char direction;
		ss >> number >> direction;
			if (number == 1) {
				if (List1.getfront() == '\0') {
					counter++;
					List1.pushback(direction);
					if (List1.getfront() == List2.getfront()) {
						List1.popfront();
						List2.popfront();
						counter = counter-2;
					}
				} 
				else if ((List1.getback() == 'N' && direction == 'S') || (List1.getback() == 'S' && direction == 'N') || (List1.getback() == 'E' && direction == 'W') || (List1.getback() == 'W' && direction == 'E')) {
					counter--;
					List1.popback();
				}
				else {
					List1.pushback(direction);
					counter++;
				}
			} 
			else {
				if (List2.getback() == '\0') {
					counter++;
					List2.pushback(direction);
					if (List2.getfront() == List1.getfront()) {
						List2.popfront();
						List1.popfront();
						counter = counter-2;
					}
				} 
				else if ((List2.getback() == 'N' && direction == 'S') || (List2.getback() == 'S' && direction == 'N') || (List2.getback() == 'E' && direction == 'W') || (List2.getback() == 'W' && direction == 'E')) {
					counter--;
					List2.popback();
				}
				else {
					List2.pushback(direction);
					counter++;
				} 
			}
	
	}

cout << counter << endl;
}
