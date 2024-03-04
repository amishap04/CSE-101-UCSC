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
#include <sstream>
#include <string>



using namespace std;

const ListElement BASE  = 10;  
const int         POWER = 9;    


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
    if (this->signum != N.signum) {
        return this->signum > N.signum ? 1 : -1;
    }
    if (this->signum == 0) {
        return 0;
    }

    List A = this->digits;
    List B = N.digits;
    int lengthComparison = A.length() - B.length();

    if (this->signum == 1) {
        if (lengthComparison != 0) {
            return lengthComparison > 0 ? 1 : -1;
        }
    } else {
        if (lengthComparison != 0) {
            return lengthComparison < 0 ? 1 : -1;
        }
    }

    A.moveFront();
    B.moveFront();
    while (A.position() < A.length()) {
        int digitComparison = A.peekNext() - B.peekNext();
        if (digitComparison != 0) {
            return (this->signum == 1 ? 1 : -1) * (digitComparison > 0 ? 1 : -1);
        }
        A.moveNext();
        B.moveNext();
    }

    return 0;
}






void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}


void BigInteger::negate() {
	signum *= -1;
}


void sumList(List& Result, List First, List Second, int signMultiplier) {
    Result.clear();
    for(Second.moveFront(); Second.position() < Second.length(); Second.moveNext()) {
        Second.setAfter(signMultiplier * Second.peekNext());
    }
    
    First.moveBack();
    Second.moveBack();
    
    while (First.position() > 0 && Second.position() > 0) {
        Result.insertAfter(First.peekPrev() + Second.peekPrev());
        First.movePrev();
        Second.movePrev();
    }
    
    while (First.position() > 0) {
        Result.insertAfter(First.peekPrev());
        First.movePrev();
    }
    
    while (Second.position() > 0) {
        Result.insertAfter(Second.peekPrev());
        Second.movePrev();
    }

    Result.moveFront();
    while (Result.front() == 0 && Result.length() > 1) {
        Result.eraseAfter();
    }
}

void invertListValues(List& myList) {
    for (myList.moveFront(); myList.position() < myList.length(); myList.moveNext()) {
        myList.setAfter(myList.peekNext() * -1);
    }
}

void negateList(List* L) {
    L->moveFront();

    for (; L->length() > 0 && !L->peekNext(); L->eraseAfter());
}


int normalizeList(List& L) {
    if (L.front() == 0) return 0;

    int sign = L.front() < 0 ? -1 : 1;
    if (sign == -1) invertListValues(L);

    int carry = 0;
    for (L.moveBack(); L.position() > 0; L.movePrev()) {
        int element = L.peekPrev() + carry;
        carry = 0;

        if (element < 0) {
            element += BASE;
            carry = -1;
        } else if (element >= BASE) {
            carry = element / BASE;
            element %= BASE;
        }

        L.setBefore(element);
    }

    if (carry > 0) {
        L.moveFront();
        L.insertAfter(carry);
    }

    return sign;
}


void shiftList(List& L, int p) {
    L.moveBack();
    int i = 0;
    while (i < p) {
        L.insertAfter(0);
        i++;
    }
}


List scalarMult(long s, List* tempList, int* count) {
    ListElement carry = 0, tempL = 0;
    List newList;

    tempList->moveBack();

    while (tempList->position() > 0) {
        tempL = (tempList->peekPrev() * s) + carry;
        carry = tempL / BASE;
        tempL %= BASE;
        newList.insertAfter(tempL);
        tempList->movePrev();
    }

    if (carry > 0) {
        newList.insertAfter(carry);
    }

    newList.moveBack();
    int pos = 0;

    while (pos < *count) {
        newList.insertAfter(0);
        pos += 1;
    }

    return (newList);
}


BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger A = *this; 
    BigInteger B = N;
    BigInteger C;

    if (A.sign() > 0 && B.sign() < 0) {
        B.negate();
        return (A - B);
    }
    if (A.sign() < 0 && B.sign() > 0) {
        A.negate();
        return (B - A);
    }
    if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        C = A.add(B);
        C.negate();
        return (C);
    }

    if (A > B) {
	std::swap(A, B);
    }

    List aList = A.digits;
    List bList = B.digits;
    List cList = C.digits;
    ListElement carry = 0;

    aList.moveBack();
    bList.moveBack();

    for (; aList.position() > 0 && bList.position() > 0; aList.movePrev(), bList.movePrev()) {
        ListElement element = carry + aList.peekPrev() + bList.peekPrev();
        carry = element / BASE;
        element %= BASE;
        cList.insertAfter(element);
    }

    for (; bList.position() > 0; bList.movePrev()) {
        ListElement element = carry + bList.peekPrev();
        carry = element / BASE;
        element %= BASE;
        cList.insertAfter(element);
    }

    if (carry > 0) {
        cList.insertAfter(carry);
    }

    C.signum = 1;
    C.digits = cList;
    return (C);
}


BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger A = N; 
    BigInteger B = *this;
    BigInteger C;

    List aList = A.digits;
    List bList = B.digits; 
    List cList = C.digits;

    if (A == B){
        return C;
    }

    if (!A.sign() && B.sign()) {
        return B;
    }

    if (A.sign() && !B.sign()) { 
        A.negate(); 
        return A; 
    }

    if (A.sign() < 0 && B.sign() > 0) { 
        B.negate(); 
        C = A.add(B); 
        C.negate(); 
        return C; 
    }

    if (A.sign() > 0 && B.sign() < 0) { 
        A.negate(); 
        C = A.add(B); 
        return C; 
    }

    if (A.sign() < 0 && B.sign() < 0) { 
        A.negate(); 
        B.negate(); 
        C = B.sub(A); 
        C.negate(); 
        return C; 
    }

    if (A < B) { 
        C = A.sub(B); 
        C.negate(); 
        return C; 
    }

    aList.moveBack();
    bList.moveBack();
    ListElement dist = 0;
    ListElement element = 0;
    int pos = bList.position();

    for (; pos > 0; --pos) {
        if (aList.peekPrev() - dist < bList.peekPrev()) {
            element = aList.peekPrev() + BASE - bList.peekPrev() - dist;
            dist = 1;
        } 
        else {
            element = aList.peekPrev() - dist - bList.peekPrev();
            if (aList.peekPrev() > 0) {
                dist = 0;
            }
        }
        cList.insertAfter(element);
        aList.movePrev();
        bList.movePrev();
    }

    for (; aList.position() > 0; aList.movePrev()) {
        if (aList.peekPrev() - dist < 0) {
            element = aList.peekPrev() + BASE - 0 - dist;
            dist = 1;
        } 
        else {
            element = aList.peekPrev() - dist - 0;
            if (aList.peekPrev() > 0) {
                dist = 0;
            }
        }
        cList.insertAfter(element);
    }

    C.digits = cList;
    negateList(&(C.digits));
    C.signum = -1;
    return (C);
}





// multiplication heler function

List multiplyAndShift(long scalar, List *inputList, int* shiftCount) {
    List result;
    long carryOver = 0;
    long intermediateResult = 0;

    inputList->moveBack();
    while (inputList->position() > 0) {
        intermediateResult = (inputList->peekPrev() * scalar) + carryOver;
        carryOver = intermediateResult / BASE;
        intermediateResult %= BASE;
        result.insertAfter(intermediateResult);
        inputList->movePrev();
    }

    if (carryOver > 0) {
        result.insertAfter(carryOver);
    }

    result.moveBack();
    int zerosToAppend = *shiftCount;
    while (zerosToAppend-- > 0) {
        result.insertAfter(0);
    }

    return result;
}


 
BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger A;
    List newList = N.digits; 
    List digVal = digits;

    newList.moveBack();
    digVal.moveBack();

    int count = 0;
    int pos = newList.position();
    
    while (pos > 0) {
        List element = scalarMult(newList.peekPrev(), &digVal, &count);
        BigInteger newBigInt;
        newBigInt.signum = 1;
        newBigInt.digits = element;
        A = A.add(newBigInt);
        newList.movePrev();
        count += 1 ;
        pos -= 1 ;
    }
    
    A.signum = signum * N.signum;
    return (A);
}




std::string BigInteger::to_string() {
    std::string output;
    if (this->signum == 0) {
        return "0";
    }
    if (this->signum == -1) {
        output = "-";
    }
    
    digits.moveFront();
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }
    
    bool isFirstDigit = true;
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        if (!isFirstDigit) {
            for (int i = std::to_string(digits.peekNext()).length(); i < POWER; ++i) {
                output += '0';
            }
        }
        output += std::to_string(digits.peekNext());
        isFirstDigit = false;
    }
    return output;
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











