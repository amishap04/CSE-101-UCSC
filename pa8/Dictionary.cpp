/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA8 // Assignment Number
 * * * * Dictionary.cpp // FileName
 * * * * Implementation for Dictionary ADT // Description
 * * * ***/




#include "Dictionary.h"
#include <stdexcept>
#include <iostream>
#include <functional>

using namespace std;

enum { BLACK, RED };

Dictionary::Node::Node(keyType k, valType v)
    : key(k), 
      val(v), 
      parent(nullptr), 
      left(nullptr), 
      right(nullptr), 
      color(RED) 
{}

Dictionary::Dictionary() : num_pairs(0) {
    nil = new Node("", 0);
    nil->color = BLACK;
    root = nil;
    current = nil;
}

Dictionary::Dictionary(const Dictionary& D) : Dictionary() {
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;
}

Dictionary::~Dictionary() {
    clear();
    delete nil;
}

void Dictionary::inOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const {
    if (R != nil) {
        s.append(R->key);
        if (R->color == RED) {
            s.append(" (RED)\n");
        } 
        else {
            s.append("\n");
        }
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::BST_insert(Node* M) {
    Node* A = nil;
    Node* B = root;
    while (B != nil) {
        A = B;
        if (M->key < B->key) B = B->left;
        else B = B->right;
    }
    M->parent = A;
    if (A == nil) root = M;
    else if (M->key < A->key) A->left = M;
    else A->right = M;
    M->left = nil;
    M->right = nil;
    M->color = RED;
    RB_InsertFixUp(M);
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
    while (R != nil && k != R->key) {
        R = (k < R->key) ? R->left : R->right;
    }
    return R;
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

void Dictionary::LeftRotate(Node* x) {
    Node* newNd = x->right;
    x->right = newNd->left;
    if (newNd->left != nil) {
        newNd->left->parent = x;
    }
    newNd->parent = x->parent;

    if (x->parent == nil) { 
        root = newNd;
    } 
    else if (x == x->parent->left) {
        x->parent->left = newNd;
    } 
    else {
        x->parent->right = newNd;
    }

    newNd->left = x;
    x->parent = newNd;
}

void Dictionary::RightRotate(Node* x) {
    Node* newNd = x->left; 
    x->left = newNd->right;
    if (newNd->right != nil) {
        newNd->right->parent = x;
    }
    newNd->parent = x->parent;

    if (x->parent == nil) {
        root = newNd;
    } 
    else if (x == x->parent->right) {
        x->parent->right = newNd;
    } 
    else {
        x->parent->left = newNd;
    }

    newNd->right = x;
    x->parent = newNd;
}

void Dictionary::RB_InsertFixUp(Node* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* newNd = z->parent->parent->right; 
            if (newNd->color == RED) {
                z->parent->color = BLACK;
                newNd->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RightRotate(z->parent->parent);
            }
        } 
        else {
            Node* newNd = z->parent->parent->left;
            if (newNd->color == RED) {
                z->parent->color = BLACK;
                newNd->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                LeftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v) {
    if (u->parent == nil) {
        root = v;
    } 
    else if (u == u->parent->left) {
        u->parent->left = v;
    } 
    else {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

void Dictionary::RB_Delete(Node* z) {
    Node* A = z;
    Node* B;
    int A_og_color = A->color;

    if (z->left == nil) {
        B = z->right;
        RB_Transplant(z, z->right);
    } 
    else if (z->right == nil) {
        B = z->left;
        RB_Transplant(z, z->left);
    } 
    else {
        A = findMin(z->right);
        A_og_color = A->color;
        B = A->right;

        if (A->parent == z) {
            B->parent = A; 
        } 
        else {
            RB_Transplant(A, A->right);
            A->right = z->right;
            A->right->parent = A;
        }

        RB_Transplant(z, A);
        A->left = z->left;
        A->left->parent = A;
        A->color = z->color;
    }
    if (A_og_color == BLACK) {
        RB_DeleteFixUp(B);
    }
}

void Dictionary::RB_DeleteFixUp(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* newNd = x->parent->right;
            if (newNd->color == RED) {
                newNd->color = BLACK;
                x->parent->color = RED;
                LeftRotate(x->parent);
                newNd = x->parent->right;
            }
            if (newNd->left->color == BLACK && newNd->right->color == BLACK) {
                newNd->color = RED;
                x = x->parent;
            } 
            else {
                if (newNd->right->color == BLACK) {
                    newNd->left->color = BLACK;
                    newNd->color = RED;
                    RightRotate(newNd);
                    newNd = x->parent->right;
                }

                newNd->color = x->parent->color;
                x->parent->color = BLACK;
                newNd->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;
            }
        } 
        else {
            Node* newNd = x->parent->left;
            if (newNd->color == RED) {
                newNd->color = BLACK;
                x->parent->color = RED;
                RightRotate(x->parent);
                newNd = x->parent->left;
            }
            if (newNd->right->color == BLACK && newNd->left->color == BLACK) {
                newNd->color = RED;
                x = x->parent;
            } 
            else {
                if (newNd->left->color == BLACK) {
                    newNd->right->color = BLACK;
                    newNd->color = RED;
                    LeftRotate(newNd);
                    newNd = x->parent->left;
                }

                newNd->color = x->parent->color;
                x->parent->color = BLACK;
                newNd->left->color = BLACK;
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

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


void Dictionary::clear() {
    postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v) {
    Node* newNode = search(root, k);
    if (newNode != nil) {
        newNode->val = v;
    } 
    else {
        Node* addNode = new Node(k, v);
        addNode->left = nil;
        addNode->right = nil;
        addNode->parent = nil;
        BST_insert(addNode);
        num_pairs++;
    }
}


void Dictionary::remove(keyType k) {
    Node* remVal = search(root, k);
    if (remVal == nil) {
        throw std::out_of_range("remove(): Key does not exist.");
    }

    Node* newNd = remVal;
    Node* temp;
    int new_og_color = newNd->color;

    if (remVal->left == nil) {
        temp = remVal->right;
        RB_Transplant(remVal, remVal->right);
    } 
    else if (remVal->right == nil) {
        temp = remVal->left;
        RB_Transplant(remVal, remVal->left);
    } 
    else {
        newNd = findMin(remVal->right);
        new_og_color = newNd->color;
        temp = newNd->right;
        if (newNd->parent == remVal) {
            temp->parent = newNd;
        } 
        else {
            RB_Transplant(newNd, newNd->right);
            newNd->right = remVal->right;
            newNd->right->parent = newNd;
        }

        RB_Transplant(remVal, newNd);
        newNd->left = remVal->left;
        newNd->left->parent = newNd;
        newNd->color = remVal->color;
    }

    delete remVal;
    if (new_og_color == BLACK) {
        RB_DeleteFixUp(temp);
    }

    if (current == remVal) {
        current = nil;
    }

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
    std::function<bool(Node*, Node*)> compareTrees = [&](Node* node1, Node* node2) -> bool {
        if (node1 == nil && node2 == D.nil) return true;
        if (node1 == nil || node2 == D.nil) return false;
        return (node1->key == node2->key && node1->val == node2->val && node1->color == node2->color && 
                compareTrees(node1->left, node2->left) && compareTrees(node1->right, node2->right));
    };

    return compareTrees(root, D.root);
}



std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
    return stream << D.to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D) {
    if (this != &D) {
        clear();
        preOrderCopy(D.root, D.nil);
        num_pairs = D.num_pairs;
    }
    return *this;
}


