#include<iostream>
#include<cstdio>
using namespace std;
#define MAXN 100010
struct SPL
{
    int size,val,cnt,ch[2];
}spl[MAXN];
#define ls(x) spl[x].ch[0]
#define rs(x) spl[x].ch[1]
int tot,root;
inline int newnode(int val)
{
    spl[++tot].val=val;
    spl[tot].size++;
    spl[tot].cnt++;
    return tot;
}
inline void update(int now)
{
    spl[now].size=spl[ls(now)].size+spl[rs(now)].size+spl[now].cnt;
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
void splay(int x,int& y)
{
    if(x==y)return;
    int &l=ls(y),&r=rs(y);
    if(x==l)rrotate(y);
    else if(x==r)lrotate(y);
    else
    {
        if(spl[x].val<spl[y].val)
        {
            if(spl[x].val<spl[l].val)
            splay(x,ls(l)),rrotate(y),rrotate(y);
            else splay(x,rs(l)),lrotate(l),rrotate(y);
        }
        else
        {
            if(spl[x].val>spl[r].val)
            splay(x,rs(r)),lrotate(y),lrotate(y);
            else splay(x,ls(r)),rrotate(r),lrotate(y);
        }
    }
}
inline void help_deletnode(int now)//basic hanshu
{
    splay(now,root);
    if(spl[now].cnt>1) spl[now].cnt--,spl[now].size--;
    else if(rs(root))
    {
        int p=rs(root);
        while (ls(p))p=ls(p);
        splay(p,rs(root));
        spl[rs(root)].ch[0]=ls(root);
        root=rs(root);
        update(root);
    }
    else root=ls(root);
}
void insert(int& now,int val)//different
{
    if(!now) now=newnode(val),splay(now,root);
    else if(val<spl[now].val) insert(ls(now),val);
    else if(val>spl[now].val) insert(rs(now),val);
    else spl[now].size++,spl[now].cnt++,splay(now,root);
}
void delet(int now,int val)
{
    if(val==spl[now].val) help_deletnode(now);
    else if(val<spl[now].val) delet(ls(now),val);
    else delet(rs(now),val);
}
int gtrank(int val)
{
    int now=root,rank=1;
    while (now)
    {
        if(val==spl[now].val)
        {
            rank+=spl[ls(now)].size;
            splay(now,root);
            break;
        }
        if(val<spl[now].val)//diff
        now=ls(now);
        else
        {
            rank+=spl[ls(now)].size+spl[now].cnt;
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
        int lsize=spl[ls(now)].size;
        if(lsize+1<=rank && rank<=lsize+spl[now].cnt)
        {
            splay(now,root);
            break;
        }
        else if(lsize>=rank)now=ls(now);
        else
        {
            rank-=lsize+spl[now].cnt;
            now=rs(now);
        }
    }
    return spl[now].val;
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