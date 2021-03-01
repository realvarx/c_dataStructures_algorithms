/**CFile***********************************************************************

  FileName    [functions.c]

  Synopsis    [Contains all the functions for the different options in the menu]

  Description [All eight functions are void, that will be called by FinalProject.c]

  Authors     [ALVARO MERINO ARGUMANEZ 100406665
			         VICTOR SANTOS LOPEZ 100409373
			         ALEXIA SANCHEZ ESPERANTE 100384082
               TOMAS SANCHEZ DE DIOS 100406601]

  Copyright   [Copyright (c) 2012 Carlos III University of Madrid
  All rights reserved.

  Permission is hereby granted, without written agreement and without license
  or royalty fees, to use, copy, modify, and distribute this software and its
  documentation for any purpose, provided that the above copyright notice and
  the following two paragraphs appear in all copies of this software.

  IN NO EVENT SHALL THE CARLOS III UNIVERSITY OF MADRID BE LIABLE TO ANY PARTY
  FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING
  OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE CARLOS III
  UNIVERSITY OF MADRID HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  THE CARLOS III UNIVERSITY OF MADRID SPECIFICALLY DISCLAIMS ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND CARLOS III UNIVERSITY OF MADRID HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.]

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*---------------------------------------------------------------------------*/
/* Type declarations                                                         */
/*---------------------------------------------------------------------------*/

/**Enum************************************************************************

  Synopsis    [Enum created to assign a cell's different modes]

******************************************************************************/
typedef enum mod{Auto,Ad_Hoc,Maganed,Master,Repeater,Secondary,Monitor,Unknown}mode;

/**Enum************************************************************************

  Synopsis    [Enum created to assign a cell's two types of encryptions]

******************************************************************************/
typedef enum enc{off,on}encryption;

/*---------------------------------------------------------------------------*/
/* Structure declarations                                                    */
/*---------------------------------------------------------------------------*/

/**Struct*********************************************************************

  Synopsis    [Struct to store the data from each cell]

******************************************************************************/
struct celldata{
  char mac_address[30];
  char essid[50];
  mode mode;
  int channel;
  encryption encryption;
  int quality;
  float freq;
  int signal_level;
  struct celldata *cellnext;
};

/**Struct*********************************************************************

  Synopsis    [Struct point to the begining of the list]

******************************************************************************/
struct celldata *cellhead=NULL;

/**Struct*********************************************************************

  Synopsis    [Struct to store temporal cell data]

******************************************************************************/
struct celldata *cellaux=NULL;

/**Struct*********************************************************************

  Synopsis    [Struct to store the data from the cell with the best quality]

******************************************************************************/
struct celldata *cellbest=NULL;

/**Struct*********************************************************************

  Synopsis    [Struct to point to the previous cell in the list]

******************************************************************************/
struct celldata *cellprev=NULL;

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/**Variable********************************************************************

  Synopsis    [Character used to ask the user if he wants to exit the program]

******************************************************************************/
char yNopt;

/**Variable********************************************************************

  Synopsis    [Character used to ask the user if he wants to add another
               acces point]

******************************************************************************/
char yN2;

/**Variable********************************************************************

  Synopsis    [Static int variable, used to verify if there is already a head
              (cellhead) node or not.]

******************************************************************************/
static int fcounter = 0;

/**Variable********************************************************************

  Synopsis    [Int variable used to choose between debug mode on and off]

******************************************************************************/
int debug = 0;



/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************

  Synopsis           [Function for printing the menu every time the user
                      finishes an option]

  SideEffects        [It will exit the program and finish everything]

******************************************************************************/
void print_menu(){
puts("==================================================\n[2019] SUCEM S.L. WIFI COLLECTOR\nVER ALPHA 0.1\n==================================================\n");

puts("[1] wificollector_quit \n[2] wificollector_collect \n[3] wificollector_show_data_one_network\n[4] wificollector_select_best \n[5] wificollector_delete_net\n[6] wificollector_sort\n[7] wificollector_export\n[8] wificollector_import \n[100] Turn on/off debug mode\nOption:\n");
}

