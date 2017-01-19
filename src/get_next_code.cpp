/*
 * test_function.cpp
 *
 *  Created on: 16 ene. 2017
 *      Author: mvelascoj
 */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>

#include "global.h"

void get_next_code(std::string cod_cliente, std::string & new_code)
{
	std::string aux_num_char;
	std::string aux2;
	std::stringstream aux_num_strs;
	std::string aux_num_str;
	int num_cod;
	int i;
	int length;

	/*Comprobamos que la entrada sea válida:*/
	if(cod_cliente.length() != 5 && cod_cliente.compare("ZERO") != 0){
		std::cout << "Formato de código de cliente no válido.\n";
		new_code = "ERROR";
		return;
	}

	/*Comprobamos si es el primer código que se va a generar:*/
	if(!cod_cliente.compare("ZERO")){
		new_code = "A0001";
		return;
	}

	/*1º: Comprobar si es la antigua o la nueva codificación:*/
	if(isdigit(cod_cliente[0])){
		num_cod = atoi(cod_cliente.c_str());
		/*Aquí habría que llamar al siguiente valor de la secuencia*/

		if(num_cod + 1 < 100000){
			aux_num_strs << num_cod + 1;
			aux_num_str = aux_num_strs.str();
			length = aux_num_str.length();
			/*Append zero chars*/
			for (i = 0; i < 5 - length; i++){
				aux_num_str = "0" + aux_num_str;
			}
			new_code = aux_num_str;
		}else{
			reset_seq(cod_cliente, -99999, new_code);
		}
	}else{
		num_cod = atoi(cod_cliente.c_str() + 1);

		if(num_cod + 1 < 10000){
			new_code = cod_cliente.substr(0,1);

			aux_num_strs << num_cod + 1;
			aux_num_str = aux_num_strs.str();

			length = aux_num_str.length();
			/*Append zero chars*/
			for (i = 0; i < 4 - length; i++)
			{
				aux_num_str = "0" + aux_num_str;
			}
			new_code = new_code + aux_num_str;
		}else{
			reset_seq(cod_cliente, -9999, new_code);
		}
	}

}

void reset_seq(std::string cod_client, double reset_val, std::string & new_cod)
{
	int ascii_code;

	if(reset_val == -99999){
		new_cod = "A0001";
	}
	else if (reset_val == -9999){
		ascii_code = cod_client[0];
		if(ascii_code + 1 <= 90){
			new_cod = char(ascii_code + 1);
			new_cod = new_cod + "0001";
		}else{
			new_cod = "LIMITE ALCANZADO";
		}
	}
}



