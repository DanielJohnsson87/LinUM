
/**
* libpower.c
* Mårten Norman 2018-10-10
*
*  Returns the [heating] power in a resistor according to:
*  P = U * I
*  P = U^2 / R 
*
*  P: power
*  U: voltage over resistor
*  I: current through resistor
*  R: Resistance of resistor
*/

#include "libpower.h"
#include <float.h>

float
calc_power_r (float volt,
	      float resistance)
{
	if (resistance > 0.0f)
		return (volt*volt/resistance);
	else
		return FLT_MAX; /* Perfect shortcircuit with infinite power */
}

float
calc_power_i (float volt,
	      float current)
{
	return volt * current;
}
