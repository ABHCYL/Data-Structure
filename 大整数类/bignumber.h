#ifndef _BIG_h
#define _BIG_h
#include <string>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
class big
{
    vector<int>v;
    int sign;
    ull vsize;
    public:
    big();
    big(int);
    big(ll);
    big(string);
    
    friend ostream& operator << (ostream&,const big&);
	friend istream& operator >> (istream&, big&);
    big& operator=(const big &);

    bool operator >(const big &) const;
    bool operator  <(const big &)const;
    bool operator ==(const big &)const;
    bool operator !=(const big &)const;
    bool operator >=(const big &)const;
    bool operator <=(const big &)const;

    big operator+(const big &)const;
    big operator+=(const big &);
    big operator-(const big &)const;
    big operator-=(const big &);

    big operator++();
    big operator++(int);
	big operator--();
    big operator--(int);

    big operator-();
    big operator*(const big &)const;
    big operator*=(const big &);
    big operator/(const big &)const;
    big operator/=(const big &);
    big operator%(const big &)const;
    big operator%=(const big &);
};
big::big()
{
    v.clear();vsize=0;
}
big::big(int n)
{
    v.clear();
    if(n>0)sign=1;
    else if(!n)sign=0;
    else sign=-1,n*=-1;
    string s=to_string(n);
    reverse(s.begin(),s.end());
    vsize=s.size();
    for(int i=0;i<vsize;i++)v.push_back(s[i]-'0');
}
big::big(ll n)
{
    v.clear();
    if(n>0)sign=1;
    else if(!n)sign=0;
    else sign=-1,n*=-1;
    string s=to_string(n);
    reverse(s.begin(),s.end());
    vsize=s.size();
    for(int i=0;i<vsize;i++)v.push_back(s[i]-'0');
}
big::big(string s)
{
    v.clear();
    sign=(s[0]=='-')?-1:1;
    if(s.size()==1&&s[0]=='0')sign=0;
    reverse(s.begin(),s.end());
    vsize=s.size();
    if(sign==-1)vsize--;
    for(int i=0;i<vsize;i++)v.push_back(s[i]-'0');
}
ostream& operator << (ostream& output,const big&c)
{
    big temp=c;
    if(c.v.empty())
    {
        output<<0;
        return output;
    }
    if(c.sign==-1)cout<<"-";
    while (temp.v.size()>1&&!temp.v.back())temp.v.pop_back();
    temp.vsize=temp.v.size();
    for(int i=temp.vsize-1;i>=0;i--)output << temp.v[i];
    return output;
}
istream& operator >> (istream& input, big& c)
{
    string s;
	input >> s;
    c.v.clear();
    c.sign = (s[0] == '-') ? -1 : 1;
    if(s.size()==1&&s[0]=='0')c.sign=0;
    reverse(s.begin(),s.end());
    c.vsize=s.size();
    if(c.sign==-1)c.vsize--;
    for(int i=0;i<c.vsize;i++)c.v.push_back(s[i]-'0');
    return input;
}
big& big::operator=(const big &c)
{
    sign=c.sign;
    vsize=c.vsize;
    v.clear();
    v.assign(c.v.begin(),c.v.end());
    return *this;
}

bool big::operator >(const big &c)const
{
    if(sign>c.sign)return 1;
    if(sign<c.sign)return 0;
    //走到这一步说明相同符号
    if(sign==0)return 0;
    if(sign==1)
    {
        if(vsize>c.vsize)return 1;
        if(vsize<c.vsize)return 0;
        for(int i=vsize-1;i>=0;i--)
        {
            if(v[i]>c.v[i])return 1;
            else if(v[i]<c.v[i])return 0;
        }
    }
    if(sign==-1)
    {
        if(vsize>c.vsize)return 0;
        if(vsize<c.vsize)return 1;
        for(int i=vsize-1;i>=0;i--)
        {
            if(v[i]>c.v[i])return 0;
            else if(v[i]<c.v[i])return 1;
        }
    }
    return 0;
}
bool big::operator <(const big &c)const
{
    return c>(*this);
}
bool big::operator >=(const big &c)const
{
    return !(*this<c);
}
bool big::operator <=(const big &c)const
{
    return !(*this>c);
}
bool big::operator !=(const big &c)const
{
    return *this>c||c>*this;
}
bool big::operator ==(const big &c)const
{
    return !(*this!=c);
}

