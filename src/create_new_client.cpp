/*
 * create_new_client.cpp
 *
 *  Created on: 18 ene. 2017
 *      Author: mvelascoj
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "global.h"

void create_new_client(std::list<Client> & ClientList, Client & client, std::string name, int index)
{
	std::string new_code;
	std::string last_code;

	client.Name = name;
	client.index = index;
	if(ClientList.empty())
	{
		last_code = "ZERO";
	}
	else
	{
		last_code = ClientList.back().Code;
	}
	get_next_code(last_code, new_code);
	client.Code = new_code;
	client.date_contr = time(0);
}



