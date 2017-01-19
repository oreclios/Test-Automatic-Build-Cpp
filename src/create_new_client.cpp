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
#include <fstream>

#include "global.h"

static int callback_last_code(void *VeryUsed, int argc, char **argv, char **azColName){
	std::string * last_code = (std::string *)VeryUsed;
	*last_code = argv[0];
	return 0;
}

void create_new_client(std::list<Client> & ClientList, Client & client, std::string name, int index, int count, sqlite3 * db)
{
	std::string new_code;
	std::string last_code;

	char * sql_str = new char [200];
	char *sql;
	char *zErrMsg = 0;
	int rc;

	client.Name = name;
	client.index = index;
	if(index == 0)
	{
		last_code = "ZERO";
	}
	else if(index != 0 && count != 0)
	{
		last_code = ClientList.back().Code;
	}
	else if(index != 0 && count == 0)
	{
		/*Obtener ultimo codigo de BBDD:*/
		sprintf(sql_str, "SELECT CODE FROM CLIENTS WHERE ID = %d;",index-1);
		sql = sql_str;
		rc = sqlite3_exec(db, sql, callback_last_code, &last_code, &zErrMsg);
		if( rc != SQLITE_OK ){
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
		   	sqlite3_free(zErrMsg);
		}else{
			fprintf(stdout, "Last code obtained correctly: %s \n", last_code.c_str());
		}

	}
	get_next_code(last_code, new_code);
	client.Code = new_code;
	client.date_contr = (long int)time(0);
}



