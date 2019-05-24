//
// Created by Ark on 5/20/2019.
//

#include "Cmp.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <fstream>

using namespace std;

double Cmp::LCS(string &str1, string &str2) {
    if(str1.length() < 3 || str2.length() < 3) return 0;
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
    file1 = filename1; file2 = filename2;
}

double Cmp::LCS(double copyrate) {
    string line1, line2;
    int linenum1 = 0;
    int linenum2 = 0;
    int copyline = 0;
    double rate = 0;
    ifstream fileA;
    fileA.open(file1);
    while (getline(fileA, line1)) {
        linenum1++;
        rate = 0;
        linenum2 = 0;
        ifstream fileB;
        fileB.open(file2);
        while (rate < 1 && getline(fileB, line2)) {
            linenum2++;
            cout << "------\n" << linenum1 << '\t' << line1 << '\n' << linenum2 << '\t' << line2 << '\n';
            rate = max(rate, LCS(line1, line2));
        }
        fileB.close();
        if (rate > copyrate) copyline++;
    }
    fileA.close();
    return double(copyline) / double(linenum1);
}

double Cmp::kgramHash(double copyrate) {
    string line1, line2;
    int linenum1 = 0;
    int linenum2 = 0;
    int copyline = 0;
    double rate = 0;
    fstream fileA;
    fileA.open(file1);
    while (getline(fileA, line1)) {
        linenum1++;
        map<int, int> hashl1 = encodehash(line1);
        rate = 0;
        linenum2 = 0;
        fstream fileB;
        fileB.open(file2);
        while (rate < 1 && getline(fileB, line2)) {
            linenum2++;
            cout << "------\n" << linenum1 << '\t' << line1 << '\n' << linenum2 << '\t' << line2 << '\n';
            map<int, int> hashl2 = encodehash(line2);
            rate = max(rate, findpublichash(hashl1, hashl2));
        }
        if (rate > copyrate) copyline++;
    }
    fileA.close();
    return double(copyline) / double(linenum1);
}

string *Cmp::kgram(const string &str) {
    int n = str.length();
    auto *strgram = new string[n-k+1];
    for(int i = 0; i < n-k+1; ++i) {
        string temp_string = str.substr(i, k);
        strgram[i] = temp_string;
    }
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
        if (iter == hashmap.end())
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

double Cmp::findpublichash(map<int, int> &hashmap1, map<int, int> &hashmap2) {
    map<int, int>::iterator iter1, iter2;
    int publichash = 0;
    int hashmap1size = 0;
    for (iter1 = hashmap1.begin(); iter1 != hashmap1.end(); iter1++) {
        hashmap1size++;
        for (iter2 = hashmap2.begin(); iter2 != hashmap2.end(); iter2++) {
            if (iter2->second == iter1->second) {
                publichash++;
                break;
            }
        }
    }
    double rate = double(publichash) / (hashmap1size ? hashmap1size : 1);
    cout << publichash << " of " << hashmap1size << " token from A is the same from B, sim rate: " << rate << "\n";
    return rate;
}
