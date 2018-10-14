/**
* Filename: testlib.c
* Auther: Thomas Johansson
* Date: 2018-10-08
*
* Used to test the functionality of libcomponent
*/

#include "libcomponent.h"
#include "libresistance.h"
#include "libpower.h"

#include <stdio.h>

int main (void){

    // test libresistance
    int antal = 2;
    char conn = 'P';
    float components[2] = {1.0, 2.0};

    float libtest = calc_resistance(antal, conn, components);
    printf("Test libresistance %f\n", libtest);

    // test libpower

    float power_i = calc_power_i(2.0, 5.0);
    float power_r = calc_power_i(2.0 ,5.0);

    printf("Test libpower\n");
    printf("Power i = %f\n", power_i);
    printf("Power r = %f\n", power_r);

    // test libcomponents
    float resistor = 10;
    float e12_replace[NBR_COMPONTENTS];
    int nbr_resistors = e_resistance(resistor, e12_replace);
    
    printf("Test libcomponents\n");
    printf("\nE12 replacement resistors ");
    for (int i = 0; i < NBR_COMPONTENTS; i++){
        printf("%0.2E, ", e12_replace[i]);
    }
    
    printf("\nNumber of resistors %d\n", nbr_resistors);

}
