//*************************************************************************************************
#ifndef DATAFUNCTIONS_H
#define DATAFUNCTIONS_H

#include "datatypes.h"
#include "constants.h"
//*************************************************************************************************
int compare_boats(const void* boat1, const void* boat2);
int compare_entry(String entry, BoatDataType* boat);
BoatPlace string_to_place(String place);
void set_name(BoatDataType* boat, String name);
void set_length(BoatDataType* boat, int length);
void set_place(BoatDataType* boat, String place);
void set_amount_owed(BoatDataType* boat, float amount);
void set_info(BoatDataType* boat, char* input);
char* get_name(BoatDataType* boat);
int get_length(BoatDataType* boat);
BoatPlace get_place(BoatDataType* boat);
float get_amount_owed(BoatDataType* boat);
char* place_to_string(BoatDataType* boat);
void print_boat(BoatDataType* boat);
void month(BoatDataType* boat);
void make_payment(BoatDataType* boat, float payment);
//*************************************************************************************************
#endif
//*************************************************************************************************
