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

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

static int callback_count(void *VeryUsed, int argc, char **argv, char **azColName){
	int * count = (int *)VeryUsed;
	*count = atoi(argv[0]);
	return 0;
}

static int callback_last_id(void *VeryUsed, int argc, char **argv, char **azColName){
	int * indice = (int *)VeryUsed;
	*indice = atoi(argv[0]);
	return 0;
}

static int callback_select(void *VeryUsed, int argc, char **argv, char **azColName){
	int i;
	int indice;
	long int date_num;
	std::string nombre;
	Client new_client;

	ClientList * newClient = (ClientList *)VeryUsed;

	for(i=0; i<argc; i++)
	{
		if(!strcmp(azColName[i],"ID"))
		{
			new_client.index = atoi(argv[i]);
		}
		else if(!strcmp(azColName[i],"NAME"))
		{
			new_client.Name = argv[i];
		}
		else if(!strcmp(azColName[i],"CODE"))
		{
			new_client.Code = argv[i];
		}
		else if(!strcmp(azColName[i],"DATE"))
		{
			new_client.date_contr = atoi(argv[i]);
		}
	}
	newClient->push_back(new_client);

	return 0;
}

int main()
{
	int i;
	int index;
	int count;
	int first;
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
	    return(0);
	}else{
		std::cout << "BBDD abierta correctamente.\n";
	}

	/*Create SQL statement*/
	sql = "CREATE TABLE IF NOT EXISTS CLIENTS("  \
	      "ID  INT PRIMARY KEY     NOT NULL," \
	      "NAME   TEXT			      NOT NULL," \
	      "CODE   CHAR(5)		      NOT NULL," \
	      "DATE   INT);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
	fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   sqlite3_free(zErrMsg);
	}else{
	   fprintf(stdout, "Tabla creada correctamente.\n");
	}

	/*Obtenemos el ultimo ID de la tabla:*/
	/*Primero comprobamos si hay info. en la tabla:*/
	sql = "SELECT COUNT(*) FROM CLIENTS;";
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
		sql = "SELECT ID FROM CLIENTS WHERE " \
				"ID = (SELECT MAX(ID) FROM CLIENTS);";
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
	for(i=index; i<index + 1000; i++)
	{
		index_strs << i;
		index_str = index_strs.str();
		nombre = "Prueba " + index_str;
		create_new_client(myClients, new_client, nombre, i, count, db);
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
		ClientsFile << "Código de Cliente: " << ci->Code << "\r\n";
		ClientsFile << "Fecha de contratación: " << ctime(&ci->date_contr) << "\r\n" << "\r\n";
	}
	ClientsFile.close();

	/*Añadimos la información a la BBDD:*/
	for(ClientList::iterator ci = myClients.begin(); ci != myClients.end(); ci++)
	{
		sprintf(sql_str, "INSERT INTO CLIENTS(ID, NAME, CODE, DATE) "
					"VALUES (%d, \"%s\", \"%s\", %d);",
					ci->index, ci->Name.c_str(), ci->Code.c_str(), (int)ci->date_contr);
		sql = sql_str;
		rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		    	sqlite3_free(zErrMsg);
		}else{
			fprintf(stdout, "Client %s added successfully\n", ci->Code.c_str());
		}
	}

	/*Recuperamos registros que cumplan una caracteristica y los copiamos a fichero:*/
	sprintf(sql_str, "SELECT * FROM CLIENTS WHERE "
						"ID BETWEEN %d AND %d;",
						0, 10);
	sql = sql_str;
	rc = sqlite3_exec(db, sql, callback_select, &newClients, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	   	sqlite3_free(zErrMsg);
	}else{
		fprintf(stdout, "Registros recuperados correctamente.\n");
	}

	/*Volcamos los clientes recuperados a fichero:*/
	ClientsFile.open("clientes_recuperados.txt");
	for(ClientList::iterator ci = newClients.begin(); ci != newClients.end(); ci++)
	{
		ClientsFile << "\nCliente número " << ci->index << "\r\n";
		ClientsFile << "Nombre: " << ci->Name << "\r\n";
		ClientsFile << "Código de Cliente: " << ci->Code << "\r\n";
		ClientsFile << "Fecha de contratación: " << ctime(&ci->date_contr) << "\r\n" << "\r\n";
	}
	ClientsFile.close();

	/*Cerramos la conexión con la BBDD:*/
	sqlite3_close(db);

	return 0;
}



