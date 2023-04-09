//*************************************************************************************************
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "datatypes.h"
#include "constants.h"
#include "datafunctions.h"
//*************************************************************************************************
void save(DatabaseType database, int* size, FILE* file);
void populate(DatabaseType database, int* size, FILE* file);
void cleanup(DatabaseType database, int* size);
void provisional_sort(DatabaseType database, int* size);
BoatDataType* add_boat(String userinput);
void remove_boat(BoatDataType* boat);
void add_to_database(DatabaseType database, int* size);
void remove_from_database(DatabaseType database, int* size);
void print_database(DatabaseType database, int size);
void new_month(DatabaseType database, int size);
void payment(DatabaseType database, int size);
void free_database(DatabaseType database, int size);
//*************************************************************************************************
#endif
//*************************************************************************************************
