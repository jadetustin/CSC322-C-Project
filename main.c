//*************************************************************************************************
// main file for boat management program.
// contains protocols for basic menu navigation and loading/saving.
//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
//*************************************************************************************************
// function declarations go here.
//*************************************************************************************************
int main(int argc, char* argv[]) {

    char initinput, userinput;

    // print welcome message.
    printf("Welcome to the Boat Management System\n");
    printf("-------------------------------------\n");

    // load the file, using the command-line argument as the name of the file.
    if (argc < 2) {
	printf("No file name was provided. Would you like to provide one? ");
	printf("(y for yes [default], n for no): ");
	scanf(" %c", &initinput);
	if (initinput == 'n' || initinput == 'N') {
	    printf("No file name provided!\n");
	    printf("Exiting the Boat Management System\n");
	    exit(EXIT_FAILURE);
	}
    }

    // main menu implementation with a switch statement.
    printf("\n");
    printf("(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
    scanf(" %c", &userinput);
    while (userinput != 'X' && userinput != 'x') {
	switch(userinput) {
	    case 'i':
	    case 'I':
		// call print inventory function
	        printf("Valid option %c\n", userinput);
		break;
	    case 'a':
	    case 'A':
	        // call add function
	        printf("Valid option %c\n", userinput);
		break;
	    case 'r':
	    case 'R':
                // call remove function
	        printf("Valid option %c\n", userinput);
		break;
	    case 'p':
	    case 'P':
		// call payment function
	        printf("Valid option %c\n", userinput);
		break;
	    case 'm':
	    case 'M':
		// call month function
	        printf("Valid option %c\n", userinput);
		break;
	    default:
	        printf("Invalid option %c\n", userinput);
		break;

	}
	printf("\n");
	printf("(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
	scanf(" %c", &userinput);
    }
    
    // save the file using the same name and exit.
    printf("\n");
    printf("Exiting the Boat Management System\n");
    return EXIT_SUCCESS;

}
//*************************************************************************************************
