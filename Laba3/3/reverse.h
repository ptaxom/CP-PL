#ifndef REVERSE_H
#define REVERSE_H
#pragma once

namespace utilities
{
	template<typename Cont>
	class ReverseImpl
	{
	public:
		ReverseImpl(Cont& cont) :
			cont_{ cont }
		{}

		auto begin() const
		{
			return cont_.rbegin();
		}
		auto end() const
		{
			return cont_.rend();
		}

		auto begin()
		{
			return cont_.rbegin();
		}
		auto end()
		{
			return cont_.rend();
		}

	private:
		Cont & cont_;
	};

	template<typename Cont>
	ReverseImpl<Cont> Reverse(Cont& container)
	{
		return ReverseImpl<Cont>(container);
	}
}

#endif