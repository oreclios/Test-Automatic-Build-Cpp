/*
 * global.h
 *
 *  Created on: 16 ene. 2017
 *      Author: mvelascoj
 */
#include "Client.h"
#include <list>

void prueba1();

void get_next_code(std::string cod_cliente, std::string & new_code);
void reset_seq(std::string cod_client, double reset_val, std::string & new_cod);
void create_new_client(std::list<Client> & ClientList, Client & client, std::string name, int index);
