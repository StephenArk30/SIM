using namespace std; 
$keyword, const$  $keyword, char$  left='-'; 
$keyword, const$  $keyword, char$  least='\\'; 
$keyword, const$  $keyword, char$  up='|'; 
$keyword, int$**  result; 
$keyword, int$  *cost1; 
$keyword, int$  *volume; 
$keyword, int$  *cost; 
$keyword, int$**  result1; 
{ 
ifstream in ( "input.txt" ) ; 
$keyword, if$  ( !in ) { cout<<"file is not exist!"; $keyword, return$;  } 
$keyword, int$  num; 
$keyword, int$  maxvolume; 
in>>num; 
in>>maxvolume; 
cout<<endl<<"number of goods："<<num<<endl<<"maximum volume："<<maxvolume<<endl; 
volume=new $keyword, int$  [num] ; 
cost=new $keyword, int$  [num] ; 
cout<<"The volume array：\t"; 
$keyword, for$  ( $keyword, int$  i=0; i<num; i++ ) { in>>volume [i] ; cout<<setw ( 5 ) <<volume [i] ; } 
cout<<endl; 
cout<<"cost_array：\t"; 
$keyword, for$  ( $keyword, int$  i=0; i<num; i++ ) { in>>cost [i] ; cout<<setw ( 5 ) <<cost [i] ; } 
cout<<endl; 
n=num; 
max=maxvolume; 
in.close ( ) ; 
} 
$keyword, int$  main ( ) { 
cout << "0-1Knapsack" << endl<<; 
$keyword, int$  number=0; 
$keyword, int$  maxvolume=0; 
fileInit ( number,maxvolume ) ; 
$keyword, if$  ( number==0 ) { return 0; } 
result=new $keyword, int$  * [number+1] ; 
$keyword, for$  ( $keyword, int$  i = 0; i <= number; i++ ) 
{ 
result [i] =new $keyword, int$  [maxvolume+1] ; 
} 
inItResult ( result,number+1,maxvolume+1 ) ; 
cout<<"the init table is:"<<endl; 
print ( result,number+1,maxvolume+1 ) ; 
cout<<"the result table is:"<<endl; 
myKnapsack ( cost,volume,maxvolume,number,result ) ; 
print ( result,number+1,maxvolume+1 ) ; 
cout<<endl<<"the maximum value is："<<result [number] [maxvolume] <<endl; 
system ( "pause" ) ; 
return 0; 
} 
using namespace std; 
template<class Type> 
$keyword, void$  print ( Type** m,int n,int c ) 
{ 
$keyword, for$  ( $keyword, int$  i=0; i<n; i++ ) 
{ 
$keyword, for$  ( $keyword, int$  j=0; j<c; j++ ) 
{ 
cout<<setw ( 5 ) <<m [i] [j] ; 
} 
cout<<endl; 
} 
} 
template<class Type> 
$keyword, void$  inItResult ( Type** result,int n,int c ) 
{ 
$keyword, for$  ( $keyword, int$  i=0; i<n; i++ ) 
{ 
$keyword, for$  ( $keyword, int$  j=0; j<c; j++ ) 
{ 
result [i] [j] =0; 
} 
} 
} 
template<class Type> 
$keyword, void$  myKnapsack ( Type *v,int* w,int c,int n,Type** m ) 
{ 
$keyword, for$  ( $keyword, int$  i=1; i<n+1; i++ ) { 
$keyword, for$  ( $keyword, int$  j=1; j<c+1; j++ ) 
{ 
$keyword, if$  ( w [i-1] <=j ) { 
$keyword, if$  ( v [i-1] +m [i-1] [j-w [i-1] ] <m [i-1] [j] ) 
m [i] [j] =m [i-1] [j] ; 
$keyword, else$  m [i] [j] =v [i-1] +m [i-1] [j-w [i-1] ] ; 
} $keyword, else$  { 
m [i] [j] =m [i-1] [j] ; 
} 
} 
} 
} 
} 
