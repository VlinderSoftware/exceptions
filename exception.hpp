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

