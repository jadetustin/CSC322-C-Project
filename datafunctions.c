//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatypes.h"
#include "constants.h"
//*************************************************************************************************
BoatPlace string_to_place(String place) {

    if (strcmp(place, "slip") == 0) {
	return slip;
    } else if (strcmp(place, "land") == 0) {
	return land;
    } else if (strcmp(place, "trailor") == 0) {
	return trailor;
    } else {
	return storage;
    }

}
//*************************************************************************************************
void set_name(BoatDataType* boat, String name) {
    strcpy(boat->name, name);
    return;
}
//*************************************************************************************************
void set_length(BoatDataType* boat, int length) {
    boat->length = length;
    return;
}
//*************************************************************************************************
void set_place(BoatDataType* boat, String place) {
    boat->place = string_to_place(place);
    return;
}
//*************************************************************************************************
void set_amount_owed(BoatDataType* boat, float amount) {
    boat->amount_owed = (float)amount;
    return;
}
//*************************************************************************************************
void set_info(BoatDataType* boat, char* input) {
    
    BoatPlace place = boat->place;

    if (place == slip) {
	boat->info.slip_number = atoi(input);
    } else if (place == land) {
	boat->info.bay_letter = *input;
    } else if (place == trailor) {
	strcpy(boat->info.trailor_tag, input);
    } else {
	boat->info.storage_number = atoi(input);
    }

}
//*************************************************************************************************
char* place_to_string(BoatDataType* boat) {
    
    BoatPlace place = boat->place;

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
 
    BoatPlace place = boat->place;

    if (place == slip) {
	printf("%-20s %3d' %7s   #%3d   Owes $%7.2f\n", boat->name, boat->length,
			place_to_string(boat), boat->info.slip_number, boat->amount_owed);
    } else if (place == land) {
	printf("%-20s %3d' %7s      %c  Owes $%7.2f\n", boat->name, boat->length,
			place_to_string(boat), boat->info.bay_letter, boat->amount_owed);
    } else if (place == trailor) {
	printf("%-20s %3d' %7s %6s Owes $%7.2f\n", boat->name, boat->length,
			place_to_string(boat), boat->info.trailor_tag, boat->amount_owed);
    } else {
	printf("%-20s %3d' %7s   #%3d   Owes $%7.2f\n", boat->name, boat->length,
			place_to_string(boat), boat->info.storage_number, boat->amount_owed);
    }

}
