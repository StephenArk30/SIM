//
// Created by Ark on 5/22/2019.
//

#include <sstream>
#include "symbols.h"

symbols::symbols() {
    gap_sybs_num = 16;
    del_sybs_num = 7;

    int i;
    gap_sybs = new string[gap_sybs_num];
    string temp_gap_sybs[] = {
            "\\!", "%", "\\^", "&", "\\*",
            "\\-", "\\+", "\\=", "\\|", "\\:",
            "\\<", "\\>", ",", "/", "\\?",
            "#"
    };
    for (i = 0; i < gap_sybs_num; i++) gap_sybs[i] = temp_gap_sybs[i];

    del_sybs = new string[del_sybs_num];
    string temp_del_sybs[] = {
            "\\(", "\\)", "\\{", "\\}", "\\[", "\\]", ";"
    };
    for (i = 0; i < del_sybs_num; i++) del_sybs[i] = temp_del_sybs[i];
}

symbols::~symbols() {
    delete[] gap_sybs;
    delete[] del_sybs;
}

bool symbols::replacesymbol(string &symbol) {
    for (int i = 0; i < gap_sybs_num; ++i) {
        if (symbol[0] == gap_sybs[i][gap_sybs[i].length() - 1]) {
            ostringstream sybstream;
            sybstream << "$2," << i << "$";
            symbol = sybstream.str();
            return true;
        }
    }
    return false;
}