/**Function********************************************************************

  Synopsis           [Function to turn on or off the debug mode]

  SideEffects        [No side effects because it only prints certain vaules if
                      debug mode is activated]

******************************************************************************/
void debugfnc(){
  if (debug == 1){
    debug = 0;
  }else debug = 1;
}

/**Function********************************************************************

  Synopsis           [Function for exiting the program if the user wants to]

  SideEffects        [It will exit the program and finish everything]

******************************************************************************/
void case1fnc(){
  puts("You have chosen option 1: wificollector_quit");
  puts("Are you sure you want to exit the program? [y,N]");
  
  do{
   int end1 = scanf ("%s", &yNopt);
     clearerr (stdin);
   if(end1 == EOF){
      perror("Operation cancelled");
      return;
    } 
  
    if(yNopt != 'y' && yNopt != 'N'){
      puts("Error: introduce y or N");
    }
  }while(yNopt != 'y' && yNopt != 'N');

  if(yNopt=='y'){
    puts("End of the program");
    exit(0);
  }
}

/**Function********************************************************************

  Synopsis           [Function for collecting information of specified cells]

  SideEffects        [It affects directly to case3fnc(), case4fnc() and
                      case5fnc() because if there are no collected cells,
                      these functions will not be able to fullfill their purpose]

******************************************************************************/
void case2fnc(){
  puts("You have chosen option 2: wificollector_collect");

  int case2input;
 do{
   do{
    puts("What cell do you want to collect? (1 - 21):");

        int end2 = scanf("%d", &case2input);
        clearerr (stdin);
      if(end2 == EOF){
        perror("Operation cancelled");
      return;
      }

    if (case2input <1 || case2input >21)puts("ERROR : Try again\n");
   }while(case2input <1 || case2input >21);

   FILE *cellptr;
   size_t bytes = 0;

   char tmpstr[11] = "info_cell_";
   char c2ichar[3];
   if (debug==1)printf("DEBUG strinicial %s\n", tmpstr );

   sprintf(c2ichar, "%d", case2input);
   char ichartemp[3];
   strcpy(ichartemp, c2ichar);

   strcat(tmpstr, c2ichar);
   if (debug==1)printf("DEBUG 1ST CONCAT %s\n", tmpstr);
   strcat(tmpstr, ".txt");
   if (debug==1)printf("DEBUG 2ND CONCAT %s\n", tmpstr);

   cellptr = fopen(tmpstr, "r");
   char searchcell[7] = "Cell ";
   strcat(searchcell, ichartemp);
   char *line=NULL;

   if (debug==1)printf("DEBUG SEARCHCELL : %s\n", searchcell);

    struct celldata *lastcell;
    struct celldata *auxlastcell;
    auxlastcell = cellhead;
    
    int emptybool;
    
    if (cellhead == NULL){
      emptybool = 1;
    }else{
      emptybool = 0;
    }
    
    //Seek for the last node of the LinkedList
    if (emptybool == 0){              
    while(auxlastcell != NULL){
        if(auxlastcell->cellnext == NULL) lastcell = auxlastcell;
        auxlastcell = auxlastcell->cellnext;
    }
    cellaux = lastcell;
    }

   while((getline(&line, &bytes, cellptr) != EOF)){

     if (debug==1)printf("DEBUG : %s\n", line);
     

     if(strstr(line , "Address")){
       char *token;
       token = strtok(line, ": ");
       token = strtok(NULL, " ");
       strcpy(cellaux->mac_address, token);

       if (debug==1)printf("DEBUG ADDRESS : %s", cellaux->mac_address);
     }

     if(strstr(line, "ESSID")){
       char *token;
       token = strtok(line, ":");
       token = strtok(NULL, ":");
       strcpy(cellaux->essid, token);
       if (debug==1)printf("TOKEN PRINT ESSID:%s", cellaux->essid);
     }

     if(strstr(line , "Mode")){
       char *token;
       token = strtok(line, ":");
       token = strtok(NULL, ":");
       char modebuff[10];
       strcpy(modebuff, token);

       if(strstr(token, "Auto")) cellaux->mode = 0;
       else if (strstr(token, "Ad-Hoc")) cellaux->mode = 1;
       else if (strstr(token, "Managed")) cellaux->mode = 2;
       else if (strstr(token, "Master")) cellaux->mode = 3;
       else if (strstr(token, "Repeater")) cellaux->mode = 4;
       else if (strstr(token, "Secondary")) cellaux->mode = 5;
       else if (strstr(token, "Monitor")) cellaux->mode = 6;
       else if (strstr(token, "Unknown")) cellaux->mode = 7;
     }

     if(strstr(line , "Channel")){
       char *token;
       token = strtok(line, ":");
       token = strtok(NULL, ":");
       cellaux->channel = atoi(token);
       if (debug==1)printf("TOKEN PRINT CHANNEL:%d", cellaux->channel);
     }

     if(strstr(line , "Encryption key")){
       char *token;
       token = strtok(line, ":");
       token = strtok(NULL, ":");

       if(strstr(token, "off")) cellaux->encryption = 0;
       else if (strstr(token, "on")) cellaux->encryption = 1;

       if (debug==1)printf("TOKEN PRINT ENCRYPTIONKEY:%d", cellaux->encryption);
     }

     if(strstr(line , "Quality")){
       char *token;
       token = strtok(line, "=");
       token = strtok(NULL, "=");
       char qualitybuff[6];
       strcpy(qualitybuff, token);
       token = strtok(qualitybuff, "/");
       
       cellaux->quality = atoi(token);
       if (debug==1)printf("TOKEN PRINT QUALITY:%d", cellaux->quality);
     }

     if(strstr(line , "Frequency")){
       char *token;
       token = strtok(line, ":");
       token = strtok(NULL, ":");
       char freqbuff[10];
       strcpy(freqbuff, token);
       token = strtok(freqbuff, " ");
      
       cellaux->freq = atof(token);
       if (debug==1)printf("TOKEN PRINT FREQ:%.3f", cellaux->freq);
     }

     if(strstr(line , "Signal level")){
       char *token;
       token = strtok(line, "=");
       token = strtok(NULL, "=");
       char slbuff[8];
       strcpy(slbuff, token);
       token = strtok(slbuff, " ");
       cellaux->signal_level = atoi(token);
       if (debug==1)printf("TOKEN PRINT SIGNAL_:%d", cellaux->signal_level);
     }
     
     if (strstr(line,  searchcell)){
       if (fcounter == 0){
         cellaux = (struct celldata*)malloc(sizeof(struct celldata));

         cellaux->cellnext = NULL;
         cellhead = cellaux;
         if (debug==1)printf("fcounter = 0 detected\n");

       }else{
         cellaux->cellnext = (struct celldata*)malloc(sizeof(struct celldata));
         cellaux = cellaux->cellnext;
       }
       fcounter++;
     }

   }

   printf("All networks contained in %s have been successfully loaded\n", searchcell);

   puts("Do you want to add another access point? [y / N]:");
   do{
     scanf ("%s", &yN2);
     if(yN2 != 'y' && yN2 != 'N'){
     puts("Error: introduce y or N");
     }
   }while(yN2 != 'y' && yN2 != 'N');

 }while(yN2 != 'N');

}

