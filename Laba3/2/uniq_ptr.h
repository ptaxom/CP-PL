#pragma once

template<typename T>
class UniqPtr
{
public:

	UniqPtr() : ptr(nullptr)
	{}

	UniqPtr(T* ptr) : ptr(ptr)
	{}

	~UniqPtr() 
	{
		this->Reset();
	}


	UniqPtr(const UniqPtr<T> &ptr) = delete;  //Copy constructor 

	UniqPtr<T> &operator=(const UniqPtr<T> &ptr) = delete;  //Copy assigment

	

	UniqPtr(UniqPtr<T> &&other) : ptr(other.ptr)			//Move constructor
	{
		other.ptr = nullptr;
	}

	UniqPtr<T> &operator=(UniqPtr<T> &&other)			  //Move assigment
	{
		Reset(other.Release());
		return *this;
	}



	bool Empty() const 
	{
		return ptr == nullptr;
	}

	void Reset() 
	{
		if (!Empty()) 
		{
			delete ptr;
			ptr = nullptr;
		}
	}

	void Reset(T *other) 
	{
		this->Reset();
		this->ptr = other;
		other = nullptr;
	}

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


	T* Release()
	{
		T* buf = this->ptr;
		this->ptr = nullptr;
		return buf;
	}

private:
	T* ptr;
};