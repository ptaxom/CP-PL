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
	Test(const Test&) = delete;
	Test(Test&&) = delete;
	Test& operator=(const Test&) = delete;
	Test& operator=(Test&&) = delete;

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

//������ ������ ���������������
UniqPtr<Test> CheckPointerStrategy()
{
	return UniqPtr<Test>( new Test(13) );
}

void TestPointerConvertion(Test* p)
{
	return;
}

void OutDestroyCount()
{
	cout << tree::destroy_count << " nodes destroyed" << endl;
	tree::destroy_count = 0;
}

int main()
{ 
	try
	{
		Tree my_map = { { 1,0 },{ 2,0 },{ 3,1 },{ 4,0 },{ 5,1 },{ 6,0 },{ 7,1 },{ 8,0 },{ 9,0 },{ 10,0 },{ 11,1 } };
		cout << "Size after creating " << my_map.size() << endl;
		my_map.erase(1);
		OutDestroyCount();
		cout << "Size after erasing 1 " << my_map.size() << endl;

		cout << "Is 6 simple: " << my_map[6]<<endl;
		my_map.erase(6);
		OutDestroyCount();
		cout << "Is 6 simple: " << my_map.at(6) << endl;
	}
	catch (std::range_error& ex)
	{
		cout << ex.what() << endl;
	}
	OutDestroyCount();
	cout << endl;

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
	assert(tree::destroy_count == total_count);
	OutDestroyCount();
	cout << endl;
	
	cout << "Const pointer check: " << endl;
	{
		const UniqPtr<Test> p = new Test(451);
		cout << "Value is " << *p << endl;
		//p = new Test(14); //�� ������ ���������������: p - ���������
		//p = CheckPointerStrategy(); //�� ������ ���������������: p - ���������
		TestPointerConvertion( static_cast<Test*>(p) );
		//p.Release(); //�� ������ ���������������: p - ���������
	}//������ ���� ����� ���� �����������
	cout << endl;
	
	cout << "Non-const pointer check: " << endl;
	{
		UniqPtr<Test> p = new Test(451);
		cout << "Value is " << *p << endl;
		p = new Test(14); //����������� 1
		p = CheckPointerStrategy(); //����������� 2
		TestPointerConvertion( static_cast<Test*>(p) );
		delete p.Release(); //����������� 3
	} //������ ���� ����� ��� �����������
	cout << endl;

	cout << "Non-const pointer check: " << endl;
	{
		UniqPtr<const Test> p = new Test(451);
		cout << "Value is " << *p << endl;
		p = new Test(14);
		//p = CheckPointerStrategy(); //�� �������������, � �������� ��, ��� �������. ��������, ����� ���������� � ���������
		//TestPointerConvertion(static_cast<Test*>(p)); //�� ������ ���������������, ��� ��� p - ��������� �� ���������
	} //������ ���� ����� ��� �����������
	cout << endl;

	cout << "Swap testing"<<endl;
	{
		UniqPtr<const Test> p1 = new Test(4);
		UniqPtr<const Test> p2 = new Test(7);
		swap(p1, p2);
		assert(*p1 == 7);
		assert(*p2 == 4);
	}
	
	cout << "The happy end!" << endl;
	cin.get();
	return 0; 
}
