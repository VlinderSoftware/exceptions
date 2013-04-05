#ifndef vlinder_exceptions_exception_h
#define vlinder_exceptions_exception_h

#include <stdexcept>	// most-used values of B require this
#include <string>

namespace Vlinder { namespace Exceptions {
	template < typename B, typename E >
	class Exception_
		: public B
	{
	public :
		explicit Exception_(const std::string &message)
			: B(message)
		{ /* no-op */ }

		virtual E which() const = 0;
	};

	template < typename B, typename E, E v__ >
	class Exception
		: public Exception_< B, E >
	{
	public :
		explicit Exception(const std::string &message)
			: Exception_< B, E >(message)
		{ /* no-op */ }

		virtual E which() const { return v__; }
	};
}}

#endif

