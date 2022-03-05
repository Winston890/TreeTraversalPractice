// Dictionary.cpp
// Implementation file for Dictionary ADT
// Winston Yi
// wyi10
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdlib.h>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include"Dictionary.h"

// Class Constructors & Destructors -------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Creates a new Dictionary in the empty state.
Dictionary::Dictionary(){
   nil = nullptr;
   root = nullptr;
   current = nullptr;
   num_pairs = 0;
}

// Given Dictionary D, insert values in preorder traversal from root of another tree
void Dictionary::preOrderCopy(Node* R) {
	setValue(R->key, R->val);
    if (R->left != nullptr) {
	    preOrderCopy(R->left);
    }
    if (R->right != nullptr) {
	    preOrderCopy(R->right);
    }
}
	

// Copy Constructor.
Dictionary::Dictionary(const Dictionary& N){
	nil = nullptr;
	num_pairs = 0;
    if (N.root != nullptr) {
        root = new Node(N.root->key, N.root->val);
		num_pairs += 1;
	    preOrderCopy(N.root);
    } else {
        root = nullptr;
    }
	current = nullptr;
}

Dictionary::~Dictionary() { //Clear will clear root node, begin will set current to root
    delete nil;
	if (num_pairs != 0) {
    	postOrderDelete(root);
	}
}

Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const {
	if (R == nullptr or R->key == k) {
		return R;
	} 
	if (R->key < k) {
		return search(R->right, k);
	}
	return search(R->left, k);
}
				
       
// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
	if (search(root, k) != nullptr) {
        return true;
    } else {
        return false;
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
	Node* N = search(root, k);
    if (N != nullptr) {
        return N->val;
    } else {
		throw std::logic_error("Dictionary: getValue(): key " + k + " does not exist");
	}
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
	if (current != nullptr) {
		return true;
	} else {
		return false;
	}
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
	if (hasCurrent()) {
		return current->key;
	} else {
		throw std::logic_error("currentKey does not contain k");
	}
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
	if (hasCurrent()) {
		return current->val;
	} else {
		throw std::logic_error("Dictionary: currentVal(): current undefined");
	}
}

// Manipulation procedures -------------------------------------------------

Dictionary::Node* Dictionary::findMin(Node* R) {
	if (R == nullptr) {
		return nullptr;
	}
    while (R->left != nullptr) {
        R = R->left;
    }
    return R;
}


Dictionary::Node* Dictionary::findMax(Node* R) {
	if (R == nullptr) {
		return nullptr;
	}
    while (R->right != nullptr) {
        R = R->right;
    }
    return R;
}


void Dictionary::begin() {
    current = findMin(root);
}

void Dictionary::end() {
    current = findMax(root);
}

void Dictionary::next() {
    if (hasCurrent()) {
        if (current->right != nullptr) {
            current = findMin(current->right);
        } else {   
			Node* y = current->parent;                     
   			while (y != nullptr and current == y->right) {
      			current = y;
      			y = y->parent;
            }
            current = y;
        }
    } else {
		throw std::logic_error("Dictionary: next(): current not defined");
	}
}
        
void Dictionary::prev() {
    if (hasCurrent()) {
        if (current->left != nullptr) {
            current = findMax(current->left);
        } else {
			Node* y = current->parent;                     
   			while (y != nullptr and current == y->left) {
      			current = y;
      			y = y->parent;
            }
            current = y;
        }
    } else {
		throw std::logic_error("Dictionary: prev(): current not defined");
	}
}

void Dictionary::postOrderDelete(Node* R) {
	if (R->left != nullptr) {
		postOrderDelete(R->left);
	}
	if (R->right != nullptr) {
		postOrderDelete(R->right);
	}
	delete R;
    num_pairs -= 1;
}
	
void Dictionary::clear() {
	if (this->root == nullptr) {
		return;
	}
	postOrderDelete(root);
	current = nullptr;
}
    
void Dictionary::setValue(keyType k, valType v) {
	Node* y = nullptr;
	Node* x = root;
	while (x != nil) {
		y = x;
		if (k < x->key) {
			x = x->left;
		} else if (k > x->key) {
			x = x->right;
		} else {
			x->val = v;
			return;
		}
	}
	Node* z = new Node(k, v);
	z->parent = y;
	if (y == nil) {
		root = z; // Tree was empty
	} else if (k < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	num_pairs += 1;
}


void Dictionary::Transplant (Node* u, Node* v) { 
   	if (u->parent == nil) {
		root = v;
	} else if (u == u->parent->left) {
		u->parent->left = v;
   	} else {
    	u->parent->right = v;
	}
   	if (v != nil) {
    	v->parent = u->parent;
	}
}

void Dictionary::remove(keyType k) {
	Node* z = search(root, k);
	if (z == nil) {
		printf("throw error here");
		return;
	}
	if (z == current) {
		current = nullptr;
	} 
	if (z->left == nil) {               // case 1  or case 2.1 ->right only)
      	Transplant(z, z->right);
	} else if (z->right == nil) {        // case 2.2 ->left only)
     	Transplant(z, z->left);
	} else {                          // case 3
		Node* y = findMin(z->right);
    	if (y->parent != z) {
        	Transplant(y, y->right);
        	y->right = z->right;
        	y->right->parent = y;
		}
    	Transplant(z, y);
     	y->left = z->left;
      	y->left->parent = y;
	}
	delete z;
	num_pairs -= 1;
}

/*void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R == nullptr) {
        return;
    }
    s += R->key + " : " + std::to_string(R->val) + "\n";
    preOrderString(s, R->left);
    preOrderString(s, R->right);
}*/

void Dictionary::preOrderStringNoVal(std::string& s, Node* R) const {
    if (R == nullptr) {
        return;
    }
    s += R->key + "\n";
    preOrderStringNoVal(s, R->left);
    preOrderStringNoVal(s, R->right);
}

std::string Dictionary::pre_string() const {
    std::string s = "";
    preOrderStringNoVal(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (this->num_pairs == D.size()) {
		if (D.to_string() == this->to_string()) {
			return true;
		}
	}
	return false;
} 

void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R == nullptr) {
		return;
	}
	inOrderString(s, R->left);
	s += R->key + " : " + std::to_string(R->val) + "\n";
	inOrderString(s, R->right);
}
	
std::string Dictionary::to_string() const {
	std::string s = "";
	inOrderString(s, root);
	return s;
}
	
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    if (A.equals(B)) {
        return true;
    } else {
        return false;
    }
}

Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this != &D) {
		clear();
		nil = nullptr;
		if (D.root != nullptr) {
			root = new Node(D.root->key, D.root->val);
			preOrderCopy(D.root);
			num_pairs += 1;
		} else {
			root = nullptr;
		}
		current = nullptr;
	}
    return *this;
}
