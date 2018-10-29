#include <stdio.h>
#include <stdlib.h>
#include "libresistance.h"
int main()
{
  int count;
  //float array[(sizeof(float)*3)];
  char conn;
  float resistance = 0.0;

  printf("How many resistors?: ");
  scanf("%d", &count);

  float * array = malloc(count * sizeof(float));

  for(int i = 0; i < count; i++)
  {
    printf("Value resistor %d: ", i);
    scanf("%f", &array[i]);
  }

  printf("Series or parallel circut? Answer: S or P: ");
  scanf(" %c", &conn);

  resistance = calc_resistance(count, conn, array);

  printf("\nResistance \t  Value \n");
  for(int i = 0; i < count; i++) {
    printf("Resistance %d \t  %f \t \n", i,array[i]);
  }

  printf("Connection is %c \n",conn);
  printf("Resistance is %f \n", resistance);
  free(array);
  return 0;
}

