#include<iostream>//int merge
#include<cstdio>
#define MAXN 100010
using namespace std;
struct FHQ
{
    int size,val,ch[2];
}fhq[MAXN];
#define ls(x) fhq[x].ch[0]
#define rs(x) fhq[x].ch[1]
int root,tot;
inline void update(int now)
{
    fhq[now].size=fhq[ls(now)].size+fhq[rs(now)].size+1;
}
inline int newnode(int val)
{
    fhq[++tot].size=1,fhq[tot].val=val;
    return tot;
}
void spilt(int now,int& x,int& y,int val)
{
    if(!now){x=y=0;return;}
    if(fhq[now].val<=val)x=now,spilt(rs(now),rs(x),y,val);
    else y=now,spilt(ls(now),x,ls(y),val);
    update(now);
}
int merge(int x,int y)//x <= y
{
    if(!x||!y)return x+y;
    if(99999998%(fhq[x].size+fhq[y].size)<fhq[x].size)
    {
        rs(x)=merge(rs(x),y);
        update(x);
        return x;
    }
    else
    {
        ls(y)=merge(x,ls(y));
        update(y);
        return y;
    }
}
int x,y,z;
inline void insert(int val)
{
    spilt(root,x,y,val);
    root=merge(x,merge(newnode(val),y));
}
inline void delet(int val)
{
    spilt(root,x,z,val);
    spilt(x,x,y,val-1);
    y=merge(ls(y),rs(y));
    root=merge(merge(x,y),z);
}
inline int gtrank(int val)
{
    spilt(root,x,y,val-1);
    int rank=fhq[x].size+1;
    root=merge(x,y);
    return rank;
}
inline int getnum(int rank)//k small
{
    int now=root;
    while (now)
    {
        if(fhq[ls(now)].size==rank-1) break;
        else if(fhq[ls(now)].size>=rank) now=ls(now);
        else
        {
            rank-=fhq[ls(now)].size+1;
            now=rs(now);   
        }
    }
    return fhq[now].val;
}
inline int pre(int val)
{
    spilt(root,x,y,val-1);
    int now=x;
    while (rs(now))
    {
        now=rs(now);
    }
    root=merge(x,y);
    return fhq[now].val;
}
inline int suf(int val)
{
    spilt(root,x,y,val);
    int now=y;
    while (ls(now))
    {
        now=ls(now);
    }
    root=merge(x,y);
    return fhq[now].val;
}
int n,opt,num;
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif
    scanf("%d",&n);
    while (n--)
    {
        scanf("%d%d",&opt,&num);
        switch(opt)
        {
            case 1:insert(num);break;
            case 2:delet(num);break;
            case 3:printf("%d\n",gtrank(num));break;
            case 4:printf("%d\n",getnum(num));break;
            case 5:printf("%d\n",pre(num));break;
            case 6:printf("%d\n",suf(num));break;
        }
    }
}
void sizespilt(int now,int& x,int& y,int size)
{
    if(!now){x=y=0;return;}
    if(ls(now)<size)y=now,sizespilt(ls(now).x,ls(y),szie);
    else x=now,sizespilt(rs(now),rs(x),y,size-fhq[ls(now)].size-1);
    update(now);
}