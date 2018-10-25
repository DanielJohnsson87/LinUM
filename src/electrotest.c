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
#include <string.h>
#define BUFFERLENGHT 100

int read_input(char *input, int lenght, char* promt_msg);
void print_resistor(float val);

int main (void) {
    float voltage;
    char  connection;
    int   component_count;

    char input[BUFFERLENGHT];
    char* error_msg = "Felaktig inmatning\n";
    
    float *components;
    float resistor;
    float e12_replace[NBR_E12_COMPONTENTS];
    
    
    int correct_input = 0;
    
    // Read in voltage  
    while (correct_input == 0){
        if(read_input(input, sizeof(input)/sizeof(char), "Ange spänningskälla i V: ")){
            correct_input = sscanf(input, "%f", &voltage);
            if (correct_input == 0){
                printf("%s", error_msg);
            }
        }
        else{
            printf("%s", error_msg);
        }    
    }

    correct_input = 0;
    // Read connection type
    while (correct_input == 0){
        if (read_input(input, sizeof(input)/sizeof(char), "Ange koppling[S | P]: ")){
            correct_input = sscanf(&input[0], "%c", &connection);
            
            if (correct_input == 0){
                printf("%s", error_msg);
            }
            else{
                if (toupper(connection) != 'S' && toupper(connection) != 'P'){
                    correct_input = 0;
                    input[strcspn(input, "\n")] = 0; // trim newline
                    printf("Felaktig angiven koppling. Du angav\n%s"
                            "\ninmating skall vara S eller P\n", input);
                }
            }
        }
        else{
            printf("%s", error_msg);
        }   
    }
    
    // Read number of components
    correct_input = 0;
    while (correct_input == 0){
        if(read_input(input, sizeof(input)/sizeof(char), "Antal komponenter: ")){
            correct_input = sscanf(input, "%d", &component_count);
            if (correct_input == 0){
                printf("%s", error_msg);
            }
        }
        else{
            printf("%s", error_msg);
        }    
    }

    components = (float *) calloc(component_count, sizeof(float));
    
    if (components == NULL) {
	 printf("failed to allocate array of %d floats\n", component_count);
	 exit(-1);
    }
    
    // Read all resistor values
    char promt[50];

    for (int i = 0; i < component_count; i++) {
        sprintf(promt,"Komponent %d i ohm: ", i+1);
        correct_input = 0;
        while (correct_input == 0){
            if(read_input(input, sizeof(input)/sizeof(char), promt)){
                correct_input = sscanf(input, "%f.d", &components[i]);
                if (correct_input == 0){
                    printf("%s", error_msg);
                }
            }
            else{
                printf("%s", error_msg);
            }
        }    
    }
	

    resistor = calc_resistance(component_count, connection, components);
    
    if (resistor == -1){
        fprintf(stderr, "calc_resistance kan ej utföra beräkning\n");
        exit(-1);  
    }
    else{
        printf("Ersättningsresistans:\n");
        printf("%.1f\n", resistor);
    }
    
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

/**
 * Prints a promt with name promt_msg and reads lenght number of charaters
 * into the string input from stdin. If the stdin contais more charaters than lenght
 * it clears all charaters left in stdin and returns 0;
 * Return 1 on succes and 0 if it could not read all charaters from stdin
 */ 

int read_input(char *input, int lenght, char* promt_msg){
    printf("%s", promt_msg);

    if (fgets(input, lenght, stdin)){
        
        if (strchr(input, '\n')){
            return 1;
        }
        else{
            while (!strchr(input, '\n') && fgets(input, lenght, stdin));
        }
    }

    return 0;
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
