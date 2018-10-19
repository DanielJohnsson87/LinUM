/**
* Filename: libcomponent.c
* Auther: Thomas Johansson
* Date: 2018-10-09
* 
* Calculates witch 3 resistors from E12 series that coresponds
* to a given resistance value
*/

#include "libcomponent.h"
#include <stdio.h>


#define NBR_E12_DECADES 10

const float E12_BASE_VALUES[] = {0.1, 0.12, 0.15, 0.18, 0.22, 0.27, 0.33,
    0.47, 0.56, 0.68, 0.82};

void generate_e12_series(float e12_serie[], int size);


/**
 * Generates all resistor values in e12 series from 0.1 Ohm to 820 MOhm
 */
void generate_e12_series(float e12_serie[], int size){
    int factor = 1;
    int series_multiple = 10;

    int e12_base_index = 0;
    int nbr_elements = sizeof(E12_BASE_VALUES) / sizeof(float);

    for (int i = 0; i < size; i++){
        if (i > 0 && i % nbr_elements == 0) {
            factor *= series_multiple;
            e12_base_index = 0;
        }

        e12_serie[i] = factor * E12_BASE_VALUES[e12_base_index];
        e12_base_index++;
    }
}

/**
 * Calaculates which three serial conencted resistors in E12 series that corresponds
 * to the orgin_resistance and adds them to res_array
 * Usued resistors in res_array is set to 0
 * Returns the number of E12 resistors (0-3)
 * Returns -1 if orgin_resistance is negativ or res_array is a null pointer
 */
int e_resistance(float orgin_resistance, float* res_array){

    if (orgin_resistance < 0 || res_array == NULL)
        return -1;

    int count = 0;
    int nbr_elements = sizeof(E12_BASE_VALUES) / sizeof(float);

    float e12_series[nbr_elements * NBR_E12_DECADES];
    
    int e12_size = sizeof(e12_series) / sizeof(float);
    generate_e12_series(e12_series, e12_size);
   
    float curr_res_value = orgin_resistance;
           
    for (int i = e12_size -1; i >= 0 ; i--){
        
        if (curr_res_value >= e12_series[i]){
            curr_res_value = curr_res_value - e12_series[i];

            if (count < NBR_E12_COMPONTENTS){
                *(res_array+count) = e12_series[i];
                count++;
            }  
        }
    }

    // set unused components values to zero
    for (int i = count; i < NBR_E12_COMPONTENTS; i++){
        *(res_array + i) = 0;
    }

    return count;
}