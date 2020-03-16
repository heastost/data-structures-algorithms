/* Created by Eduardo Wall�n & Junior Corazza */
#include "binary_tree.h"

Node* new_node(int x) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->key = x;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	return temp;
}
Node* insert(Node* T, Node* z) {
	Node* y = (Node*)malloc(sizeof(Node));
	Node* x = (Node*)malloc(sizeof(Node));
	y = NULL;
	x = T;
	while (x != NULL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else x = x->right;
	}
	z->parent = y;
	if (y == NULL) {
		T = z; // tree T was empty
	}	
	else if (z->key < y->key)
		y->left = z;
	else y->right = z;
	return z;
}
/* The following code (with a few additions) follows the pseudocode that can be read on page 296 in the book "Introduction to Algorithms Third edition" (ISBN: 978-0-262-03384-8)*/
void transplant(Node* T, Node* u, Node* v) {
	Node* parent = new_node(0);
	if (u->parent != NULL)
		parent = u->parent;
	if (u->parent == NULL)
		T = v;
	else if (u == parent->left)
		parent->left = v;
	else parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}
/* The following code (with a few additions) follows the pseudocode that can be read on page 298 in the book "Introduction to Algorithms Third edition" (ISBN: 978-0-262-03384-8)*/
void delete(Node* T, Node* z) {
	Node* y = new_node(0);
	Node* temp = new_node(0);
	if (z->left == NULL)
		transplant(T, z, z->right);
	else if (z->right == NULL)
		transplant(T, z, z->left);
	else {
		y = treemin(z->right);
		if (y->parent != z) {
			transplant(T, y, y->right);
			y->right = z->right;
			temp = y->right;
			temp->parent = y;
		}
		transplant(T, z, y);
		y->left = z->left;
		temp = y->left;
		temp->parent = y;
	}
}
void inordertreewalk(Node* root) {		// print out tree in the correct order
	if (root != NULL) {
		inordertreewalk(root->left);			// Goes through left side
		printf("%d ", root->key);
		inordertreewalk(root->right);			// Goes through right side
	}
}
Node* treemax(Node* root) {

	while (root->right != NULL)
		root = root->right;
	return root;
}
Node* treemin(Node* root) {
	while (root->left != NULL)
		root = root->left;
	return root;
}
Node* treesearch(Node* root, int key) {
	if ((root == NULL) || (root->key == key))
		return root;
	if (root->key > key)
		return treesearch(root->left, key);
	return treesearch(root->right, key);

}
Node* successor(Node* root) {
	Node* temp = new_node(0);
	if (root->right != NULL) {
		temp = treemin(root->right);
		return temp;
	}
	temp = root->parent;
	while ((temp != NULL) && (root == temp->right)) {
		root = temp;
		temp = temp->parent;
	}
	return temp;
}
Node* predecessor(Node* root) {
	Node* temp = new_node(0);
	if (root->left != NULL) {
		return treemax(root->left);
	}
	temp = root->parent;
	while ((temp != NULL) && (root == temp->left)) {
		root = temp;
		temp = temp->parent;
	}
	return temp;
}
int treeheight(Node* root) {
	if (root == NULL)
		return 0;
	else
	{
		int rd = treeheight(root->right);
		int ld = treeheight(root->left);
		if (ld > rd)
			return (ld + 1);
		else return (rd + 1);
	}
}
int treesize(Node* root) {
	if (root == NULL)
		return 0;
	else
		return(1 + treesize(root->right) + treesize(root->left));
}
// ********** PRINT TREE START *********** 
void padding(char ch, int n) {
	int i;

	for (i = 0; i < n; i++)
		putchar(ch);
}
void printTree(Node* root, int level) {
	if (root == NULL) {
		padding('\t', level);
		puts("~");
	}
	else {
		printTree(root->right, level + 1);
		padding('\t', level);
		printf("%d\n", root->key);
		printTree(root->left, level + 1);
	}
}
// ********* PRINT TREE END *************/

/* Function that grows a tree for us */
void growTree(Node* root) {
	insert(root, new_node(5));		// Inserts node
	insert(root, new_node(3));		// Inserts node
	insert(root, new_node(4));		// Inserts node
	insert(root, new_node(50));		// Inserts node
	insert(root, new_node(49));		// Inserts node
	insert(root, new_node(12));		// Inserts node
	insert(root, new_node(11));		// Inserts node
	insert(root, new_node(42));		// Inserts node
}