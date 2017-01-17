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

void get_next_day()
{
	time_t now;
	time_t tomorrow;
	char* tomorrow_date;

	now = time(0);
	tomorrow = now + 86400;
	tomorrow_date = ctime(&tomorrow);

	std::cout << "Tomorrow will be: " << tomorrow_date << std::endl;
}
