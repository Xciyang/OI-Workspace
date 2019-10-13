#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Ignore_ret {
	private:
	struct Delete {
		virtual void del(void *p)= 0;
	};
	template < class T >
	struct DeleteT : public Delete {
		virtual void del(void *p) {
			delete(T *)p;
		}
	};

	private:
	void *mem;
	Delete *pdel;

	public:
	Ignore_ret() : mem(0), pdel(0) {}
	~Ignore_ret() {
		release();
	}
	void release() {
		if(mem) {
			pdel->del(mem);
			mem= 0;
			delete pdel;
		}
	}
	template < class T >
	void allocate() {
		if(mem) release();
		mem= new T();
		pdel= new DeleteT< T >();
	}
	template < class T >
	operator T &() {
		allocate< T >();
		return *(T *)mem;
	}
	template < class T >
	operator T *() {
		allocate< T >();
		return (T *)mem;
	}
	template < class T >
	void operator=(const T &x) const {}
} ignore_ret;

int main() {
	int *a= new int();
    *a = 10;
	swap(*(int *)ignore_ret, *a);
	cout << *a << endl;
	return 0;
}