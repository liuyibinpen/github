
#ifndef __MY_SMART_PTR_
#define __MY_SMART_PTR_
#include <iostream>
using namespace std;
template <typename T>
class mySmartPtr
{
public:
	mySmartPtr():pointer(0),counter(0){}
	
	mySmartPtr(T* p):pointer(0),counter(0){*this = p;}

	mySmartPtr(const mySmartPtr<T> &p):
	pointer(p.pointer),counter(p.counter){
		Increase();
	}

	~mySmartPtr()
	{
		Decrease();
	}
	mySmartPtr operator=(T* p)
	{
		Decrease();
		if(p)
		{
			pointer = p;
			counter = new int(1);
		}
		else
		{
			pointer = 0;
			counter = 0;
		}

		return *this;
	}

	mySmartPtr operator=(mySmartPtr<T> &p)
	{
		if(this != &p)
		{
			Decrease();
			pointer = p.pointer;
			counter = p.counter;
			Increase();
		}
		return *this;
	}
	operator bool()const{
		return counter != 0;
	}

	T* operator*()const
	{
		return this;
	}
	T* operator->()const
	{
		return pointer;  //c++ 会自动延续->
	}
	int getPtrPointer()const
	{
		return *pointer;
	}
	int getPtrCounter()const
	{
		return *counter;
	}
	template<typename C>friend class mySmartPtr; //另外一个类型 基类

	template <typename C>
	mySmartPtr(const mySmartPtr<C> &p):
		pointer(p.pointer),counter(p.counter)
		{
			Increase();
		}

	template <typename C>
	mySmartPtr<T>& operator=(const mySmartPtr<C>& p)
	{
		Decrease();
		pointer = p.pointer;
		counter = p.counter;
		Increase();
		return *this;
	}
	template<typename C>  
	mySmartPtr<C> Cast()const
	{
		C* converted = dynamic_cast<C*>(pointer);
		mySmartPtr<C> result;
		if(converted)
		{
			result.pointer = converted;
			result.counter = counter;
			result.Increase();
		}
		return result;
	}
private:
	T* pointer;
	int * counter;

	void Increase()
	{
		if(counter)
			++*counter;
	}
	void Decrease()
	{
		if(counter && --*counter == 0)
		{
			delete pointer;
			delete counter;
			counter = 0;
			pointer = 0;
		}
	}
};








#endif //__MY_SMART_PTR_
