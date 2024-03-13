/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA8 // Assignment Number
 * * * * Dictionary.cpp // FileName
 * * * * Implementation for Dictionary ADT // Description
 * * * ***/


#include "Dictionary.h"
#include <stdexcept>

#define RED -1
#define BLACK -2

using namespace std;


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


void Dictionary::LeftRotate(Node* N){
    Node* M = N->right;
    N->right = M->left;
    if(M->left != nil){
        M->left->parent = N;
    }
    M->parent = N->parent;
    if(N->parent == nil){
        root = M;
    }else if(N == N->parent->left){
        N->parent->left = M;
    }else{
        N->parent->right = M;
    }
    M->left = N;
    N->parent = M;
}


void Dictionary::RightRotate(Node* N){
    Node* M = N->left;

    N->left = M->right;
    if(M->right != nil){
        M->right->parent = N;
    }
    M->parent = N->parent;
    if(N->parent == nil){
        root = M;
    }else if(N == N->parent->right){
        N->parent->right = M;
    }else{
        N->parent->left = M;
    }
    M->right = N;
    N->parent = M;
}


void Dictionary::RB_InsertFixUp(Node* N){
    while(N->parent->color == RED){
        if(N->parent == N->parent->parent->left){
            Node* M = N->parent->parent->right;
            if(M->color == RED){
                N->parent->color = BLACK;
                M->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else {
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }else{
            Node* M = N->parent->parent->left;
            if(M->color == RED){
                N->parent->color = BLACK;
                M->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }else {
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}


void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}



void Dictionary::RB_DeleteFixUp(Node* N){
    while(N != root && N->color == BLACK){
        if(N == N->parent->left){
            Node* M = N->parent->right;
            if(M->color == RED){
                M->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                M = N->parent->right;
            }
            if(M->left->color == BLACK && N->right->color == BLACK){
                M->color = RED;
                N = N->parent;
            }else{
                if(M->right->color == BLACK){
                    M->left->color = BLACK;
                    M->color = RED;
                    RightRotate(M);
                    M = N->parent->right;
                }
                M->color = N->parent->color;
                N->parent->color = BLACK;
                M->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }else{
            Node* M = N->parent->left;
            if(M->color == RED){
                M->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                M = N->parent->left;
            }
            if(M->right->color == BLACK && N->left->color == BLACK){
                M->color = RED;
                N = N->parent;
            }else{
                if(M->left->color == BLACK){
                    M->right->color = BLACK;
                    M->color = RED;
                    LeftRotate(M);
                    M = N->parent->left;
                }
                M->color = N->parent->color;
                N->parent->color = BLACK;
                M->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}


void Dictionary::RB_Delete(Node* N){
    Node* Y = N;
    Node* X = nil;
    int Y_ORIGIN_COLOR = Y->color;
    if(Y->left == nil){
        X = N->right;
        RB_Transplant(N, N->right);
    }else if(N->right == nil){
        X = N->left;
        RB_Transplant(N, N->left);
    }else{
        Y = findMin(N->right);
        Y_ORIGIN_COLOR = Y->color;
        X = Y->right;
        if(Y->parent == N){
            X->parent = Y;
        }else{
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }
    if(Y_ORIGIN_COLOR == BLACK){
        RB_DeleteFixUp(X);
    }
}



Dictionary::Dictionary(){
    nil = new Node("NIL", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;  
    num_pairs = 0;
}


Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("NIL", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){
    clear();
    delete nil;
    nil = nullptr;
    current = nullptr;
    root = nullptr;
}


int Dictionary::size() const{
    return num_pairs;
}



bool Dictionary::contains(keyType k) const {
    if (search(root, k) == nil) {
        return false;
    }
    return true;
}

valType& Dictionary::getValue(keyType k) const {
    Node *N = search(root, k);
    if (N == nil) {
        throw logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
    }
    return N->val;
}

bool Dictionary::hasCurrent() const {
    if (current == nil || current == nullptr) {
        return false;
    }
    return true;
}



void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}


void Dictionary::setValue(keyType k, valType v) {
    Node* X = root;
    Node* Y = nil;
    Node* Z = new Node(k, v);
    Z->left = nil;
    Z->right = nil;
    Z->color = RED;

    while (X != nil) {
        Y = X;
        if (k < X->key) {
            X = X->left;
        }
        else {
            X = X->right;
        }
    }
    Z->parent = Y;
    if (Y == nil) {
        root = Z;
        num_pairs++;
    }
    else if (k < Y->key) {
        Y->left = Z;
        num_pairs++;
    }
    else if (k > Y->key) {
        Y->right = Z;
        num_pairs++;
    }
    else {
        Y->val = v;
        delete Z;
        return;
    }    
    RB_InsertFixUp(Z);
}

void Dictionary::remove(keyType k) {
    if (contains(k) == false) {
        throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node* N = search(root, k);
    if (N == current) {
        current = nil;
    }
    RB_Delete(N);
    num_pairs--;
}

void Dictionary::begin() {
    if (num_pairs > 0) {
        current = findMin(root);
    }
}

void Dictionary::end() {
    if (num_pairs > 0) {
        current = findMax(root);
    }
}


void Dictionary::next() {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: next(): current undefined");
    }
    if (findNext(current) != nil) {
        Node* N = findNext(current);
        current = N;
    }
    else {
        current = nil;
    }
}

void Dictionary::prev() {
    if (hasCurrent() == false) {
        throw logic_error("Dictionary: prev(): current undefined");
    }
    if (findPrev(current) != nil) {
        Node* N = findPrev(current);
        current = N;
    }
    else {
        current = nil;
    }
}

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








