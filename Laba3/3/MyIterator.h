#pragma once
#include <iterator>
#include <utility>


namespace ranges
{

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
		int step_;
		int masterID_;

		std::pair<int, int> bounds_;

		friend class Range;

		MyIterator(int value_, int step_, int masterID_, const std::pair<int, int> &bounds_) : value_(value_), step_(step_), masterID_(masterID_), bounds_(bounds_)
		{}

		inline bool isOutOfBounds(int val) const
		{
			int offset1 = val - bounds_.first;
			int offset2 = bounds_.second - val;
			return offset1 * offset2 < 0;
		}
	};

	bool MyIterator::operator==(const MyIterator & other) const
	{
		if (masterID_ != other.masterID_)
			throw std::exception("incomparable containers");
		return value_ == other.value_;
	}

	bool MyIterator::operator!=(const MyIterator & other) const
	{
		return !(*this == other);
	}

	bool MyIterator::operator<(const MyIterator & other) const
	{
		if (masterID_ != other.masterID_)
			throw std::exception("incomparable containers");
		return (value_ - other.value_ )* step_ < 0;
	}


	#include <iostream>

	bool MyIterator::operator>(const MyIterator & other) const
	{
		//std::cout << std::boolalpha << (other < *this) << " : < " << this->value_ << " vs " << other.value_ << "\n";
		return other < *this;
	}

	bool MyIterator::operator<=(const MyIterator & other) const
	{
		return !(other < *this);
	}

	bool MyIterator::operator>=(const MyIterator & other) const
	{
		return !(*this < other);
	}

	int MyIterator::operator*() const
	{
		if (value_ == bounds_.second)
			throw std::exception("Out of bounds");
		return value_;
	}

	MyIterator & MyIterator::operator++()
	{
		if (isOutOfBounds(value_ + step_)) 
			throw std::exception("Out of bounds!");
		
		value_ += step_;
		return *this;
	}

	MyIterator MyIterator::operator++(int)
	{
		MyIterator temp(*this);
		++*this;
		return temp;
	}

	MyIterator & MyIterator::operator--()
	{
		if (isOutOfBounds(value_ - step_)) 
			throw std::exception("Out of bounds!");
		
		value_ -= step_;
		return *this;
	}

	MyIterator MyIterator::operator--(int)
	{
		MyIterator temp(*this);
		--*this;
		return temp;
	}

}