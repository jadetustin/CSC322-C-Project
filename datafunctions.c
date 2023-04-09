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
    int result = strcasecmp(get_name(boatA), get_name(boatB));
    return result;
}
//*************************************************************************************************
int compare_entry(String entry, BoatDataType* boat) {
    return strcasecmp(entry, get_name(boat));
}
//*************************************************************************************************
BoatPlace string_to_place(String place) {

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
    boat->amount_owed = amount;
    return;
}
//*************************************************************************************************
void set_info(BoatDataType* boat, char* input) {
    
    BoatPlace place = get_place(boat);

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
    return boat->name;
}
//*************************************************************************************************
int get_length(BoatDataType* boat) {
    return boat->length;
}
//*************************************************************************************************
BoatPlace get_place(BoatDataType* boat) {
    return boat->place;
}
//*************************************************************************************************
float get_amount_owed(BoatDataType* boat) {
    return boat->amount_owed;
}
//*************************************************************************************************
char* place_to_string(BoatDataType* boat) {
    
    BoatPlace place = get_place(boat);

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
	printf("That is more than the amount owed, $%-7.2f", get_amount_owed(boat));
    } else {
        set_amount_owed(boat, (get_amount_owed(boat) - payment));
    }

}
//*************************************************************************************************
