//
// Created by Ark on 5/20/2019.
//

#include "Cmp.h"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

double Cmp::LCS(string &str1, string &str2) {
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

Cmp::Cmp(const string &filename1, const string &filename2, int kk, int ww, int b) : k(kk), w(ww), B(b) {
    file1.open(filename1); file2.open(filename2);
}

Cmp::~Cmp() {
    file1.close(); file2.close();
}

double Cmp::LCS(double copyrate) {
    string line1, line2;
    int linenum = 0;
    int copyline = 0;
    double rate = 0;
    file1.seekg(0, ios::beg);
    while (!file1.eof()) {
        getline(file1, line1);
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

double Cmp::kgramHash(double copyrate) {
    string line1, line2;
    int linenum = 0;
    int copyline = 0;
    double rate = 0;
    int i, n;
    file1.seekg(0, ios::beg);
    while (!file1.eof()) {
        getline(file1, line1);
        rate = 0;
        file2.seekg(0, ios::beg);
        while (rate < 1 && !file2.eof()) {
            getline(file2, line2);
            int *hashl1 = encodehash(line1);
            int *hashl2 = encodehash(line2);
        }
        if (rate > copyrate) copyline++;
        linenum++;
    }
    return 0;
}

string *Cmp::kgram(const string &str) {
    int n = str.length();
    auto *strgram = new string[n-k+1];
    for(int i = 0; i < n-k+1; ++i)
        strgram[i] = str.substr(i, k);
    return strgram;
}

int Cmp::hash(const string &str) {
    int hashgram = 0;
    for (int i = 0; i < str.length(); ++i) hashgram += int(str[i] * pow(B, k-i-1));
    return hashgram;
}

int *Cmp::winnowing(int *hashset) {
    return nullptr;
}

int *Cmp::encodehash(string &str) {
    string *strgram = kgram(str);
    int n = str.length();
    int i;
    int *hasharray = new int[n-k+1];
    for (i = 0; i < n-k+1; ++i)
        hasharray[i] = hash(strgram[i]);
    int *gramhash = winnowing(hasharray);
    delete[]strgram;
    delete[]hasharray;

    return gramhash;
}
