/*
 * get_next_day.cpp
 *
 *  Created on: 17 ene. 2017
 *      Author: mvelascoj
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <ctime>

#include "global.h"

void get_next_day(time_t *now, time_t *tomorrow)
{
	*tomorrow = *now + 86400;
}
