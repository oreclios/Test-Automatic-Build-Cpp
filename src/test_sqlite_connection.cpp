/*
 * test_sqlite_connection.cpp
 *
 *  Created on: 19 ene. 2017
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

void test_sqlite_connection(int num_clients)
{
	int i;
	int index;
	int count;
	int first;
	int rlow, rhigh;

	Client new_client;
	ClientList myClients;
	ClientList newClients;
	std::ofstream ClientsFile;
	std::string nombre;
	std::stringstream index_strs;
	std::string index_str;

	char * sql_str = new char [200];
	char *sql;
	char *zErrMsg = 0;
	sqlite3 *db;
	int rc;
	int indice;

	/*Create and open the database file:*/
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		std::cout << "No se ha podido abrir la BBDD.\n";
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	/*Obtenemos el ultimo ID de la tabla:*/
	/*Primero comprobamos si hay info. en la tabla:*/
	sql = "SELECT COUNT(*) FROM CLIENTS_DETAILED;";
	rc = sqlite3_exec(db, sql, callback_count, &count, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   	sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Tamaño de la tabla obtenido correctamente: %d. \n", count);
	}

	if(count == 0){
		index = 0;
	}else{
		sql = "SELECT ID FROM CLIENTS_DETAILED WHERE " \
				"ID = (SELECT MAX(ID) FROM CLIENTS_DETAILED);";
		rc = sqlite3_exec(db, sql, callback_last_id, &index, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   	sqlite3_free(zErrMsg);
		}else{
			fprintf(stdout, "Último índice recuperado correctamente: %d \n", index);
		}
		index = index + 1;
	}

	/*Añadimos una lista de clientes:*/
	count = 0;
	for(i=index; i<index + num_clients; i++)
	{
		index_strs << i;
		index_str = index_strs.str();
		nombre = "Prueba " + index_str;
		create_new_client(myClients, new_client, nombre, i, count, db);
		new_client.product = 1;
		myClients.push_back(new_client);
		index_strs.str("");
		count ++;
	}

	/*Volcar el contenido de la lista de clientes a un fichero:*/
	ClientsFile.open("clients.txt");
	for(ClientList::iterator ci = myClients.begin(); ci != myClients.end(); ci++)
	{
		ClientsFile << "\nCliente número " << ci->index << "\r\n";
		ClientsFile << "Nombre: " << ci->Name << "\r\n";
		ClientsFile << "1er Apellido: " << ci->Surname1 << "\r\n";
		ClientsFile << "2do Apellido: " << ci->Surname2 << "\r\n";
		ClientsFile << "Código de Cliente: " << ci->Code << "\r\n";
		ClientsFile << "Producto contratado: " << ci->product << "\r\n";
		ClientsFile << "Fecha de contratación: " << ctime(&ci->date_contr) << "\r\n" << "\r\n";
	}
	ClientsFile.close();

	/*Añadimos la información a la BBDD:*/
	for(ClientList::iterator ci = myClients.begin(); ci != myClients.end(); ci++)
	{
		sprintf(sql_str, "INSERT INTO CLIENTS_DETAILED(ID, NAME, SURNAME1, SURNAME2, CODE, PRODUCT, DATE) "
					"VALUES (%d, \"%s\", \"%s\", \"%s\", \"%s\", %d, %d);",
					ci->index, ci->Name.c_str(), ci->Surname1.c_str(),
					ci->Surname2.c_str(), ci->Code.c_str(), ci->product, (int)ci->date_contr);
		sql = sql_str;
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		    	sqlite3_free(zErrMsg);
		}
	}

	/*Cerramos la conexión con la BBDD:*/
	sqlite3_close(db);
}







