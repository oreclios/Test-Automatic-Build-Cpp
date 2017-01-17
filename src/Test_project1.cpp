//============================================================================
// Name        : Test_project1.cpp
// Author      : oreclios
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "global.h"
using namespace std;

int main() {

	char cod_cliente[5];
	char new_code[5];

	strcpy(cod_cliente, "98444");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	strcpy(cod_cliente, "99999");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	strcpy(cod_cliente, "FR785");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	strcpy(cod_cliente, "FZ999");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	strcpy(cod_cliente, "ZT999");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	strcpy(cod_cliente, "ZZ999");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	strcpy(cod_cliente, "TFR44567344");
	std::cout << "Código = " << cod_cliente << "\n";
	get_next_code(cod_cliente, new_code);
	std::cout << "Nuevo código = " << new_code << "\n\n";

	return 0;
}
