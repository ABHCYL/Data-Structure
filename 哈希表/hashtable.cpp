#include<cstdio>
#include<iostream>
using namespace std;
#include"hashtable.h"
int use[7]={1,3,14,1119,14,15,1119};
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt","r",stdin);
    freopen("0out.txt","w",stdout);
    #endif
    hashtab *tab=create(19);
    for(int i=0;i<7;++i)
    cout<<Insert(tab,use[i])<<endl;
    DestroyTable(tab);
}