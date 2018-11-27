#pragma once

#include <iterator>

namespace ranges
{

	class MyIterator;
	class Range;

	class MyIterator : public std::iterator<std::bidirectional_iterator_tag, int>
	{
	public:

		bool operator==(const MyIterator &other) const;
		bool operator!=(const MyIterator &other) const;

		bool operator<(const MyIterator &other) const;
		bool operator>(const MyIterator &other) const;

		bool operator<=(const MyIterator &other) const;
		bool operator>=(const MyIterator &other) const;

		int operator*() const;

		MyIterator& operator++();
		MyIterator operator++(int);

		MyIterator& operator--();
		MyIterator operator--(int);



	private:
		int value_;
		int type_;
		const Range &master_;


		friend class Range;

		MyIterator(int value, int type, const Range &master) : value_(value), type_(type), master_(master)
		{}

		int getStep() const;


	};

	class Range
	{
	public:

		Range(int begin_, int end_, int step_ = 1);

		bool operator!=(const Range &other) const { return this != &other; }


		int first() const;

		int last() const;

		int size() const;

		int getStep() const;

		MyIterator begin() const;

		MyIterator end() const;

		MyIterator rbegin() const;

		MyIterator rend() const;

		const int operator[](int index) const
		{
			int val = begin_ + step_ * index;
			return val;
		}



		inline std::pair<int, int> getBounds(int type = 0) const //Type0 - direct iterator
		{
			if (type == 0)
				return std::make_pair(begin_, end_ + step_);
			else return std::make_pair(end_, begin_ - step_);
		}

		inline bool isOutOfBounds(int value, int boundsType, bool isStrictCompare = false) const
		{
			auto bounds = getBounds(boundsType);
			int offset1 = sign(value - bounds.first);
			int offset2 = sign(bounds.second - value);
			if (isStrictCompare)
				return offset2 == 0 || offset1 * offset2 < 0;
			return offset1 * offset2 < 0;
		}


	private:
		int begin_;
		int end_;
		int step_;

		static int sign(int val)
		{
			if (val < 0) return -1;
			if (val == 0) return 0;
			else return 1;
		}

		MyIterator factoryIterator(int value, int type = 0) const
		{
			return ranges::MyIterator(value, type, *this);
		}

	};



}