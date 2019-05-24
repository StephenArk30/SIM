//
// Created by Ark on 5/22/2019.
//

#include <sstream>
#include <iomanip>
#include "symbols.h"

symbols::symbols() {
    gap_sybs_num = 18;
    del_sybs_num = 5;

    int i;
    gap_sybs = new string[gap_sybs_num];
    string temp_gap_sybs[] = {
            "\\!", "%", "\\^", "&", "\\*",
            "\\-", "\\+", "\\=", "\\|", "\\:",
            "\\<", "\\>", ",", "/", "\\?",
            "#", "\\{", "\\}"
    };
    for (i = 0; i < gap_sybs_num; i++) gap_sybs[i] = temp_gap_sybs[i];

    del_sybs = new string[del_sybs_num];
    string temp_del_sybs[] = {
//            "\\(", "\\)", "\\{", "\\}", "\\[", "\\]", ";"
            "\\(", "\\)", "\\[", "\\]", ";"
    };
    for (i = 0; i < del_sybs_num; i++) del_sybs[i] = temp_del_sybs[i];
}

symbols::~symbols() {
    delete[] gap_sybs;
    delete[] del_sybs;
}

bool symbols::replacesymbol(string &symbol, int linenum) {
    for (int i = 0; i < gap_sybs_num; ++i) {
        if (symbol[0] == gap_sybs[i][gap_sybs[i].length() - 1]) {
            if (symbol[0] == '{') {
                if (braces.empty()) {
                    funcstart.push_back(linenum);
//                    symbol = "-----func start-----";
                    symbol = "";
                }
                else symbol = "";
                braces.push(linenum);
                return true;
            }
            else if (symbol[0] == '}') {
                braces.pop();
                if (braces.empty()) {
                    funcend.push_back(linenum);
//                    symbol = "-----func end-----";
                    symbol = "";
                }
                else symbol = "";
                return true;
            }
            ostringstream sybstream;
            sybstream << "$2," << setw(4) << setfill('0') << i << "$";
            symbol = sybstream.str();
            return true;
        }
    }
    return false;
}
