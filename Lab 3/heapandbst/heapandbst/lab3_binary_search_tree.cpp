#include <iostream>
#include "lab3_binary_search_tree.hpp"
#include <algorithm>

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	size = 0;
	root = NULL;
}

// PURPOSE
void BinarySearchTree::delete_recursive(TaskItem* node) {
	if (node == NULL) return;
	delete_recursive(node->left);
	delete_recursive(node->right);
	delete node;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	delete_recursive(root);
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if(!root) return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* current = root;
	while (current->right != NULL) {
		current = current->right;
	}
	return *current;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if(!root) return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* current = root;
	while (current->left != NULL) {
		current = current->left;
	}
	return *current;
}

// PURPOSE: Overloaded tree height function to use recursion
unsigned int BinarySearchTree::height(TaskItem* node) const {
	if (node == NULL) return 0;
	return 1 + std::max(height(node->right), height(node->left));
}


// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	if (root == NULL) return 0;
	return height(root) - 1;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {

}

// PURPOSE: Overloaded exists helper function to use recursion
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem* node) const {
	if (node == NULL) return false;
	if (*node == val) return true;
	if (node->priority > val.priority) return exists(val, node->left);
	return exists(val, node->right);
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	return BinarySearchTree::exists(val, root);
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	if (n == NULL) return 0;
	return 1 + std::max(height(n->right), height(n->left));
}

BinarySearchTree::TaskItem* BinarySearchTree::insert(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem* node) {
	if (node == NULL) {
		node = new TaskItem(val.priority, val.description);
	}
	else if (val.priority < node->priority) {
		node->left = insert(val, node->left);
	}
	else if (val.priority > node->priority) {
		node->right = insert(val, node->right);
	}
	return node;
}


// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	if (exists(val)) return false;
	root = insert(val, root);
	size++;
}

// PURPOSE: Finds the minimum value provided a node
BinarySearchTree::TaskItem* BinarySearchTree::find_min(BinarySearchTree::TaskItem* node) {
	if (node == NULL) return NULL;
	else if (node->left == NULL) return node;
	else return find_min(node->left);
}


// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	if (!exists(val)) return false;
	root = remove(val, root);
	size--;
	return true;
}


// PURPOSE: Overloaded remove helper function to use recursion
BinarySearchTree::TaskItem* BinarySearchTree::remove(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem* node) {
	if (node == NULL) return node;
	else if (val.priority < node->priority) node->left = remove(val, node->left);
	else if (val.priority > node->priority) node->right = remove(val, node->right);
	else{
		if (node->left == NULL && node->right == NULL) {
			delete node;
			node = NULL;
		}
		else if (node->left == NULL) {
			TaskItem* temp = node;
			node = node->right;
			delete temp;
		}
		else if (node->right == NULL) {
			TaskItem* temp = node;
			node = node->left;
			delete temp;
		}
		else {
			TaskItem* temp = find_min(node->right);
			node->description = temp->description;
			node->priority = temp->priority;
			node->right = remove(*temp, node->right);
		}
	}
	return node;
}