/**Function********************************************************************

  Synopsis           [Function for printing information of a specified cell]

  SideEffects        [This function does not have any side effects, as it can
                      only search and read cells, which will not affect the
                      performance of other functions]

******************************************************************************/
void case3fnc(){
  puts ("You have chosen option 3: wificollector_show_data_one_network");
  puts ("Indicate the ESSID (use “”): ");

   char case3input[100];
   
   int end3 = scanf("%s", case3input);
    clearerr (stdin);
   if(end3 == EOF){
    perror("Operation cancelled");
    return;
  }
   
   int essidcounter = 0;
   puts("These are the networks found with the specified name in the collected cells");

   cellaux = cellhead;

   if (debug==1)printf("DEBUG CASE3: %s\n", cellhead->mac_address);
   while(cellaux != NULL && cellhead != NULL){
     if(strstr(cellaux->essid, case3input)){
       essidcounter++;
       printf("Coincidence %d:\n", essidcounter);
       printf("==============================\n");
       printf("Address: %s", cellaux->mac_address);
       printf("ESSID:%s", cellaux->essid);
       if(cellaux->mode == 0) printf("Mode:Auto\n") ;
       else if (cellaux->mode == 1) printf("Mode:Ad-Hoc\n");
       else if (cellaux->mode == 2) printf("Mode:Managed\n");
       else if (cellaux->mode == 3) printf("Mode:Master\n");
       else if (cellaux->mode == 4) printf("Mode:Repeater\n");
       else if (cellaux->mode == 5) printf("Mode:Secondary\n");
       else if (cellaux->mode == 6) printf("Mode:Monitor\n");
       else if (cellaux->mode == 7) printf("Mode:Unknown\n");
       printf("Channel:%d\n", cellaux->channel);
       if(cellaux->encryption == 0) printf("Encryption key:off\n");
       else if (cellaux->encryption == 1) printf("Encryption key:on\n");
       printf("Quality:%d/70\n", cellaux->quality);
       printf("Frequency:%.3f GHz\n", cellaux->freq);
       printf("Signal level=%d dBm\n", cellaux->signal_level);
       printf("==============================\n");

       cellaux = cellaux->cellnext;
       
     }else{
       cellaux = cellaux->cellnext;
     }
   }
   if(essidcounter == 0) puts("(No networks were found)");

}

