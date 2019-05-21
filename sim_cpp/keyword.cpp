//
// Created by Ark on 2019/5/16.
//

#include "keyword.h"
#include <string>
#include <cstring>

keyword::keyword() {
    keywords = new string[32];
    type = new int[32];
    suffix = new string[6];
    int i;
    /**
     * 0. 后跟n个*,
     * 1. 后跟{...
     * 2. 后跟(...
     * 3. 无
     * 4. 后跟;
     * */
     // 关键字
    std::string words[32] = {
            "void", "char", "short", "int", "long", "float", "double", // 7
            "else", "do", // 2
            "if", "for", "while", "switch", "sizeof", // 5
            "case", "default", "goto", "auto", "static", "extern", "register", "const", "volatile", "struct", "union", "enum", "typedef", "signed", "unsigned", // 15
            "break", "continue", "return" // 3
    };
    // 关键字对应类型
    int wordstype[32] = {
            0,0,0,0,0, 0,0,
            1,1,
            2,2,2,2,2,
            3,3,3,3,3, 3,3,3,3,3, 3,3,3,3,3,
            4,4,4
    };
    for(i = 0; i < 32; i++) {
        keywords[i] = words[i];
        type[i] = wordstype[i];
    }

    // 关键字类型对应后缀
    string wordssuffix[] = {
            "\\**", // 1
            "", // 1
            "", // 1
            "", // 1
            ";", // 1
            ";" // 1
    };
    for(i = 0; i < 6; i++)
        suffix[i] = wordssuffix[i];
}

keyword::~keyword() {
    delete[] keywords;
    delete[] type;
    delete[] suffix;
}
