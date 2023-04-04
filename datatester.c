//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "datatypes.h"
//*************************************************************************************************
int main(void) {

    BoatDataType* sample_data[4];
    BoatDataType* entry;
    int index = 0;

    for (index = 0; index < 4; index++) {
	if ((entry = (BoatDataType *)malloc(sizeof(BoatDataType))) == NULL) {
	    perror("Cannot malloc.");
	    exit(EXIT_FAILURE);
	}
	sample_data[index] = entry;
    }

    for (index = 0; index < 4; index++) {
	free(sample_data[index]);
    }

    return EXIT_SUCCESS;

}
//*************************************************************************************************
