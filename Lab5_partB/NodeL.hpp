/*
 *  SNode.hpp
 *
 *  Created on: Sep 18, 2019
 * 	NAME: William Cantera
 * 	TA NAME: Agnijit
 *
 * 	The class in this file is for the node class for lab 4
 */

#ifndef NODEL_HPP_
#define NODEL_HPP_

#include <iostream>
#include <string>
using namespace std;


class NodeL {
	friend class LL;
	friend class Game;
	string word;
	NodeL *next;
public:
	NodeL();
	NodeL(string c);
	~NodeL();
	void printNode();
};





#endif /* NODEL_HPP_ */
