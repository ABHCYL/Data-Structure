// myvector.h
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <memory>
#include <iostream>
#include <algorithm>

template<class T , class Alloc=std::allocator<T> >
class myvector
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;//typedef unsigned long long size_t (整这些鬼名字，标准库有点恶心，还是standrd writing)
    typedef ptrdiff_t difference_type;//typedef long long ptrdiff_t
protected:
    std::allocator<T> _alloc;//分配器
    iterator _start;
    iterator _end;
    iterator _end_of_storage;
public:
    // 构造 赋值重载 析构 7件套
    myvector():_start(0),_end(0),_end_of_storage(0){}
    myvector(size_type n,const T& value);
    myvector(size_type n);
    myvector(iterator first,iterator last);
    myvector(const myvector&v);//复制构造
    myvector& operator=(const myvector&v);//赋值重载
    virtual ~myvector(){_destroy();}

    //begin,end,size,capacity,老生常谈的区间大小范围 4件套
    iterator begin() {return _start;}
    iterator end() {return _end;}
    const_iterator cbegin() const{return _start;}
    const_iterator cend() const{return _end;}
    size_type size(){return size_type(end()-begin());}
    size_type capacity(){return size_type(_end_of_storage-begin());}
    //冷门的东西,判空 交换(这个有大文章可做，跟内存回收有关的技巧swap)
    bool empty(){return begin()==end();}
    void swap(myvector &other);//两个vectr做交换，不是内部元素换，这也是standrd writing

    //一头一尾 以及重载一个[ ]运算符
    reference front() {return *begin();}
    reference back() {return *end();}
    reference operator[](size_type n) {return *(begin()+n);}
    // 插删 入出 清除
    void insert_help(iterator pos,const T&x);
    void pop_back();
    void push_back(const T&value);
    void insert(iterator pos,size_type n,const T&x);
    iterator erase(iterator pos);
    iterator erase(iterator first,iterator last);
    void clear() {erase(begin(),end());}

    void _destroy();//删除与释放
};
template <class T,class Alloc>
void myvector<T,Alloc>::_destroy()
{
    if(_start)
    {
        iterator it(_end);
        while (it != _start)
		_alloc.destroy(--it);
    }
    //释放内存
	_alloc.deallocate(_start, _end_of_storage - _start);
	_start= _end_of_storage = _end = 0;
}
template <class T,class Alloc>
myvector<T,Alloc>::myvector(size_type n,const T& value)
{
    _start=_alloc.allocate(n);
    std::uninitialized_fill(_start,_start+n,value);
    _end=_end_of_storage=_start+n;
}
template <class T,class Alloc>
myvector<T,Alloc>::myvector(size_type n)
{
    _start=_alloc.allocate(n);
    std::uninitialized_fill(_start,_start+n,0);
    _end=_end_of_storage=_start+n;
}
template <class T,class Alloc>
myvector<T,Alloc>::myvector(iterator first,iterator last)
{
    _start=_alloc.allocate(last-first);
    _end=_end_of_storage=std::uninitialized_copy(first,last,_start);
}
template <class T,class Alloc>
myvector<T,Alloc>::myvector(const myvector&v)
{
    size_type n=v.cend()-v.cbegin();
    _start=_alloc.allocate(n);
    _end=_end_of_storage=std::uninitialized_copy(v.cbegin(),v.cend(),_start);
}
template <class T,class Alloc>
myvector<T,Alloc> &myvector<T,Alloc>::operator=(const myvector&v)
{
    if(this==&v)return *this;
    size_type n=v.cend()-v.cbegin();
    _start=_alloc.allocate(n);
    _end=_end_of_storage=std::uninitialized_copy(v.cbegin(),v.cend(),_start);
    return *this;
}
template <class T,class Alloc>
void myvector<T,Alloc>::swap(myvector &other)
{
    std::swap(_start,other._start);
    std::swap(_end,other._end);
    std::swap(_end_of_storage,other._end_of_storage);
}
template <class T,class Alloc>
void myvector<T,Alloc>::insert(iterator pos,size_type n,const T&x)
{
    if(n<0)return;
    if(_end_of_storage-_end>=n)
    {
        T xcopy=x;
        const size_type elem_after=_end-pos;//计算插入点之后的元素个数
        iterator old_end = _end;
        if (elem_after >n) 
        {
			std::uninitialized_copy(_end - n, _end, _end);
			_end = _end + n;        //将尾端后移
			std::copy_backward(pos, old_end - n, old_end);
			std::fill(pos, pos + n, xcopy);
		}
		else 
        {                      //要插入的元素大于等于插入点之后元素
			std::uninitialized_fill_n(_end, n - elem_after, xcopy);
			_end += n - elem_after;
			std::uninitialized_copy(pos, old_end, _end);
			_end += elem_after;
			fill(pos, old_end, xcopy);
		}
    }
    else
    {                           //如果剩余空间不足
        const size_type old_size = size();
        size_type tt=n;
        if(old_size>tt)tt=old_size;
		const size_type len = old_size + tt;
		iterator new_start = _alloc.allocate(len);
		iterator new_end = new_start;
        new_end =std::uninitialized_copy(_start, pos , new_start);   //将position之前的元素复制到新容器
		new_end=std::uninitialized_fill_n(new_end, n, x);    //插入元素
		new_end=std::uninitialized_copy(pos, _end, new_end);
        _destroy();   //调用成员函数进行释放空间
		//重新调整迭代器，使其指向新的位置
		_start = new_start;
		_end = new_end;
		_end_of_storage = new_start + len;
    }
}
template <class T,class Alloc>
void myvector<T, Alloc>::insert_help(iterator pos, const T& x)
{
	if (_end != _end_of_storage) {}
	else 
    {
		const size_type old_size = size();                    //需要注意，如果开始长度为0
		const size_type len = old_size ? 2 * old_size : 1;    //则配置长度1，否则，加倍
		iterator new_start = _alloc.allocate(len);            //重新分配空间
		iterator new_end = new_start;
	    
		new_end = std::uninitialized_copy(_start, pos, new_start);   //对于push_back来说position=_end,将其拷贝出来
	    _alloc.construct(new_end, x);                     //插入元素
		++new_end;
		new_end = std::uninitialized_copy(pos, _end, new_end);     //将插入点后的元素也拷贝过来

		_destroy();                    //执行自定义函数
		//调整迭代器，指向新的指针

		//重新调整迭代器，使其指向新的位置
		_start = new_start;
		_end = new_end;
		_end_of_storage = new_start + len;
	}
}
template <class T,class Alloc>
void myvector<T,Alloc>::push_back(const T&value)
{
    if(_end!=_end_of_storage)   //如果还有剩余的空间
    {
        _alloc.construct(_end,value);   //在_end处调用配置器插入value
        ++_end;                 //迭代器后移
    }
    else insert_help(end(),value);
}
template <class T,class Alloc>
void myvector<T,Alloc>::pop_back()
{
    --_end;   //这里要注意的是，删除尾部，要让_end先移动到最后一个元素
    _alloc.destroy(_end); 
}
template <class T,class Alloc>
typename myvector<T,Alloc>::iterator myvector<T,Alloc>::erase(iterator pos)
{
    if(pos+1!=end())//也就是说要删除的这个元素不是最后一个元素
    std::copy(pos+1,end(),pos);
    --_end;
    _alloc.destroy(_end);
    return pos;
}
template <class T,class Alloc>
typename myvector<T,Alloc>::iterator myvector<T,Alloc>::erase(iterator first,iterator last)
{
    difference_type Left=_end-last;
    std::copy(last, _end, first);         //first last avail 向前迁移元素
	iterator it(first + Left);
    while (_end != it)                   //需要析构，有可能不需要析构，这要看在last后元素与删除元素的比较
		_alloc.destroy(--_end);
	return first;
}
#endif