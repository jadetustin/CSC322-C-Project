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

    while (fgets(userentry, STRING_LENGTH, file) != NULL) {
        database[*size] = add_boat(userentry);
        *size = *size + 1;
    }

    provisional_sort(database, size);
    
    return;
    
}
//*************************************************************************************************
void cleanup(DatabaseType database, int* size) {

    int index = 0;
    BoatDataType* temp;

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

    if ((new_boat = (BoatDataType* )malloc(sizeof(BoatDataType))) == NULL) {
        perror("Cannot malloc.");
        exit(EXIT_FAILURE);
    }

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
    
    free(boat);
    return;

}
//*************************************************************************************************
void add_to_database(DatabaseType database, int* size) {

    String userentry;

    fgetc(stdin);
    printf("Please enter the boat data in CSV format                 : ");
    fgets(userentry, STRING_LENGTH, stdin);
    database[*size] = add_boat(userentry);
    *size = *size + 1;
    provisional_sort(database, size);
    // qsort(database, *size, sizeof(BoatDataType), compare_boats);
    return;
    
}
//*************************************************************************************************
void remove_from_database(DatabaseType database, int* size) {

    String userentry;
    int index;

    fgetc(stdin);
    printf("Please enter the boat name                               : ");
    fgets(userentry, STRING_LENGTH, stdin);
    
    userentry[(strlen(userentry) - 1)] = '\0';

    for (index = 0; index < *size; index++) {
        if ((compare_entry(userentry, database[index])) == 0) {
            remove_boat(database[index]);
	    database[index] = NULL;
	    cleanup(database, size);
	    *size = *size - 1;
            provisional_sort(database, size);
	    // qsort(database, *size, sizeof(BoatDataType), compare_boats);
	    return;
        }
    }

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

    fgetc(stdin);
    printf("Please enter the boat name                               : ");
    fgets(userentry, STRING_LENGTH, stdin);

    userentry[(strlen(userentry) - 1)] = '\0';

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

    printf("No boat with that name.\n");
    return;

}
//*************************************************************************************************
void free_database(DatabaseType database, int size) {

    int index = 0;

    for (index = 0; index < size; index++) {
	remove_boat(database[index]);
    }

}
//*************************************************************************************************