int isabs(vector<int>a,const vector<int>&b)
{
    if(a.size()>b.size())return 1;
    if(a.size()<b.size())return -1;
    int alen=a.size();
    for(int i=alen-1;i>=0;i--)
    {
        if(a[i]>b[i])return 1;
        if(a[i]<b[i])return -1;
    }
    return 0;
}
vector<int> sub(vector<int>a,const vector<int>&b)
{
    vector<int>c;
    c.clear();
    int blen=b.size(),alen=a.size();
    for(int i=0;i<blen;i++)
    {
        if(a[i]<b[i])
        {
            a[i]+=10;
            a[i+1]--;
        }
        c.push_back(a[i]-b[i]);
    }
    for(int i=blen;i<alen;i++)
    {
        if(a[i]<0)
        {
            a[i]+=10;
            a[i+1]--;
        }
        c.push_back(a[i]);
    }
    return c;
}
big big::operator+(const big &c)const
{
    big ans;
    ans.v.clear();
    int x=0;
    if(sign==c.sign)
    {
        for(int i=0,g=0;;i++)
        {
            if(!g&&i>=v.size()&&i>=c.v.size())break;
            x=g;
            if(i<v.size())x+=v[i];
            if(i<c.v.size())x+=c.v[i];
            ans.v.push_back(x%10);
            g=x/10;
        }
        ans.sign=sign;
        ans.vsize=ans.v.size();
    }
    int babs=2;
    if(sign!=c.sign)
    {
        if(sign==0)
        {
            ans.sign=c.sign;
            ans.vsize=c.v.size();
            ans.v.clear();
            ans.v=c.v;
        }
        if(c.sign==0)
        {
            ans.sign=sign;
            ans.vsize=v.size();
            ans.v.clear();
            ans.v=v;
        }
        if(sign==1&&c.sign==-1)
        {
            babs=isabs(v,c.v);
            if(babs==0)
            {
                ans.sign=0;
                ans.vsize=1;
                ans.v.clear();
                ans.v.push_back(0);
            }
            if(babs==1)
            {
                ans.sign=1;
                ans.v.clear();
                ans.v=sub(v,c.v);
                ans.vsize=ans.v.size();
            }
            if(babs==-1)
            { 
                ans.sign=-1;
                ans.v.clear();
                ans.v=sub(c.v,v);
                ans.vsize=ans.v.size();
            }
        }
        if(sign==-1&&c.sign==1)
        {
            babs=isabs(v,c.v);
            if(babs==0)
            {
                ans.sign=0;
                ans.vsize=1;
                ans.v.clear();
                ans.v.push_back(0);
            }
            if(babs==1)
            {
                ans.sign=-1;
                ans.v.clear();
                ans.v=sub(v,c.v);
                ans.vsize=ans.v.size();
            }
            if(babs==-1)
            { 
                ans.sign=1;
                ans.v.clear();
                ans.v=sub(c.v,v);
                ans.vsize=ans.v.size();
            }
        }
    }
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back(); 
    ans.vsize=ans.v.size(); 
    return ans;
}
big big::operator+=(const big &c)
{
    *this=*this+c;
    return *this;
}
big big::operator-=(const big &c)
{
    if(c.sign==0)return *this;
    big temp=c;
    temp.sign*=-1;
    *this=*this+temp;
    return *this;
}
big big::operator-(const big &c)const
{
    big ans=*this;
    ans-=c;
    return ans;
}

