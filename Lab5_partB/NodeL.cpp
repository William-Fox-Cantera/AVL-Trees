/*
 *  Book.cpp
 *
 *  Created on: Sep 18, 2019
 * 	NAME: William Cantera
 * 	TA NAME: Agnijit
 *
 *  The methods made in this cpp file are meant for the SNode class for lab 4
 */
#include "NodeL.hpp"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

/*
 * SNode, first constructor, asks for user input and makes it the comments and rating
 * Consumes: Nothing
 * Produdces: Nothing
 */
NodeL::NodeL() {
	string userComment = "";

	cout << "Enter a comment about the book: ";
	cin >> userComment;

	word = userComment;
	next = NULL;
}

/*
 * SNode, second constructor, sets the comments and rating field
 * Consumes: An integer and a String
 * Produces: Nothing
 */
NodeL::NodeL(string c) {
	word = c;
	next = NULL;
}

/*
 * ~SNode, destructor
 * Consumes: Nothing
 * Produces: Nothing
 */
NodeL::~NodeL() {
//	if (next != NULL) {
//	cout << "deleting may cause memory leak." << endl;
//	}
}

/*
 * printNode, prints out the fields of the node
 * Consumes: Nothing
 * Produces: Nothing
 */
void NodeL::printNode() {
	cout << "The comments are: " << word << endl;
}
