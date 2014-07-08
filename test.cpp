/* Vlinder Software's exceptions base classes
 * Copyright 2014  Vlinder Software
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

