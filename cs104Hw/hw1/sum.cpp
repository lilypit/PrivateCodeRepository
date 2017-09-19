#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

int helper (int input, int len)
{
	//The entire number has been consumed.
	if (len == 0) return input;

	//Obtain the sum of all subsequent digits.
	int x = helper(input/10, len-1);

	//make your changes only below this line.  You may not use any loops.
	return x + input % 10; 
}

//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an integer." << endl;
    return 1;
  }
  int x = atoi(argv[1]);
  cout << helper(x, strlen(argv[1])) << endl;
  return 0;
}