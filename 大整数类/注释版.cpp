//+-*/ cin cout ><=  = ++  --
//代码无压位 ，无FFT 
//代码AC了 洛谷OJ 的高精+ 高精- 高精* 高精/ 高精% 的相关题目
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
    private:
    vector<int>v;//vector 不定长数组 来存数字
    int sign;//-1 0 1 负 零 正
    ull vsize;//一个vector的长度
    public:
    big();//无参的构造，具体看下面的代码
    big(int);//int 和ll 只有形参的不同，代码内容是一样的
    big(ll);//int 和ll 都是先确定sign，然后与string的构造处理思路一致
    big(string);//把字符串的sign处理好，倒序存在vector里，具体看下面的代码
    
    //两个流操作，倒序输入和倒序输出
    friend ostream& operator << (ostream&,const big&);
	friend istream& operator >> (istream&, big&);
    big& operator=(const big &);//类型是big&，因为为了可以实现a=b=c，这样的连续赋值操作
    //这其中牵扯到左值右值的问题，关于赋值运算符的问题细节太多了，这里不写了

    bool operator >(const big &) const;//六个比较的重载，先处理好>的
    bool operator  <(const big &)const;//剩下的五个都可以用已处理好的比较运算符定义处理
    bool operator ==(const big &)const;//具体看下面代码
    bool operator !=(const big &)const;
    bool operator >=(const big &)const;
    bool operator <=(const big &)const;

    big operator+(const big &)const;//由于加法有4种情况，（正+正）（负+负）（正+负）（负+正）
    big operator+=(const big &);//把+的重载定义好，剩下的所有+，-和++ --都可以用已处理好的+ -运算符定义处理
    big operator-(const big &)const;//具体看下面代码
    big operator-=(const big &);
    big operator++();
    big operator++(int);
	big operator--();
    big operator--(int);

    big operator-();//一元减运算符重载，使得big型的变量像内置数据类型一样可以直接取 负 （0--0，-1--1）

    big operator*(const big &)const;//按照竖式乘法的运算思路来处理
    big operator*=(const big &);//实现了*，就顺便实现*=的
    big operator/(const big &)const;//具体的算法下面解释
    big operator/=(const big &);//实现了/，就顺便实现/=的
    big operator%(const big &)const;//与除法极为相似
    big operator%=(const big &);
};
big::big()
{
    v.clear();vsize=0;//这里和内置数据类型一样，如果声明但是没有初始化，就默认它是无定义的，好比没有初始化的局部变量
}
big::big(int n)
{
    v.clear();
    if(n>0)sign=1;
    else if(!n)sign=0;
    else sign=-1,n*=-1;//确定符号,如果n是负数,把它取绝对值，这样在下面的to_string操作时才不会把-号也写入字符串s中
    string s=to_string(n);
    reverse(s.begin(),s.end());//倒序
    vsize=s.size();//确定vector长度
    for(int i=0;i<vsize;i++)v.push_back(s[i]-'0');//读入
}
big::big(ll n)
{
    v.clear();//和big::big(int n)的代码完全一致
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
    sign=(s[0]=='-')?-1:1;//确定符号
    if(s.size()==1&&s[0]=='0')sign=0;//确定符号
    reverse(s.begin(),s.end());//倒序
    vsize=s.size();
    if(sign==-1)vsize--;//确定vector长度
    for(int i=0;i<vsize;i++)v.push_back(s[i]-'0');//读入
}
ostream& operator << (ostream& output,const big&c)
{
    big temp=c;//这一步把c赋值给temp，是因为c是引用不能修改，如果c有前导0，输出就是错的了
    //把c赋值给temp ，通过删掉temp的前导0保证输出是正确的
    //对于c来说，保留前导0是没有什么影响的，不影响四则运算，这个temp只是为了保证输出正确而已
    if(c.v.empty())
    {
        output<<0;
        return output;
    }
    if(c.sign==-1)cout<<"-";//负号先输出
    while (temp.v.size()>1&&!temp.v.back())temp.v.pop_back();//删掉temp的前导0
    temp.vsize=temp.v.size();
    for(int i=temp.vsize-1;i>=0;i--)output << temp.v[i];
    return output;
}
istream& operator >> (istream& input, big& c)
{
    string s;
	input >> s;//把读入全部存到字符串里
    c.v.clear();
    c.sign = (s[0] == '-') ? -1 : 1;//确定符号
    if(s.size()==1&&s[0]=='0')c.sign=0;//确定符号
    reverse(s.begin(),s.end());//倒序
    c.vsize=s.size();
    if(c.sign==-1)c.vsize--;//确定vector长度
    for(int i=0;i<c.vsize;i++)c.v.push_back(s[i]-'0');//读入到c.v中
    return input;
}
big& big::operator=(const big &c)
{
    sign=c.sign;
    vsize=c.vsize;
    v.clear();//=号具有覆盖原本信息的特点，所以一定要把原来的v调用clear清0！！！
    v.assign(c.v.begin(),c.v.end());//v.assign会把区间c.v.begin(),c.v.end()的值拷贝
    return *this;//返回的是*this
}

