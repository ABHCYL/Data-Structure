#ifndef _MAXHEAP_h
#define _MAXHEAP_h
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
template<class T>
class maxheap
{
    private:
    T *heap;
    int msize;
    int mcapacity;
    void filterdown(int cur, int end);// 最大堆的向上调整算法(从cur开始向上直到0，调整堆)
    void filterup(int index);
    public:
    maxheap();
    maxheap(int capacity);
    maxheap(T a[], int size); // O(n)建堆
    ~maxheap();
    bool remove(T data); // 删除最大堆中的data
    bool insert(T data); // 将data插入到二叉堆中
    T top();
    void pr();
};
template<class T>
maxheap<T>::maxheap()
{
    msize=0;
    mcapacity=30;
    heap=new T[30];
}
template<class T>
maxheap<T>::maxheap(int capacity)
{
    msize=0;
    mcapacity=capacity;
    heap=new T[capacity];
    //new数组长度为0不报错，但实际没有分配内存, 当修改数据时就会导致内存被破坏. 当被破坏的内存恰好被使用时就会导致异常.学过csapp第三章3.10的应该明白
}
template<class T>
maxheap<T>::~maxheap()
{
    msize=mcapacity=0;
    delete [] heap;
}
template<class T>
void maxheap<T>::filterup(int index)//从下到上调整堆,插入元素时候使用,O(lgn)
{
    T value = heap[index];//待调整的节点在末端
    while (index>0)
    {
        int parent=(index-1)/2;
        if(value>heap[parent])
        {
            heap[index]=heap[parent];
            index=parent;
        }
        else break;
    }
    heap[index]=value;
}
template<class T>
bool maxheap<T>::insert(T data)
{
    if(msize==mcapacity)return 0;//insert false
    heap[msize]=data;
    filterup(msize);
    ++msize;
    return 1;
}
template<class T>
void maxheap<T>::filterdown(int cur, int end)//从上到下调整堆,删除元素时候使用,O(lgn)
{
    int child=cur*2+1;
    T value = heap[cur];
    while (child<=end)
    {
        if(child<end && heap[child]<heap[child+1])++child;//选出两个孩子中较大的孩子
        if(value<heap[child])
        {
            heap[cur]=heap[child];
            cur=child;
            child=child*2+1;
        }
        else break;
    }
    heap[cur]=value;
}
template<class T>
bool maxheap<T>::remove(T data)
{
    if (!msize)return 0; //如果堆是空的
    int index;
    for (index=0;index<msize;++index)if(heap[index]==data)break;//获取值在数组中的索引
    if (index == msize)return 0; //数组中没有该值
    heap[index] = heap[msize - 1]; //使用最后一个节点来代替当前结点，然后再向下调整当前结点。
    filterdown(index,msize--);  
    return 1;
}
template<class T>
maxheap<T>::maxheap(T a[], int size)
{
    msize=size;
    mcapacity=size<<1;
    heap=new T[mcapacity];
    for(int i=0;i<msize;++i)heap[i]=a[i];
    for(int i=size/2;i>=0;--i)filterdown(i,size-1);
}
template<class T>
T maxheap<T>::top()
{
    return heap[0];
}
template<class T>
void maxheap<T>::pr()
{
    for(int i=0;i<msize;++i)cout<<heap[i]<<" ";
}
#endif