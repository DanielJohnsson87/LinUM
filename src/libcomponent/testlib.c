/**
* Filename: testlib.c
* Auther: Thomas Johansson
* Date: 2018-10-08
*
* Used to test the functionality of libcomponent
*/

#include "libcomponent.h"
#include <stdio.h>

int main (void){

    float resistor;
    printf("Ange resistor värde: ");
    scanf("%f", &resistor);

    float e12_replace[NBR_COMPONTENTS];
    
    
    int nbr_resistors = e_resistance(resistor, e12_replace);
    
    printf("\nE12 replacement resistors ");
    for (int i = 0; i < NBR_COMPONTENTS; i++){
        printf("%0.2E, ", e12_replace[i]);
    }
    
    printf("\nNumber of resistors %d\n", nbr_resistors);

}