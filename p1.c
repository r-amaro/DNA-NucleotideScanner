/**
 Steps to Target File and Run Program through Command Line:
 
 1. cc p1.c
 2. ./a.out "file-name.txt"
 
 ------------------------------------------------------------------
 Memory allocated to save 30 positions for each unique word.
 
 Future plans:
  - Dynamically set memory allocated for specific word addresses
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WORD_SIZE 11 // to account for null character when strncat() is used
FILE *fp;
int indexing(char word[]);
char *unHash(int dh);
int *final[1048576];

int main( int argc, char *argv[] )  {
    
    //  Command Line operations for arguments
   if( argc == 2 ) {
       
       char l;//l for letter
       char word[WORD_SIZE]; //word transport array
       int w = 0; //word counter
       int beg; //beginning of word
       //opens file to read
       fp = fopen(argv[1], "r");

       // counts through the text file.
       for (char l = getc(fp); l != EOF; l = getc(fp)) {
           if (w < 10) {
               if (l == 'A' || l == 'a') {//A is identified
                   strncat(word, &l, 1);//Appending char string with value of l = A
                   w = w+1; //add to word counter
                   
                   if (w==1) {//Saves the location of the 1st letter
                       beg = ftell(fp);
                   }
               }
               else if (l == 'C' || l == 'c') {//C is identified
                   strncat(word, &l, 1);//Appending char string with value of l = C
                   w = w+1; //add to word counter
                   
                   if (w==1) {//Saves the location of the 1st letter
                       beg = ftell(fp);
                   }
               }
               else if (l == 'G' || l == 'g') {//G is identified
                   strncat(word, &l, 1);//Appending char string with value of l = G
                   w = w+1; //add to word counter
                   
                   if (w==1) {//Saves the location of the 1st letter
                       beg = ftell(fp);
                   }
               }
               else if (l == 'T' || l == 't') {//T is identified
                   strncat(word, &l, 1);//Appending char string with value of l = T
                   w = w+1; //add to word counter
                   
                   if (w==1) {//Saves the location of the 1st letter
                       beg = ftell(fp);
                   }
               }
               else{
                   //not a valid letter so therefore not a complete word
                   //resets counter and word array
                   w = 0;
                   beg = 0; // clears first letter of word
                   memset(word,0,sizeof word);//resets word array
               }
           }
           else{//w >= 10
               //The word is complete and ready for transport to the final array
               //move word to be indexed
               int index = indexing(word);
               
               //Uses index as location of the word's pointers in the final array
               if(final[index] == NULL){  //Hashes The char array to an integer
                   int *temp;
                   
                   temp = (int *) calloc(30, sizeof(int));
                   
                   temp[0] = beg -1;
               
                   final[index] = temp;
               }
               else
               {
                   int end = 0;
                   for (int z = 0; z< 30; z++) {
                       if (final[index][z] == 0) {
                           end = z;
                           z = 30;
                       }
                   }
                   
                   final[index][end] = beg -1; // adds new address to the nearest empty space of final[index]
               }
               
               w = 0;
               memset(word,0,sizeof word);//resets word array
               fseek( fp, -10, SEEK_CUR);//sets current position after the 1st letter
               beg = 0; // clears first letter of word
           }
       }
   }
    
   else {
      printf("Invalid argument input.\n");
   }
    
    //Undoes the hashing
    for (int dh = 0; dh < 1048575; dh++)
        {
            //int max = 0;
            
            if (final[dh] != NULL) //word is present in the file
            {
                printf("%s:     ", unHash(dh));

                int z = 0;
                while (final[dh][z] != 0)
                {
                    printf("%d ", final[dh][z]);
                    z = z+1;
                }
                printf("\n");
            }
        }
    
    
    fclose (fp);//closes file
    return 0;
}



//Function to hash the value of each word
int indexing(char word[]) {
    
    long result = 0;
    //result = (A*4^10)+(C*4^9)(G*4^8)(T*4^7)...
        
        for (size_t i = 0; i < 10; i++) {
            
            int parenthesis = pow(4, 9-i); //exponential part, ready for treadmilling
            
            switch(word[i]) {//compares current character of the word[] with ACGT

                case 'A' :
                case 'a' :
                    result = result + (0 * parenthesis); //Attaches to indexing equation
                    break;
                    
                case 'C' :
                case 'c' :
                    result = result + (1 * parenthesis); //Attaches to indexing equation
                    break;
                    
                case 'G' :
                case 'g' :
                    result = result + (2 * parenthesis); //Attaches to indexing equation
                    break;
            
                case 'T' :
                case 't' :
                    result = result + (3 * parenthesis); //Attaches to indexing equation
                    break;
            
                default :
                    printf("Error occured in indexing the sequence: %s\n", word);
            }
        }
        
    return result;
}


//Function that translates the values back into the original words
char *unHash(int dh){
    
    int result[10];
    static char pop[10];
    
        for (int x = 0; x < 10; x++) {
            int mod = dh % 4; //gets remainder
            
            result[9-x] = mod;
            dh = dh/4; //holds quotient
        }
    
        for (int x = 0; x < 10; x++) {
                if (result[x] == 0) { //A
                    pop[x] = 'A';
                }
                else if (result[x] == 1) { //C
                    pop[x] = 'C';
                }
                else if (result[x] == 2) { //G
                    pop[x] = 'G';
                }
                else if (result[x] == 3) { //T
                    pop[x] = 'T';
                }
        }
    return pop;
    }
