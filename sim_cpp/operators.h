//
// Created by Ark on 5/22/2019.
//

#ifndef SIM_CPP_OPERATORS_H
#define SIM_CPP_OPERATORS_H

#include <string>

using namespace std;

class operators {
public:
    int gap_opts_num;
    int del_opts_num;
    string *gap_opts;
    string *del_opts;
    operators();
    ~operators();
};


#endif //SIM_CPP_OPERATORS_H
