//
// Created by Ark on 2019/5/16.
//

#ifndef SIM_CPP_KEYWORD_H
#define SIM_CPP_KEYWORD_H

#include <string>
using namespace std;

class keyword {
public:
    string *keywords;
    int *type;
    string *suffix;
    keyword();
    ~keyword();
};


#endif //SIM_CPP_KEYWORD_H
