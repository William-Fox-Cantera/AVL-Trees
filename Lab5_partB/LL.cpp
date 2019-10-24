/*
 *  Book.cpp
 *
 *  Created on: Sep 18, 2019
 * 	NAME: William Cantera
 * 	TA NAME: Agnijit
 *
 *  The methods made in this cpp file are meant for the SLL class for lab 4
 */
#include "LL.hpp"

#include <stdlib.h>
#include <iostream>
using namespace std;


/*
 * SLL, default constructor, sets first to NULL, last to NULL, and size to 0
 * Consumes: Nothing
 * Produces: Nothing
 */
LL::LL() {
	first = NULL;
	last = NULL;
	size = 0;
	score = 0;
}

/*
 * ~SLL, destructor
 * Consumes: Nothing
 * Produces: Nothing
 */
LL::~LL() {
	NodeL *temp = first;
	while(size > 0) {
		NodeL *next = temp->next;
		delete temp;
		temp = next;
		size--;
	}
	cout << "deleted each node" << endl;
}

/*
 * printSLL, prints out the linked list
 * Consumes: Nothing
 * Produces: Nothing
 */
void LL::printList() {
	NodeL *temp = first;
	while(temp != NULL) {
		temp = temp->next;
	}
	cout << endl;
}

/*
 * addFirst, adds the first node to the list
 * Consumes: An Integer and a String
 * Produces: Nothing
 */
void LL::addFirst(string s) {
	size++;
	first = new NodeL(s);
	last = first;
}

/*
 * push, puts a new element on the end of the linked list
 * Consumes: An Integer and a String
 * Produces: Nothing
 */
void LL::push(string s) {
	NodeL *n = new NodeL(s);
	if (size == 0) {
		addFirst(s);
	} else {
		n->next = NULL;
		last->next = n;
		last = n;
		size++;
	}
}

/*
 * getScore, traverses the linked list and adds up the score of each word
 * Consumes: Nothing
 * Produces: Nothing
 */
void LL::getScore() {
	NodeL *temp = first;
	int total = 0;
	while (temp != NULL) {
		total += 10;
		temp = temp->next;
	}
	score = total;
}
