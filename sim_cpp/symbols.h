//
// Created by Ark on 5/22/2019.
//

#ifndef SIM_CPP_SYMBOLS_H
#define SIM_CPP_SYMBOLS_H

#include <string>
#include <stack>
#include <vector>

using namespace std;

class symbols {
public:
    int gap_sybs_num;
    int del_sybs_num;
    string *gap_sybs;
    string *del_sybs;
    stack<int> braces;
    vector<int> funcstart;
    vector<int> funcend;

    bool replacesymbol(string &symbol, int linenum);

    symbols();

    ~symbols();
};


#endif //SIM_CPP_SYMBOLS_H
