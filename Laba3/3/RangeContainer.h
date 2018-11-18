#pragma once

#include <stdexcept>
#include <utility>

namespace ranges
{

	class Range
	{
	public:

		Range(int begin_, int end_, int step_ = 1);

		int first() const;

		int last() const;

		int size() const;


		
		MyIterator begin();

		MyIterator end();

		MyIterator rbegin();

		MyIterator rend();



		MyIterator begin() const;

		MyIterator end() const;

		MyIterator rbegin() const;

		MyIterator rend() const;

		
		int operator[](int index)
		{
			int val = begin_ + step_ * index;
			return val;
		}

		const int operator[](int index) const
		{
			int val = begin_ + step_ * index;
			return val;
		}



	private:
		int begin_;
		int end_;
		int step_;
		

		inline std::pair<int, int> getBounds(int type = 0) const //Type0 - direct iterator
		{
			if (type == 0)
				return std::make_pair(begin_, end_ + step_);
			else return std::make_pair(end_, begin_ - step_);
		}

		MyIterator factoryIterator(int start_, int step_, int type = 0)
		{
			return ranges::MyIterator(start_, step_, (int)this, getBounds(type));
		}

		MyIterator factoryIterator(int start_, int step_, int type = 0) const
		{
			return ranges::MyIterator(start_, step_, (int)this, getBounds(type));
		}

	};


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


	//Non-const iterators


	MyIterator Range::begin()
	{
		return this->factoryIterator(first(), step_);
	}

	MyIterator Range::end()
	{
		return this->factoryIterator(last() + step_, step_);
	}

	MyIterator Range::rbegin()
	{
		return this->factoryIterator(last(), -step_, 1);
	}

	MyIterator Range::rend()
	{
		return this->factoryIterator(first() - step_, -step_, 1);
	}


	//const Iterators

	MyIterator Range::begin() const
	{
		return this->factoryIterator(first(), step_);
	}

	MyIterator Range::end() const
	{
		return this->factoryIterator(last() + step_, step_);
	}

	MyIterator Range::rbegin() const
	{
		return this->factoryIterator(last(), -step_, 1);
	}

	MyIterator Range::rend() const
	{
		return this->factoryIterator(first() - step_, -step_, 1);
	}


	
}