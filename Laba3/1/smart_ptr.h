#pragma once

template<typename T>
class SmartPtr {

public:
	
	SmartPtr() 
	{
		ptr = nullptr;
	}

	SmartPtr( T* ptr) 
	{
		this->ptr = ptr;
	}

	~SmartPtr() {
		this->Reset();
	}


	SmartPtr(const SmartPtr<T> &ptr) = delete;  //Copy constructor 

	SmartPtr(SmartPtr<T> &&other) = delete;				//Move constructor


	SmartPtr<T> &operator=(const SmartPtr<T> &ptr) = delete;    //Copy assigment
	
	SmartPtr<T> &operator=(SmartPtr<T> &&other) 		  //Move assigment
	{
		this->Reset(other);
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

	void Reset(SmartPtr<T> &other) {
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


private:
	T* ptr;


};