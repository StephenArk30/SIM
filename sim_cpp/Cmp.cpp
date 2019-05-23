//
// Created by Ark on 5/20/2019.
//

#include "Cmp.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>

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
    file1.seekg(0, ios::beg);
    while (!file1.eof()) {
        getline(file1, line1);
        map<int, int> hashl1 = encodehash(line1);
        rate = 0;
        file2.seekg(0, ios::beg);
        while (rate < 1 && !file2.eof()) {
            getline(file2, line2);
            map<int, int> hashl2 = encodehash(line2);
            rate = max(rate, findpublichash(hashl1, hashl2));
        }
        if (rate > copyrate) copyline++;
        linenum++;
    }
    return double(copyline) / double(linenum);
}

string *Cmp::kgram(const string &str) {
    int n = str.length();
    auto *strgram = new string[n-k+1];
    for(int i = 0; i < n-k+1; ++i)
        strgram[i] = str.substr(i, k);
    return strgram;
}

int Cmp::hash(const string &str, int prehash, int preroll) {
    int hashgram = 0;
    if (prehash < 0) for (int i = 0; i < str.length(); ++i) hashgram += int(str[i] * pow(B, k - i - 1));
    else hashgram = (prehash - int(preroll * pow(B, k - 1))) * B + str[str.length() - 1];
    return hashgram;
}

map<int, int> Cmp::winnowing(const int *hashset, int setsize) {
    map<int, int> hashmap;
    map<int, int>::iterator iter;
    int mini = 0, minh = 0;
    for (int i = 0; i < setsize - w + 1; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j == 0) {
                minh = hashset[i];
                mini = i;
            } else if (minh >= hashset[i + j]) {
                minh = hashset[i + j];
                mini = i + j;
            }
        }
        iter = hashmap.find(mini);
        if (iter != hashmap.end())
            hashmap.insert(pair<int, int>(mini, minh));
    }
    return hashmap;
}

map<int, int> Cmp::encodehash(string &str) {
    string *strgram = kgram(str);
    int n = str.length();
    int i;
    int *hasharray = new int[n-k+1];
    for (i = 0; i < n - k + 1; ++i) {
        if (i == 0) hasharray[i] = hash(strgram[i], -1, -1);
        else hasharray[i] = hash(strgram[i], hasharray[i - 1], strgram[i - 1][0]);
    }
    map<int, int> gramhash = winnowing(hasharray, n - k + 1);
    delete[]strgram;
    delete[]hasharray;

    return gramhash;
}

double Cmp::findpublichash(map<int, int> hashmap1, map<int, int> hashmap2) {
    map<int, int>::iterator iter1, iter2;
    int publichash = 0;
    for (iter1 = hashmap1.begin(); iter1 != hashmap1.end(); iter1++) {
        for (iter2 = hashmap2.begin(); iter2 != hashmap2.end(); iter2++) {
            if (iter2->second == iter1->second) {
                publichash++;
                break;
            }
        }
    }
    cout << publichash << " token from A is the same from B\n";
    return double(publichash) / hashmap1.size();
}
