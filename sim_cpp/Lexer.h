//
// Created by Ark on 2019/5/17.
//

#ifndef SIM_CPP_LEXER_H
#define SIM_CPP_LEXER_H

#include <fstream>
#include <string>
#include <map>
#include "keyword.h"

using namespace std;

class Lexer {
private:
    ifstream ifile;
    ofstream ofile;
    keyword *kw;
    map<string, string> macro;
    string replace_keyword(const string& line);
    string preprocessing(const string& line);
    bool judgeCommentStart(string& line);
    bool judgeCommentEnd(string& line);
public:
    explicit Lexer(const string& filename);
    ~Lexer();
    void analyse();
};


#endif //SIM_CPP_LEXER_H
