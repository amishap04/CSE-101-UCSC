/**
 * * * * Amisha Prasad // First and Last Name
 * * * * aprasa14 // UCSC UserID
 * * * * 2024 Winter CSE101 PA8 // Assignment Number
 * * * * WordFrequency.cpp // FileName
 * * * * Client file for Dictionary ADT // Description
 * * * ***/

#include "Dictionary.h"
#include <fstream>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    size_t begin;
    size_t end;
    size_t len;
    ifstream input;
    ofstream output;
    string line;
    string key;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    Dictionary newDict;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    input.open(argv[1]);

    if (!input.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    output.open(argv[2]);

    if (!output.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input, line)) {
        len = line.length();

        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        key = line.substr(begin, (end - begin));

        while (key != "") {
            transform(key.begin(), key.end(), key.begin(), ::tolower);

            if (newDict.contains(key)) {
                newDict.getValue(key)++;
            }
            else {
                newDict.setValue(key, 1);
            }

            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            key = line.substr(begin, (end - begin));
        }
    }

    output << newDict << endl;
    
    newDict.clear();
    input.close();
    output.close();

    return 0;
}

