#include<iostream>
#include<cstdio>
using namespace std;
#define MAXN 100010
struct AVL
{
    int size,val,height,ch[2];
}avl[MAXN];
#define ls(x) avl[x].ch[0]
#define rs(x) avl[x].ch[1]
int root,tot;
inline int newnode(int val)
{
    avl[++tot].val=val;
    avl[tot].size=1;
    return tot;
}
inline void update(int now)
{
    avl[now].size=avl[ls(now)].size+avl[rs(now)].size+1;
    avl[now].height=max(avl[ls(now)].height,avl[rs(now)].height)+1;
}
inline int cauclate(int now)
{
    return avl[ls(now)].height-avl[rs(now)].height;
}
inline void lrotate(int& now)
{
    int y=rs(now);
    rs(now)=ls(y);
    ls(y)=now;
    now=y;
    update(ls(now)),update(now);
}
inline void rrotate(int& now)
{
    int y=ls(now);
    ls(now)=rs(y);
    rs(y)=now;
    now=y;
    update(rs(now)),update(now);
}
inline void check(int& now)
{
    int nf=cauclate(now);
    if(nf>1)
    {
        int lf=cauclate(ls(now));
        if(lf>0) rrotate(now);
        else lrotate(ls(now)),rrotate(now);
    }
    else if(nf<-1)
    {
        int rf=cauclate(rs(now));
        if(rf<0) lrotate(now);//
        else rrotate(rs(now)),lrotate(now);
    }
    else if(now) update(now);
}
void insert(int& now,int val)
{
    if(!now) now=newnode(val);
    else if(val<avl[now].val)insert(ls(now),val);
    else insert(rs(now),val);
    check(now);
}
int help_findsuf(int& now,int fa)
{
    int res;
    if(!(ls(now)))
    {
        res=now;
        ls(fa)=rs(now);
    }
    else
    {
        res=help_findsuf(ls(now),now);
        check(now);
    }
    return res;
}
void delet(int& now,int val)
{
    if(val==avl[now].val)
    {
        int l=ls(now),r=rs(now);
        if(!l||!r) now=l+r;
        else 
        {
            now=help_findsuf(r,r);
            if(now!=r)rs(now)=r;
            ls(now)=l;
        }
    }
    else if(val<avl[now].val) delet(ls(now),val);
    else delet(rs(now),val);
    check(now);
}
int gtrank(int val)
{
    int now=root,rank=1;
    while (now)
    {
        if(val<=avl[now].val)now=ls(now);
        else 
        {
            rank+=avl[ls(now)].size+1;//
            now=rs(now);
        }
    }
    return rank;
}
int getnum(int rank)
{
    int now=root;
    while (now)
    {
        if(avl[ls(now)].size+1==rank)break;
        else if(avl[ls(now)].size>=rank)now=ls(now);
        else
        {
            rank-=avl[ls(now)].size+1;//
            now=rs(now);
        }
    }
    return avl[now].val;
}
inline int pre(int num)
{
    return getnum(gtrank(num)-1);
}
inline int suf(int num)
{
    return getnum(gtrank(num+1));
}
int n,opt,num;
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    scanf("%d",&n);
    while (n--)
    {
        scanf("%d%d",&opt,&num);
        switch(opt)
        {
            case 1:insert(root,num);break;
            case 2:delet(root,num);break;
            case 3:printf("%d\n",gtrank(num));break;
            case 4:printf("%d\n",getnum(num));break;
            case 5:printf("%d\n",pre(num));break;
            case 6:printf("%d\n",suf(num));break;
        }
    }
}