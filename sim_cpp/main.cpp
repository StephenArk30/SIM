#include <iostream>
#include <stdlib.h>
#include "Lexer.h"
#include "Cmp.h"

using namespace std;

int main() {
    cout << "Reading cmp1.c and cmp2.c" << std::endl;
    Lexer lexer1("../cmp1");
    Lexer lexer2("../cmp2");
    lexer1.analyse();
    lexer2.analyse();
    cout << "\n\n==========format done==========\n\n";
    system("pause");
    Cmp cmp("../cmp1_output.c", "../cmp2_output.c", 8, 4, 3);
    cout << "=====LCS=====\n";
    cout << "cmp1 have " << cmp.LCS(0.9) << " percent similarity with cmp2\n";
    cout << "=====LCS done=====\n";
    system("pause");
    cout << "=====K-gram=====\n";
    cout << "cmp1 have " << cmp.kgramHash(0.5) << " percent similarity with cmp2\n";
    cout << "=====K-gram done=====\n";

    return 0;
}