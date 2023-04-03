//*************************************************************************************************
#ifndef DATATYPES_H
#define DATATYPES_H
//*************************************************************************************************
#include "constants.h"

typedef char String[STRING_LENGTH];

typedef enum {
    slip,
    land,
    trailor,
    storage
} BoatPlace;

typedef union {
    unsigned int slip_number;
    char bay_letter;
    String trailor_tag;
    unsigned int storage_number;
} BoatInfo;

typedef struct {
    String name;
    unsigned int length;
    BoatPlace place;
    BoatInfo info;
    float amount_owed;
} BoatDataType;

#endif
//*************************************************************************************************
