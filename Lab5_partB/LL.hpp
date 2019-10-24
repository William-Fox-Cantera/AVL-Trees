/*
 * SLL.hpp
 *
 *  Created on: Sep 18, 2019
 *      Author: wfcan
 */

#ifndef LL_HPP_
#define LL_HPP_

#include "NodeL.hpp"
#include <stdlib.h>
#include <iostream>
using namespace std;


class LL {
friend class Game;
	NodeL *first;
	NodeL *last;
	int size;
	int score;
public:
	LL();
	~LL();
	void push(string s);
	void addFirst(string s);
	void printList();
	void getScore();
};



#endif /* LL_HPP_ */
