#pragma once

#include <iostream>

template<typename T>
class UniqPtr 
{
public:

	UniqPtr()
	{
		ptr = nullptr;
	}

	UniqPtr(T* ptr)
	{
		this->ptr = ptr;
	}

	~UniqPtr() {
		//std::cout << "Destruct: " << ptr << std::endl;
		this->Reset();
	}


	UniqPtr(const UniqPtr<T> &ptr) = delete;  //Copy constructor 

	UniqPtr(UniqPtr<T> &&other) : ptr(other.ptr)			//Move constructor
	{
		other.ptr = nullptr;
	}

	UniqPtr<T> &operator=(const UniqPtr<T> &ptr) = delete;  //Copy assigment

	UniqPtr<T> &operator=(UniqPtr<T> &&other)			  //Move assigment
	{
		this->ptr = other.ptr;
		other.ptr = nullptr;
		return *this;
	}



	bool Empty() const {
		return ptr == nullptr;
	}

	void Reset() {
		if (!Empty()) {
			delete ptr;
			ptr = nullptr;
		}
	}

	void Reset(UniqPtr<T> &other) {
		this->Reset();
		this->ptr = other.ptr;
		other.ptr = nullptr;
	}

	T& operator*() const {
		return *ptr;
	}

	T* operator->() const {
		return ptr;
	}


	operator T*() const {
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