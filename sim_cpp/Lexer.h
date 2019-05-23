//
// Created by Ark on 2019/5/17.
//

#ifndef SIM_CPP_LEXER_H
#define SIM_CPP_LEXER_H

#include <fstream>
#include <string>
#include "keyword.h"
#include "symbols.h"
#include "variate.h"

using namespace std;

class Lexer {
private:
    ifstream ifile;
    ofstream ofile;
    keyword *kw;
    symbols *sybs;
    variate *var;

    void preprocessing(string &line);

    void replaceunit(string &line);

    bool replacenum(string &num);

    bool hasCommentStart(string &line);

    bool hasCommentEnd(string &line);
public:
    explicit Lexer(const string& filename);
    ~Lexer();
    void analyse();
};


#endif //SIM_CPP_LEXER_H
