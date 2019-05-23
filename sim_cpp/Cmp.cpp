//
// Created by Ark on 5/20/2019.
//

#include "Cmp.h"
#include <algorithm>
#include <iostream>

using namespace std;

double Cmp::LCS(string str1, string str2) {
    if(str1.length() < 3 || str2.length() < 3) return 0;
    cout << "------\n" << str1 << '\n' << str2 << '\n';
    int **lcstable;
    lcstable = new int*[str1.length()+1];
    int i, j;
    for (i = 0; i < str1.length()+1; i++) lcstable[i] = new int[str2.length()+1];
    for (i = 0; i < str1.length()+1; i++) {
        for (j = 0; j < str2.length()+1; j++) {
            if (i == 0 || j == 0) lcstable[i][j] = 0;
            else if (str1[i] == str2[j]) lcstable[i][j] = lcstable[i-1][j-1] + 1;
            else lcstable[i][j] = max(lcstable[i-1][j], lcstable[i][j-1]);
        }
    }
    double rate = double(lcstable[str1.length()][str2.length()]) / (str1.length() > 0 ? str1.length() : 1);
    for (i = 0; i < str1.length()+1; i++) delete[]lcstable[i];
    delete[]lcstable;
    cout << rate << '\n';

    return rate;
}

Cmp::Cmp(const string &filename1, const string &filename2, const double &cprate) {
    copyrate = cprate;
    file1.open(filename1); file2.open(filename2);
}

Cmp::~Cmp() {
    file1.close(); file2.close();
}

double Cmp::LCS() {
    string line1, line2;
    int linenum = 0;
    int copyline = 0;
    double rate = 0;
    while (getline(file1, line1)) {
        rate = 0;
        file2.seekg(0, ios::beg);
        while (rate < 1 && !file2.eof()) {
            getline(file2, line2);
            rate = max(rate, LCS(line1, line2));
        }
        if (rate > copyrate) copyline++;
        linenum++;
    }
    return double(copyline) / double(linenum);
}
