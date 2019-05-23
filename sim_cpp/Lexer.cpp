//
// Created by Ark on 2019/5/17.
//
#include "Lexer.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <map>

Lexer::Lexer(const string& filename) {
    kw = new keyword();
    opts = new operators();
    ifile.open(filename + ".c");
    ofile.open(filename + "_output.c");
}

Lexer::~Lexer() {
    delete(kw);
    ifile.close();
    ofile.close();
}

void Lexer::analyse() {
    string line;
    int line_num = 1;
    bool inComment = false;
    while (getline(ifile, line)) {
        cout << line_num++ << ' ' << line << endl;
        preprocessing(line);
    }
}

void Lexer::preprocessing(string &line) {
    
}
