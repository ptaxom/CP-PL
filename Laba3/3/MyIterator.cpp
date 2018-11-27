#include "range.h"
#include <stdexcept>

using ranges::MyIterator;

int MyIterator::getStep() const
{
	if (type_ == 0)
		return master_.getStep();
	else return -master_.getStep();
}


bool MyIterator::operator==(const MyIterator & other) const
{
	if (master_ != other.master_)
		throw std::exception("incomparable containers");
	return value_ == other.value_;
}

bool MyIterator::operator!=(const MyIterator & other) const
{
	return !(*this == other);
}

bool MyIterator::operator<(const MyIterator & other) const
{
	if (master_ != other.master_)
		throw std::exception("incomparable containers");
	return (value_ - other.value_) * getStep() < 0;
}

bool MyIterator::operator>(const MyIterator & other) const
{
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

	if (master_.isOutOfBounds(value_, type_, true))
		throw std::exception("Out of bounds");
	return value_;
}

MyIterator & MyIterator::operator++()
{
	if (master_.isOutOfBounds(value_ + getStep(), type_))
		throw std::exception("Out of bounds!");

	value_ += getStep();
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
	if (master_.isOutOfBounds(value_ - getStep(), type_))
		throw std::exception("Out of bounds!");

	value_ -= getStep();
	return *this;
}

MyIterator MyIterator::operator--(int)
{
	MyIterator temp(*this);
	--*this;
	return temp;
}
