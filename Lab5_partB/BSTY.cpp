#include "BSTY.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

BSTY::BSTY() {
	root = NULL;
}

// You write: insert a new node with data x (a string) into the
// binary search tree
// This method should return true if a new node is inserted and 
// false if the data x is already in the tree
// Remember to check whether the new node will be the root
// (meaning the root is currently NULL) and if so, set the root
// to be the new node.
// Note: Make sure you make the new node point to its parent!!! 
// Note2: after you've inserted a new node, you should call the 
// adjustHeights method that will update the heights of all the 
// ancestors of the node that was just inserted.
bool BSTY::insertit(string x) {
	// Making new node, setting data
	NodeT *newNode = new NodeT(x);
	bool wasInserted = false;

	cout << "inserting " << x << endl;
	// Check if the root is NULL, if it is, the new node is root
	if (root == NULL) {
		root = newNode;
		newNode->height = 0;
		newNode->parent = NULL;
		wasInserted = true;
	} else {
		// Compares the new nodes first character to roots first character and inserts them alphabetically
		// from left to right in accordance to the binary search tree
		NodeT *temp = root;
		while (newNode->parent == NULL) {
			// Making sure the new nodes data ins't already in the list
			if (temp->data == newNode->data) {
				cout << temp->data << " is already in the tree!" << endl;
				exit(0);
			}
			// Handling left nodes
			if (newNode->data < temp->data) {
				if (temp->left == NULL) {
					temp->left = newNode;
					newNode->parent = temp;
					wasInserted = true;
				} else {
					temp = temp->left;
				}
			// Handling right nodes
			} else {
				if (temp->right == NULL) {
					temp->right = newNode;
					newNode->parent = temp;
					wasInserted = true;
				} else {
					temp = temp->right;
				}
			}
		}
	}
	// Reconfigure the heights
	adjustHeights(newNode);
	return wasInserted;
}

// the adjustHeights method updates the heights of every ancestor of the node n.
// This method will be massively useful with our next lab, so make sure you have 
// this working now. It should be called whenever you change the height of a
// a particular node. So, for instance, when a new node is inserted as a leaf,
// its height is 1. The adjustHeights method should then check the parent to see
// if the height of the parent changes (the height of each node is the maximum of 
// the height of the left child and the height of the right child, plus 1). If
// the parent's height changes, then the grandparent's height should be checked and,
// if necessary, adjusted. If the grandparent's height is updated, then the great-
// grandparent's height should be adjusted, etc. The checking stops when either
// the loop has worked its way up to the root, or until the currently being checked
// ancestor is not changed.  
void BSTY::adjustHeights(NodeT *n) {
	NodeT *ancestor = NULL;
	bool needsToChange = true;
	int leftHeight;
	int rightHeight;
	int balance;
	int ancestorLeftBalance;
	int ancestorRightBalance;

	// Check n's parent to make sure it isn't NULL before trying to access it
	if (n->parent != NULL) {
		ancestor = n->parent;
	}

	// Make sure the current nodes height is correct (AVL tree update)
	n->left != NULL ? leftHeight = n->left->height : leftHeight = 0;
	n->right != NULL ? rightHeight = n->right->height : rightHeight = 0;
	leftHeight > rightHeight ? n->height = leftHeight + 1 : n->height = rightHeight + 1;

	// Loop all the way up to root if necessary
	while (needsToChange && ancestor != NULL) {
		// If ancestors left/right is not null, set their heights, if they are NULL height is 0
		ancestor->left != NULL ? leftHeight = ancestor->left->height : leftHeight = 0;
		ancestor->right != NULL ? rightHeight = ancestor->right->height : rightHeight = 0;

		// If the current ancestor has not changed, no need to go any further
		if ((ancestor->height == leftHeight + 1) && (ancestor->height == rightHeight + 1)) {
			needsToChange = false;
		}

		// Change the ancestors height to the max of left or right, if they heights are equal it doesn't matter which
		leftHeight > rightHeight ? ancestor->height = leftHeight + 1 : ancestor->height = rightHeight + 1;

		// FIXING BALANCES
		// Assign balance of the ancestor of the new leaf as well as the eft and right children of the ancestor
		balance = findBalance(ancestor);
		if (ancestor->left != NULL) { // The if statements are used to avoid segmentation faults
			ancestorLeftBalance = findBalance(ancestor->left);
		}
		if (ancestor->right != NULL) {
			ancestorRightBalance = findBalance(ancestor->right);
		}

		// CASE 1: left left rotation
		if ((balance > 1) && (ancestorLeftBalance >= 1)) {
			cout << ancestor->data << " must rotate right " << "(" << balance << ")" << endl;
			rotateRight(ancestor);
		}
		// CASE 2: right right rotation
		if ((balance < -1) && (ancestorRightBalance <= -1)) {
			cout << ancestor->data << " must rotate left " << "(" << balance << ")" << endl;
			rotateLeft(ancestor);
		}
		// CASE 3: left right rotation
		if ((balance < -1) && (ancestorRightBalance >= 1)) {
			cout << ancestor->data << " must rotate left " << "(" << balance << ")" << endl;
			cout << ancestor->right->data << " child, rotating right" << endl;
			rotateRight(ancestor->right);
			rotateLeft(ancestor);
		}
		// CASE 4: right left rotation
		if ((balance > 1) && (ancestorLeftBalance <= -1)) {
			cout << ancestor->data << " must rotate right " << "(" << balance << ")" << endl;
			cout << ancestor->left->data << " child, rotating left" << endl;
			rotateLeft(ancestor->left);
			rotateRight(ancestor);
		}

		// Increment heights, get ready for next iteration
		ancestor = ancestor->parent;
		leftHeight++;
		rightHeight++;
	}
}

