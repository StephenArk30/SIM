//
// Created by Ark on 5/22/2019.
//

#ifndef SIM_CPP_SYMBOLS_H
#define SIM_CPP_SYMBOLS_H

#include <string>

using namespace std;

class symbols {
public:
    int gap_sybs_num;
    int del_sybs_num;
    string *gap_sybs;
    string *del_sybs;

    bool replacesymbol(string &symbol);

    symbols();

    ~symbols();
};


#endif //SIM_CPP_SYMBOLS_H
