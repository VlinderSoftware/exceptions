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

#endif

