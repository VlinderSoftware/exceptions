/* Exceptions library - Generic support for exceptions and Contract theory
 * Copyright (C) $$__YEAR__$$  Vlinder Software
 *
 * $$__LICENSE__$$
 *
 * To obtain a different license, or for more information about this
 * and related software, contact us at <support@vlinder.ca>
 */
#ifndef vlinder_bug_h
#define vlinder_bug_h

#include <stdexcept>

namespace Vlinder {
	class Bug : public std::logic_error
	{
	public :
		explicit Bug(const std::string &message)
			: std::logic_error(message)
		{ /* no-op */ }
	};
}

#define bug_if(c, m) { if (c) throw Vlinder::Bug(m); }

#endif