void BSTY::printTreeIO() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreeIO(root);
	}
}

// Print the tree in order (left child, then parent, then right child).
// Use the slides, but make sure you can understand how the tree is 
// traversed in order
void BSTY::printTreeIO(NodeT *n) {
	if (n == NULL) {
		return;
	}
	printTreeIO(n->left);
	cout << "|" << n->data << ", " << "(" << n->height << "):\n";
	printTreeIO(n->right);
}

void BSTY::printTreePre() {
	if (root == NULL) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreePre(root);
	}
}

// Prints the tree using pre-order traversal (parent, then left child, then right
// child.  Use the slides, but make sure you understand how a tree is traversed in
// pre-order
void BSTY::printTreePre(NodeT *n) {
	if (n == NULL) {
		return;
	}
	cout << "|" << n->data << ", " << "(" << n->height << "):\n";
	printTreePre(n->left);
	printTreePre(n->right);
}

void BSTY::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		printTreePost(root);
		cout << endl;
	}
}

// Prints the tree using pre-order traversal (left child, then right, then parent)
// Use the slides, but make sure you understand how a tree is traversed in
// post-order
void BSTY::printTreePost(NodeT *n) {
	if (n == NULL) {
			return;
		}
	printTreePost(n->left);
	printTreePost(n->right);
	cout << "|" << n->data << ", " << "(" << n->height << "):\n";
}
void BSTY::myPrint() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		myPrint(root);
		cout << endl;
	}
}
void BSTY::myPrint(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		myPrint(n->left);
		cout << n->data.length()-1;
		if (mine) {
			cout <<".";
			mine = false;
		}
		myPrint(n->right);
	}
}