bool big::operator >(const big &c)const
{
    if(sign>c.sign)return 1;//先从符号比较，return 1
    if(sign<c.sign)return 0;//反过来
    //走到这一步说明相同符号，有3种情况
    if(sign==0)return 0;//符号都是0，说明两个数都是0，不是大于关系
    if(sign==1)//符号都是1，两个正 比大小
    {
        if(vsize>c.vsize)return 1;//先比长度
        if(vsize<c.vsize)return 0;
        for(int i=vsize-1;i>=0;i--)//长度相同逐位比较
        {
            if(v[i]>c.v[i])return 1;
            else if(v[i]<c.v[i])return 0;
        }
    }
    if(sign==-1)//符号都是-1，两个负 比大小 和正数相反
    {
        if(vsize>c.vsize)return 0;
        if(vsize<c.vsize)return 1;
        for(int i=vsize-1;i>=0;i--)
        {
            if(v[i]>c.v[i])return 0;
            else if(v[i]<c.v[i])return 1;
        }
    }
    return 0;//当两数同正同负且绝对值大小相等，说明他们相等，return 0
}
bool big::operator <(const big &c)const
{
    return c>(*this);//如果(*this)<c，说明c>(*this)为真，返回1.否则其余情况都返0
}
bool big::operator >=(const big &c)const
{
    return !(*this<c);//剩下几个都是用上面来定义的
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

//isabs sub是两个辅助函数，辅助 +号重载里 2个数符号不同的情况
int isabs(vector<int>a,const vector<int>&b)//这个函数，比较两个数绝对值的大小
{
    if(a.size()>b.size())return 1;//a>b return 1
    if(a.size()<b.size())return -1;//a<b return -1
    int alen=a.size();
    for(int i=alen-1;i>=0;i--)
    {
        if(a[i]>b[i])return 1;
        if(a[i]<b[i])return -1;
    }
    return 0;//a==b return 0
}
vector<int> sub(vector<int>a,const vector<int>&b)//这个函数，用来计算大绝对值数减去小绝对值数的结果
{
    vector<int>c;//结果存在c中，这个函数调用前，保证a>b，所以不存在最高位最后的数字是负数的情况
    c.clear();
    int blen=b.size(),alen=a.size();
    for(int i=0;i<blen;i++)//b是小的数，算完b的全部位后，不用再算
    {
        if(a[i]<b[i])
        {
            a[i]+=10;//2个正数 减法的基本原理，不解释
            a[i+1]--;
        }
        c.push_back(a[i]-b[i]);
    }
    for(int i=blen;i<alen;i++)//把剩余的a的位全部存入
    {
        if(a[i]<0)
        {
            a[i]+=10;
            a[i+1]--;
        }
        c.push_back(a[i]);
    }
    return c;//返回c
}
big big::operator+(const big &c)const//最难写的部分，逻辑有些复杂
{
    big ans;//首先声明ans
    ans.v.clear();//保险起见，再次清空，避免奇怪的错误出现
    //以下是同号加法
    int x=0;
    if(sign==c.sign)//同号加法，直接相加，ans.sign=sign
    {
        for(int i=0,g=0;;i++)//两个正数 加法的基本原理
        {
            if(!g&&i>=v.size()&&i>=c.v.size())break;//当此判断为true时，指的是加完了2个数的所有位，并且最高位g==0
            x=g;//g保存的是高一位的结果
            if(i<v.size())x+=v[i];
            if(i<c.v.size())x+=c.v[i];//x把两个位加完
            ans.v.push_back(x%10);//对10取模并存入
            g=x/10;//更新高位的g
        }
        ans.sign=sign;
        ans.vsize=ans.v.size();
    }
    //以下是异号加法，也是最难写的部分
    int babs=2;//babs是一个辅助变量，与上面的辅助函数isabs对应，用来保存isabs返回的值，=2是初始化的习惯，避免奇怪的错误
    if(sign!=c.sign)//异号加法
    {
        if(sign==0)//2个数中有一个是0，那么ans显然等于另一个
        {
            ans.sign=c.sign;
            ans.vsize=c.v.size();
            ans.v.clear();
            ans.v=c.v;
        }
        if(c.sign==0)//2个数中有一个是0，那么ans显然等于另一个
        {
            ans.sign=sign;
            ans.vsize=v.size();
            ans.v.clear();
            ans.v=v;
        }
        if(sign==1&&c.sign==-1)//2个数中*this是正，c是负
        {
            babs=isabs(v,c.v);//绝对值比大小
            if(babs==0)//绝对值==0，说明2数之和==0
            {
                ans.sign=0;
                ans.vsize=1;
                ans.v.clear();
                ans.v.push_back(0);
            }
            if(babs==1)//绝对值==1，说明v>c.v(*this>c)
            {
                ans.sign=1;//此时ans=*this-c（指大的减小的），ans.sign=1
                ans.v.clear();
                ans.v=sub(v,c.v);//sub函数把减完的数值赋值给ans
                ans.vsize=ans.v.size();
            }
            if(babs==-1)//绝对值==-1，说明v<c.v(*this<c)
            { 
                ans.sign=-1;//此时ans=c-*this（指大的减小的），ans.sign=-1，但实际上我们算的是*this-c的值，所以结果的符号是-1
                ans.v.clear();
                ans.v=sub(c.v,v);//sub函数把减完的数值赋值给ans
                ans.vsize=ans.v.size();
            }
        }
        if(sign==-1&&c.sign==1)//2个数中*this是负，c是正，和上面的逻辑是一样的，不注释了
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
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back(); //清除前导0
    ans.vsize=ans.v.size(); 
    return ans;
}
big big::operator+=(const big &c)//实现了+ ，+=也就实现了
{
    *this=*this+c;
    return *this;
}
big big::operator-=(const big &c)//实现了+和+=，-=也就实现了
{
    if(c.sign==0)return *this;//this-=0，this不变直接return
    big temp=c;//this-=c等价于this+= -1*c
    temp.sign*=-1;//形参c是引用，不能改变，用temp保存起来，改变符号
    *this=*this+temp;
    return *this;
}
big big::operator-(const big &c)const//用-=实现即可
{
    big ans=*this;
    ans-=c;
    return ans;
}

big big::operator++()//自增 和 自减 都可以用上面的重载来实现
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

big big::operator*(const big &c)const//乘法重载
{
    big ans;
    ans.v.clear();
    if(sign==0||c.sign==0)//乘法中有一个是0 ，结果是 0
    {
        ans.sign=0;
        ans.vsize=1;
        ans.v.push_back(0);
        return ans;
    }
    if(sign==c.sign)ans.sign=sign;//乘法同号结果+
    else ans.sign=-1;//乘法异号结果-

    ans.vsize=vsize+c.vsize+1;//乘法结果最长是vsize+c.vsize+1
    for(int i=0;i<ans.vsize;i++)ans.v.push_back(0);//为了简化过程，使vector像全部初始化为0的全局静态数组一样
    for(int i = 0;i < vsize;i++)//O(n*n)的时间复杂度，模拟竖式乘法
    {
        for(int j = 0;j <c.vsize;j++)
        {
            ans.v[i+j]+=v[i]*c.v[j];
            ans.v[i+j+1]+=ans.v[i+j]/10;
            ans.v[i+j]%=10;
        }
    }
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back();//清除前导0
    ans.vsize=ans.v.size();  
    return ans;
}
big big::operator*=(const big &c)
{
    *this=*this*c;
    return *this;
}

big big::operator/(const big &c)const//除法重载，除法的运算方法是不断做减法，记录次数
{
    big ans;
    if(sign==0||isabs(v,c.v)==-1)//big/是像int类型的整除，除数*this==0 或者 除数绝对值小于被除数，结果=0
    {
        ans.sign=0;
        ans.vsize=1;
        ans.v.clear();
        ans.v.push_back(0);
        return ans;
    }
    if(sign==c.sign)ans.sign=1;else ans.sign=-1;//除法同号结果+ ，异号结果-
    ans.vsize=vsize-c.vsize+1;//商的长度为vsize-c.vsize+1

    vector<int>temp(ans.vsize-1,0);
    for(int j=0;j<c.v.size();j++)temp.push_back(c.v[j]);
    //上2行代码是把被除数不足除数长度的个位补0，补到一样长，因为c是引用不能修改，所以用temp复制c.v
    while (temp.size()>1&&!temp.back())temp.pop_back();//把temp（被除数）清除前导0，这一步很重要！！！

    vector<int>myself(v);//因为v不能修改，所以用myself复制v
    while (myself.size()>1&&!myself.back())myself.pop_back();//把myself（除数）清除前导0，这一步很重要！！！

    for(int i=ans.vsize-1;i>=0;i--)//商的长度为vsize-c.vsize+1
    {
        int cnt=0;  
        while (isabs(myself,temp)>=0)//除数myself绝对值大于等于被除数temp
        {
            cnt++;
            if(isabs(myself,temp)==0)break;//如果绝对值是等于关系，myself就不用再减少了
            myself=sub(myself,temp);//把myself减等emp
            while (myself.size()>1&&!myself.back())myself.pop_back();//把myself（除数）清除前导0，这一步很重要！！！，没有这一步会死循环
        }
        ans.v.push_back(cnt%10);//cnt==10时取模变0
        temp.erase(temp.begin());//删除temp头部补充的0，每次for循环删一个
    }
    reverse(ans.v.begin(),ans.v.end());//ans.v的存储结果是正序的（输出时就会变成倒序），要把它反成倒序
    while (ans.v.size()>1&&!ans.v.back())ans.v.pop_back();//把ans清除前导0
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
big big::operator-()//这个只是为了让big 型变量 能像内置数据类型一样
{
    sign*=-1;
    return *this;
}
int main()
{   
    big a("-11111111222222000"),b(10),c(11111111222222),d;//四个构造 string int ll 无参
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    -a,-b,-c;
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    cin>>a>>b>>c>>d;
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    a=c+d; b=c-d;
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    a=c*d; b=c/d;
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    a++;++b;c--;--d;
    cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
    cout<<(a>b);
    cout<<(c<d);
}