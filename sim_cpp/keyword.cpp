//
// Created by Ark on 2019/5/16.
//

#include "keyword.h"
#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

keyword::keyword() {
    keywords = new string[32];
    type = new int[32];
    int i;
     // 关键字
    std::string words[32] = {
            "void", "char", "short", "int", "long", "float", "double", // 类型关键字 7
            "volatile", "register", "extern", "signed", "unsigned", "static", "const", "auto", "break", "continue",
            "return", // 修饰类型关键字 11
            "else", "do", "if", "for", "while", "switch", "case", "default", "goto", // 控制关键字 9
            "struct", "union", "enum", // 结构关键字 3
            "typedef", // typedef
            "sizeof", // sizeof
    };
    // 关键字对应类型
    int wordstype[32] = {
            0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2, 2,
            3, 3, 3,
            4, 5
    };
    for(i = 0; i < 32; i++) {
        keywords[i] = words[i];
        type[i] = wordstype[i];
    }
}

keyword::~keyword() {
    delete[] keywords;
    delete[] type;
}

bool keyword::replacekeyword(string &unit) {
    ostringstream kwstream;
    for (int i = 0; i < 32; ++i) {
        if (unit == keywords[i]) {
            kwstream << "$1," << setw(4) << setfill('0') << type[i] << "$";
            unit = kwstream.str();
            return true;
        }
    }
}
