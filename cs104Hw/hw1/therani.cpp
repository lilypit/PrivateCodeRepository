#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }
  
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if (input.fail()) {
  	cerr << "Please insert a valid file." << endl;
  	return 1;
  }

  if (output.fail()) {
  	cerr << "Please insert a valid file." << endl;
  	return 1;
  }

  int experiments = 1;
  int *numsubjects = NULL;
  int *tempnumsubjects = NULL; 
  string **history = NULL;
  string **tempArray = NULL; 
  string line;
  string curr;
  int lineCounter = 0;
  int subjectsStart;
  int subjectsEnd;
  int experimentOrgin;
  int experimentEnd;
  bool fillHistory = false; 
  bool populatePool = false;
  bool prevExperiment = false; 
  int n;
  bool startCheck = true;
  //for each experiment, you will need to keep track of the number of subjects; and for each subject, of their history

  //loop to read The Rani's logbook.
  while(getline(input, curr)) {
    lineCounter++;
    line = curr;

    stringstream ss;
    ss << curr;
    ss >> curr;

    if (ss.fail()) {
    	cerr << "Please insert a valid file.";
    	continue;

    }
    if (curr == "START") {
      // Hint: This does not cover all errors yet.
      if (prevExperiment == true) {
           for (int i = 0; i < experiments; i++) {
            delete [] history[i];         
          }
            delete [] history;  // if the the history is not deleted yet, we have to remove it.

            delete[] numsubjects;
            return 0;
          }
      
      double dn;
      ss >> dn;

       if (ss.fail() ) {
        startCheck = false;
        output << "Error - incorrect command: " << line << endl;
        output << "Parameter should be an integer." << endl;
        continue;  
        }

      if (floor(dn) != dn) {
        startCheck = false;
        output << "Error - incorrect command: " << line << endl;
        output << "Parameter should be an integer." << endl;
        continue;  
      }

      n = (int)dn;


      if (ss.fail()) {
          output << "Error - incorrect command: " << line << endl;
          output << "Parameter should be an integer" << endl;
          continue;
      }
      else if (n < 0) {
        output << "Error - incorrect command: " << line << endl;
        output << "Number out of range" << endl;
        continue;
      }
      
      else {
    
        history = new string*[1]; //allocate enough for 1 experiment ((subjectpool))
        history[0] = new string[n]; //within that experiment, allocate for enough individual 
        numsubjects = new int[1]; //we plan to keep track of n subjects in our array. 
        numsubjects[0] = n;

        for (int i = 0; i < n; i++) {
          history[0][i] = "";
        }

        prevExperiment = true;

        }
      }

    else if (curr == "ADD") {

          if (prevExperiment == false) {
            output << "Error - incorrect command: " << lineCounter << endl; 
            output << "Error - no subjects yet"<< endl;
            continue; 
          }
          
          experiments++;

          tempnumsubjects = new int[experiments]; //creates a temp array of size 2
          
           for (int i = 0; i < experiments-1; i ++) { // from 0 to 1, put the numsubject into numsubject
              tempnumsubjects[i] = numsubjects[i];
            }
          
          tempnumsubjects[experiments-1] = 0; 

          delete[] numsubjects;


          numsubjects = new int[experiments];

         for (int i = 0; i < experiments; i ++) { //from 0 to 2 (3 iterat)
            numsubjects[i] = tempnumsubjects[i] ;
          }

          delete[] tempnumsubjects;
        
         

          tempArray = new string*[experiments]; //the temparray is now one bigger than the history array and can hold 2 elements (implying one ADD was called)

          for (int i = 0; i < experiments; i ++) {
            tempArray[i] = new string[n]; // should have the same elements as the previous. 
          }



          for (int i = 0; i < experiments; i ++) {
            for (int j = 0; j < numsubjects[i]; j ++ ) {
                        if (fillHistory == false ) {
                              history[i][j] = "";
                         }
                         else { 
                           tempArray[i][j] = history[i][j] + "";
                         }
            }
          }
        
           for (int i = 0; i < experiments-1; i++) {
            delete [] history[i];         
          }
            delete [] history;  // if the the history is not  yet, we have to remove it.

          history = new string*[experiments]; //the temparray is now one bigger than the history array and can hold 2 elements (implying one ADD was called)

          for (int i = 0; i < experiments; i ++) {
            history[i] = new string[n]; // should have the same elements as the previous. 
          }

           for (int i = 0; i < experiments; i++) {
            delete [] tempArray[i];         
          }
            delete [] tempArray;  // if the the history is not  yet, we have to remove it.



     }

    else if (curr == "MOVE") {
        int argCount = 0 ;


      for (int i = 0; i < 4; i++) { 
      if (!(ss.fail())) {
        argCount++;
       }
      }
  
          if (prevExperiment == false) {
            output << "Error - incorrect command: " << lineCounter << endl; 
            output << "Error - no subjects yet"<< endl;
            continue; 
          }


      double dexperimentOrgin, dexperimentEnd, dsubjectsStart, dsubjectsEnd; 

      ss >> dexperimentOrgin >> dexperimentEnd >> dsubjectsStart >> dsubjectsEnd;

       if (ss.fail() ) {
        output << "Parameter should be an integer." << endl;
        continue;  
        }

      if (floor(dexperimentOrgin) != dexperimentOrgin) {
        output << "Parameter should be an integer." << endl;
        continue;  
      }


       if (floor(dexperimentEnd) != dexperimentEnd) {
        output << "Parameter should be an integer.";;
        continue;

      }

       if (floor(dsubjectsStart) != dsubjectsStart) {
        output << "Parameter should be an integer.";
        continue;
      }

       if (floor(dsubjectsEnd) != dsubjectsEnd) {
        output << "Parameter should be an integer." << endl;
        continue;

      }

      experimentOrgin = (int)dexperimentOrgin; //x
      experimentEnd = (int)dexperimentEnd;   // y
      subjectsStart = (int)dsubjectsStart; //n 
      subjectsEnd = (int)dsubjectsEnd; //m



          if (subjectsStart > subjectsEnd) {
                output << "Error - incorrect command: " << lineCounter << endl; 
                output << "Error - Invalid range of subjects to move."<< endl;
          }


            if (experimentOrgin < 0 || experimentEnd < 0 || subjectsStart < 0 || subjectsEnd  < 0 || subjectsEnd > n || experimentEnd > experiments) {
                output << "Error - incorrect command: " << lineCounter << endl; 
                output << "Error - number out of range"<< endl;
                continue; 

            }
  
              ss >> experimentOrgin >> experimentEnd >> subjectsStart >> subjectsEnd;



             if (experimentOrgin == 0  && populatePool == false)  {
                 populatePool = true;
                 for (int i = 0 ; i < experiments; i ++) {
                  for (int j = 0 ; j < n; j++) {
                    history[i][j] = "";
                   }
                 }
              }
              	//i couldn't really figure out how to do a temp array, so instead, i did it all in this function block.

                for (int i = subjectsStart; i <= subjectsEnd; i++) { // we take the values from subject start to subject end and iterate through. we then move these to the appopriate origin population.
                  history[experimentEnd][numsubjects[experimentEnd]] = history[experimentOrgin][i];
                  numsubjects[experimentOrgin] = numsubjects[experimentOrgin] - 1; //after moving the experiment, we have to decrement in the origin.
                  history[experimentEnd][numsubjects[experimentEnd]] = history[experimentEnd][numsubjects[experimentEnd]] +  char ('0' + experimentEnd) + " "; //char conversion necessary for compiling.
                  numsubjects[experimentEnd] = numsubjects[experimentEnd] + 1;          //after adding the experiment, we have to increment in the origin.
                  }   

                 //should be the end of the move function
}
        
      
  
    else if (curr == "QUERY") {
          int argCount = 0; 

          if (prevExperiment == false) {
            output << "Error - incorrect command: " << lineCounter << endl; 
            output << "Error - no subjects yet"<< endl;

            continue; 
          }


      int queryExperiment, querySubject;

      double dqueryExperiment, dquerySubject; 

    
      ss >> dqueryExperiment >> dquerySubject;
        if (ss.fail() ) {
        output << "Parameter should be an integer." << endl;
        continue;  
        }
    
      if (floor(dqueryExperiment) != dqueryExperiment) {
        output << "Parameter should be an integer." << endl;
        continue;  
      }

       if (floor(dquerySubject) != dquerySubject) {
        output << "Parameter should be an integer." << endl;
        continue;

      }

      queryExperiment = (int)dqueryExperiment;
      querySubject = (int)dquerySubject;


      
      for (int i = 0; i < 2; i++) { 
      if (!(ss.fail())) {
        argCount++;     
      }

      }

      if (argCount != 2) {


                output << "Error - incorrect command: " << lineCounter << endl; 
                output << "Error - number out of range"<< endl;
                output << "Too few parameters"<< endl;

                continue;
      }


        if (queryExperiment > experiments || querySubject >= numsubjects[queryExperiment]) {

                
            
                continue;
        }

      ss >> queryExperiment >> querySubject;



      output << history[queryExperiment][querySubject] << endl;

    }
    else {
        output<< "Error - incorrect command: " << lineCounter << endl;
        output<< "Command does not exist. " << lineCounter << endl; 



        continue; 
        }

      
    }
  
  if (startCheck == true) { 
           for (int i = 0; i < experiments; i++) {
            delete [] history[i];         
          }
            delete [] history;  // if the the history is not yet, we have to remove it.

            delete[] numsubjects;
            return 0;
  
}

  return 0;
}