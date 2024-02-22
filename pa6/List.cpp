/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA6 // Assignment Number
 * * * * List.cpp // FileName
 * * * * Implementation for List ADT // Description
 * * * ***/



#include <set>
#include <string>
#include "List.h"

List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        insertBefore(N->data);
        N = N->next;
    }
}

List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return num_elements;
}

ListElement List::front() const {
	if (length() == 0) {
		throw std::length_error("List: front(): empty list");
	}
    return frontDummy->next->data;
}

ListElement List::back() const {
	if (length() == 0) {
		throw std::length_error("List: back(): empty list");
	}
    return backDummy->prev->data;
}

int List::position() const {
    return pos_cursor;
}

ListElement List::peekNext() const {
	if (position() >= length()) {
		 throw std::range_error("List: peekNext(): cursor at back");
	}
    return afterCursor->data;
}

ListElement List::peekPrev() const {
	if (position() <= 0) {
	    throw std::range_error("List: peekPrev(): cursor at front");
	 }
    return beforeCursor->data;
}

void List::clear() {

	moveFront();
    while (length() > 0) {
    	if(afterCursor != backDummy){
    		eraseAfter();
    	}
    }
}

void List::moveFront() {

    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
}

ListElement List::moveNext() {
	if (position() >= length()) {
		throw std::range_error("List: moveNext(): cursor at back");
	}

    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    ++pos_cursor;
    return beforeCursor->data;
}

ListElement List::movePrev() {
	if (position() <= 0) {
		 throw std::range_error("List: movePrev(): cursor at front");
	}
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    --pos_cursor;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
    Node* newNode = new Node(x);

    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    beforeCursor->next = newNode;
    afterCursor->prev = newNode;

    afterCursor = newNode;

    ++num_elements;
}


void List::insertBefore(ListElement x) {
    Node* newNode = new Node(x);

    newNode->next = afterCursor;
    newNode->prev = beforeCursor;
    afterCursor->prev = newNode;
    beforeCursor->next = newNode;

    beforeCursor = newNode;

    pos_cursor++;
    ++num_elements;
}


void List::setAfter(ListElement x) {
	if (position() >= length()) {
		 throw std::range_error("List: setAfter(): cursor at back");
	}
    afterCursor->data = x;
}

void List::setBefore(ListElement x) {
	if (position() <= 0) {
		 throw std::range_error("List: setBefore(): cursor at front");
	}
    beforeCursor->data = x;
}

void List::eraseAfter() {
	if (position() >= length()) {
		 throw std::range_error("List: eraseAfter(): cursor at back");
	}
    Node* temp = afterCursor;
    beforeCursor->next = afterCursor->next;
    afterCursor->next->prev = beforeCursor;
    afterCursor = afterCursor->next;
    delete temp;
    --num_elements;
}

void List::eraseBefore() {
	if (position() <= 0) {
		 throw std::range_error("List: eraseBefore(): cursor at front");
	}
    movePrev();
    eraseAfter();
}

int List::findNext(ListElement x) {
	Node* current = afterCursor;
    int position = pos_cursor;

    while (current != backDummy) {
        if (current->data == x) {
            beforeCursor = current;
            afterCursor = current->next;
            ++position;
            pos_cursor=position;
            return pos_cursor;
        }
        current = current->next;
        ++position;
    }

    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = length();
    return -1;
}

int List::findPrev(ListElement x) {
    Node* current = beforeCursor;
    int position = pos_cursor;

    while (current != frontDummy) {
        if (current->data == x) {
            afterCursor = current;
            beforeCursor = current->prev;
            --position;
            pos_cursor = position;
            return pos_cursor;
        }
        current = current->prev;
        --position;
    }

    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
    return -1;
}

void List::cleanup() {
    Node* current = frontDummy->next;
    int curr_pos = 0;

    std::set<ListElement> uniqueElements;

    Node* temp;

    while (current != backDummy) {
        if (uniqueElements.find(current->data) == uniqueElements.end()) {
            uniqueElements.insert(current->data);
            temp = current;
            current = current->next;
            curr_pos++;
        } else {
            temp->next = current->next;
            current->next->prev = temp;
            delete current;
            current = temp->next;
            --num_elements;
            if(curr_pos < pos_cursor){
		beforeCursor = afterCursor->prev;
            	pos_cursor--;
            }

        }
    }
}


List List::concat(const List& L) const {
    List result;  

    Node* current = frontDummy->next;
    while (current != backDummy) {
        result.insertBefore(current->data);
        current = current->next;
    }

    current = L.frontDummy->next;
    while (current != L.backDummy) {
        result.insertBefore(current->data);
        current = current->next;
    }

    result.moveFront();

    return result;
}


std::string List::to_string() const {
    std::string result = "(";

    Node* current = frontDummy->next;
    while (current != backDummy) {
        result += std::to_string(current->data);
        if (current->next != backDummy) {
            result += ", ";
        }
        current = current->next;
    }

    result += ")";
    return result;
}


bool List::equals(const List& R) const {
    if (length() != R.length()) {
        return false;
    }

    Node* currentL = frontDummy->next;
    Node* currentR = R.frontDummy->next;

    while (currentL != backDummy) {
        if (currentL->data != currentR->data) {
            return false;
        }
        currentL = currentL->next;
        currentR = currentR->next;
    }

    return true;
}


std::ostream& operator<<(std::ostream& stream, const List& L) {



	List::Node* current = L.frontDummy->next;

    while (current != L.backDummy) {
        stream << current->data << " ";
        current = current->next;
    }

    return stream;

}


bool operator==(const List& A, const List& B) {
    if (A.length() != B.length()) {
        return false;
    }

    List::Node* currentA = A.frontDummy->next;
    List::Node* currentB = B.frontDummy->next;

    while (currentA != A.backDummy) {
        if (currentA->data != currentB->data) {
            return false;
        }
        currentA = currentA->next;
        currentB = currentB->next;
    }

    return true;
}

List& List::operator=(const List& L) {
    if (this != &L) {
        clear();

        Node* current = L.frontDummy->next;
        while (current != L.backDummy) {
            insertBefore(current->data);
            current = current->next;
        }
    }
    return *this;
}








