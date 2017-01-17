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

void get_next_code(char cod_cliente[5], char new_code[5])
{
	char *aux_num_char;
	std::stringstream aux_num_strs;
	std::string aux_num_str;
	int num_cod;

	/*Comprobamos que la entrada sea válida:*/
	if(strlen(cod_cliente) != 5)
	{
		std::cout << "Formato de código de cliente no válido.\n";
		strcpy(new_code, "ERROR");
		return;
	}

	/*1º: Comprobar si es la antigua o la nueva codificación:*/
	if(isdigit(cod_cliente[0]))
	{
		num_cod = atoi(cod_cliente);
		/*Aquí habría que llamar al siguiente valor de la secuencia*/

		if(num_cod + 1 < 100000)
		{
			aux_num_strs << num_cod + 1;
			aux_num_str = aux_num_strs.str();
			aux_num_char = (char *)aux_num_str.c_str();
			strcpy(new_code, aux_num_char);
		}
		else
		{
			reset_seq(cod_cliente, -99999, new_code);
		}
	}
	else
	{
		num_cod = atoi(cod_cliente + 2);

		if(num_cod + 1 < 1000)
		{
			new_code[0] = cod_cliente[0];
			new_code[1] = cod_cliente[1];
			new_code[2] = '\0';

			aux_num_strs << num_cod + 1;
			aux_num_str = aux_num_strs.str();
			aux_num_char = (char *)aux_num_str.c_str();
			strcat(new_code, aux_num_char);
		}
		else
		{
			reset_seq(cod_cliente, -999, new_code);
		}
	}

}

void reset_seq(char cod_client[], double reset_val, char new_cod[5])
{
	int ascii_code;

	if(reset_val == -99999)
	{
		strcpy(new_cod, "AA000");
	}
	else
	{
		ascii_code = (int) cod_client[1];
		if(ascii_code + 1 <= 90)
		{
			new_cod[0] = cod_client[0];
			new_cod[1] = ascii_code + 1;
			new_cod[2] = '\0';
			strcat(new_cod, "000");
		}
		else
		{
			ascii_code = (int) cod_client[0];
			if(ascii_code < 90)
			{
				new_cod[0] = ascii_code + 1;
				new_cod[1] = 65;
				new_cod[2] = '\0';
				strcat(new_cod, "000");
			}
			else
			{
				strcpy(new_cod, "LIMITE ALCANZADO");
			}
		}

	}

}