// the find method takes as input a string, and finds whether that string is already
// in the tree or not. If it is in the tree, that node is returned from the tree.
// If it isn't, NULL is returned.  
// NOTE: If the node can't be found, this method prints out that x can't be found.
// if it is found, the printNode method is called for the node.  
NodeT *BSTY::find(string x) {
	int numberOfSteps = 1;

	// See if the tree is empty
	if (root == NULL) {
		cout << "The tree is empty, nothing to find" << endl;
		exit(0);
	}
	NodeT *toBeReturned = NULL;
	NodeT *temp = root;
	while (temp != NULL) {
		// Checks if the string is already in the list, if it is break from the loop
		if (x == temp->data) {
			toBeReturned = temp;
			cout << numberOfSteps << ":";
			temp->printNode();
			break;
		}

		// Iterating through the tree
		if (x < temp->data && temp->left != NULL) {
			temp = temp->left;
		} else {
			temp = temp->right;
		}

		if (temp == NULL) {
			cout << x << " not found" << endl;
		}
		numberOfSteps++;
	}

	// Returns the node if it was found to be in the list, otherwise NULL
	return toBeReturned;
}


// rotateLeft: rotates the nodes in a tree left
// Consumes: A node
// Produces: A node
NodeT *BSTY::rotateLeft(NodeT *n) {
	NodeT *temp1 = n->right;
	NodeT *temp2 = NULL;

	// Make sure there is a left child of the nodes right, avoid segmentation faults
	if (temp1->left != NULL) {
		temp2 = temp1->left;
		n->right = temp2;
		temp2->parent = n;
	} else {
		n->right = NULL;
	}

	// If the pivot is the root, must take additional step
	if (n == root) {
        root = temp1;
		temp1->parent = NULL;
		n->parent = temp1;
		temp1->left = n;
	} else { // Normal rotation not involving the root
		if (n->parent->left == n) {
			n->parent->left = temp1;
		} else {
			n->parent->right = temp1;
		}
		temp1->parent = n->parent;
		n->parent = temp1;
		temp1->left = n;
	}

	// Update the heights
	int leftHeight = (n->left != NULL) ? n->left->height : 0;
	int rightHeight = (n->right != NULL) ? n->right->height : 0;
	if (leftHeight > rightHeight) {
		n->height = leftHeight + 1;
	} else {
		n->height = rightHeight + 1;
	}

	int tempLeftHeight = (temp1->left != NULL) ? temp1->left->height : 0;
	int tempRightHeight = (temp1->right != NULL) ? temp1->right->height : 0;
	if (tempLeftHeight > tempRightHeight) {
		temp1->height = tempLeftHeight + 1;
	} else {
		temp1->height = tempRightHeight + 1;
	}

	// Return new node on top
	return temp1;
}


// rotateRight: rotates the nodes in a tree right
// Consumes: A node
// Produces: A node
NodeT *BSTY::rotateRight(NodeT *n) {
	NodeT *temp1 = n->left;
	NodeT *temp2 = NULL;

	// Make sure there is a left child of the nodes right, avoid segmentation faults
	if (temp1->right != NULL) {
		temp2 = temp1->right;
		n->left = temp2;
		temp2->parent = n;
	} else {
		n->left = NULL;
	}

	// If the pivot is the root, must take additional step
	if (n == root) {
        root = temp1;
		temp1->parent = NULL;
		n->parent = temp1;
		temp1->right = n;
	} else { // Normal rotation not involving the root
		if (n->parent->left == n) {
			n->parent->left = temp1;
		} else {
			n->parent->right = temp1;
		}
		temp1->parent = n->parent;
		n->parent = temp1;
		temp1->right = n;
	}

	// Update the heights
	int leftHeight = (n->left != NULL) ? n->left->height : 0;
	int rightHeight = (n->right != NULL) ? n->right->height : 0;
	if (leftHeight > rightHeight) {
		n->height = leftHeight + 1;
	} else {
		n->height = rightHeight + 1;
	}

	int tempLeftHeight = (temp1->left != NULL) ? temp1->left->height : 0;
	int tempRightHeight = (temp1->right != NULL) ? temp1->right->height : 0;
	if (tempLeftHeight > tempRightHeight) {
		temp1->height = tempLeftHeight + 1;
	} else {
		temp1->height = tempRightHeight + 1;
	}

	// Return new node on top
	return temp1;
}

