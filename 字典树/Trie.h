#ifndef TRIE_H
#define TRIE_H
#include<string>
using std::string;
class Trie
{
    Trie *ch[26]={0};
    bool isend;
    string word;
    public:
    Trie(){isend=0;word="";}
    void insert(string &str)
    {
        Trie *p=this;
        for(auto i:str)
        {
            if(!p->ch[i-'a'])p->ch[i-'a']=new Trie();
            p=p->ch[i-'a'];
        }
        p->isend=1;
        p->word=str;
    }
    bool search(string &str) 
    {
        Trie *p=this;
        for(auto i:str)
        {
            if(!p->ch[i-'a'])return 0;
            p=p->ch[i-'a'];
        }
        return p->isend;
    }
    bool startsWith(string &prefix) 
    {
        Trie *p=this;
        for(auto i:prefix)
        {
            if(!p->ch[i-'a'])return 0;
            p=p->ch[i-'a'];
        }
        return 1;
    }
    string getlongest(Trie *root)//在trie中具有最长前缀的字符串
    {
        if(!root->isend)return "";
        string ans=root->word;
        for(int i=0;i<26;i++)
        {
            if(!root->ch[i])continue;
            string tmp=getlongest(root->ch[i]);
            if(tmp.size()>ans.size())ans=tmp;
        }
        return ans;
    }
};
#endif