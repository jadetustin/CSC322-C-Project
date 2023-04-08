//*************************************************************************************************
// main file for boat management program.
// contains protocols for basic menu navigation.
// remainder of functionality has been delegated to other files.
//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "datatypes.h"
#include "datafunctions.h"
#include "mainfunctions.h"
//*************************************************************************************************
int main(void) {

    char initinput, userinput;
    DatabaseType database;
    int size = 0;

    // print welcome message.
    printf("Welcome to the Boat Management System\n");
    printf("-------------------------------------\n");

    // main menu implementation with a switch statement.
    printf("\n");
    printf("(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
    scanf(" %c", &userinput);
    while (userinput != 'X' && userinput != 'x') {
	switch(userinput) {
	    case 'i':
	    case 'I':
		print_database(database, size);
		break;
	    case 'a':
	    case 'A':
	        add_to_database(database, &size);
		break;
	    case 'r':
	    case 'R':
                remove_from_database(database, &size);
		break;
	    case 'p':
	    case 'P':
		payment(database, size);
		break;
	    case 'm':
	    case 'M':
		new_month(database, size);
		break;
	    default:
	        printf("Invalid option. %c\n", userinput);
		break;

	}
	printf("\n");
	printf("(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
	scanf(" %1c", &userinput);
    }
    
    // save the file using the same name and exit.
    printf("\n");
    printf("Exiting the Boat Management System\n");

    free_database(database, size);

    return EXIT_SUCCESS;

}
//*************************************************************************************************
