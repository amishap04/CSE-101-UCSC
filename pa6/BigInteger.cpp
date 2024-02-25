/**
 
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA6 // Assignment Number
 * * * * BigInteger.cpp // FileName
 * * * * Implementation for BigInteger ADT // Description
 * * * ***/


#include "BigInteger.h"
#include "List.h"
#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

const ListElement BASE  = 10;  
const int         POWER = 2;    


// making constructors


BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}


BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
        return;
    }
    if (x < 0) {
        signum = -1;
        x = -x;
    } else {
        signum = 1;
    }
    while (x > 0) {
        digits.insertBefore(x % BASE);
        x /= BASE;
    }
}


// needs to be fixed bc parsing it strange
BigInteger::BigInteger(std::string s){

	if (s.empty()) {
        	throw std::invalid_argument("BigInteger: Constructor: empty string");
    	}

	if (s[0] == '-') {
        	signum = -1;
        	s.erase(0, 1);
    	} 
	else if (s[0] == '+') {
        	s.erase(0, 1);
    	} 
	else {
        	signum = 1; 
    	}

	int i = 0;
	while (i < s.length()) {
    		if (!std::isdigit(s[i])) {
        		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    		}
    		i++;
	}
	
	int length = s.length();
    	string temp = "";
    	for (int i = length - 1; i >= 0; i--) {
        	temp = s[i] + temp;
        	if (temp.length() == POWER || i == 0) {
            		long digit_val = stol(temp); 
            		digits.insertBefore(digit_val); 
            		temp = ""; 
        	}
    	}


	// not sure if this is needed.
	if (digits.length() == 0) {
        	signum = 0;
        	digits.insertAfter(0); 
    	}

}



BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}
















