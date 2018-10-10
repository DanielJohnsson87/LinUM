#include <stdio.h>
#include <stdlib.h>
#include "calc_resistance.h"

float calc_resistance(int count, char conn, float *array) {
	float resistance = 0.0;
	debug_function(count, conn, array);

	if( array == 0) {
		return -1;
	}
	
	if(conn != 'S' && conn != 'P') {
		printf("Wrong connection supplied. You passed %c, value should be either S or P", conn);
		return -1;
	}
	
	if(conn == 'S') {
		resistance = calc_resistance_s(count, conn, array);
		printf("Connection is S. Resistance is %f \n\n", resistance);
	}
	
	if(conn == 'P') {
		resistance = calc_resistance_p(count, conn, array);
		printf("Connection is P. Resistance is %f \n\n", resistance);
	}

	return resistance;
}


float calc_resistance_p(int count, char conn, float *array) {
	float resistance = 0.0;
	for(int i = 0; i < count; i++) {
		
		if(array[i] == 0) {
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


void debug_function(int count, char conn, float *array) {
	printf("count \t conn \n");
	printf("%d \t %c \n", count, conn);

	printf("\narray contents\nIndex \t\t Value \t\tAdress \n");
	for(int i = 0; i < count; i++) {
		printf("array[%d] \t  %f \t %p \n", i,array[i], &array[i]);
	}

	printf("\n----------------\n");

}


