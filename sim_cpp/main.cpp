#include <iostream>
#include "Lexer.h"
#include "Cmp.h"

using namespace std;

int main() {
    cout << "Reading cmp1.c and cmp2.c" << std::endl;
    Lexer lexer1("../cmp1");
    Lexer lexer2("../cmp2");
    lexer1.analyse();
    lexer2.analyse();


    return 0;
}