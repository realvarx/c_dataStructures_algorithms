/**CFile***********************************************************************

  FileName    [FinalProject.c]

  Synopsis    [The main() function is allocated here]

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
#include "functions.h"

/*---------------------------------------------------------------------------*/
/* Variable declarations                                                     */
/*---------------------------------------------------------------------------*/

/**Variable********************************************************************

  Synopsis    [Int variable used to store the option that the user wants to
              perform]

******************************************************************************/
int option;

/*---------------------------------------------------------------------------*/
/* Definition of functions                                                   */
/*---------------------------------------------------------------------------*/

/**Function********************************************************************

  Synopsis           [The main() function executes all the functons stored in
                      functions.c]

  SideEffects        [It does not have any side effects appart from the ones
                      mentioned in the functions.c file]

******************************************************************************/

int main(int argc, char* argv[]) {
  if(argc>=2){
  if(strcmp(argv[1], "DEBUG") == 0)debugfnc();
}

do{

print_menu();
scanf("%d", &option);


switch(option){

 case 1:
  case1fnc();
 break;

 case 2:
  case2fnc();
 break;

 case 3:
  case3fnc();
 break;

 case 4:
  case4fnc();
 break;

 case 5:
  case5fnc();
 break;

 case 6:
  case6fnc();
 break;

 case 7:
  case7fnc();
 break;

 case 8:
  case8fnc();
 break;

 case 100:
  debugfnc();
 break;

 case 0:
 puts("EOF. End of the program.");
 exit(0);
 break;

 default:
 puts("ERROR : Unavailable option, try again.");
 }

}while(option != 0);

 return 0;
}