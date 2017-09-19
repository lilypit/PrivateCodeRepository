/*

Author: Jacob Pitts

Short description of this file: label.cpp takes an image 
as input and effectively colors them in based on segments. These
segments are calculated using a BFS-based algorithm. BFS uses 
queue.cpp in  


*/



#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "bmplib.h" 
#include "queue.h"
using namespace std;

void usage() { 
    cerr << "usage: ./label <options>" << endl;
    cerr <<"Examples" << endl;
    cerr << "./label test_queue" << endl;
    cerr << "./label gray <input file> <outputfile>" << endl;
    cerr << "./label binary <inputfile> <outputfile>" << endl;
    cerr << "./label segment <inputfile> <outputfile>" << endl;
}

//function prototypes
void test_queue();
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width);
void gray2binary(unsigned char **in,unsigned char **out,int height,int width);
int component_labeling(unsigned char **binary_image,
int **labeled_image,int height,int width);
void label2RGB(int  **labeled_image, unsigned char 
***rgb_image,int num_segment,int height,int width);
void clean(unsigned char ***input,unsigned char **gray,
    unsigned char **binary, int **labeled_image,int height , int width);

// main function, you do not need to make any changes to this function 
int main(int argc,char **argv) {

    srand( time(0) );
    if(argc < 2 )  {
        usage();
        return -1;
    }        
    unsigned char ***input=0;
    unsigned char **gray=0;
    unsigned char **binary=0;
    int **labeled_image=0;
    if( strcmp("test_queue",argv[1]) == 0 ) { 
        test_queue();
    } 
    else if(strcmp("gray",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for gray" << endl;
            return -1;
        }
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            return -1;
        }            
        gray = new unsigned char*[height];
        for(int i=0;i<height;i++) 
            gray[i] = new unsigned char[width];
        rgb2gray(input,gray,height,width);
        if(writeGSBMP(argv[3],gray,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        clean(input,gray,binary,labeled_image,height,width);

    }
    else if(strcmp("binary",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for binary" << endl;
            return -1;
        }            
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            

        gray = new unsigned char*[height];
        for(int i=0;i<height;i++) 
            gray[i] = new unsigned char[width];
        rgb2gray(input,gray,height,width);

        binary = new unsigned char*[height];
        for(int i=0;i<height;i++)
            binary[i] = new unsigned char[width];

        gray2binary(gray,binary,height,width);
        if(writeBinary(argv[3],binary,height,width) != 0) { 
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        clean(input,gray,binary,labeled_image,height,width);
     
    }
    else if(strcmp("segment",argv[1]) == 0 ) {
        if(argc <4 ) {
            cerr << "not enough arguemnt for segment" << endl;
            return -1;
        } 
        int height,width;
        input = readRGBBMP(argv[2],&height,&width);
        if(input == 0)
        {
            cerr << "unable to open " << argv[2] << " for input." << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }            

        gray = new unsigned char*[height];
        for(int i=0;i<height;i++) 
            gray[i] = new unsigned char[width];
        rgb2gray(input,gray,height,width);

        binary = new unsigned char*[height];
        for(int i=0;i<height;i++)
            binary[i] = new unsigned char[height];

        gray2binary(gray,binary,height,width);


        labeled_image = new int*[height];
        for(int i=0;i<height;i++) labeled_image[i] = new int[width];
        int segments= component_labeling(binary, labeled_image,height,width); 

        for(int i=0;i<height;i++) 
            for(int j=0;j<width;j++) 
                for(int k=0;k<RGB;k++) 
                    input[i][j][k] = 0;
        label2RGB(labeled_image, input ,segments, height,width);
        if(writeRGBBMP(argv[3],input,height,width) != 0) {
            cerr << "error writing file " << argv[3] << endl;
            clean(input,gray,binary,labeled_image,height,width);
            return -1;
        }
        clean(input,gray,binary,labeled_image,height,width);

    }

   return 0;
}

//This function is used to test your queue implementation. 
//You do not need to change it,
//though doing so might be useful/helpful

void test_queue() { 
    // create some locations;
    Location three_one, two_two;
    three_one.row = 3; three_one.col = 1;
    two_two.row = 2; two_two.col = 2;

    //create an Queue with max capacity 5
    Queue q(5);

    cout << boolalpha;
    cout << q.is_empty() << endl;           // true
    q.push(three_one);
    cout << q.is_empty() << endl;           // false
    q.push(two_two);

    Location loc = q.pop();
    cout << loc.row << " " << loc.col << endl; // 3 1
    loc = q.pop();
    cout << loc.row << " " << loc.col << endl; // 2 2
    cout << q.is_empty() << endl;           // true
}

//Loop over the 'in' image array and calculate 
//the single 'out' pixel value using the formula
// GS = 0.2989 * R + 0.5870 * G + 0.1140 * B 
void rgb2gray(unsigned char ***in,unsigned char **out,int height,int width) {
      cout << "running";
     for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j ++) {
            out[i][j] = (char)((0.2989 * in[i][j][0]) + 
            (0.5879 * in[i][j][1]) + (0.1140 * in[i][j][2]));
        }
     }
}

