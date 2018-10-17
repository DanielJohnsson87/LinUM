#include <stdio.h>
#include <stdlib.h>
#include "electrotest.h"

float calc_resistance_p(int count, char conn, float *array);

float calc_resistance_s(int count, char conn, float *array);

float calc_resistance(int count, char conn, float *array) {
	float resistance = 0.0;

	if( array == 0) {
		return -1;
	}
	
	if(conn != 'S' && conn != 'P') {
		printf("Wrong connection supplied. You passed %c, value should be either S or P", conn);
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

