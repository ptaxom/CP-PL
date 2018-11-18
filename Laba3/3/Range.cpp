#include "range.h"

namespace ranges
{
	Range::Range(int begin_, int end_, int step_)
	{
		int range = end_ - begin_;

		if (step_ == 0 || range / step_ < 0)
			throw std::logic_error("Series disverges!");
		this->begin_ = begin_;
		this->step_ = step_;
		this->end_ = std::abs(range) < std::abs(step_) ? this->begin_ : end_ - range % step_;
	}

	int Range::first() const
	{
		//if (begin_ == end_) throw std::exception("crutch!");
		return begin_;
	}

	int Range::last() const
	{
		//if (begin_ == end_) throw std::exception("crutch!");
		return end_;
	}

	int Range::size() const
	{
		return (end_ - begin_) / step_ + 1;
	}

	int Range::getStep() const
	{
		return step_;
	}

	//Non-const iterators

	/*
	MyIterator Range::begin() 
	{
		return this->factoryIterator(first());
	}

	MyIterator Range::end() 
	{
		return this->factoryIterator(last() + step_);
	}

	MyIterator Range::rbegin() 
	{
		return this->factoryIterator(last(), 1);
	}

	MyIterator Range::rend() 
	{
		return this->factoryIterator(first() - step_, 1);
	}

	*/
	

	//const Iterators

	MyIterator Range::begin() const
	{
		return this->factoryIterator(first());
	}

	MyIterator Range::end() const
	{
		return this->factoryIterator(last() + step_);
	}

	MyIterator Range::rbegin() const
	{
		return this->factoryIterator(last(), 1);
	}

	MyIterator Range::rend() const
	{
		return this->factoryIterator(first() - step_, 1);
	}




}