/**Function********************************************************************

  Synopsis           [Function to show the information of the best quality cell
                      out of the ones that have been already collected]

  SideEffects        [This function does not have any side effects, as it can
                      only search and read cells to compare their qualities,
                      which will not affect the performance of other functions]

******************************************************************************/
void case4fnc(){
  puts ("You have chosen option 4: wificollector_select_best");
  int bestbuff = 0;
   cellaux = cellhead;
   while(cellaux!=NULL){
     if(cellaux->quality > bestbuff){
       bestbuff = cellaux->quality;
       cellbest = cellaux;
     }
     cellaux = cellaux->cellnext;
   }
   puts("This is the info about the best quality network found");
   printf("==============================\n");
       printf("Address: %s", cellbest->mac_address);
       printf("ESSID:%s", cellbest->essid);
       if(cellbest->mode == 0) printf("Mode:Auto\n") ;
       else if (cellbest->mode == 1) printf("Mode:Ad-Hoc\n");
       else if (cellbest->mode == 2) printf("Mode:Managed\n");
       else if (cellbest->mode == 3) printf("Mode:Master\n");
       else if (cellbest->mode == 4) printf("Mode:Repeater\n");
       else if (cellbest->mode == 5) printf("Mode:Secondary\n");
       else if (cellbest->mode == 6) printf("Mode:Monitor\n");
       else if (cellbest->mode == 7) printf("Mode:Unknown\n");
       printf("Channel:%d\n", cellbest->channel);
       if(cellbest->encryption == 0) printf("Encryption key:off\n");
       else if (cellbest->encryption == 1) printf("Encryption key:on\n");
       printf("Quality:%d/70\n", cellbest->quality);
       printf("Frequency:%.3f GHz\n", cellbest->freq);
       printf("Signal level=%d dBm\n", cellbest->signal_level);
       printf("==============================\n");

}

/**Function********************************************************************

  Synopsis           [Function to delete the information of a specified cell
                      out of the ones that have been already collected]

  SideEffects        [Because this function deletes collected cells, it affects
                      dierctlty to the two previous functions]

******************************************************************************/
void case5fnc(){
  puts ("You have chosen option 5: wificollector_delete_net");
  char case5input[100];
  puts ("Indicate the ESSID (use “”): ");
  if(debug == 1)printf("DEBUG: CELLHEAD ESSID : %s", cellhead->essid);

  int end5 = scanf("%s", case5input);
      clearerr (stdin);
  if(end5 == EOF){
    perror("Operation cancelled");
    return;
  } 
  
 
  cellaux = cellhead;
  cellprev = NULL;

  while (cellaux != NULL){
    if(strstr(cellaux->essid, case5input)){
      if(cellprev == NULL){
        cellhead = cellhead->cellnext;
        free(cellaux);
        cellaux = cellhead;
      }else{
        cellprev->cellnext = cellaux->cellnext;
        free(cellaux);
        cellaux = cellprev->cellnext;
      }
    }else{
      cellprev = cellaux;
      cellaux = cellaux->cellnext;
    }
  }
 printf("All networks with name %s have been successfully removed\n", case5input);
 if(cellhead == NULL)fcounter = 0;
 if (debug==1 && cellhead == NULL)puts("Cellhead is null now");
 if (debug==1 && cellhead != NULL)puts("Cellhead isn't null");

}

