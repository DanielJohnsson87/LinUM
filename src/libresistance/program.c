#include <stdio.h>
#include "calc_resistance.h"
int main() {	
	int count = 3;
	float array[(sizeof(float)*3)];
	char conn;
	float resistance = 0.0;
	
	printf("Is the circut in series or parallel? [S | P]: ");
	scanf("%c", &conn);

	printf("Resistance 1: ");
	scanf("%f",&array[0]);
	printf("Resistance 2: ");
	scanf("%f",&array[1]);
	printf("Resistance 3: ");
	scanf("%f",&array[2]);

	printf("\nResistance \t  Value \n");
	for(int i = 0; i < count; i++) {
		printf("Resistance %d \t  %f \t \n", i,array[i]);
	}

	resistance = calc_resistance(count, conn, array);
	printf("Connection is %c \n",conn);
	printf("Resistance is %f \n", resistance);
	return 0;
}

