#include<cstdio>
#include<iostream>
#include"BinTree.h"
using namespace std;
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("0in.txt", "r", stdin);
    freopen("0out.txt", "w", stdout);
    #endif
    BinTree *BST, *MinP, *MaxP, *Tmp;
    int X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for ( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:"); PreorderTraversal(BST); printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL) printf("%d is not found\n", X);
        else {
            printf("%d is found\n", Tmp->data);
            if (Tmp==MinP) printf("%d is the smallest key\n", Tmp->data);
            if (Tmp==MaxP) printf("%d is the largest key\n", Tmp->data);
        }
    }
    scanf("%d", &N);
    for( i=0; i<N; i++ ) {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:"); InorderTraversal(BST); printf("\n");
    return 0;
}