// findBalance, finds the balance of a given node by subtracting the left childs height from the right childs height
// Consumes: A node
// Produces: An integer
int BSTY::findBalance(NodeT *n) {
	int leftHeight = n->left != NULL ? n->left->height : 0;
	int rightHeight = n->right != NULL ? n->right->height : 0;
	int balance = leftHeight - rightHeight;
	return balance;
}


/*************************************************************************************/
/* Extra Credit Methods                                                              */
/* Challenging: worth 35 EC pts to go towards labs                                   */
/* NOTE: IF YOU CHOOSE NOT TO IMPLEMENT THESE METHODS, YOU ARE STILL RESPONSIBLE FOR */
/* UNDERSTANDING HOW THEY WORK!!                                                     */
/*************************************************************************************/
/* When removing a node from a binary search tree, the resulting tree MUST BE a binary
 * search tree.
 *
 * When removing a node, there are 3 conditions:
 * 1: when the node being removed has no children, in which case the node is deleted,
 * the node's parent is set to NULL, and the node's parent's height is adjusted (if
 * necessary) and heights on up are adjusted.
 * 2: when the node being removed has one child, in which case the node's parent points
 * to the node's child, and the node's child points to the node's parent, and the node
 * is deleted (and the height of the parent on up as necessary is adjusted)
 * 3: when the node has 2 children, in which case the left-most child of the node's
 * right child replaces the node.
 * A couple of notes about this one: you are replacing a node with a node that is lower
 * down in the tree. That means that you are, in essence, removing the node from that
 * lower position and moving it up to the old node's location. Thus the replacing node
 * must be removed using 1 or 2 above (why not 3?). The heights must be adjusted after
 * the replacing node is removed from its old location but before it is inserted into its
 * new location. Equally, the replacing node's height must be adjusted to be the larger of
 * its two children's heights before you adjust heights above that.
 *****************************************************************************************
 * remove(): takes as input a string, uses the find method to find the node in the tree that
 * holds that string, and then calls replace1, replace2, or replace3 depending on what type
 * of replacing should be done. It adjusts the heights, deletes the node, and returns
 * true if the removal was successful.
*/
bool BSTY::remove(string s) {
	NodeT *toBeRemoved = find(s);
	bool wasRemoved = false;

	// CASE 1: node has no children
	if ((toBeRemoved->left == NULL) && (toBeRemoved->right == NULL)) {
		remove1(toBeRemoved);
		wasRemoved = true;
	}

	// CASE 2: node has one child
	if (((toBeRemoved->left != NULL) && !(toBeRemoved->right != NULL)) || (!(toBeRemoved->left != NULL) && (toBeRemoved->right != NULL))) {
		remove2(toBeRemoved);
		wasRemoved = true;
	}

	// CASE 3: node has 2 children
	if ((toBeRemoved->left != NULL) && (toBeRemoved->right != NULL)) {
		remove3(toBeRemoved);
		wasRemoved = true;
	}

	return wasRemoved;
}

/* remove1(): called when the node to be removed has no children. Takes as input the 
 * node to be removed, and sets the parent of the node to point to NULL.
 * helpful hint: if (n->parent->left == n) is true, then n is its parent's left child.
 * Make sure you check to whether n is the root or not.
*/
void BSTY::remove1(NodeT *n) {
	NodeT *nParent = n->parent;
	// Checks to see if the node to be deleted is the root
	if (n == root) {
		delete n;
	}
	// Checks if the node is a left child, if so delete the left, else delete right
	if(nParent->left == n) {
		delete nParent->left;
		nParent->left = NULL;
	} else {
		delete nParent->right;
		nParent->right = NULL;
	}
	// Heights only need to be adjusted if the deleted node was the parents only child
	if (nParent->left == NULL && nParent->right == NULL) {
		nParent->height = 1;
		adjustHeights(nParent);
	}
}