/**Function********************************************************************

  Synopsis           [Function to sort by quality all the cells that have been
                      already collected in the list]

  SideEffects        [The omly effect this function has is to rearange the
                      nodes, it never removes or adds any new ones]

******************************************************************************/
void case6fnc(){
    puts ("You have chosen option 6: wificollector_sort");
    puts("These are all the networks sorted by decreasing order of the value of their qualities : ");
    
    int bool;
    struct celldata *cellbubble = NULL;
    struct celldata *cellbubblebuff = (struct celldata*)malloc(sizeof(struct celldata));
    
    do{
        bool = 0;
        cellaux = cellhead;
        
        while(cellaux->cellnext != cellbubble){
            
            if(cellaux->quality < cellaux->cellnext->quality){
                
                //We store the cellaux data in the buffer
                strcpy(cellbubblebuff->mac_address, cellaux->mac_address);
                strcpy(cellbubblebuff->essid, cellaux->essid);
                cellbubblebuff->mode = cellaux->mode;
                cellbubblebuff->channel = cellaux->channel;
                cellbubblebuff->encryption = cellaux->encryption;
                cellbubblebuff->quality = cellaux->quality;
                cellbubblebuff->freq = cellaux->freq;
                cellbubblebuff->signal_level = cellaux->signal_level;
                
                //We copy the information from the next node to the node itself
                strcpy(cellaux->mac_address, cellaux->cellnext->mac_address);
                strcpy(cellaux->essid, cellaux->cellnext->essid);
                cellaux->mode = cellaux->cellnext->mode;
                cellaux->channel = cellaux->cellnext->channel;
                cellaux->encryption = cellaux->cellnext->encryption;
                cellaux->quality = cellaux->cellnext->quality;
                cellaux->freq = cellaux->cellnext->freq;
                cellaux->signal_level = cellaux->cellnext->signal_level;
                
                //We copy the information from the buffer to the next node
                strcpy(cellaux->cellnext->mac_address, cellbubblebuff->mac_address);
                strcpy(cellaux->cellnext->essid, cellbubblebuff->essid);
                cellaux->cellnext->mode = cellbubblebuff->mode;
                cellaux->cellnext->channel = cellbubblebuff->channel;
                cellaux->cellnext->encryption = cellbubblebuff->encryption;
                cellaux->cellnext->quality = cellbubblebuff->quality;
                cellaux->cellnext->freq = cellbubblebuff->freq;
                cellaux->cellnext->signal_level = cellbubblebuff->signal_level;
                bool = 1;
            }
            cellaux = cellaux->cellnext;
        }
        cellbubble = cellaux;
    }while(bool);
  
    free(cellbubblebuff);
    
    //Lastly, we print the reordered list
    cellaux = cellhead;

    while(cellaux != NULL){
        
       printf("==============================\n");
       printf("Address: %s", cellaux->mac_address);
       printf("ESSID:%s", cellaux->essid);
       if(cellaux->mode == 0) printf("Mode:Auto\n") ;
       else if (cellaux->mode == 1) printf("Mode:Ad-Hoc\n");
       else if (cellaux->mode == 2) printf("Mode:Managed\n");
       else if (cellaux->mode == 3) printf("Mode:Master\n");
       else if (cellaux->mode == 4) printf("Mode:Repeater\n");
       else if (cellaux->mode == 5) printf("Mode:Secondary\n");
       else if (cellaux->mode == 6) printf("Mode:Monitor\n");
       else if (cellaux->mode == 7) printf("Mode:Unknown\n");
       printf("Channel:%d\n", cellaux->channel);
       if(cellaux->encryption == 0) printf("Encryption key:off\n");
       else if (cellaux->encryption == 1) printf("Encryption key:on\n");
       printf("Quality:%d/70\n", cellaux->quality);
       printf("Frequency:%.3f GHz\n", cellaux->freq);
       printf("Signal level=%d dBm\n", cellaux->signal_level);
       printf("==============================\n");
       
       cellaux = cellaux->cellnext;
    }
}

