/**
* Filename: libresistance.c
* Author: Daniel Johnsson
* Date: 2018-10-23
*
* Calculates the minimum resistance needed to replace N resistors
* in parallel or in series.
*
* Series circuit
* R = R1 + R2 ... R3
*
* Parallel circuit
* R = 1 / ( 1/R1 + 1/R2 ... + 1/R3 )
*
* int count: Number of resistors in circuit
* char conn: Type of circuit S or P for series or parallel
* float *array: Values from the resistors to be replaced
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "libresistance.h"

float calc_resistance_p(int count, char conn, float *array);

float calc_resistance_s(int count, char conn, float *array);

float calc_resistance(int count, char conn, float *array) {
	float resistance = 0.0;

	char orginal_conn = conn;
	conn = toupper(conn);

	if( array == 0) {
		return -1;
	}
	
	if(conn != 'S' && conn != 'P') {
		return -1;
	}
	
	if(conn == 'S') {
		resistance = calc_resistance_s(count, conn, array);
	}
	
	if(conn == 'P') {
		resistance = calc_resistance_p(count, conn, array);
	}
	
	return resistance;
}


float calc_resistance_p(int count, char conn, float *array) {
	float resistance = 0.0;
	for(int i = 0; i < count; i++) {
		
		if(array[i] == 0.0 || array[i] == 0) {
			return 0;
		}
		
		resistance += (1/array[i]);
	}		
	return (1/resistance);
}

float calc_resistance_s(int count, char conn, float *array ) {
	float resistance = 0.0;
	for(int i = 0; i < count; i++) {
		resistance += array[i]; 
	}
	return resistance;
}

