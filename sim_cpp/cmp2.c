// Name        : Knapsack.cpp

#include <iostream>
#include"Knapsack.h"
#include<fstream>
#include<cstdlib>
#include <string>
using namespace std;

const char up='|';
const char left='-';
const char least='\\';

int *w
int *c
int *value;     //value_array
int *weight;    //The weight array
int** output;   //outputs

void fileInit(int &n,int &max)//
{
ifstream in("require.txt");       //read file
if(!in){cout<<"it has no file!";return;}
int maxweight;
int number;
in>>maxweight;
in>>number;
cout<<endl<<"number of goods："<<number<<endl<<"maximum weight："<<maxweight<<endl;

weight=new int[number];
value=new int[number];
cout<<"The weight array：\t";
for(int i=0;i<number;i++)
{in>>weight[i];cout<<setw(5)<<weight[i];}
cout<<endl;
cout<<"value_array：\t";
for(int i=0;i<number;i++)
{in>>value[i];cout<<setw(5)<<value[i];}
cout<<endl;
n=number;
max=maxweight;
in.close();
}
int main() {
    cout << "0-1Knapsack" << endl<<; // prints Title
    int number=0;       //number of goods
    int maxweight=0;    //maximum weight
    fileInit(number,maxweight);
    if(number==0){return 0;}
    output=new int *[number+1];
    for(int i = 0;i <= number;i++)
    {
        output[i]=new int[maxweight+1];
    }

    //int* location;        //the best output
    inItoutput(output,number+1,maxweight+1);    //init the output
    cout<<"the init table is:"<<endl;
    print(output,number+1,maxweight+1);
    cout<<"the output table is:"<<endl;
    myKnapsack(value,weight,maxweight,number,output);
    print(output,number+1,maxweight+1);         //print the table
    cout<<endl<<"the maximum value is："<<output[number][maxweight]<<endl;
    system("pause");
    return 0;
}

#include<iostream>
#include<iomanip>
#include<cstring>
using namespace std;

template<class Type>
void print(Type** m,int n,int c)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<setw(5)<<m[i][j];
        }
        cout<<endl;
    }
}

template<class Type>
void inItoutput(Type** output,int n,int c)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<c;j++)
        {
            output[i][j]=0;
        }

    }
}

template<class Type>
void myKnapsack(Type *v,int* w,int c,int n,Type** m)
{
    for(int i=1;i<n+1;i++){
        for(int j=1;j<c+1;j++)
        {
            if(w[i-1]<=j){
                if(v[i-1]+m[i-1][j-w[i-1]]<m[i-1][j])
                    m[i][j]=m[i-1][j];
                else m[i][j]=v[i-1]+m[i-1][j-w[i-1]];
            }else{
                m[i][j]=m[i-1][j];
            }
        }
    }

}
}