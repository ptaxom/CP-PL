#include <iostream>
#include <vector>
#include <functional>
#include <cassert>

#include "reverse.h"
#include "range.h"

using namespace std;
using namespace utilities;

using ranges::Range;

#define EXPECT_EXCEPTION( EXPR ) try{ EXPR; assert(false); } catch(std::exception&){}

class TestNumber
{
public:
	TestNumber()
	{
		std::cout << "=========Test "<<number<<"=========="<<endl;
		++number;
	}
	~TestNumber()
	{
		std::cout << "Passed!" << endl<<endl;
	}
private:
	static int number;
};
int TestNumber::number = 0;

/*==============Tests==============
0. Creating, first() and last()
1. Custom step sequence
2. Default step sequence
3. begin() and end() with const and without

4. iterator creating and dereferencing*
5. iterator increments
6. iterators ==
7. iterators !=
8. iterators >
9. iterators <
10. iterators >=
11. iterators <=

12. reverse iterator creating and dereferencing*
13. reverse iterator increments
14. reverse iterators ==
15. reverse iterators !=
16. reverse iterators >
17. reverse iterators <
18. reverse iterators >=
19. reverse iterators <=

20. range::size()
21. range[]
*/

enum class Result
{
	True, False, Exception, Undefined
};

template<typename Itr, typename Func>
Result IteratorTest(Itr lhs, Itr rhs, Func func )
{
	Result result = Result::Undefined;
	try
	{
		result = func(lhs, rhs) ? Result::True : Result::False;
	}
	catch (std::exception&)
	{
		result = Result::Exception;
	}
	return result;
}

template<typename Cont, typename RefCont, typename Func>
void CompareResults(Cont& range, RefCont& ref_range, Func f)
{
	auto result = IteratorTest(range.begin(), range.end(), f);
	auto ref_result = IteratorTest(ref_range.begin(), ref_range.end(), f);
	assert(result == ref_result);

	result = IteratorTest(range.end(), range.begin(), f);
	ref_result = IteratorTest(ref_range.end(), ref_range.begin(), f);
	assert(result == ref_result);

	result = IteratorTest(range.begin(), ++range.begin(), f);
	ref_result = IteratorTest(ref_range.begin(), ++ref_range.begin(), f);
	assert(result == ref_result);

	result = IteratorTest(++range.begin(), range.begin(), f);
	ref_result = IteratorTest(++ref_range.begin(), ref_range.begin(), f);
	assert(result == ref_result);

	result = IteratorTest(--range.end(), range.end(), f);
	ref_result = IteratorTest(--ref_range.end(), ref_range.end(), f);
	assert(result == ref_result);

	result = IteratorTest(range.end(), --range.end(), f);
	ref_result = IteratorTest(ref_range.end(), --ref_range.end(), f);
	assert(result == ref_result);

	result = IteratorTest(range.begin(), range.begin(), f);
	ref_result = IteratorTest(ref_range.begin(), ref_range.begin(), f);
	assert(result == ref_result);

	result = IteratorTest(range.end(), range.end(), f);
	ref_result = IteratorTest(ref_range.end(), ref_range.end(), f);
	assert(result == ref_result);
}

template<typename Cont, typename ConstCont, typename RefCont, typename ConstRefCont>
void DoIteratorTesting(Cont& range1, ConstCont& range2, ConstCont& zero_range,
	RefCont& ref_range1, ConstRefCont& ref_range2)
{
	//iterator creating
	{
		auto test = TestNumber();
		//commented should not compile
		//Range::iterator itr; 
		//Range::iterator itr(range1);
		//Range::iterator itr(range1,0);
		//Range::iterator itr(0,range1);
		auto itr1 = range1.begin();
		auto itr2 = std::move(itr1);

		auto itr3 = zero_range.begin();
		auto itr4 = std::move(itr3);

		EXPECT_EXCEPTION(*range1.end());
	}

	// increments
	{
		auto test = TestNumber();
		EXPECT_EXCEPTION(--range1.begin());
		EXPECT_EXCEPTION(++range1.end());

		EXPECT_EXCEPTION(--range2.begin());
		EXPECT_EXCEPTION(++range2.end());

		EXPECT_EXCEPTION(--zero_range.begin());
		EXPECT_EXCEPTION(++zero_range.end());

		auto itr1 = range1.begin();
		assert(itr1++ == range1.begin());
		assert(itr1 == ++range1.begin());

		auto itr2 = range2.end();
		assert(itr2-- == range2.end());
		assert(itr2 == --range2.end());
	}

	//operator ==
	{
		auto test = TestNumber();
		auto lambda = [](auto lhs, auto rhs) { return lhs == rhs; };

		//regular versions
		CompareResults(range1, ref_range1, lambda);

		//const versions
		CompareResults(range2, ref_range2, lambda);

		//different containers
		auto result = IteratorTest(zero_range.begin(), range2.begin(), lambda);
		assert(result == Result::Exception);
	}

	//operator !=
	{
		auto test = TestNumber();
		auto lambda = [](auto lhs, auto rhs) { return lhs != rhs; };

		//regular versions
		CompareResults(range1, ref_range1, lambda);

		//const versions
		CompareResults(range2, ref_range2, lambda);

		//different containers
		auto result = IteratorTest(zero_range.begin(), range2.begin(), lambda);
		assert(result == Result::Exception);
	}

	//operator >
	{
		auto test = TestNumber();
		auto lambda = [](auto lhs, auto rhs) { return lhs > rhs; };

		//regular versions
		CompareResults(range1, ref_range1, lambda);

		//const versions
		CompareResults(range2, ref_range2, lambda);

		//different containers
		auto result = IteratorTest(zero_range.begin(), range2.begin(), lambda);
		assert(result == Result::Exception);
	}

	//operator <
	{
		auto test = TestNumber();
		auto lambda = [](auto lhs, auto rhs) { return lhs < rhs; };

		//regular versions
		CompareResults(range1, ref_range1, lambda);

		//const versions
		CompareResults(range2, ref_range2, lambda);

		//different containers
		auto result = IteratorTest(zero_range.begin(), range2.begin(), lambda);
		assert(result == Result::Exception);
	}

	//operator >=
	{
		auto test = TestNumber();
		auto lambda = [](auto lhs, auto rhs) { return lhs >= rhs; };

		//regular versions
		CompareResults(range1, ref_range1, lambda);

		//const versions
		CompareResults(range2, ref_range2, lambda);

		//different containers
		auto result = IteratorTest(zero_range.begin(), range2.begin(), lambda);
		assert(result == Result::Exception);
	}

	//operator <=
	{
		auto test = TestNumber();
		auto lambda = [](auto lhs, auto rhs) { return lhs <= rhs; };

		//regular versions
		CompareResults(range1, ref_range1, lambda);

		//const versions
		CompareResults(range2, ref_range2, lambda);

		//different containers
		auto result = IteratorTest(zero_range.begin(), range2.begin(), lambda);
		assert(result == Result::Exception);
	}
}


