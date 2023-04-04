//*************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "datatypes.h"
#include "datafunctions.h"
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

    set_name(sample_data[0], "Example Name");
    set_length(sample_data[0], 69);
    set_place(sample_data[0], "slip");
    set_info(sample_data[0], "27");
    float amount = 55.21;
    printf("Value of amount is       $%7.2f\n", amount);
    set_amount_owed(sample_data[0], amount);

    printf("This is the amount owed: $%7.2f\n", sample_data[0]->amount_owed);

    print_boat(sample_data[0]);
    month(sample_data[0]);
    printf("After the month passed...\n");
    print_boat(sample_data[0]);
    make_payment(sample_data[0], 50.00);
    printf("After I paid $50 and picked up the garbage...\n");
    print_boat(sample_data[0]);

    for (index = 0; index < 4; index++) {
	free(sample_data[index]);
    }

    return EXIT_SUCCESS;

}
//*************************************************************************************************
