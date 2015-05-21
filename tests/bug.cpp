/* Exceptions library - Generic support for exceptions and Contract theory
 * Copyright (C) $$__YEAR__$$  Vlinder Software
 *
 * $$__LICENSE__$$
 *
 * To obtain a different license, or for more information about this
 * and related software, contact us at <support@vlinder.ca>
 */
#include "../bug.hpp"
#include <cassert>
#include <cstring>

int main()
{
	try
	{
		bug_if(1, "test");
	}
	catch (std::logic_error const &e)
	{
		assert(strcmp(e.what(), "test") == 0);
	}
	return 0;
}
