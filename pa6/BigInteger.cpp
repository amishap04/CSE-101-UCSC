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
            		digits.insertAfter(digit_val); 
            		temp = ""; 
        	}
    	}


	
	if (digits.length() == 0) {
        	signum = 0;
        	digits.insertAfter(0); 
    	}

}





BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}



int BigInteger::sign() const{
    return this->signum;
}



int BigInteger::compare(const BigInteger& N) const {

	return 0;

}

void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}


void BigInteger::negate() {

}


BigInteger BigInteger::add(const BigInteger& N) const {

	BigInteger X = *this;

	return X;
}


  
BigInteger BigInteger::sub(const BigInteger& N) const {
	
	BigInteger X = *this;

        return X;

}
 

BigInteger BigInteger::mult(const BigInteger& N) const {

	BigInteger X = *this;

        return X;
}



std::string BigInteger::to_string() {

	std::string out = "";
	return out;
}



std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream<<N.BigInteger::to_string();
}



bool operator==( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 0) ? true : false;
}



bool operator<( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == -1) ? true : false;
}




bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == -1)) ? true : false;
}



bool operator>( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 1) ? true : false;
}


 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == 1)) ? true : false;
}



BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}



BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}



BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}


BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.sub(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}


BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}


BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.mult(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}















