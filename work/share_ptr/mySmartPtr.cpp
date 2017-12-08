
#include <iostream>
#include <vector>
#include "mySmartPtr.h"
using namespace std;
class Base
{
public:
	virtual ~Base()
	{
		cout<< "class Base"<<endl;
	}
};

class Derived1: public Base
{
public:
	~Derived1()
	{
		cout << "class Derived1"<<endl;
	}
};

class Derived2: public Base
{
public:
	~Derived2()
	{
		cout << "class Derived2"<<endl;
	}
};



int main()
{
	int *pi = new int(42);	
	mySmartPtr<int> *hpa(new mySmartPtr<int>(pi)); //指针构造函数
	mySmartPtr<int> *hpb = new mySmartPtr<int>(*hpa); //拷贝构造函数
	mySmartPtr<int> hpd = *hpa;  //拷贝赋值函数
	
	cout<< hpa->getPtrCounter() << " "<<hpb->getPtrCounter() \
	<< " "<<hpd.getPtrCounter()<<endl; 

	delete hpa;
	cout<< " "<<hpd.getPtrCounter()<<endl; 
	delete hpb;
	cout<< " "<<hpd.getPtrCounter()<<endl; 

	vector<mySmartPtr<Base> >obj;
	obj.push_back(new Derived1);
	obj.push_back(new Derived2);

	vector<mySmartPtr<Base> >obj2;
	obj2.push_back(obj[0]);

	if(obj2[0])
		cout<< " cast Derivedl to Base successd"<<endl;
	else
		cout<< " cast Derivedl to Base failed"<<endl;

#if 1
	mySmartPtr<Derived1> d1 = new Derived1;
	mySmartPtr<Base> b = d1;
	mySmartPtr<Derived2> d2 = b.Cast<Derived2>();

	if(d2)
		cout<< "Cast Derived1 to Derived2 successed"<<endl;
	else
		cout<< "Cast Derived1 to Derived2 failed"<<endl;
	

#endif
	return 0;
}
