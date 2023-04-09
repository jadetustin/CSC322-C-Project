//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainfunctions.h"
#include "datatypes.h"
#include "datafunctions.h"
#include "constants.h"
//*************************************************************************************************
void save(DatabaseType database, int* size, FILE* file) {

    int index;
    BoatPlace place;
    BoatDataType* boat;

    // go through the entire database and save each boat to the file.
    // if statement handles different cases for boat info.
    for (index = 0; index < *size; index++) {
        
	boat = database[index];
	place = get_place(boat);

	if (place == slip) {
            fprintf(file, "%s,%d,%s,%d,%f\n", get_name(boat), get_length(boat),
                        place_to_string(boat), boat->info.slip_number, get_amount_owed(boat));
    	} else if (place == land) {
	    fprintf(file, "%s,%d,%s,%c,%f\n", get_name(boat), get_length(boat),
                        place_to_string(boat), boat->info.bay_letter, get_amount_owed(boat));
    	} else if (place == trailor) {
            fprintf(file, "%s,%d,%s,%s,%f\n", get_name(boat), get_length(boat),
                        place_to_string(boat), boat->info.trailor_tag, get_amount_owed(boat));
    	} else {
	    fprintf(file, "%s,%d,%s,%d,%f\n", boat->name, boat->length,
                        place_to_string(boat), boat->info.storage_number, get_amount_owed(boat));
    	}
    
    }

    return;
    
}
//*************************************************************************************************
void populate(DatabaseType database, int* size, FILE* file) {

    String userentry;

    // while not at the end of the file, pass each line of the file to boat add function.
    // assign the database element to the returned pointer and increment the size.
    // checks that size has not been exceeded.
    while ((fgets(userentry, STRING_LENGTH, file) != NULL) && ((*size + 1) <= DATABASE_SIZE)) {
        database[*size] = add_boat(userentry);
        *size = *size + 1;
    }

    // once populated, sort the database.
    provisional_sort(database, size);
    
    return;
    
}
//*************************************************************************************************
void cleanup(DatabaseType database, int* size) {

    int index = 0;
    BoatDataType* temp;

    // function assumes only one "empty" pointer exists, since deletion is one item at a time.
    // swaps empty pointer to the place where the first empty element goes (should be size - 1).
    for (index = 0; index < *size; index++) {
	if (database[index] == NULL) {
	    temp = database[*size - 1];
	    database[*size - 1] = NULL;
	    database[index] = temp;
	    return;
	}
    }

    return;
}
//*************************************************************************************************
void provisional_sort(DatabaseType database, int* size) {
    
    int index = 0;
    int swapped = 1;
    BoatDataType* temp;

    // simple bubble sort implementation.
    // uses compare_boats(args) function to handle comparisons.
    swapped = 1;
    while (swapped != 0) {
        swapped = 0;
        for (index = 0; index < *size - 1; index++) {
            if ((compare_boats(database[index], database[index + 1])) > 0) {
                temp = database[index];
                database[index] = database[index + 1];
                database[index + 1] = temp;
                swapped = 1;
            }
        }
    }

}
//*************************************************************************************************
BoatDataType* add_boat(String entry) {

    BoatDataType* new_boat;
    char* receive;

    // malloc for the pointer and give it the amount of memory it needs, checking for errors.
    if ((new_boat = (BoatDataType* )malloc(sizeof(BoatDataType))) == NULL) {
        perror("Cannot malloc.");
        exit(EXIT_FAILURE);
    }

    // set all relevant data fields.
    // fields are set in the order they are expected to come from the file.
    receive = strtok(entry, SEPARATOR);
    set_name(new_boat, receive);
    receive = strtok(NULL, SEPARATOR);
    set_length(new_boat, atoi(receive));
    receive = strtok(NULL, SEPARATOR);
    set_place(new_boat, receive);
    receive = strtok(NULL, SEPARATOR);
    set_info(new_boat, receive);
    receive = strtok(NULL, SEPARATOR);
    set_amount_owed(new_boat, ((float)atof(receive)));
    
    return new_boat;

}
//*************************************************************************************************
void remove_boat(BoatDataType* boat) {
    
    // free the memory and return.
    free(boat);
    return;

}
//*************************************************************************************************
void add_to_database(DatabaseType database, int* size) {

    String userentry;

    // dump off the \n from stdin. 
    fgetc(stdin);

    // if size + 1 exceeds maximum size, don't add the new element.
    if ((*size + 1) > DATABASE_SIZE) {
	printf("Database is full!\n");
    }

    // prompt user for input, and pass it along to the add_boats function.
    // element (int size) of the array gets the returned pointer.
    // the size of the database increments.
    printf("Please enter the boat data in CSV format                 : ");
    fgets(userentry, STRING_LENGTH, stdin);
    database[*size] = add_boat(userentry);
    *size = *size + 1;

    // sort the database and return.
    provisional_sort(database, size);
    return;
    
}
//*************************************************************************************************
void remove_from_database(DatabaseType database, int* size) {

    String userentry;
    int index;

    // dump off the \n from stdin. 
    fgetc(stdin);

    // prompt user for input and dump off the newline character.
    printf("Please enter the boat name                               : ");
    fgets(userentry, STRING_LENGTH, stdin);
    userentry[(strlen(userentry) - 1)] = '\0';

    // search for the element.
    // if found, remove it (free the data).
    // then null out the pointer, cleanup, and sort what's left. return when done.
    for (index = 0; index < *size; index++) {
        if ((compare_entry(userentry, database[index])) == 0) {
            remove_boat(database[index]);
	    database[index] = NULL;
	    cleanup(database, size);
	    *size = *size - 1;
            provisional_sort(database, size);
	    return;
        }
    }

    // if this element is reached, there was no boat matching the entry.
    printf("No boat with that name.\n");
    return;

}
//*************************************************************************************************
void print_database(DatabaseType database, int size) {

    int index = 0;

    for (index = 0; index < size; index++) {
	print_boat(database[index]);
    }

    return;

}
//*************************************************************************************************
void new_month(DatabaseType database, int size) {
    
    int index = 0;

    // apply monthly payment function to every boat.
    for (index = 0; index < size; index++) {
	month(database[index]);
    }

    return;
}
//*************************************************************************************************
void payment(DatabaseType database, int size) {

    String userentry;
    int index = 0;
    float amount;

    // dump off the \n from stdin. 
    fgetc(stdin);

    // prompt user for input and dump off the newline character.
    printf("Please enter the boat name                               : ");
    fgets(userentry, STRING_LENGTH, stdin);
    userentry[(strlen(userentry) - 1)] = '\0';

    // search for the element.
    // if found, prompt the user for the amount needed, again dumping off \n.
    // pass that amount to the make_payment(args) function and return.
    for (index = 0; index < size; index++) {
	if ((compare_entry(userentry, database[index])) == 0) {
	    printf("Please enter the amount to be paid                       : ");
	    fgets(userentry, STRING_LENGTH, stdin);
            userentry[(strlen(userentry) - 1)] = '\0';
	    amount = (float)(atof(userentry));
	    make_payment(database[index], amount);
	    return;
	}
    }

    // if this element is reached, there was no boat matching the entry.
    printf("No boat with that name.\n");
    return;

}
//*************************************************************************************************
void free_database(DatabaseType database, int size) {

    int index = 0;

    // free each element of the database that has actually been used.
    for (index = 0; index < size; index++) {
	remove_boat(database[index]);
    }

}
//*************************************************************************************************
