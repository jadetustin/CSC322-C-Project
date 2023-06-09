//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes.h"
#include "datafunctions.h"
#include "constants.h"
//*************************************************************************************************
int compare_boats(const void* boat1, const void* boat2) {
    
    BoatDataType* boatA = (BoatDataType*)boat1;
    BoatDataType* boatB = (BoatDataType*)boat2;
    
    // find and return result for lexicographic ordering of the boat names.
    int result = strcasecmp(get_name(boatA), get_name(boatB));
    return result;
}
//*************************************************************************************************
int compare_entry(String entry, BoatDataType* boat) {

    // find and return result for a match. will return 0 on match.
    return strcasecmp(entry, get_name(boat));

}
//*************************************************************************************************
BoatPlace string_to_place(String place) {

    // takes place as string input and converts it to the enum type.
    if (strcasecmp(place, "slip") == 0) {
	return slip;
    } else if (strcasecmp(place, "land") == 0) {
	return land;
    } else if (strcasecmp(place, "trailor") == 0) {
	return trailor;
    } else {
	return storage;
    }

}
//*************************************************************************************************
void set_name(BoatDataType* boat, String name) {
    
    // sets name to provided string argument.
    strcpy(boat->name, name);
    return;

}
//*************************************************************************************************
void set_length(BoatDataType* boat, int length) {
    
    // sets length to provided int argument.
    boat->length = length;
    return;

}
//*************************************************************************************************
void set_place(BoatDataType* boat, String place) {

    // sets place.
    // uses string_to_place(args) to convert user entry to enum type.
    boat->place = string_to_place(place);
    return;

}
//*************************************************************************************************
void set_amount_owed(BoatDataType* boat, float amount) {
    
    // sets amount owed to provided float argument.
    boat->amount_owed = amount;
    return;

}
//*************************************************************************************************
void set_info(BoatDataType* boat, char* input) {
    
    BoatPlace place = get_place(boat);

    // based on the place type (enum) of the boat, information is set differently.
    // char* argument allows for considerable flexibility in handling this.
    if (place == slip) {
	boat->info.slip_number = atoi(input);
    } else if (place == land) {
	boat->info.bay_letter = *input;
    } else if (place == trailor) {
	strcpy(boat->info.trailor_tag, input);
    } else {
	boat->info.storage_number = atoi(input);
    }

    return;

}
//*************************************************************************************************
char* get_name(BoatDataType* boat) {

    // returns string (char*) of boat name.
    return boat->name;

}
//*************************************************************************************************
int get_length(BoatDataType* boat) {
    
    // returns int of boat length.
    return boat->length;

}
//*************************************************************************************************
BoatPlace get_place(BoatDataType* boat) {
    
    // returns type for boat place.
    return boat->place;

}
//*************************************************************************************************
float get_amount_owed(BoatDataType* boat) {
    
    // returns float for boat's amount owed.
    return boat->amount_owed;

}
//*************************************************************************************************
char* place_to_string(BoatDataType* boat) {
    
    BoatPlace place = get_place(boat);

    // based on the type for boat place, return corresponding string.
    if (place == slip) {
	return "slip";
    } else if (place == land) {
	return "land";
    } else if (place == trailor) {
	return "trailor";
    } else {
	return "storage";
    }

}
//*************************************************************************************************
void print_boat(BoatDataType* boat) {
 
    BoatPlace place = get_place(boat);

    // based on the type of boat place, print the data differently.
    // this serves as a print handler for the main function.
    if (place == slip) {
	printf("%-20s %3d' %7s   #%3d   Owes $%7.2f\n", get_name(boat), get_length(boat),
			place_to_string(boat), boat->info.slip_number, get_amount_owed(boat));
    } else if (place == land) {
	printf("%-20s %3d' %7s      %c   Owes $%7.2f\n", get_name(boat), get_length(boat),
			place_to_string(boat), boat->info.bay_letter, get_amount_owed(boat));
    } else if (place == trailor) {
	printf("%-20s %3d' %7s %6s   Owes $%7.2f\n", get_name(boat), get_length(boat),
			place_to_string(boat), boat->info.trailor_tag, get_amount_owed(boat));
    } else {
	printf("%-20s %3d' %7s   #%3d   Owes $%7.2f\n", boat->name, boat->length,
			place_to_string(boat), boat->info.storage_number, get_amount_owed(boat));
    }

    return;

}
//*************************************************************************************************
void month(BoatDataType* boat) {

    BoatPlace place = get_place(boat);

    // update amount owed based on the type of boat place.
    if (place == slip) {
	set_amount_owed(boat, (get_amount_owed(boat) + (SLIP_RATE * get_length(boat))));
    } else if (place == land) {
	set_amount_owed(boat, (get_amount_owed(boat) + (LAND_RATE * get_length(boat))));
    } else if (place == trailor) {
	set_amount_owed(boat, (get_amount_owed(boat) + (TRAILOR_RATE * get_length(boat))));
    } else {
	set_amount_owed(boat, (get_amount_owed(boat) + (STORAGE_RATE * get_length(boat))));
    }

    return;

}
//*************************************************************************************************
void make_payment(BoatDataType* boat, float payment) {

    if (payment > get_amount_owed(boat)) {
	printf("That is more than the amount owed, $%.2f.\n", get_amount_owed(boat));
    } else {
        set_amount_owed(boat, (get_amount_owed(boat) - payment));
    }

}
//*************************************************************************************************
