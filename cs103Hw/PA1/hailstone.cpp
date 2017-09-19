/* Name: Jacob Pitts
Code description: hailstone.cpp runs through the 
hailstone sequence for a single integer. 
The integer will be modified through a series of 
steps ultimately reducing to 
1. At each step, the integer is printed to the output. 
When the integer reduces to 1, 
the amount of steps the program took to reach 1 is printed. 

*/


#include <iostream>
using namespace std;

int main() {
    int length = 0;
    int input = 0;
   
    cout << "Enter a number: ";
    cin >> input;
      do { //Using a while loop since we do not have a defined endpoint 
        if (input % 2 == 0 )
            {
                input = (input / 2);
                ++length; 
                cout << input << " " ;
            }
        else if ((input %2 != 0) && (input != 1))
            {
                input = (input * 3) + 1;
                ++length; 
                cout << input << " ";
            }
      }
        while (input > 1); // if the input is == 1, we're done! print the length
        cout << "\nLength: " << length << endl;
}
