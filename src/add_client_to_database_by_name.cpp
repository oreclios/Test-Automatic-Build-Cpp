/*
 * add_client_to_database.cpp
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

void add_client_to_database_by_name()
{
	Client new_client;
	Client last_client;

	std::string name;
	std::string surname1;
	std::string surname2;
	int count;
	int product;

	int rc;
	char *sql;
	char * sql_str = new char [200];
	char *zErrMsg = 0;
	sqlite3 * db;

	/*Se pregunta por los datos del cliente a añadir:*/
	std::cout << "Introduce el nombre del cliente:\n";
	std::cin >> name;
	std::cout << "Introduce el primer apellido del cliente:\n";
	std::cin >> surname1;
	std::cout << "Introduce el segundo apellido del cliente:\n";
	std::cin >> surname2;

	/*Se establece conexión con la BBDD:*/
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		std::cout << "No se ha podido abrir la BBDD.\n";
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	/*Obtencion de ID y CODE de último registro:*/
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
		new_client.index = 0;
		last_client.Code = "ZERO";
	}else{
		sql = "SELECT ID, CODE FROM CLIENTS_DETAILED WHERE ID = (SELECT MAX(ID) FROM CLIENTS_DETAILED);";
		rc = sqlite3_exec(db, sql, callback_last_id_code, &last_client, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}else{
			fprintf(stdout, "Datos de último registro obtenidos correctamente.\n");
		}
		new_client.index = last_client.index + 1;
	}

	/*Obtenemos el producto contratado de forma aleatoria:*/
	sql = "SELECT ID FROM CODE_PRODUCTS ORDER BY RANDOM() LIMIT 1;";
	rc = sqlite3_exec(db, sql, callback_get_random_product, &product, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Dato obtenido correctamente.\n");
	}
	std::cout << "Producto obtenido: " << product << "\n";
	new_client.product=product;

	/*Rellenamos los datos del nuevo cliente:*/
	new_client.Name = name;
	new_client.Surname1 = surname1;
	new_client.Surname2 = surname2;
	get_next_code(last_client.Code, new_client.Code);
	new_client.date_contr = time(0);

	/*Añadimos el nuevo cliente a la BBDD:*/
	sprintf(sql_str, "INSERT INTO CLIENTS_DETAILED(ID, NAME, SURNAME1, SURNAME2, CODE, PRODUCT, DATE) "
				"VALUES (%d, \"%s\", \"%s\", \"%s\", \"%s\", %d, %d);",
				new_client.index, new_client.Name.c_str(), new_client.Surname1.c_str(),
				new_client.Surname2.c_str(), new_client.Code.c_str(), new_client.product,
				(int)new_client.date_contr);
	sql = sql_str;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    	sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
}

void add_client_to_database_by_name(Client new_client)
{
	Client last_client;

	int count;
	int rc;
	char *sql;
	char * sql_str = new char [200];
	char *zErrMsg = 0;
	sqlite3 * db;

	/*Se establece conexión con la BBDD:*/
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		std::cout << "No se ha podido abrir la BBDD.\n";
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	/*Obtencion de ID y CODE de último registro:*/
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
		new_client.index = 0;
		last_client.Code = "ZERO";
	}else{
		sql = "SELECT ID, CODE FROM CLIENTS_DETAILED WHERE ID = (SELECT MAX(ID) FROM CLIENTS_DETAILED);";
		rc = sqlite3_exec(db, sql, callback_last_id_code, &last_client, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}else{
			fprintf(stdout, "Datos de último registro obtenidos correctamente.\n");
		}
		new_client.index = last_client.index + 1;
	}

	/*Rellenamos los datos del nuevo cliente:*/
	get_next_code(last_client.Code, new_client.Code);
	new_client.date_contr = time(0);

	/*Añadimos el nuevo cliente a la BBDD:*/
	sprintf(sql_str, "INSERT INTO CLIENTS_DETAILED(ID, NAME, SURNAME1, SURNAME2, CODE, PRODUCT, DATE) "
				"VALUES (%d, \"%s\", \"%s\", \"%s\", \"%s\", %d, %d);",
				new_client.index, new_client.Name.c_str(), new_client.Surname1.c_str(),
				new_client.Surname2.c_str(), new_client.Code.c_str(), new_client.product,
				(int)new_client.date_contr);
	sql = sql_str;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	    	sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);
}


