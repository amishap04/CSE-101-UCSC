/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA7 // Assignment Number
 * * * * Order.cpp // FileName
 * * * * Client file for Dictionary ADT // Description
 * * * ***/


#include "Dictionary.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        return EXIT_FAILURE;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Could not open the file " << argv[1] << endl;
        return EXIT_FAILURE;
    }
    ofstream outfile;
    outfile.open(argv[2], fstream::out);


    Dictionary D;
    string k = "";
    int v = 1;
    while (getline(infile, k)) {
        D.setValue(k, v);
        v++;
    }

    outfile << D.to_string() << endl;
    outfile << D.pre_string() << endl;

    D.clear();

    infile.close();
    outfile.close();
    return EXIT_SUCCESS;
}



