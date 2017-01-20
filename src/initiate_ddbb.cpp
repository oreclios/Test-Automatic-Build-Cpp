/*
 * initiate_ddbb.cpp
 *
 *  Created on: 20 ene. 2017
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

void initiate_ddbb()
{
	int count;
	char *sql;
	char *zErrMsg = 0;
	sqlite3 *db;
	int rc;

	/*Inicializamos las tablas de nombres y apellido:*/
	add_surnames();
	add_names();

	/*CREACION TABLA DE PRODUCTOS:*/
	/*Establecemos conexi�n con la BBDD:*/
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		std::cout << "No se ha podido abrir la BBDD.\n";
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	/*Creamos si no esta creada la tabla:*/
	sql = "CREATE TABLE IF NOT EXISTS CODE_PRODUCTS("  \
	      "ID  INT PRIMARY KEY     NOT NULL," \
	      "DESCRIPTION   TEXT	   NOT NULL);";
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Tabla creada correctamente.\n");
	}

	/*A�adimos la lista de servicios posibles si se ha creado la tabla por primera vez:*/
	/*Primero chequeamos que la tabla est� vac�a:*/
	sql = "SELECT COUNT(*) FROM CODE_PRODUCTS;";
	rc = sqlite3_exec(db, sql, callback_count, &count, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   	sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Tama�o de la tabla obtenido correctamente: %d. \n", count);
	}

	if(count==0){
		sql = "INSERT INTO CODE_PRODUCTS (ID, DESCRIPTION) VALUES (1, \"Linea Basica\");" \
				"INSERT INTO CODE_PRODUCTS (ID, DESCRIPTION) VALUES (2, \"Linea M�vil\");" \
				"INSERT INTO CODE_PRODUCTS (ID, DESCRIPTION) VALUES (3, \"Linea Completa\");" \
				"INSERT INTO CODE_PRODUCTS (ID, DESCRIPTION) VALUES (4, \"Fibra 50\");" \
				"INSERT INTO CODE_PRODUCTS (ID, DESCRIPTION) VALUES (5, \"Fibra 300\");" \
				"INSERT INTO CODE_PRODUCTS (ID, DESCRIPTION) VALUES (6, \"Fibra 500\");";
		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}else{
			fprintf(stdout, "Informacion de productos a�adida correctamente.\n");
		}
	}

	/*CREACION DE LA TABLA DE CLIENTES:*/
	/*Creamos si no esta creada la tabla:*/
	sql = "CREATE TABLE IF NOT EXISTS CLIENTS_DETAILED("  \
	      "ID  INT PRIMARY KEY     NOT NULL," \
	      "NAME   TEXT			      NOT NULL," \
	      "SURNAME1		TEXT	NOT NULL," \
		  "SURNAME2		TEXT	NOT NULL," \
		  "CODE   CHAR(5)		      NOT NULL," \
		  "PRODUCT   INT		      NOT NULL," \
	      "DATE   INT," \
		  "FOREIGN KEY(PRODUCT) REFERENCES CODE_PRODUCTS(ID));";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
	}else{
	   fprintf(stdout, "Tabla creada correctamente.\n");
	}

	/*Cerramos la conexi�n con la BBDD:*/
	sqlite3_close(db);

}




