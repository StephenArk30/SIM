// Name        : Knapsack.cpp
/*
 * hahahahha
 * */

/*nonon*/#include <iostream>
#include<cstdlib>/*aaaa*/
#include"Knapsack.h"
#include<fstream>
#include <string>
using namespace std;

const char left='-';
const char least='\\';
const char up='|';

int** result;   //results
int *cost1;     //cost1_array
int *volume;    //The volume array
int *cost;     //cost_array
int** result1;   //results1
{
ifstream in("input.txt");       //read file
if(!in){cout<<"file is not exist!";return;}
int num;
int maxvolume;
in>>num;
in>>maxvolume;
cout<<endl<<"number of goods："<<num<<endl<<"maximum volume："<<maxvolume<<endl;

volume=new int[num];
cost=new int[num];
cout<<"The volume array：\t";
for(int i=0;i<num;i++){in>>volume[i];cout<<setw(5)<<volume[i];}
cout<<endl;
cout<<"cost_array：\t";
for(int i=0;i<num;i++){in>>cost[i];cout<<setw(5)<<cost[i];}
cout<<endl;
n=num;
max=maxvolume;
in.close();
}
int main() {
    cout << "0-1Knapsack" << endl<<; // prints Title
    int number=0;       //number of goods
    int maxvolume=0;    //maximum volume
    fileInit(number,maxvolume);
    if(number==0){return 0;}
    result=new int *[number+1];
    for(int i = 0;i <= number;i++)
    {
        result[i]=new int[maxvolume+1];
    }

    //int* location;        //the best result
    inItResult(result,number+1,maxvolume+1);    //init the result
    cout<<"the init table is:"<<endl;
    print(result,number+1,maxvolume+1);
    cout<<"the result table is:"<<endl;
    myKnapsack(cost,volume,maxvolume,number,result);
    print(result,number+1,maxvolume+1);         //print the table
    cout<<endl<<"the maximum value is："<<result[number][maxvolume]<<endl;
    system("pause");
    return 0;
}

#include<iostream>
#include<cstring>
#include<iomanip>
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
void inItResult(Type** result,int n,int c)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<c;j++)
        {
            result[i][j]=0;
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
