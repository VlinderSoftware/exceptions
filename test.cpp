/* Exceptions library
 * Generic support for exceptions and Contract theory
 * Copyright (C) 2010-2012  Vlinder Software
 *
 * $$__LICENSE__$$
 *
 * To obtain a different license, or for more information about this
 * and related software, contact us at <support@vlinder.ca>
 */
#include <cstdlib>
#include <iostream>
#include <stdexcept>

unsigned long count__ = 0;

class C
{
public :
	C(bool silent = false)
		: silent_(silent)
	{
		if (!silent_) std::cout << "C()" << std::endl;
		if (--count__ == 0)
		{
			throw std::runtime_error("Default constructor");
		}
	}

	C(const C &c)
		: silent_(c.silent_)
	{
		if (!silent_) std::cout << "C(const C&)" << std::endl;
		if (--count__ == 0)
		{
			throw std::runtime_error("Copy constructor");
		}
	}

	~C()
	{
		if (!silent_) std::cout << "~C()" << std::endl;
	}

	C& operator=(const C &c)
	{
		silent_ = c.silent_;
		if (!silent_) std::cout << "operator=" << std::endl;
		if (--count__ == 0)
		{
			throw std::runtime_error("Assignment operator");
		}
		return *this;
	}

private :
	bool silent_;
};

void* operator new(size_t size, C &c)
{
	std::cout << "operator new" << std::endl;
	if (--count__ == 0)
	{
		throw std::runtime_error("new operator");
	}
	return malloc(sizeof(c));
}

void operator delete(void *p, C &c)
{
	free(p);
}

int main()
{
	bool done = false;
	C c(true);

	for (unsigned long count = 1; !done; ++count)
	{
		std::cout << "count = " << count << std::endl;
		count__ = count;
		try 
		{
			C *p1(new (c) C);
			C *p2(new (c) C);
			C c1(*p1);
			C c2;
			c2 = *p2;
			p2->~C();
			p1->~C();
			done = true;
		}
		catch (const std::runtime_error & e)
		{
			std::cout << "==>" << e.what() << std::endl;
		}
	}
}

