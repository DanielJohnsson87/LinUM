
/**
* test.c
* Mårten Norman 2018-10-10
*
* Test of libpower
*
*/

#include "libpower.h"
#include <stdio.h>
#include <float.h>

int
main ()
{
	char  test_mode = ' '; /* Which test is selected */
	float resistance;
	float voltage;
	float current;

	float expected_power;
	float calculated_power;

/**
* Ask user about test parameters.
*
* Loop until q(uit) is selected
*/	
	while (test_mode != 'q') {
		printf("\nIs resistance or current known (q to quit)? [R | C | Q]:");
		scanf("%c", &test_mode);
		test_mode |= 0x60; /* Turn to lower case, eg r/R--> r */

		switch (test_mode) {

/**
* Test calc_power_r ()
*/
		case 'r':
			printf("Voltage? [V] ");
			scanf("%f",&voltage);
			
			printf("Resistance? [Ohm]: ");
			scanf("%f",&resistance);

/* Use  P = U^2/R  as reference value*/
			if (resistance == 0) 
				expected_power = FLT_MAX; /* ~ infinity */
			else
				expected_power = voltage * voltage / resistance;

			calculated_power = calc_power_r (voltage, resistance);

			printf("calc_power_r () says %f [W].....",calculated_power);
			printf("expected %f [W] \n",expected_power);
			
			break;


/**
* Test calc_power_i ()
*/
		case 'c':
			printf("Voltage? [V]: ");
			scanf("%f",&voltage);
			
			printf("Current? [A]: ");
			scanf("%f",&current);

/* Use  P = U*I  as reference value*/
			expected_power = voltage * current;
			calculated_power = calc_power_i (voltage, current);

			printf("calc_power_i () says %f [W].....", calculated_power);
			printf("expected %f [W] \n",expected_power);
			
			break;

		}
	}
}



/*
float calc_power_r(float volt, float resistance) {
float calc_power_i(float volt, float current) {
*/
