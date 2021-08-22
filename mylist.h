#ifndef _LIST_h
#define _LIST_h
class mylist
{
    private:
    struct node
    {
        int val;
        node *next;
        node(int v=0,node *p=0):val(v),next(p){}
    };
    node *head;//sen,meanwhile,as one part of the private data
    public:
    mylist():head(nullptr){}

    void reverse();

    //获得链表中第index个节点的值
    int get(int index);

    //在链表头部插一个值为val的节点
    void addAtHead(int val);

    //在链表尾部添加一个值为val的节点
    void addAtTail(int val);

    //在索引为index的节点之前添加值为val的节点
    void addAtIndex(int index,int val);

    //walk a list
    void walk();

    //删除索引为index的节点
    void deleteAtIndex(int index);

    //表长
    int length();
};
void mylist::reverse()
{
    node *p=head,*q;
    head=nullptr;
    while(p)
    {
        q=p->next;
        p->next=head;
        head=p;
        p=q;
    }
}
int mylist::get(int index)
{
    int i=0;
    node *p=head;
    for(;p&&i<index;p=p->next,++i);
    if(p)return p->val;
    return -1;
}
void mylist::addAtHead(int val)
{
    head=new node(val,head);
}
void mylist::addAtTail(int val)
{
    node *p=new node(val);
    //链表为空，直接将新节点作为头节点
    if(!head)
    {
        head=p;
        return;
    }
    node *q=head;
    //遍历直到q的next节点为空
    while(q->next)q=q->next;
    q->next=p;
}
void mylist::addAtIndex(int index,int val)
{
    node *p=new node(val);
    //1、index小于等于0，直接在头部插入节点
    if(index<=0)
    {
        p->next=head;
        head=p;
        return;
    }
    int i=0;
    node *q=head;
    //在索引为index的节点之前插入新节点，我们需要找到它的前驱节点，然后插入在它的前驱节点后面
    for(;q&&i<index-1;q=q->next,++i);
    //2、q为索引节点的前驱节点
    if(q)
    {
        p->next=q->next;
        q->next=p;
    }
}
void mylist::walk()
{
    node *p=head;
    while(p)printf("%d ",p->val),p=p->next;
}
void mylist::deleteAtIndex(int index)
{
    //1、index为0，我们直接删除head节点
    if(index<=0&&head)
    {
        node *del=head;
        head=head->next;
        delete del;
        return;
    }
    int i=0;
    node *q=head;
    //删除索引为index的节点，我们需要找到它的前驱节点q,q->next为需要删除节点
    for(;q&&i<index-1;q=q->next,++i);
    //2、index超过链表范围，删除失败
    if(!q)return;
    //3、index的位置合法，我们找到需要删除的q->next节点
    if(q->next)
    {
        node *del=q->next;
        q->next=del->next;
        delete del;
    }
}
int mylist::length()
{
    int i=0;
    node *p=head;
    for(;p;p=p->next,++i);
    return i;
}
#endif