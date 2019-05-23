//
// Created by Ark on 5/20/2019.
//

#ifndef SIM_CPP_CMP_H
#define SIM_CPP_CMP_H

#include <string>
#include <fstream>

using namespace std;

class Cmp {
private:
    ifstream file1, file2;
    double LCS(string &str1, string &str2);
    string* kgram(const string &str);
    int hash(const string &str);
    int* winnowing(int *hashset);
    int* encodehash(string &str);
    int k; int w; int B;
public:
    Cmp(const string &filename1, const string &filename2, int kk, int ww, int b);
    ~Cmp();
    double LCS(double copyrate);
    double kgramHash(double copyrate);
};


#endif //SIM_CPP_CMP_H
