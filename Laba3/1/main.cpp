#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <initializer_list>

#include <map>
#include "tree.h"

using namespace std;
using tree::Tree;

bool CompareMaps(const Tree& map1, const map<int, int>& map2)
{
	if (map1.size() != map2.size()) return false;
	for (const auto &p : map2)
	{
		if (map1.at(p.first) != p.second) return false;
	}
	return true;
}

class Test
{
public:
	Test(int v): value_(v)
	{
		cout << "Value "<<value_<<" constructed!" << endl;
	}
	~Test()
	{
		cout << "Value destroyed!" << endl;
	}

	operator int() const
	{
		return value_;
	}

private:
	int value_;
};

/*
//Не должно компилироваться
SmartPtr<Test> CheckPointerStrategy()
{
	return SmartPtr<Test>( new Test(13) );
}
*/

void TestPointerConvertion(Test* p)
{
	return;
}


int main()
{
	int total_count = 0;
	string str = "Hello, map on the knee!";
	{
		Tree map1;
		map<int, int> map2;

		for (char ch : str)
		{
			map1[ch]++;
			map2[ch]++;
		}

		cout << "Root value: " << map1.root()<<endl;
		cout << "Size of map: " << map2.size() << endl;
		total_count = map2.size();

		if (CompareMaps(map1, map2))
		{
			cout << "Map and Tree are eual!!!" << endl;
		}
		else
		{
			cout << "I am sorry, it is a FAIL!!!" << endl;
		}
	}
	cout << tree::destroy_count << " nodes has destroyed!"<<endl;
	assert(tree::destroy_count == total_count);
	cout << endl;
	
	cout << "Const pointer check: " << endl;
	{
		const SmartPtr<Test> p = new Test(451);
		cout << "Value is " << *p << endl;
		//p = new Test(14); //Не должно компилироваться: p - константа
		//p = CheckPointerStrategy(); //Не должно компилироваться
		TestPointerConvertion( static_cast<Test*>(p) );
	}//должно быть видно одно уничтожение
	cout << endl;
	
	cout << "Non-const pointer check: " << endl;
	{
		SmartPtr<Test> p = new Test(451);
		cout << "Value is " << *p << endl;
		p = new Test(14);
		//p = CheckPointerStrategy(); //Не должно компилироваться
		TestPointerConvertion( static_cast<Test*>(p) );
	} //должно быть видно два уничтожения
	cout << endl;

	cout << "Non-const pointer check: " << endl;
	{
		SmartPtr<const Test> p = new Test(451);
		cout << "Value is " << *p << endl;
		p = new Test(14);
		//p = CheckPointerStrategy(); //Не должно компилироваться
		//TestPointerConvertion(static_cast<Test*>(p)); //Не должно компилироваться, так как p - указатель на константу
	} //должно быть видно два уничтожения
	cout << endl;

	cout << "The happy end!" << endl;
	cin.get();
	return 0; 
}
