/*
 * test_project1_v2.cpp
 *
 *  Created on: 17 ene. 2017
 *      Author: mvelascoj
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <list>
#include <fstream>

#include "global.h"

typedef std::list<Client> ClientList;

int main()
{
	int index;
	Client new_client;
	ClientList myClients;
	std::ofstream ClientsFile;
	std::string nombre;
	std::stringstream index_strs;
	std::string index_str;

	/*Añadimos una lista enorme de clientes:*/
	for(index=0; index < 2501; index++)
	{
		index_strs << index + 1;
		index_str = index_strs.str();
		nombre = "Prueba " + index_str;
		create_new_client(myClients, new_client, nombre, index);
		myClients.push_back(new_client);
		index_strs.str("");
	}

	/*Comprobamos lo que hemos insertado:*/
	std::cout << "Añadidos " << index << " clientes.\n";

	/*Volcar el contenido de la lista de clientes a un fichero:*/
	ClientsFile.open("clients.txt");
	for(ClientList::iterator ci = myClients.begin(); ci != myClients.end(); ci++)
	{
		ClientsFile << "\nCliente número " << ci->index << "\r\n";
		ClientsFile << "Nombre: " << ci->Name << "\r\n";
		ClientsFile << "Código de Cliente: " << ci->Code << "\r\n";
		ClientsFile << "Fecha de contratación: " << ctime(&ci->date_contr) << "\r\n" << "\r\n";
	}
	ClientsFile.close();

	return 0;
}



