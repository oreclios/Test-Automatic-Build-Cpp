/*
 * test_project1_v2.cpp
 *
 *  Created on: 17 ene. 2017
 *      Author: mvelascoj
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "global.h"

void show_options(int & option){
	std::cout << "option = " << option << "\n";
	std::cout << "Escoge una opci�n:\n\n";
	std::cout << "(1) Realizar test de conexi�n a BBDD\n";
	std::cout << "(2) Insertar clientes aleatorios\n";
	std::cout << "(3) Insertar nuevo cliente especificando su nombre\n";
	std::cout << "(0) Para salir de la aplicaci�n.\n";
	std::cout << "\t\t Escoja opci�n  >> ";
	std::cin >> option;
	std::cout << "\nHa elegido la opci�n " << option << "\n";
}

int main()
{

	int option = 0;
	int quantity = 0;
	std::string name;
	std::string name_surname;

	initiate_ddbb();

	show_options(option);

	while(option != 0)
	{
		if(option == 0){
			return 0;
		}else if(option == 1){
			/*Test que a�ade X clientes a BBDD y extrao info. de un subgrupo:*/
			std::cout << "Realizando test de conexi�n...\n";
			test_sqlite_connection(10);
			std::cout << "Terminado\n";
			show_options(option);
		}else if(option == 2){
			/*A�adimos clientes Aleatorios a BBDD:*/
			std::cout << "Indica la cantidad de clientes que quieres a�adir:\n";
			std::cin >> quantity;
			std::cout << "A�adiendo registros...\n";
			add_random_clients(quantity);
			std::cout << "Terminado\n";
			show_options(option);
		}else if(option == 3){
			std::cout << "option = " << option << "\n";
			/*M�todo para a�adir cliente especificando su nombre.*/
			add_client_to_database_by_name();
			std::cout << "Terminado\n";
			show_options(option);
		}else{
			std::cout << "Comando incorrecto\n";
			show_options(option);
		}
	}
}
