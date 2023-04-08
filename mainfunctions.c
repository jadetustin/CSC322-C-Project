//*************************************************************************************************
#include <tdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainfunctions.h"
#include "datatypes.h"
#include "datafunctions.h"
#include "constants.h"
//*************************************************************************************************
BoatDataType* add_boat(String userinput) {

    BoatDataType* new_boat;
    char* receive;

    if ((new_boat = (BoatDataType *)malloc(sizeof(BoatDataType))) == NULL) {
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
    boat = NULL;
    return;

}
//*************************************************************************************************
void add_to_database(DatabaseType database, int* size) {

    String userentry;

    printf("Please enter the boat data in CSV format                 : ");
    scanf(" %s", userentry);
    database[size] = add_boat(userentry);
    *size++;
    qsort(database, *size, sizeof(BoatDataType), compare_boats);
    return;
    
}
//*************************************************************************************************
void remove_from_database(DatabaseType database, int* size) {

    String userentry;

    printf("Please enter the boat name                               : ");
    scanf(" %s", userentry);
    for (index = 0; index < *size; index++) {
        if ((compare_entry(userentry, database[index])) == 0) {
            remove_boat(database[index]);
	    *size--;
	    qsort(database, *size, sizeof(BoatDataType), compare_boats);
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

    printf("Please enter the boat name                               : ");
    scanf(" %s", userentry);

    for (index = 0; index < size; index++) {
	if ((compare_entry(userentry, database[index])) == 0) {
	    printf("Please enter the amount to be paid                       : ");
	    scanf(" %f", amount);
	    make_payment(database[index], amount);
	    return;
	}
    }

    printf("No boat with that name.\n");
    return;

}
//*************************************************************************************************