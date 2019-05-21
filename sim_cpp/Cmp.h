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
    double copyrate;
    double LCS(string, string);
public:
    Cmp(const string&, const string&, const double&);
    ~Cmp();
    double LCS();
};


#endif //SIM_CPP_CMP_H
