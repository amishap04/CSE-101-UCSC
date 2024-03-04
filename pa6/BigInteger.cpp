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

const ListElement BASE  = 1000000000;  
const int         POWER = 9;           


void removeLeadingZeros( List* L) {
    L->moveFront();
    while (L->length() > 0 && !L->peekNext()) {
        L->eraseAfter();
    }
}

List multHelper(long sVal, List *bList, int* count) {
    List newL;
    long carryVal = 0;
    long temp = 0;

    for (bList->moveBack(); bList->position() > 0; bList->movePrev()) {
        temp = (bList->peekPrev() * sVal) + carryVal;
        carryVal = temp / BASE;
        temp %= BASE;
        newL.insertAfter(temp);
    }
    if (carryVal > 0) {
        newL.insertAfter(carryVal);
    }
    newL.moveBack();
    for (int i = 0; i < *count; i++) {
        newL.insertAfter(0);
    }
    return newL;
}


BigInteger::BigInteger() {
    digits = List();
    signum = 0;
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


BigInteger::BigInteger(std::string s) {
    if (!s.length()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    int indent = 0;
    if ((s[0] == '+') | (s[0] == '-')) {
        signum = 1;
        if (s[0] == '-') {
            signum = -1;
        }
        indent = 1;
        s = s.substr(indent, s.length() - 1);
    } 
    else {
        signum = 1;
    }

    for (long unsigned int i = 0; i < s.length();) {
        if (!std::isdigit(s[i])) {
            throw std::invalid_argument("BigInt Constructor is non-numeric");
        }
        i = i + 1;
    }

    string comp = "";
    List L;
    size_t maxVal = 0;
    size_t curr = s.length();

    while (maxVal < s.length() / POWER) {
        comp = s.substr(curr - POWER, POWER);
        digits.insertAfter(std::stol(comp, nullptr, 10));
        curr = curr - POWER;
        maxVal++;
    }
    if (curr > 0) {
        comp = s.substr(0, curr);
        digits.insertAfter(std::stol(comp, nullptr, 10));
    }

    removeLeadingZeros(&digits);  
}




BigInteger::BigInteger(const BigInteger& N) {
    this->digits = N.digits;
    this->signum = N.signum;
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


void negateList(List& L) {
    L.moveFront();

    while (L.position() < L.length()) {
        L.setAfter(-1 * L.peekNext());
        L.moveNext();
    }

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


int normalizeList(List& L) {
    if (L.front() == 0) {
        return 0;
    }

    int signVal = 1;
    if (L.front() < 0) {
        negateList(L);
        signVal = -1;
    }

    ListElement val = 0;
    int carryOver = 0;
    L.moveBack();
    while (L.position() > 0) {
        val = L.peekPrev();
        if (val < 0) {
            val += BASE + carryOver;
            L.setBefore(val);
            carryOver = -1;
        }
        else {
            val += carryOver;
            carryOver = 0;
            if (val >= BASE) {
                carryOver = val / BASE;
                val = val % BASE;
            }
            L.setBefore(val);
        }
        L.movePrev();
    }
    if (carryOver != 0) {
        L.moveFront();
        L.insertAfter(carryOver);
    }
    return signVal;
}

void shiftList(List& L, int p) {
    L.moveBack();
    int i = 0;
    while (i < p) {
        L.insertAfter(0);
        i++;
    }
}



void scalarMultList(List& L, ListElement element) {
    L.moveFront();
    while (L.position() < L.length()) {
        L.setAfter(L.peekNext() * element);
        L.moveNext();
    }
}



BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger A = *this;
    BigInteger B = N;
    BigInteger C;
    if (A.sign() > 0 && B.sign() < 0) {
        B.negate();
        return A.sub(B);
    } else if (A.sign() < 0 && B.sign() > 0) {
        A.negate();
        return B.sub(A);
    } else if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        C = A.add(B);
        C.negate();
        return C;
    }
    if (A > B) {
        return B.add(A);
    }
    List aList = A.digits;
    List bList = B.digits;
    List cList = C.digits;
    long carry = 0;
    long temp = 0;
    aList.moveBack();
    bList.moveBack();
    while (aList.position() > 0 && bList.position() > 0) {
        temp = carry + aList.peekPrev() + bList.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        cList.insertAfter(temp);
        aList.movePrev();
        bList.movePrev();
    }
    while (bList.position() > 0) {
        temp = carry + bList.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        cList.insertAfter(temp);
        bList.movePrev();
    }
    if (carry > 0) {
        cList.insertAfter(carry);
    }
    C.signum = 1;
    C.digits = cList;
    return C;
}



BigInteger BigInteger::sub(const BigInteger& N) const {
    
    BigInteger A = N;
    BigInteger B = *this;
    BigInteger C;
    List aList = A.digits;
    List bList = B.digits;
    List cList = C.digits;

    if (A == B) {
        return C;
    }
    if (A.sign() && !B.sign()) {
        A.negate();
        return A;
    }
    if (!A.sign() && B.sign()) {
        return B;
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
    long dist = 0;
    long temp = 0;
    int i = bList.position();
    while (!(i <= 0)) {
        if (aList.peekPrev() - dist < bList.peekPrev()) {
            temp = aList.peekPrev() + BASE - bList.peekPrev() - dist;
            dist = 1;
        } else {
            temp = aList.peekPrev() - dist - bList.peekPrev();
            dist = 0;
        }
        cList.insertAfter(temp);
        aList.movePrev();
        bList.movePrev();
        i--;
    }
    while (aList.position() > 0) {
        if (aList.peekPrev() - dist < 0) {
            temp = aList.peekPrev() + BASE - dist;
            dist = 1;
        } else {
            temp = aList.peekPrev() - dist;
            dist = 0;
        }
        cList.insertAfter(temp);
        aList.movePrev();
    }
    C.digits = cList;
    removeLeadingZeros(&(C.digits));
    C.signum = -1;
    return C;
}


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
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;

    List aList = A.digits;
    List bList = B.digits;
    
    int count = 0;

    aList.moveBack();
    bList.moveBack();
    int pos = aList.position();
    for (int i = pos; i > 0; i--) {
        List temp = multHelper(aList.peekPrev(), &bList, &count);  
        BigInteger Temp;
        Temp.signum = 1;
        Temp.digits = temp;
        C = C.add(Temp);  
        aList.movePrev();  
        count++;
    }
    C.signum = A.signum * B.signum;  
    return C;
}

std::string BigInteger::to_string() {
    std::string out = "";
    if (this->signum == 0) {
        return "0";  
    } else if (signum == -1) {
        out += "-";  
    }
    digits.moveFront();

    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string A = std::to_string(digits.peekNext());
        std::string B = "";

        while ((int)(B.length() + A.length()) < POWER && digits.position() != 0) {
            B += '0';
        }
        out += (B + A);  
    }
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






