#ifndef _MYSTACK_h
#define _MYSTACK_h
class mystack
{
    private:
    struct node
    {
        int val;
        node *next;
        node(int v=0):val(v),next(0){}
    };
    node *head;
    int cnt;
    public:
    mystack():cnt(0){}
    int size();
    int top();
    void push(int x);
    void pop();
    bool empty();
};
int mystack::size()
{
    return cnt;
}
int mystack::top()
{
    return head->val;
}
void mystack::push(int x)
{
    node *p=new node(x);
    ++cnt;
    p->next=head;
    head=p;
}
void mystack::pop()
{
    if(!cnt)return;//0个
    --cnt;
    node *p=head;
    head=head->next;
    delete p;
}
bool mystack::empty()
{
    return cnt==0;
}
#endif