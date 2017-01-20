/*
 * add_names.cpp
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

void add_names()
{
	std::ifstream file("names_list.txt");
	std::string line;
	std::string name;
	int id;
	int check = 0;

	char * sql_str = new char [200];
	char *sql;
	char *zErrMsg = 0;
	sqlite3 *db;
	int rc;

	/*Abrimos conexion con BBDD:*/
	rc = sqlite3_open("test.db", &db);
	if( rc ){
		std::cout << "No se ha podido abrir la BBDD.\n";
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	/*Creamos la BBDD si no existe:*/
	sql = "CREATE TABLE IF NOT EXISTS NAMES("  \
	      "ID  INT PRIMARY KEY     NOT NULL," \
	      "NAME   TEXT		   NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
	}else{
	   fprintf(stdout, "Tabla creada correctamente.\n");
	}

	/*Abrimos el fichero dónde están los apellidos:*/
	if(file){
		while(getline(file, line)){
			name = line;

			/*Obtenemos último ID de la tabla:*/
			sql = "SELECT ID FROM NAMES WHERE " \
					"ID = (SELECT MAX(ID) FROM NAMES);";
			rc = sqlite3_exec(db, sql, callback_last_id, &id, &zErrMsg);
			if( rc != SQLITE_OK ){
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			   	sqlite3_free(zErrMsg);
			}else{
				fprintf(stdout, "Último índice recuperado correctamente: %d \n", id);
			}
			id = id + 1;

			/*Comprobamos que el nombre no está incluido en la tabla:*/
			check = 0;
			sprintf(sql_str, "SELECT NAME FROM NAMES WHERE NAME LIKE '%%%s%%';",name.c_str());
			sql=sql_str;
			std::cout << "Sentencia SQL:\n" << sql << "\n";
			rc = sqlite3_exec(db, sql, callback_check_exists, &check, &zErrMsg);
			if( rc != SQLITE_OK ){
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
			   sqlite3_free(zErrMsg);
			}else{
			   fprintf(stdout, "Comprobado correctamente.\n");
			}

			if(check == 0){
				/*Agregamos cada apellido encontrado a la BBDD:*/
				sprintf(sql_str, "INSERT INTO NAMES (ID, NAME) "
						"VALUES(%d, \"%s\");", id, name.c_str());
				sql = sql_str;

				std::cout << "Sentencia SQL:\n" << sql << "\n";

				rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
				if( rc != SQLITE_OK ){
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}else{
					fprintf(stdout, "Datos introducidos correctamente.\n");
				}
			}
		}
	}

	sqlite3_close(db);

}