/**Function********************************************************************

  Synopsis           [Function to create a new binary file with all the already
                      collected nodes from the Linked List]

  SideEffects        [The omly effect this function has is to copy the information
                      to an external file]

******************************************************************************/
void case7fnc(){
     puts("You have chosen option 7: wificollector_export");
     
     if (cellhead == NULL){
         puts("The list of networks is empty. Please, use option 2 to collect networks");
         return;
     }
     
     puts("Indicate the name of the file: \n(without any extension)");
     
     char case7input[100];

     int end7 = scanf("%s", case7input);
        clearerr (stdin);
     if(end7 == EOF){
       perror("Operation cancelled");
       return;
      } 
     
     strcat(case7input, ".bin");
     
     FILE *fileptr;
     fileptr = fopen(case7input, "wb");
     
     cellaux = cellhead;
     
     while(cellaux != NULL){
       
         //Ints
         fwrite(&(cellaux->mode), sizeof(int), 1 , fileptr);
         fwrite(&(cellaux->channel), sizeof(int), 1 , fileptr);
         fwrite(&(cellaux->encryption), sizeof(int), 1 , fileptr);
         fwrite(&(cellaux->quality), sizeof(int), 1 , fileptr);
         fwrite(&(cellaux->signal_level), sizeof(int), 1 , fileptr);
         
         //Float
         fwrite(&(cellaux->freq), sizeof(float), 1, fileptr);
         
         //Chars
         int maclength = strlen(cellaux->mac_address)+1;
         fwrite(&maclength, sizeof(int), 1, fileptr);
         fwrite(&(cellaux->mac_address), sizeof(char), maclength, fileptr);
         
         int essidlength = strlen(cellaux->essid)+1;
         fwrite(&essidlength, sizeof(int), 1, fileptr);
         fwrite(&(cellaux->essid), sizeof(char), essidlength, fileptr);
         
         cellaux = cellaux->cellnext;
     }
     
     fclose(fileptr);
     
     printf("All the information has been successfully written on %s\n", case7input);
}