big big::operator++()
{
    big temp("1");
    *this+=temp;
    return *this;
}
big big::operator++(int)
{
    ++(*this);
    return *this;
}
big big::operator--()
{
    big temp("-1");
    *this+=temp;
    return *this;
}
big big::operator--(int)
{
    --(*this);
    return *this;
}

big big::operator*(const big &c)const
{
    big ans;
    ans.v.clear();
    if(sign==0||c.sign==0)
    {
        ans.sign=0;
        ans.vsize=1;
        ans.v.push_back(0);
        return ans;
    }
    if(sign==c.sign)ans.sign=sign;
    else ans.sign=-1;

    ans.vsize=vsize+c.vsize+1;
    for(int i=0;i<ans.vsize;i++)ans.v.push_back(0);
    for(int i = 0;i < vsize;i++)
    {
        for(int j = 0;j <c.vsize;j++)
        {
            ans.v[i+j]+=v[i]*c.v[j];
            ans.v[i+j+1]+=ans.v[i+j]/10;
            ans.v[i+j]%=10;
        }
    }
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back();
    ans.vsize=ans.v.size();  
    return ans;
}
big big::operator*=(const big &c)
{
    *this=*this*c;
    return *this;
}

big big::operator/(const big &c)const
{
    big ans;
    if(sign==0||vsize<c.vsize)
    {
        ans.sign=0;
        ans.vsize=1;
        ans.v.clear();
        ans.v.push_back(0);
        return ans;
    }
    if(sign==c.sign)ans.sign=1;else ans.sign=-1;
    ans.vsize=vsize-c.vsize+1;
    vector<int>temp(ans.vsize-1,0);
    for(int j=0;j<c.v.size();j++)temp.push_back(c.v[j]);
    while (temp.size()>1&&!temp.back())temp.pop_back();
    vector<int>myself(v);
    while (myself.size()>1&&!myself.back())myself.pop_back();
    for(int i=ans.vsize-1;i>=0;i--)
    {
        int cnt=0;
        while (isabs(myself,temp)>=0)//se is chu--this.v,t is beichu--temp.v
        {
            cnt++;
            if(isabs(myself,temp)==0)break;
            myself=sub(myself,temp);
            while (myself.size()>1&&!myself.back())myself.pop_back();
        }
        ans.v.push_back(cnt%10);
        temp.erase(temp.begin());
    }
    reverse(ans.v.begin(),ans.v.end());
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back();
    ans.vsize=ans.v.size();
    return ans;
}
big big::operator/=(const big &c)
{
    *this=*this/c;
    return *this;
}

big big::operator%(const big &c)const
{
    big ans;
    ans.sign=sign;
    if(sign==0||vsize<c.vsize)
    {
        ans.v.clear();
        for(int i=0;i<vsize;i++)
        ans.v.push_back(v[i]);
        ans.vsize=ans.v.size();
        return ans;
    }
    if(isabs(v,c.v)==0)
    {
        ans.sign=0;
        ans.vsize=1;
        ans.v.clear();
        ans.v.push_back(0);
        return ans;
    }
    ans.vsize=vsize-c.vsize+1;
    vector<int>temp(ans.vsize-1,0);
    for(int j=0;j<c.v.size();j++)temp.push_back(c.v[j]);
    while (temp.size()>1&&!temp.back())temp.pop_back();
    vector<int>myself(v);
    while (myself.size()>1&&!myself.back())myself.pop_back();
    for(int i=ans.vsize-1;i>=0;i--)
    {
        int cnt=0;
        while (isabs(myself,temp)>=0)
        {
            cnt++;
            if(isabs(myself,temp)==0)break;
            myself=sub(myself,temp);
            while (myself.size()>1&&!myself.back())myself.pop_back();
        }
        temp.erase(temp.begin());
    }
    for(int i=0;i<myself.size();i++)ans.v.push_back(myself[i]);
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back();
    ans.vsize=ans.v.size();
    return ans;
}
big big::operator%=(const big &c)
{
    *this=*this%c;
    return *this;
}
big big::operator-()
{
    sign*=-1;
    return *this;
}
#endif