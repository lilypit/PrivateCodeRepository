/*********************************************************
 * File name : tp.cpp
 * Author    : Jacob Pitts
 * Date      : 2/10/2017
 * Purpose   : Simulates the toilet-paper problem
 * Notes     : 

 tp.cpp performs the toilet-paper simulation outlined in the 
 prompt by calling single_sim() an x amount of times based on 
 user input. Each simulation, once completed, will return
 the amount of toilet paper on the non-empty roll. This 
 returned value, when combined with others, is averaged - 
 producing our desired results. 
 *********************************************************/

#include <iostream>   
#include <cstdlib>    
#include <stdlib.h> 
#include <time.h>   
#include <iomanip> 

using namespace std;

double rand_uniform();

int single_sim(int N, double p);

int main(int argc, char *argv[]) {
  
srand(time(0)); 
int N;                
double p;             
int sims;             
double average;
int result;
 
cin >> N;
cin >> p;
cin >> sims;

for (int i=0; i < sims; i++) { //for loop calls single_sim based on user input
    result = single_sim(N,p); 
    average = (average + result);
}
    average = (average)/sims; //after results are added, divide by # sims.
    cout << "Average: " << setprecision(4) << average << endl; 
    return 0;
}

int single_sim(int N, double p) {
    
int roll1 = N;
int roll2 = N;
double chanceCheck;
    
while (roll1 !=0 && roll2 != 0 ) { //if roll1 or roll2 are empty, this will fail.
    if (roll1 != roll2) { //if roll 1 is not equal to roll2, run & exec. checks
        chanceCheck = rand_uniform();  
        if ((chanceCheck <= p) && (roll1 > roll2)) { 
            roll1 = roll1 - 1;
        }
        else if ((chanceCheck <= p ) && (roll2 > roll1)) {
            roll2 = roll2 - 1;
        }
        else if  ((chanceCheck > p) && (roll1 < roll2)) {
            roll1 = roll1 - 1; 
        }
        else if  ((chanceCheck > p) && (roll1 > roll2)) {
            roll2 = roll2 - 1;
        }
    }
    else { //if roll1 is equal to roll2, take from roll1 (closer roll)
        roll1 = roll1 - 1;
    }
}

//after while loop, return nonempty roll.

if (roll1 == 0 ) {  
    return roll2;
}
else if (roll2 == 0) { 
    return roll1;
}
    else return 0; 
}

double rand_uniform()
{
 return (rand()/(double)RAND_MAX);
}