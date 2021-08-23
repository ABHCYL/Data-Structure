#ifndef _MYQUEUE_h
#define _MYQUEUE_h
class myqueue
{
    private:
    struct node
    {
        int val;
        node *next;
        node(int v=0):val(v),next(0){}
    };
    node *head;
    node *tail;
    int cnt;
    public:
    myqueue():cnt(0){}
    int size();
    int front();
    void push(int x);
    void pop();
    bool empty();
};
int myqueue::size()
{
    return cnt;
}
int myqueue::front()
{
    return head->val;
}
bool myqueue::empty()
{
    return cnt==0;
}
void myqueue::push(int x)
{
    node *p=new node(x);
    ++cnt;
    if(cnt==1)
    {
        head=tail=p;
        return;
    }
    tail->next=p;
    tail=p;
}
void myqueue::pop()
{
    if(!cnt)return;//0个
    --cnt;
    node *p=head;
    head=head->next;
    delete p;
}
#endif