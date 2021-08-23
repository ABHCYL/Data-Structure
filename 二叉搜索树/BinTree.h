#ifndef _BinTree_h
#define _BinTree_h
struct BinTree
{
    int data;
    BinTree *Left;
    BinTree *Right;
    BinTree(int d=0,BinTree *l=0,BinTree *r=0)
    {
        data=d;Left=l;Right=r;
    }
};
void PreorderTraversal( BinTree *BT);
void InorderTraversal ( BinTree *BT);
BinTree *Insert( BinTree *BST, int X );
BinTree *Delete( BinTree *BST, int X );
BinTree *Find( BinTree *BST, int X );
BinTree *FindMin( BinTree *BST );
BinTree *FindMax( BinTree *BST );
void PreorderTraversal( BinTree *BT)
{
    if(!BT)return;
    printf("%d ",BT->data);
    PreorderTraversal(BT->Left);
    PreorderTraversal(BT->Right);
}
void InorderTraversal ( BinTree *BT)
{
    if(!BT)return;
    InorderTraversal(BT->Left);
    printf("%d ",BT->data);
    InorderTraversal(BT->Right);
}
BinTree *Insert( BinTree *BST, int X )
{
    BinTree *p=BST,*per=p,*sen=new BinTree(X);
    if(!BST)return sen;
    while(p)
    {
        per=p;
        if(p->data>X)p=p->Left;
        else if(p->data<X)p=p->Right;
    }
    if(per->data>X)per->Left=sen;
    else per->Right=sen;
    return BST;
}
BinTree *Delete( BinTree *BST, int X )
{
    if(!BST)
    {
        printf("Not Found\n");
        return BST;
    }
    if(BST->data>X)BST->Left=Delete(BST->Left,X);
    else if(BST->data<X)BST->Right=Delete(BST->Right,X);
    else
    {
        if(!BST->Left)return BST->Right;
        if(!BST->Right)return BST->Left;
        BinTree *tmp=BST->Right,*p=BST;
        while(tmp->Left)tmp=tmp->Left;
        tmp->Left=BST->Left;
        BST=BST->Right;
        delete p;
        return BST;
    }
    return BST;
}
BinTree *Find( BinTree *BST, int X )
{
    BinTree *p=BST;
    while(p)
    {
        if(p->data>X)p=p->Left;
        else if(p->data<X)p=p->Right;
        else return p;
    }
    return nullptr;
}
BinTree *FindMin( BinTree *BST )
{
    BinTree *p=BST;
    if(!p)return p;
    while(p->Left)p=p->Left;
    return p;
}
BinTree *FindMax( BinTree *BST )
{
    BinTree *p=BST;
    if(!p)return p;
    while(p->Right)p=p->Right;
    return p;
}
#endif