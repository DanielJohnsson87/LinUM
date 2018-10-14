#include <stdio.h>
#include <stdlib.h>
#include "calc_resistance.h"

/**
 * calc_resistance
 * Author: Daniel Johnsson
 * Date: 2018-10-14
 *
 * Calculates the resistance needed to replace an array of
 * components in a circut. This function handles both
 * parallel and series circuts.
 */
float calc_resistance(int count, char conn, float *array)
{
  float resistance = 0.0;

  if( array == 0)
    return -1;

  if(conn != 'S' && conn != 'P')
    return -1;

  if(conn == 'S')
    resistance = calc_resistance_s(count, conn, array);

  if(conn == 'P')
    resistance = calc_resistance_p(count, conn, array);

  return resistance;
}


/**
 * Calculate resistance for parallel circuts.
 */
float calc_resistance_p(int count, char conn, float *array)
{
  float resistance = 0.0;
  for(int i = 0; i < count; i++) {

    if(array[i] == 0.0 || array[i] == 0)
      return 0;

    resistance += (1/array[i]);
  }
  return (1/resistance);
}

/**
 * Calculate resistance for circuits in series.
 */
float calc_resistance_s(int count, char conn, float *array )
{
  float resistance = 0.0;
  for(int i = 0; i < count; i++) {
    resistance += array[i];
  }
  return resistance;
}