/**Function********************************************************************

  Synopsis           [Function to import all the nodes previously copied into a binary
                      file in option seven without repeating them into the current
                      Linked list]

  SideEffects        [Because we might add new nodes, it affects to functions two,
                      (collects cells) three, (it prints the list), four,
                      (selects the best quality node), five, (deletes a node)
                      and six, (sorts by quality)]

******************************************************************************/
void case8fnc(){
    puts ("You have chosen option 8: wificollector_import");
    puts("Indicate the name of the file: \n(without any extension)");
    char case8input[100];

    int end8 = scanf("%s", case8input);
       clearerr (stdin);
   if(end8 == EOF){
     perror("Operation cancelled");
     return;
    } 
  
    strcat(case8input, ".bin");

    FILE *fileptr;
    fileptr = fopen(case8input, "rb");
    
    if(NULL == fileptr){
      puts("There was an error opening the file.\nPlease, verify the name of the file introduced.");
      return;
    }
    
    int currentchardim;
    int bool;   
    
    struct celldata *cellreadbuff = (struct celldata*)malloc(sizeof(struct celldata));
    struct celldata *lastcell;
    struct celldata *auxlastcell;
    auxlastcell = cellhead;
    
    int emptybool;
    
    if (cellhead == NULL){
    emptybool = 1;
    }
    
    if (emptybool == 0){              
      while(auxlastcell != NULL){
          if(auxlastcell->cellnext == NULL) lastcell = auxlastcell;
          auxlastcell = auxlastcell->cellnext;
      }
    }
    
    while(!feof(fileptr)){
            
            bool = 0; 
        
            if(feof(fileptr)) return;
        
            fread(&(cellreadbuff->mode), sizeof(int), 1, fileptr);
            fread(&(cellreadbuff->channel), sizeof(int), 1, fileptr);
            fread(&(cellreadbuff->encryption), sizeof(int), 1, fileptr);
            fread(&(cellreadbuff->quality), sizeof(int), 1, fileptr);
            fread(&(cellreadbuff->signal_level), sizeof(int), 1, fileptr);

            fread(&(cellreadbuff->freq), sizeof(float), 1, fileptr);
            
            fread(&currentchardim, sizeof(int), 1, fileptr);
            if(debug == 1)printf("DEBUG : currentchardim = %d\n", currentchardim);
            fread(&(cellreadbuff->mac_address), sizeof(char), currentchardim, fileptr);
            
            fread(&currentchardim, sizeof(int), 1, fileptr);
            if(debug == 1)printf("DEBUG : currentchardim = %d\n", currentchardim);
            fread(&(cellreadbuff->essid), sizeof(char), currentchardim, fileptr);
            
            
            if(debug == 1){
            puts("DEBUG : New node detected: ");
            printf("==============================\n");
            printf("Address: %s", cellreadbuff->mac_address);
            printf("ESSID:%s", cellreadbuff->essid);
            if(cellreadbuff->mode == 0) printf("Mode:Auto\n") ;
            else if (cellreadbuff->mode == 1) printf("Mode:Ad-Hoc\n");
            else if (cellreadbuff->mode == 2) printf("Mode:Managed\n");
            else if (cellreadbuff->mode == 3) printf("Mode:Master\n");
            else if (cellreadbuff->mode == 4) printf("Mode:Repeater\n");
            else if (cellreadbuff->mode == 5) printf("Mode:Secondary\n");
            else if (cellreadbuff->mode == 6) printf("Mode:Monitor\n");
            else if (cellreadbuff->mode == 7) printf("Mode:Unknown\n");
            printf("Channel:%d\n", cellreadbuff->channel);
            if(cellreadbuff->encryption == 0) printf("Encryption key:off\n");
            else if (cellreadbuff->encryption == 1) printf("Encryption key:on\n");
            printf("Quality:%d/70\n", cellreadbuff->quality);
            printf("Frequency:%.3f GHz\n", cellreadbuff->freq);
            printf("Signal level=%d dBm\n", cellreadbuff->signal_level);
            printf("==============================\n");
            }
            if(emptybool == 0){
            
            cellaux = cellhead;
                
                while(cellaux != NULL){
                
                if(debug==1)printf("DEBUG STRCMPMAC : %d\n", strcmp(cellreadbuff->mac_address, cellaux->mac_address));
                if(debug==1)printf("DEBUG STRCMPESSID : %d\n", strcmp(cellreadbuff->essid, cellaux->essid));
                
                if(strcmp(cellreadbuff->mac_address, cellaux->mac_address) == 0) bool = 1;
                    if(debug == 1)printf("Runs inside of if");
                    cellaux = cellaux->cellnext;
                }
            }
            
            if(debug == 1)puts("Runs before mallocs");
            
            if (bool == 0){
                
                if (fcounter == 0){
                    
                    cellaux = (struct celldata*)malloc(sizeof(struct celldata));

                    cellaux->cellnext = NULL;
                    cellhead = cellaux;
                    lastcell = cellaux;
                    
                    lastcell->mode = cellreadbuff->mode;
                    lastcell->channel = cellreadbuff->channel;
                    lastcell->encryption = cellreadbuff->encryption;
                    lastcell->quality = cellreadbuff->quality;
                    lastcell->freq = cellreadbuff->freq;
                    lastcell->signal_level = cellreadbuff->signal_level;
                
                    strcpy(lastcell->mac_address, cellreadbuff->mac_address);
                    strcpy(lastcell->essid, cellreadbuff->essid);
                    
                    fcounter++;
                    emptybool = 0;
                    
                }else{
                    
                    lastcell->cellnext = (struct celldata*)malloc(sizeof(struct celldata));
                
                    lastcell->cellnext->mode = cellreadbuff->mode;
                    lastcell->cellnext->channel = cellreadbuff->channel;
                    lastcell->cellnext->encryption = cellreadbuff->encryption;
                    lastcell->cellnext->quality = cellreadbuff->quality;
                    lastcell->cellnext->freq = cellreadbuff->freq;
                    lastcell->cellnext->signal_level = cellreadbuff->signal_level;
                
                    strcpy(lastcell->cellnext->mac_address, cellreadbuff->mac_address);
                    strcpy(lastcell->cellnext->essid, cellreadbuff->essid);
                 
                    lastcell = lastcell->cellnext ;
                }
            }
    }
    free(cellreadbuff);
    fclose(fileptr);
    
}