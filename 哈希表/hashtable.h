#ifndef HASHTABLE_h
#define HASHTABLE_h
typedef unsigned long long ull;
struct node
{
    int val;
    node *next;
};
struct hashtab
{
    node *head;
    int tabsize;
};
hashtab *create(int size)
{
    hashtab*h=new hashtab;
    h->tabsize=size;
    h->head=new node[size];
    for(int i=0;i<h->tabsize;++i) h->head[i].val=0,h->head[i].next=nullptr;
    return h;
}
ull Hash(int key,int size){return key%size;}
node *find(hashtab *h,int key)
{
    node *p;
    ull pos=Hash(key,h->tabsize);
    p=h->head[pos].next;
    while(p&&p->val!=key)p=p->next;
    return p;
}
bool Insert(hashtab *h,int key)
{
    node *p,*NEW;
    ull pos;
    p=find(h,key);
    if(p){printf("key was in the table. ");return 0;}
    NEW=new node;
    NEW->val=key;
    pos=Hash(key,h->tabsize);
    NEW->next=h->head[pos].next;
    h->head[pos].next=NEW;
    return 1;
}
void DestroyTable(hashtab *h)
{
    node *p,*tmp;
    for(int i=0;i<h->tabsize;++i)
    {
        p=h->head[i].next;
        while (p)
        {
            tmp=p->next;
            delete p;
            p=tmp;
        }
    }
    delete h->head;
    delete h;
}
#endif