/* remove2(): called when the node to be removed has 1 child only.  Takes as input
 * the node to be removed and bypasses it by making the parent point to the node's
 * one child, and makes the node's one child point to the node's parent.
 * This one needs a bunch of checking - you need to see if the node is the parent's
 * left or right child, and you need to see if the node's child is its left or its
 * right child.
 * Also, make sure you check that if the node to be removed is the root, then the
 * one child becomes the root.
*/ 
void BSTY::remove2(NodeT *n) {
	NodeT *nParent = n->parent;
	NodeT *child;

	// Finds if the node is the parents left or right child
	bool isLeft = false;
	if (nParent->left != NULL) {
		isLeft = true;
	}

	// Finds is the nodes child is a left or right child, initializes the child node
	n->left != NULL ? child = n->left : child = n->right;

	// Check to see if the node to be removed is the root
	if (n == root) {
		delete n;
		child->parent = NULL;
		root = child;
	}
	// Delete node, re-arrange pointers
	delete n;
	if (isLeft) {
		nParent->left = child;
		child->parent = nParent;
	} else {
		nParent->right = child;
		child->parent = nParent;
	}
	nParent->height--;
	adjustHeights(nParent);
}

/* remove3(): called when the node to be removed has 2 children. Takes as input the
 * node to be removed. The node to replace the node to be removed should be the
 * left-most descendent of the node's right child. That way the binary search tree
 * properties are guaranteed to be maintained.
 * When replacing the node to be removed with the replacing node, the replacing node
 * is, in essence, being removed from its place in the tree, and thus replace1 or
 * replace2 methods should be used.
 * The new node's parent must be set to the removed node's parent, the removed node's
 * parent must point to the new node, the new node's left child must point to the
 * removed node's left child (and the child must point to the new node as a parent),
 * and the same for the right child.
 * Remember to take into account that the node being removed might be the root.
 */
void BSTY::remove3(NodeT *n) {
	NodeT *temp = findMin(n);
	NodeT *tempParent = temp->parent;
	string tempData = temp->data;
	NodeT *replacementNode = new NodeT(tempData);

	if (temp->left == NULL && temp->right == NULL) {
		remove1(temp);
	} else {
		remove2(temp);
	}

	// Handle the case where the node to be removed is the root node
	if (n == root) {
		replacementNode->parent = NULL;
		replacementNode->left = n->left;
		replacementNode->right = n->right;
		n->left->parent = replacementNode;
		n->right->parent = replacementNode;
		root = replacementNode;
		delete n;
	} else { // If the node to be removed is not the root
		replacementNode->parent = n->parent;
		replacementNode->left = n->left;
		replacementNode->right = n->right;
		replacementNode->height = n->height;
		n->left->parent = replacementNode;
		n->right->parent = replacementNode;

		//  Check is the node is its parents left or right child
		if (n->parent->left == n) {
			n->parent->left = replacementNode;
		} else {
			n->parent->right = replacementNode;
		}
		delete n;
	}
	adjustHeights(tempParent);
}

/* findMin(): takes as input a node, and finds the left-most descendant of its 
 * right child. The left-most descendent is returned.
*/
NodeT *BSTY::findMin(NodeT *n) {
	// Go to the right child of the given node
	NodeT *deepestLeft = n->right;

	// Loop to the left-most node of the given nodes right child
	while (deepestLeft->left != NULL) {
		if (deepestLeft->left != NULL) {
			deepestLeft = deepestLeft->left;
		} else if (deepestLeft->right != NULL) {
			deepestLeft = deepestLeft->right;
		}
	}
	return deepestLeft;
}

void BSTY::myPrintEC() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		myPrintEC(root);
		cout << endl;
	}
}
void BSTY::myPrintEC(NodeT *n) {
	if (n == NULL) {
		return;
	}
	else {
		myPrintEC(n->left);
		cout << alpha[n->data.length()-2];
		myPrintEC(n->right);
	}
}


/************************************************************************/

