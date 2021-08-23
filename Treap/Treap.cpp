#include<iostream>
#include<cstdio>
using namespace std;
#define MAXN 100010
struct TREAP
{
    int val,size,rnk,ch[2];
}tre[MAXN];
#define ls(x) tre[x].ch[0]
#define rs(x) tre[x].ch[1]
int tot,root;
inline int newnode(int val)
{
    tre[++tot].val=val;
    tre[tot].size=1;
    tre[tot].rnk=rand();
    return tot;
}
inline void update(int now)
{
    tre[now].size=tre[ls(now)].size+tre[rs(now)].size+1;
}
inline void lrotate(int& now)
{
    int y=rs(now);
    rs(now)=ls(y);
    ls(y)=now;
    tre[y].size=tre[now].size;
    update(now);
    now=y;
    // now=y;
    // update(ls(now)),update(now); wrong
}
inline void rrotate(int& now)
{
    int y=ls(now);
    ls(now)=rs(y);
    rs(y)=now;
    tre[y].size=tre[now].size;
    update(now);
    now=y;
    // now=y;
    // update(rs(now)),update(now); wrong
}
void insert(int& now,int val)
{
    if(!now)
    {
        now=newnode(val);
        return;
    }
    tre[now].size++;
    if(val<tre[now].val)insert(ls(now),val);
    else insert(rs(now),val);

    if(ls(now) && tre[now].rnk>tre[ls(now)].rnk)rrotate(now);
    if(rs(now) && tre[now].rnk>tre[rs(now)].rnk)lrotate(now);
    update(now);
}
void delet(int& now,int val)
{
    tre[now].size--;
    if(val==tre[now].val)
    {
        int l=ls(now),r=rs(now);
        if(!l||!r) {now=l+r;return;}
        if(tre[ls(now)].rnk<tre[rs(now)].rnk)
        {
            rrotate(now);
            delet(rs(now),val);
            return;
        }
        else
        {
            lrotate(now);
            delet(ls(now),val);
            return;
        }
    }
    if(val<=tre[now].val)delet(ls(now),val);  // <=
    else delet(rs(now),val);
    update(now);
}
int gtrank(int val)
{
    int now=root,rank=1;
    while (now)
    {
        if(val<=tre[now].val)now=ls(now);
        else
        {
            rank+=tre[ls(now)].size+1;
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
        if(tre[ls(now)].size+1==rank)break;
        else if(tre[ls(now)].size>=rank)now=ls(now);
        else
        {
            rank-=tre[ls(now)].size+1;
            now=rs(now);
        } 
    }
    return tre[now].val;
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
    srand(19620817);
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