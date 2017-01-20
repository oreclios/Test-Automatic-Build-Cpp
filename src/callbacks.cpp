/*
 * callbacks.cpp
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

int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int callback_get_random_surname(void *VeryUsed, int argc, char **argv, char **azColName){
	std::string * surname = (std::string *)VeryUsed;
	*surname = argv[0];
	return 0;
}

int callback_get_random_name(void *VeryUsed, int argc, char **argv, char **azColName){
	std::string * name = (std::string *)VeryUsed;
	*name = argv[0];
	return 0;
}

int callback_get_random_product(void *VeryUsed, int argc, char **argv, char **azColName){
	int * product = (int *)VeryUsed;
	*product = atoi(argv[0]);
	return 0;
}

int callback_last_id_code(void *VeryUsed, int argc, char **argv, char **azColName){
	Client * client = (Client *)VeryUsed;
	client->index = atoi(argv[0]);
	client->Code = argv[1];
	return 0;
}

int callback_count(void *VeryUsed, int argc, char **argv, char **azColName){
	int * count = (int *)VeryUsed;
	*count = atoi(argv[0]);
	return 0;
}

int callback_last_id(void *VeryUsed, int argc, char **argv, char **azColName){
	int * indice = (int *)VeryUsed;
	*indice = atoi(argv[0]);
	return 0;
}

int callback_check_exists(void *VeryUsed, int argc, char **argv, char **azColName){
	int * check = (int *)VeryUsed;
	*check = 1;
	return 0;
}

int callback_last_code(void *VeryUsed, int argc, char **argv, char **azColName){
	std::string * last_code = (std::string *)VeryUsed;
	*last_code = argv[0];
	return 0;
}

