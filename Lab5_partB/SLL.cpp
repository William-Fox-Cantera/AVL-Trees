/*
 *  Book.cpp
 *
 *  Created on: Sep 18, 2019
 * 	NAME: William Cantera
 * 	TA NAME: Agnijit
 *
 *  The methods made in this cpp file are meant for the SLL class for lab 4
 */
#include "SLL.hpp"

#include <stdlib.h>
#include <iostream>
using namespace std;


/*
 * SLL, default constructor, sets first to NULL, last to NULL, and size to 0
 * Consumes: Nothing
 * Produces: Nothing
 */
SLL::SLL() {
	first = NULL;
	last = NULL;
	size = 0;
}

/*
 * ~SLL, destructor
 * Consumes: Nothing
 * Produces: Nothing
 */
SLL::~SLL() {
	SNode *temp = first;
	while(size > 0) {
		SNode *next = temp->next;
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
void SLL::printSLL() {
	SNode *temp = first;
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
void SLL::addFirst(string c) {
	size++;
	first = new SNode(c);
	last = first;
}

/*
 * push, puts a new element on the end of the linked list
 * Consumes: An Integer and a String
 * Produces: Nothing
 */
void SLL::push(string c) {
	SNode *n = new SNode(c);
	last->next = n;
	last = n;
	size++;
}

/*
 * addAtFront, adds a new node to the beginning of the list
 * Consumes: An Integer and a String
 * Produces: Nothing
 */
void SLL::addAtFront(string c) {
	SNode *temp = new SNode(c);
	temp->next = first;
	first = temp;
	size++;
}

/*
 * getAve, gets the average of all the ratings in the list
 * Consumes: Nothing
 * Produces: A double
 */
//double SLL::getAve() {
//	double average = 0;
//	int i = 0;
//	SNode *temp = first;
//
//	while(temp != NULL) {
//		average += temp->rating;
//		i++;
//		temp = temp->next;
//	}
//	average /= i;
//
//	return average;
//}

/*
 * pop, removes the last node from the list and returns the average of the node removed
 * Consumes: Nothing
 * Produces: Nothing
 */
int SLL::pop() {
	//Checking to see if the list is empty
	if(size == 0) {
		cout << "You can't pop an empty stack!";
		exit(0);
	}
	int lastRating;
	SNode *temp = first;
	while(temp != NULL) {
		if(temp->next->next == NULL) {
			temp->next = NULL;
			delete temp->next;
		}
		temp = temp->next;
	}
	size--;
	return 1;
}

/*
 * insertInOrder, creates a linked list ordered by rating. If the list is empty, calls addFirst with r
 * and c. If the rating is less than the first nodes rating in the list, calls addAtFront. If the rating
 * is greater than the rating of the last node in the list, calls the push method. Otherwise, it creates
 * a new node using r and c and inserts that node in order into the linked list.
 * Consumes: An integer and a String
 * Produces: Nothing
 */
//void SLL::insertInOrder(int r, string c) {
//	if (size == 0) {
//		addFirst(c);
//	}
//	if (r < first->rating) {
//		addAtFront(r, c);
//	} else if (r > last->rating) {
//		push(r, c);
//	} else {
//		SNode *n = new SNode(r, c);
//		SNode *temp = first;
//
//		while (n->rating > temp->rating) {
//			if (n->rating <= temp->next->rating) {
//				size++;
//				n->next = temp->next;
//				temp->next = n;
//			}
//			temp = temp->next;
//		}
//	}
//}
