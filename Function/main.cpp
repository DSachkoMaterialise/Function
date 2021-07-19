#include <iostream>
#include <functional>
#include "Function.h"

using namespace std;

struct A
	{
	void meth()
		{
		cout << "Kek2\n";
		}
	};

void func()
	{
	cout << "Kek3\n";
	}

int main()
{
	Function<void()> foo = []()
		{
		cout << "Kek1\n";
		};
	Function<void(A&)> foo2 = &A::meth;
	Function<void()> foo3 = func;
	
	A a;
	foo();
	foo2(a);
	foo3();
	return 0;
}