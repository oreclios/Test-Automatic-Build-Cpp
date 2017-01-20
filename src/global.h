/*
 * global.h
 *
 *  Created on: 16 ene. 2017
 *      Author: mvelascoj
 */
#include "Client.h"
#include "sqlite3.h"

#include <list>

void prueba1();

void get_next_code(std::string cod_cliente, std::string & new_code);
void reset_seq(std::string cod_client, double reset_val, std::string & new_cod);
void create_new_client(std::list<Client> & ClientList, Client & client, std::string name, int index, int count, sqlite3 * db);
void test_sqlite_connection(int num_clients);
void add_client_to_database_by_name();
void add_client_to_database_by_name(Client new_client);
void add_random_clients(int quantity);
void add_surnames();
void add_names();
void show_options(int & option);
void initiate_ddbb();

int callback(void *NotUsed, int argc, char **argv, char **azColName);
int callback_get_random_surname(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_get_random_name(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_get_random_product(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_last_id_code(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_count(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_last_id(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_check_exists(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_last_code(void *VeryUsed, int argc, char **argv, char **azColName);
int callback_select(void *VeryUsed, int argc, char **argv, char **azColName);
