#include <iostream>
#include "Lexer.h"
#include "Cmp.h"

using namespace std;

int main() {
    cout << "Reading cmp1.c and cmp2.c" << std::endl;
//    Lexer lexer("../cmp1");
//    lexer.analyse();
    Cmp cmp("../cmp1.c", "../cmp2.c");
    cout << "LCS: " << cmp.LCS() << endl;

    return 0;
}