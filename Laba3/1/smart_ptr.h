#pragma once

template<typename T>
class SmartPtr {

public:

	//Constructor section

	SmartPtr() : ptr(nullptr)
	{}

	SmartPtr(T* ptr) : ptr(ptr)
	{}

	~SmartPtr()
	{
		this->Reset();
	}

	//Deleted constructors

	SmartPtr(const SmartPtr<T> &ptr) = delete;  //Copy constructor 

	SmartPtr(SmartPtr<T> &&other) = delete;				//Move constructor


	SmartPtr<T> &operator=(const SmartPtr<T> &ptr) = delete;    //Copy assignment

	//Assignment 

	SmartPtr<T> &operator=(SmartPtr<T> &&other) 		  //Move assignment
	{
		this->Reset(other.ptr);
		other.ptr = nullptr;
		return *this;
	}

	//Methods

	bool Empty() const
	{
		return ptr == nullptr;
	}


	void Reset(T* other = nullptr)
	{
		if (other != ptr)
		{
			if (!Empty())
				delete ptr;
			ptr = other;
		}
	}


	//Overload operators


	T& operator*() const
	{
		return *ptr;
	}

	T* operator->() const
	{
		return ptr;
	}

	operator T*() const
	{
		return ptr;
	}


private:
	T* ptr;
};