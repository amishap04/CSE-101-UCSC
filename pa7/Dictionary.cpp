/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA7 // Assignment Number
 * * * * Dictionary.cpp // FileName
 * * * * Implementation for Dictionary ADT // Description
 * * * ***/


#include "Dictionary.h"
#include <stdexcept>

using namespace std;

// node constructor

Dictionary::Node::Node(keyType k, valType v)
    : key(k),  
      val(v),  
      parent(nullptr), 
      left(nullptr), 
      right(nullptr)   
{
    
}



// helper functions
void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val); 
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) {
    if (R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}


Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
    if (R == nil || R->key == k) return R;
    if (k < R->key) return search(R->left, k);
    else return search(R->right, k);
}

Dictionary::Node* Dictionary::findMin(Node* R) {
    while (R != nil && R->left != nil){
	 R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R) {
    while (R != nil && R->right != nil){ 
	R = R->right;
    }
    return R;
}

Dictionary::Node* Dictionary::findNext(Node* N) {
    if (N->right != nil) return findMin(N->right);
    Node* P = N->parent;

    while (P != nil && N == P->right) {
        N = P;
        P = P->parent;
    }
    return P;
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) return findMax(N->left);
    Node* P = N->parent;
    while (P != nil && N == P->left) {
        N = P;
        P = P->parent;
    }
    return P;
}

// default constructor
Dictionary::Dictionary() 
    : nil(new Node("", 0)), 
      root(nil),            
      current(nil),          
      num_pairs(0)           
{
}



// copy constructor
Dictionary::Dictionary(const Dictionary& D) : Dictionary() {
    preOrderCopy(D.root, D.nil);
}

// destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

// access functions
int Dictionary::size() const {
    return num_pairs;
}

bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

valType& Dictionary::getValue(keyType k) const {
    Node* N = search(root, k);
    if (N == nil) throw std::logic_error("Key not found");
    return N->val;
}

bool Dictionary::hasCurrent() const {
    return current != nil;
}

keyType Dictionary::currentKey() const {
    if (!hasCurrent()) throw std::logic_error("Current is undefined");
    return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) throw std::logic_error("Current is undefined");
    return current->val;
}

// manipulation functions
void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* parent = nil;
    Node* node = root;
    while (node != nil && node->key != k) {
        parent = node;
        node = (k < node->key) ? node->left : node->right;
    }
    if (node != nil) {
        node->val = v;
    } 
    else {
        Node* newNode = new Node(k, v);
        newNode->parent = parent;
        newNode->left = nil;
        newNode->right = nil;
        if (parent == nil) {
            root = newNode;
        } 
        else if (k < parent->key) {
            parent->left = newNode;
        } 
        else {
            parent->right = newNode;
        }

        num_pairs++;
    }
}



void Dictionary::remove(keyType k) {
    Node* node = search(root, k);
    if (node == nil) return;
    if (node->left != nil && node->right != nil) {
        Node* successor = findMin(node->right);
        node->key = successor->key;
        node->val = successor->val;
        node = successor;
    }
    Node* child = (node->left != nil) ? node->left : node->right;
    if (child != nil) child->parent = node->parent;
    if (node->parent == nil) {
        root = child;
    } 
    else if (node == node->parent->left) {
        node->parent->left = child;
    } 
    else {
        node->parent->right = child;
    }
    if (node == current) current = nil;
    delete node;
    num_pairs--;
}


void Dictionary::begin() {
    current = (root != nil) ? findMin(root) : nil;
}

void Dictionary::end() {
    current = (root != nil) ? findMax(root) : nil;
}

void Dictionary::next() {
    if (current != nil) {
        current = findNext(current);
    }
}

void Dictionary::prev() {
    if (current != nil) {
        current = findPrev(current);
    }
}

// other functions
std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (num_pairs != D.num_pairs) return false;
    return to_string() == D.to_string();
}


// overload operators
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.Dictionary::to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        Dictionary temp = D;
        swap(nil, temp.nil);
        swap(root, temp.root);
        swap(current, temp.current);
        swap(num_pairs, temp.num_pairs);
    }
    return *this;
}

