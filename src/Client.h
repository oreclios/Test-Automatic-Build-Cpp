/*
 * Client.h
 *
 *  Created on: 17 ene. 2017
 *      Author: mvelascoj
 */

#ifndef CLIENT_H_
#define CLIENT_H_

class Client {
public:
	Client();
	virtual ~Client();

	std::string Name;
	std::string Surname1;
	std::string Surname2;
	std::string Code;
	int product;
	long int date_contr;
	int index;
};

#endif /* CLIENT_H_ */
