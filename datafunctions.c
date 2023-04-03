//*************************************************************************************************
#include <stdio.h>
#include <string.h>
#include "datatypes.h"
#include "constants.h"
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
int get_info_slip(BoatDataType* boat) {
    return boat->info.slip_number;
}
//*************************************************************************************************
char get_info_land(BoatDataType* boat) {
    return boat->info.bay_letter;
}
//*************************************************************************************************
char* get_info_trailer(BoatDataType* boat) {
    return boat->info.trailor_tag;
}
//*************************************************************************************************
int get_info_storage(BoatDataType* boat) {
    return boat->info.storage_number;
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
