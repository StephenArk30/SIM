//
// Created by Ark on 5/23/2019.
//

#ifndef SIM_CPP_VARIATE_H
#define SIM_CPP_VARIATE_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class variate {
private:
    map<string, string> macro;
    vector<string> varset;
public:
    variate();

    void addmacro(const string &key, const string &val);

    bool getmacrovalue(string &key);

    bool replacevar(string &varname);
};


#endif //SIM_CPP_VARIATE_H
