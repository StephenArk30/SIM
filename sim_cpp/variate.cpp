//
// Created by Ark on 5/23/2019.
//

#include "variate.h"
#include <map>
#include <sstream>

variate::variate() {
    macro.empty();
}

void variate::addmacro(const string &key, const string &val) {
    auto iter = macro.find(key);
    if (iter != macro.end())
        macro.insert(pair<string, string>(key, val));
}

bool variate::getmacrovalue(string &key) {
    auto iter = macro.find(key);
    if (iter != macro.end()) {
        key = iter->second;
        return true;
    }
    return false;
}

bool variate::replacevar(string &varname) {
    int id = 0;
    for (auto it = varset.begin(); it < varset.end(); it++) {
        if (*it == varname) {
            ostringstream varstream;
            varstream << "$3," << id << "$";
            varname = varstream.str();
            return true;
        }
        id++;
    }
    varset.push_back(varname);
    return false;
}
