/*
 *  SNode.hpp
 *
 *  Created on: Sep 18, 2019
 * 	NAME: William Cantera
 * 	TA NAME: Agnijit
 *
 * 	The class in this file is for the node class for lab 4
 */

#ifndef SNODE_HPP_
#define SNODE_HPP_

#include <iostream>
#include <string>
using namespace std;


class SNode {
	friend class SLL;
	friend class Game;
	string word; // instead of int data, now the data is both the rating
					  // and the accompanying comments – think of when you rate
					  // a book or a song, and then are asked to share comments
					  //about the book. Both are the data in this node.
	SNode *next;
public:
	SNode(); // this constructor takes no input. It and asks the user to input a
			 // rating, then reads the rating into the rating field, and
			 // then asks the user to input their comments, and reads in the
			 // comments into the comments field.


	SNode(string c);
			// this constructor takes as input an integer and a string, and
			// initializes the rating field to the integer, and the comment
			// field to the string.


	~SNode();
	void printNode();
};





#endif /* SNODE_HPP_ */