template<typename Cont>
void OutContainer(const Cont& cont, ostream& stream = std::cout)
{
	stream << "================================" << endl;
	for (const auto& a : cont)
	{
		stream << a << " ";
	}
	stream << endl;
}

template<typename Cont>
auto SizeTest(Cont& cont)
{
	auto size = std::distance(cont.begin(), cont.end());
	assert(size == cont.size());
	return cont.size();
}

template<typename Cont, typename RefCont>
void ElementTest(Cont& cont, RefCont& ref_cont)
{
	for (int i = 0; i < cont.size(); ++i)
	{
		assert(cont[i] == ref_cont[i]);
	}
}

int main()
{
	vector<int> a;
	try
	{
		//test 0
		{
			auto test = TestNumber();

			Range range1(40, 50);
			const Range range2(40, -30, -1);

			Range range3(11, 100, 3);
			const Range range4(71, -17, -5);

			const Range one_number_range(10, 10);

			//first and last
			assert(range1.first() == 40);
			assert(range2.first() == 40);
			assert(range3.first() == 11);
			assert(range4.first() == 71);
			assert(one_number_range.first() == 10);

			assert(range1.last() == 50);
			assert(range2.last() == -30);
			assert(range3.last() == 98);
			assert(range4.last() == -14);
			assert(one_number_range.last() == 10);
		}

		//test 1
		{
			auto test = TestNumber();
			OutContainer(Range(0, 100, 2));
			OutContainer(Range(50, 80, 2));
			OutContainer(Range(30, -20, -3));
			EXPECT_EXCEPTION(OutContainer(Range(1, 10, 0)));
			EXPECT_EXCEPTION(OutContainer(Range(30, -20, 3)));
		}
		//test 2
		{
			auto test = TestNumber();
			OutContainer(Range(0, 100));
			EXPECT_EXCEPTION(OutContainer(Range(30, -20)));
		}
		//test 3
		{
			auto test = TestNumber();
			OutContainer<const Range>(Range(0, 100));
			OutContainer<const Range>(Range(0, 100, 2));
		}

		Range range1(40, 50);
		const Range range2(40, -30, -1);
		const Range zero_range(0, 0);

		//STL compability
		vector<int> ref_range1(range1.begin(), range1.end());
		const vector<int> ref_range2(range2.begin(), range2.end());

		//iterator testing 4-11
		DoIteratorTesting(range1, range2, zero_range, ref_range1, ref_range2);

		//reverse containers
		auto rev_range1 = Reverse(range1);
		const auto rev_range2(range2);
		const auto rev_zero_range(zero_range);
		auto rev_ref_range1(ref_range1);
		const auto rev_ref_range2(ref_range2);

		//reverse iterator testing 12-19
		DoIteratorTesting(rev_range1, rev_range2, rev_zero_range, rev_ref_range1, rev_ref_range2);

		//test 20
		{
			auto test = TestNumber();
			assert(SizeTest(range1) == SizeTest(ref_range1));
			assert(SizeTest(range2) == SizeTest(ref_range2));
			assert(SizeTest(zero_range) == 1);
		}

		//test 21: operator[]
		{
			auto test = TestNumber();
			ElementTest(range1, ref_range1);
			ElementTest(range2, ref_range2);
		}
		cout << "You did it!!!";
	}
	catch (std::exception& ex)
	{
		cout << ex.what()<<endl;
		cout << "So sad! "<<endl;
	}
	
	cin.get();
	return 0;
}