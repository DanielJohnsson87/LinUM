/**
* Filename: electrotest.c
* Author: Mårten Norman
* Date: 2018-10-15
*
* Used to test the the libs in combination
*/

/* Informal interaction format specification
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




#include "libcomponent.h"
#include "libresistance.h"
#include "libpower.h"

#include <stdio.h>
#include <ctype.h>

int main (void) {
    float voltage;
    char  connection[200];
    int   component_count;
    int   i;
    float components[200];
    float resistor;
    float e12_replace[NBR_COMPONTENTS];
    
    printf("Ange spänningskälla i V: ");
    scanf("%f", &voltage);

    printf("Ange koppling[S | P]: ");
    scanf("%s", connection);
    connection[0] = toupper(connection[0]);


    printf("Antal komponenter: ");
    scanf("%d", &component_count);

    for (i = 0; i < component_count; i++) {
	 printf("Komponent %d i ohm: ", i+1);
	 scanf("%f.d", &components[i]);
    }

    resistor = calc_resistance(component_count, connection[0], components);
    printf("Ersättningsresistans:\n %-.1f ohm\n", resistor);

    printf("Effekt\n");
    printf("%.2f W\n", calc_power_r(voltage, resistor));

    e_resistance(resistor, e12_replace);
    printf("Ersättningsresistanser i E12-serien kopplade i serie:\n");
    for (int i = 0; i < NBR_COMPONTENTS; i++) {
        printf("%.0f\n ", e12_replace[i]);
    }

}
