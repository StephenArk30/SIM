//
// Created by Ark on 5/23/2019.
//

#include "variate.h"
#include <map>
#include <sstream>
#include <iomanip>

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
    ostringstream varstream;
    for (auto it = varset.begin(); it < varset.end(); it++) {
        if (*it == varname) {
            varstream << "$3," << setw(4) << setfill('0') << id << "$";
            varname = varstream.str();
            return true;
        }
        id++;
    }
    varset.push_back(varname);
    varstream << "$3," << setw(4) << setfill('0') << id << "$";
    varname = varstream.str();
    return true;
}
