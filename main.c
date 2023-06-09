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
int main(int argc, char* argv[]) {
    
    //*****************************************************************************************
    // declare variables.
    char userinput;
    FILE* data_file;
    DatabaseType database;
    int size = 0;

    // check command line arguments for a provided file.
    // if it exists, open it and populate the database with the boats provided.
    // if not, exit.
    // check for file open/close errors too.
    if (argc < 2) {
	printf("No file provided! Exiting...\n");
	exit(EXIT_FAILURE);
    }

    if ((data_file = fopen(argv[1], "r")) == NULL) {
	perror("Cannot open file!");
	exit(EXIT_FAILURE);
    }

    populate(database, &size, data_file);

    if (fclose(data_file) == EOF) {
        perror("Cannot close file!");
        exit(EXIT_FAILURE);
    }

    //*****************************************************************************************
    printf("Welcome to the Boat Management System\n");
    printf("-------------------------------------\n");
    
    // main menu implementation with a switch statement.
    // while input is not X or x, continue giving the menu to the user and processing actions.
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
	        printf("Invalid option %c.\n", userinput);
		break;

	}
	printf("\n");
	printf("(I)nventory, (A)dd, (R)emove, (P)ayment, (M)onth, e(X)it : ");
	scanf(" %1c", &userinput);
    
    }

    //*****************************************************************************************
    // save the file using the same name, free the data, and exit.
    // handle any open/close errors along the way.
    printf("\n");
    printf("Exiting the Boat Management System\n");

    if ((data_file = fopen(argv[1], "w+")) == NULL) {
	perror("Cannot open file!");
	exit(EXIT_FAILURE);
    }

    save(database, &size, data_file);

    if (fclose(data_file) == EOF) {
        perror("Cannot close file!");
        exit(EXIT_FAILURE);
    }

    free_database(database, size);

    return EXIT_SUCCESS;
    //*****************************************************************************************

}
//*************************************************************************************************
