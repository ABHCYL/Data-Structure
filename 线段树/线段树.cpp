#include<iostream>
#include<cstdio>
#define MAXN 100010
#define ll long long
using namespace std;
struct BT
{
    int le,rt;//可以不要，表示左右端点
    ll sum,add;//add是lazytag，sum是你要维护的东西
}t[MAXN<<2];//4倍空间
int a[MAXN],n,m;//a存输入，n是元素个数，m是操作次数
void build(int p,int l,int r)//建树
{
    t[p].le=l,t[p].rt=r;//端点赋值
    if(l==r){t[p].sum=a[l];return;}//叶节点赋值并回退
    int mid=(l+r)>>1;//左右递归
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    t[p].sum=t[p<<1].sum+t[p<<1|1].sum;//pushup自底向上思想，实质是更新
}//调用入口build(1,1,n);
void spread(int p)//与lazytag搭配的下传pushdown，自顶向下思想
{
    if(t[p].add)//有标记，把father的信息下传给两个儿子
    {
        t[p<<1].sum += t[p].add*(t[p<<1].rt-t[p<<1].le +1);
        t[p<<1|1].sum += t[p].add*(t[p<<1|1].rt-t[p<<1|1].le +1);
        t[p<<1].add += t[p].add;
        t[p<<1|1].add += t[p].add;
        t[p].add = 0 ;//下传完事，去掉标记，避免重复操作
    }
}
void change(int p,int l,int r,int d)//更新函数
{
    if(l<=t[p].le&&r>=t[p].rt)//看图片理解
    {
        t[p].sum+=(ll)d*(t[p].rt-t[p].le+1);
        t[p].add+=d;
        return ;
    }
    spread(p);
    int mid=(t[p].le+t[p].rt)>>1;
    if(l<=mid) change(p<<1,l,r,d);
    if(r>mid) change(p<<1|1,l,r,d);
    t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
}//调用入口change(1,l,r,d);
ll ask(int p,int l,int r)
{
    if(l<=t[p].le&&r>=t[p].rt)return t[p].sum;
    spread(p);
    int mid=(t[p].le+t[p].rt)>>1;
    ll sum=0;
    if(l<=mid) sum+=ask(p<<1,l,r);//左边有搜左边
    if(r>mid) sum+=ask(p<<1|1,l,r);//右边有搜右边
    return sum;
}//调用入口ask(1,x,y);
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,1,n);
    int jj;
    ll x,y,c;
	while(m--)
	{
		scanf("%d%lld%lld",&jj,&x,&y);
		if(jj==1)
		{
			scanf("%lld",&c);
            change(1,x,y,c);
		}
		else
		{
			printf("%lld\n",ask(1,x,y));
		}
	}
}