//Loop over the 'in' gray scale array and create a binary (0,1) valued image 'out'
//Set the 'out' pixel to 1 if 'in' is above the threshold, else 0
void gray2binary(unsigned char **in,
unsigned char **out,int height,int width) {   
     
   //  int THRESHOLD = 250; 
     
     cout << "running2";
     for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j ++) {
            if (in[i][j] > THRESHOLD) { //35 as const threshhold
         out[i][j] = 1; 
         }
         else {
         out[i][j] = 0;
         } 
        }
     }
    
    
}

//This is the function that does the work of looping over the 
//binary image and doing the connected component labeling
//See the .pdf for more details
int component_labeling(unsigned char 
**binary_image,int **label,int height,int width) {
   int current_label = 1;
   Queue que(height * width); //Creating the queue to use in BFS. 

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((binary_image[i][j] == 1) && (label[i][j] == 0)) {
                label[i][j] = current_label;
                
                Location newLocation;
                newLocation.row = i;
                newLocation.col = j;

                que.push(newLocation); //push the location onto the queue. 

                    while (!que.is_empty()) {
                        Location loc = que.pop();
                        //check left, right, up, down.
                        if (binary_image[loc.row + 1][loc.col] == 1 && 
                            label[loc.row + 1][loc.col] == 0 && (loc.row < SIZE)) {
                           
                            label[loc.row + 1][loc.col] = current_label;
                            newLocation.row = loc.row +1;
                            newLocation.col = loc.col;
                            que.push(newLocation);
                            //if it fufills conditions, push it in queue. 
                        }
                        
                        if (binary_image[loc.row - 1][loc.col] == 1 && 
                            label[loc.row - 1][loc.col] == 0 && (loc.row > 0)) {
                           
                            label[loc.row - 1][loc.col] = current_label;
                            newLocation.row = loc.row - 1;
                            newLocation.col = loc.col;
                            que.push(newLocation);
                        }

                        if (binary_image[loc.row][loc.col +1] == 1 && 
                            label[loc.row][loc.col+1] == 0 && (loc.col < SIZE))  {
                            
                            label[loc.row][loc.col+1] = current_label;
                            newLocation.row = loc.row;
                            newLocation.col = loc.col+1;
                            que.push(newLocation);
                        }

                        if (binary_image[loc.row][loc.col -1] == 1 && 
                            label[loc.row][loc.col-1] == 0 && (loc.col > 0)) {
                            
                            label[loc.row][loc.col-1] = current_label;
                            newLocation.row = loc.row;
                            newLocation.col = loc.col-1;
                            que.push(newLocation);
                        }
                
                    }
            
            }
            current_label++;
        }
    }
    return current_label;
}    

//First make num_segments number of 
//random colors to use for coloring the labeled parts of the image.
//Then loop over the labeled image using 
//the label to index into your random colors array.
//Set the rgb_pixel to the corresponding color, 
//or set to black if the pixel was unlabeled.

#ifndef AUTOTEST
void label2RGB(int  **labeled_image, 
unsigned char ***rgb_image,int num_segments,int height,int width)
{
   //seperate arrays are dynamically allocated 
   int* ArrayR = new int[num_segments];
   int* ArrayG = new int[num_segments];
   int* ArrayB = new int[num_segments];
   for (int i = 0; i < num_segments; i++)
   {
           ArrayR[i] = rand() % SIZE;
   }

   for (int i = 0; i < num_segments; i++)
   {
           ArrayG[i] = rand() % SIZE;
   }

   for (int i = 0; i < num_segments; i++)
   {
           ArrayB[i] = rand() % SIZE;
   }

   for (int i = 0; i < height; i++){
           for (int j = 0; j < width; j++) {
               for (int k = 0; k < RGB; k++) {
                   if (labeled_image[i][j] == 0) {
                       rgb_image[i][j][k] = 0;
                   }
                   else if (labeled_image > 0 && k == 0) {
                       rgb_image[i][j][k] = (char)ArrayR[labeled_image[i][j]-1];
                   }

                   else if (labeled_image > 0 && k == 1) {
                       rgb_image[i][j][k] = (char)ArrayG[labeled_image[i][j]-1];
                   }

                   else if (labeled_image > 0 && k == 2) {
                       rgb_image[i][j][k] = (char)ArrayB[labeled_image[i][j]-1];
                   }
               }
           }
   }
   //have to clean up the dynamic allocations. 
   delete[] ArrayR;
   delete[] ArrayG;
   delete[] ArrayB;

}


    
#endif

//fill out this function to delete all of the dynamic arrays created
void clean(unsigned char ***input,unsigned char **gray,
unsigned char **binary, int **labeled_image,int height , int width) {
    if(input ) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j ++) { 
                delete[] input[i][j];
            }
            delete[] input[i];
        }  
        delete[] input; 
        } 
   
    if(gray) {
        for (int i = 0; i < height; i++) {
            delete[] gray[i];
        }
        delete [] gray;
    } 
    
    if(binary) {
        for (int i = 0; i < height; i++) {
            delete[] binary[i];
        }
        delete [] binary;
    }
     
    if(labeled_image) {
        for (int i = 0; i < height; i++) {
            delete[] labeled_image[i];
        }
        delete [] labeled_image;
    }
}