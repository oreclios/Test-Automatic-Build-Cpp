/*
 * add_random_clients.cpp
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

void add_random_clients(int quantity)
{
	Client new_client;
	std::string name;
	std::string surname1;
	std::string surname2;
	int product;

	char *sql;
	char *zErrMsg = 0;
	sqlite3 *db;
	int rc;

	/*Establecemos conexión con la BBDD:*/
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		std::cout << "No se ha podido abrir la BBDD.\n";
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	for(int i=0; i<quantity; i++){
		/*Generamos nombre aleatorio:*/
		/*Seleccionamos nombre aleatorio de la BBDD:*/
		sql = "SELECT NAME FROM NAMES ORDER BY RANDOM() LIMIT 1;";
		rc = sqlite3_exec(db, sql, callback_get_random_name, &name, &zErrMsg);
		if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   sqlite3_free(zErrMsg);
		}else{
		   fprintf(stdout, "Dato obtenido correctamente.\n");
		}
		std::cout << "Nombre obtenido: " << name << "\n";

		std::cout << "Initial: " << name << "\n";

		/*Seleccionamos apellido aleatorio de BBDD:*/
		sql = "SELECT SURNAME FROM SURNAMES ORDER BY RANDOM() LIMIT 1;";
		rc = sqlite3_exec(db, sql, callback_get_random_surname, &surname1, &zErrMsg);
		if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   sqlite3_free(zErrMsg);
		}else{
		   fprintf(stdout, "Dato obtenido correctamente.\n");
		}
		std::cout << "1er Apellido obtenido: " << surname1 << "\n";

		rc = sqlite3_exec(db, sql, callback_get_random_surname, &surname2, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}else{
		   fprintf(stdout, "Dato obtenido correctamente.\n");
		}
		std::cout << "2do Apellido obtenido: " << surname2 << "\n";

		/*Componemos el nombre creado:*/
		new_client.Name = name;
		new_client.Surname1 = surname1;
		new_client.Surname2 = surname2;

		/*Elegimos aleatoriamente el producto contratado:*/
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

		/*Añadimos cliente a la base de datos:*/
		add_client_to_database_by_name(new_client);
	}

	/*Cerramos la conexión con la BBDD:*/
	sqlite3_close(db);
}



