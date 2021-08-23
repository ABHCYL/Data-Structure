#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define MAXN 100010
const double alpha = 0.75;
struct TZY
{
    int val,size,fact,ch[2];
    bool exist;
}tzy[MAXN];
#define ls(x) tzy[x].ch[0]
#define rs(x) tzy[x].ch[1]
int tot,root;
inline int newnode(int val)
{
    tzy[++tot].val=val;
    tzy[tot].exist=true;
    tzy[tot].size=tzy[tot].fact=1;
    return tot;
}
bool imbalence(int now)
{
    if(max(tzy[ls(now)].size,tzy[rs(now)].size)>tzy[now].size*alpha||
    tzy[now].size-tzy[now].fact>tzy[now].size*0.3)
    return 1;
    return 0;
}
//violent rebuild use the vector to baocun inorder
vector<int>v;
void inorder(int now)
{
    if(!now) return;
    inorder(ls(now));
    if(tzy[now].exist)v.push_back(now);
    inorder(rs(now));
}
void lift(int& now,int l,int r)
{
    if(l==r)
    {
        now=v[l];
        ls(now)=rs(now)=0;
        tzy[now].size=tzy[now].fact=1;
        return;
    }
    int m=(l+r)>>1;
    while(m&&l<m&&tzy[v[m]].val==tzy[v[m-1]].val)m--;
    now=v[m];
    if(l<m)lift(ls(now),l,m-1);
    else ls(now)=0;
    lift(rs(now),m+1,r);
    tzy[now].size=tzy[ls(now)].size+tzy[rs(now)].size+1;
    tzy[now].fact=tzy[ls(now)].fact+tzy[rs(now)].fact+1;
}
void rebuild(int& now)
{
    v.clear();
    inorder(now);
    if(v.empty()){now=0;return;}
    lift(now,0,v.size()-1);
}
void update(int now,int end)
{
    if(!now) return;
    if(tzy[end].val<tzy[now].val)update(ls(now),end);
    else update(rs(now),end);
    tzy[now].size=tzy[ls(now)].size+tzy[rs(now)].size+1;
}
void check(int& now,int end)
{
    if(now==end)return;
    if(imbalence(now))
    {
        rebuild(now);
        update(root,now);
        return;
    }
    if(tzy[end].val<tzy[now].val)check(ls(now),end);
    else check(rs(now),end);
}
void insert(int& now,int val)
{
    if(!now)
    {
        now=newnode(val);
        check(root,now);
        return;
    }
    tzy[now].size++,tzy[now].fact++;
    if(val<tzy[now].val)insert(ls(now),val);
    else insert(rs(now),val);
}
void delet(int now,int val)
{
    if(tzy[now].exist&&tzy[now].val==val)
    {
        tzy[now].exist=false;
        tzy[now].fact--;
        check(root,now);
        return;
    }
    tzy[now].fact--;
    if(val<tzy[now].val)delet(ls(now),val);
    else delet(rs(now),val);
}
int gtrank(int val)
{
    int now=root,rank=1;
    while (now)
    {
        if(val<=tzy[now].val)now=ls(now);
        else
        {
            rank+=tzy[now].exist+tzy[ls(now)].fact;
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
        if(tzy[now].exist&&tzy[ls(now)].fact+tzy[now].exist==rank)break;
        else if(tzy[ls(now)].fact>=rank)now=ls(now);
        else
        {
            rank-=tzy[ls(now)].fact+tzy[now].exist;
            now=rs(now);
        }
    }
    return tzy[now].val;
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