/*	Eduardo Paredes-Diago
 * 	usage: mywords [-cs] [-f substring] filename
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int debug = 0;

int main(int argc, char **argv)
{
   extern char *optarg;
   extern int optind;
   int c, err = 0; 
   int cflag=0, sflag=0, fflag = 0; // initialize flag variables
   char *substring = "default_substring"; // nitialize value where initial and final results will be held
   static char usage[] = "usage: mywords [-cs] [-f substring] filename\n";

   FILE * fp; //file pointer for reading contents
   int characterCount; //keeps track of number of characters
   char currChar; //holds the current char
   char prevChar; //holds the prev char
   int wordCount; //tracks number of words in file
   char textFile[3500]; //for storing file contents
   char *token; //pointer for grabbing each token
   char tokenList[1000][250]; //for storing tokens from file
   char orderedList[1000][250]; //for storing list in order
   int i = 0;
   int j = 0;
   // switch statements that helps keep track of which arguments are passed in 
   while ((c = getopt(argc, argv, "cf:s")) != -1)
   switch (c) {
      case 'c':
         cflag = 1;
         break;
      case 's':
         sflag = 1;
         break;
      case 'f':
         fflag = 1;
         substring = optarg;
         break;
   }
	
   // checks to make sure necessary arguments are added along with flags	
   if ((optind+1) > argc) {	
      //printf("optind = %d, argc=%d\n", optind, argc);
      fprintf(stderr, "%s: missing argument\n", argv[0]);
      fprintf(stderr, usage, argv[0]);
      exit(1);
   } 
   else if (err) {
      fprintf(stderr, usage, argv[0]);
      exit(1);
      }

   // store filename from comman line arguments
   char * fileName = argv[optind];

   // checking that file exists
   fp = fopen(fileName, "r");
   if(fp == NULL){
     
      //FILE DOES NOT EXIST, set all flags to 0 to end the program from executing anything else
      printf("\nFILE %s NOT FOUND.\n", fileName);
      cflag = 0;
      sflag = 0;
      fflag = 0;
   }
   else{
       
      //FILE EXISTS  
      //grab first character in file, store into currChar
      currChar = fgetc(fp);
      //loop through, until end of file, keep count of words
      while(currChar != EOF){
         if((!isalpha(currChar)) && (isalpha(prevChar) && prevChar != ' ')){
            if((currChar != '-') && (currChar != '`')){
               wordCount++;
            }
         }
         
         if(currChar == '\0'){
            break;
         }
         textFile[i] = currChar; //store current character into textFile array of characters
         i++; 
         prevChar = currChar; 
         currChar = fgetc(fp);
      }

      //print out the contents of the file if it did exist
      printf("\nCONTENTS OF \"%s\": \n******BEGINNING OF FILE******\n", fileName);
      printf("%s\n", textFile);
      printf("*********END OF FILE**********\n\n");
   }

   //initialize char for holding delimiter characters needed for tokenizing
   char delimit[] = " .,:!;\n\t?";

   //tokeinzing of the char array that holds the text file contents
   i = 0;
   token = strtok(textFile, delimit);
   while(token != NULL){
      strcpy(tokenList[i], token);
      if(orderedList[0] == NULL){
         strcpy(orderedList[0], tokenList[i]);
      }
      
      i++;
      token = strtok(NULL, delimit);
   }

   //bubble sort for sorting the words in ASCII order
   void bubbleSort(char array[][250], int n){
      int i;
      int j;
      char temp[250];
      int cmpResult;
      for(i = 0; i < n - 1; i++){
         for(j = 0; j < n - i - 1; j++){
            //store result from compare of two integers
            cmpResult = strcmp(array[j], array[j + 1]);
            if(cmpResult > 0){
               strcpy(temp, array[j]);
               strcpy(array[j], array[j + 1]);
               strcpy(array[j + 1], temp);
            }
         }
      }
   }
   

   // ************START OF IF-STATEMENTS FOR FLAGS************

   if(sflag == 1)
   {
      //s flag was selected, prints out words in ASCII order
      printf("OPTION SELECTED: -s\n");
      wordCount;
      bubbleSort(tokenList, wordCount);
      printf("Sorted Words: \n");
      for(i = 0; i < wordCount; i++){
         printf("%s\n", tokenList[i]);
      }
      printf("\n");
   }

   if(cflag == 1)
   {
      //c flag was selected, prints out word count
      printf("OPTION SELECTED: -c\n");
      printf("Word Count: %d\n\n", wordCount); 
   }
   
   if(fflag == 1)
   {
      //f flag was selected, print out number of occurences of a given word
      printf("OPTION SELECTED: -f\n");
      int i;
      int substringCount = 0;
      for(i = 0; i < wordCount; i++){
         if(strcmp(substring, tokenList[i]) == 0){
            substringCount++;
         }
      }

      //print message if word not in file
      if(substringCount == 0){
         printf("\nSubstring \"%s\" NOT in file.\n", substring);
      }
      else{
         printf("substring \"%s\" appears %d time(s) in text file %s\n\n", substring, substringCount, fileName);
      }
   }

   // *********end of flag if-statements ************	
   
}
