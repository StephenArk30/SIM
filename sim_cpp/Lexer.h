//
// Created by Ark on 2019/5/17.
//

#ifndef SIM_CPP_LEXER_H
#define SIM_CPP_LEXER_H

#include <fstream>
#include <string>
#include <map>
#include "keyword.h"
#include "operators.h"

using namespace std;

class Lexer {
private:
    ifstream ifile;
    ofstream ofile;
    keyword *kw;
    operators *opts;
    map<string, string> macro;
    void preprocessing(string& line);
public:
    explicit Lexer(const string& filename);
    ~Lexer();
    void analyse();
};


#endif //SIM_CPP_LEXER_H
