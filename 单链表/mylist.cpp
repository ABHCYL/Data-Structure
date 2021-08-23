#include<iostream>
#include"mylist.h"
using namespace std;

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    mylist p;
    for(int i=10;i;--i)p.addAtTail(i);//尾插10个元素
    printf("%d\n",p.length());
    printf("%d\n",p.get(10));//访问出界
    p.deleteAtIndex(0);//删除第0个节点
    p.reverse();
    p.addAtHead(65536);
    p.addAtIndex(10,2333);//边界情况，最后一个是9号节点
    p.addAtIndex(100000,2333);//边界情况，插入失败，链表不发生改变
    p.walk();
}