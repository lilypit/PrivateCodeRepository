/* Name: Jacob Pitts
The following program is a modification of hailstone.cpp. 
This program iterates through a range of numbers, running the hailstone 
sequence on each individual integer. After each number in the range has gone 
through the hailstone sequence, this code outputsthe integer that took the most 
amount of steps to complete the hailstone sequence, the integer that 
took the least amount of steps 
to complete the sequence, and the specific amount of steps for each.

*/


#include <iostream>
#include <climits>
using namespace std;

int main() {

    int length = 0;
    int min = 0;
    int max = 0;
    int input = 0;
    int step = 0;
    int checkMaxLength = 0; 
    int checkMinLength = INT_MAX; // Value set at INT_MAX to pass check at line 47. 
    int maxNumber = 0;
    int minNumber = 0;   
    int savedInput = 0;

    cout << "Enter a range to search: ";
    cin >> min;
    cin >> max;
    if (min > max) {  // Checks to make sure that the range is not invalid. 
        cout << "Invalid range";
    } 
    else { //Else loop iterates through each input. Hailstone sequence for each.
      for (int i = min;  (i <= max); i++) { 
            length = 0;
            input = (min + step);
            savedInput = input; //"input" changes, store initial.  
            step++;
      do {  //Using a while loop since we do not have a defined endpoint
        if (input % 2 == 0 )
            {
                input = (input / 2);
                ++length; 
            
            }
        else if ((input %2 != 0) && (input != 1))
            {
                input = (input * 3) + 1;
                ++length; 
            }
      }
        while (input > 1); // If the input is = 1, we're done!     
            if (length > checkMaxLength) {
                checkMaxLength = length;
                maxNumber = savedInput;
            }
            if (length < checkMinLength) {
                checkMinLength = length;
                minNumber = savedInput;
            }          
        }
    cout << "Minimum Length: " << checkMinLength << endl;
    cout << "Achieved by " << minNumber << endl;
    cout << "Maximum Length: " << checkMaxLength << endl;
    cout << "Achieved by " << maxNumber << endl;
    }
}