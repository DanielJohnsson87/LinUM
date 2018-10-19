/**
* Filename: electrotest.c
* Authors:
* Thomas Johansson
* DanielJohnsson
* Mårten Norman
*
* Date: 2018-10-15
*
* Used to test the the libs in combination
*/

#include "libcomponent.h"
#include "libresistance.h"
#include "libpower.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void print_resistor(float val);

int main (void) {
    float voltage;
    char  connection[200];
    int   component_count;
    
    float *components;
    float resistor;
    float e12_replace[NBR_E12_COMPONTENTS];
    
    printf("Ange spänningskälla i V: ");
    scanf("%f", &voltage);

    printf("Ange koppling[S | P]: ");
    scanf("%s", connection);
    connection[0] = toupper(connection[0]);


    printf("Antal komponenter: ");
    scanf("%d", &component_count);

    components = (float *) calloc(component_count, sizeof(float));
    if (components == NULL) {
	 printf("failed to allocate array of %d floats\n", component_count);
	 exit(-1);
    }
    
    for (int i = 0; i < component_count; i++) {
	 printf("Komponent %d i ohm: ", i+1);
	 scanf("%f.d", &components[i]);
    }

    resistor = calc_resistance(component_count, connection[0], components);
    printf("Ersättningsresistans:\n");
    printf("%.1f\n", resistor);

    free(components);
    
    printf("Effekt\n");
    printf("%.2f W\n", calc_power_r(voltage, resistor));

    component_count = e_resistance(resistor, e12_replace);
    printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");

    for (int i = 0; i < component_count; i++)
	 print_resistor(e12_replace[i]);
}

void print_resistor(float val)
{
     if (val < 1 )                  /* 0.10 - 0.82 ohm */
	  printf("%.2f\n", val);
     else if (val < 10 )            /* 1.0 - 8.2 ohm */
	  printf("%1.1f\n", val);
     else if (val < 10000 )         /* 10 - 8200 ohm */
	  printf("%.0f\n", val);
     else if (val < 100e3 )         /* 10e3 - 82e3 ohm */
	  printf("%2.0fe3\n", val/1e3);
     else  if (val < 1000e3)        /* 100e3 - 820e3 ohm */
	  printf("%3.0fe3\n", val/1e3);
     else  if (val < 10e6)         /* 1.0e6 - 8.2e6 ohm */
	  printf("%1.1fe6\n", val/1e6);
     else  if (val < 100e6)         /* 10e6 - 82e6 ohm */
	  printf("%2.0fe6\n", val/1e6);
     else  if (val < 1000e6)        /* 100e6 - 820e6 ohm */
	  printf("%3.0fe6\n", val/1e6);
     else  if (val < 10e9)         /* 1.0e9 - 8.2e9 ohm */
	  printf("%1.1fe9\n", val/1e9);
     else  if (val < 10e9)         /* 10e9 - 82e9 ohm */
	  printf("%2.0fe9\n", val/1e9);
     else                           /* very big */
	  printf("%6.1e\n", val);
}

/** Informal interaction format specification
Ange spänningskälla i V: 50
Ange koppling[S | P]: S
Antal komponenter: 3
Komponent 1 i ohm: 300
Komponent 2 i ohm: 500
Komponent 3 i ohm: 598
Ersättningsresistans:
1398,0 ohm
Effekt:
1.78 W
Ersättningsresistanser i E12-serien kopplade i serie:
1200
180
18
*/
