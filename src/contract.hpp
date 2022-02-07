/* Copyright 2016  Vlinder Software
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
 * limitations under the License. */
#ifndef vlinder_contract_h
#define vlinder_contract_h

#include "exceptions-export.h"
#include "bug.hpp"

#ifdef assert
#undef assert
#endif

#ifdef _MSC_VER //TODO make this check better
#define pre_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("pre-condition failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define require(x) ( (x) || ( Vlinder::Contract::reportFailure("requirement not met", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define post_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("post-condition failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define ensure(x) ( (x) || ( Vlinder::Contract::reportFailure("failed to ensure", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define invariant(x) ( (x) || ( Vlinder::Contract::reportFailure("invariant failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define assert(x) ( (x) || ( Vlinder::Contract::reportFailure("assertion failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#else
#define pre_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("pre-condition failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define require(x) ( (x) || ( Vlinder::Contract::reportFailure("requirement not met", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define post_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("post-condition failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define ensure(x) ( (x) || ( Vlinder::Contract::reportFailure("failed to ensure", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define invariant(x) ( (x) || ( Vlinder::Contract::reportFailure("invariant failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define assert(x) ( (x) || ( Vlinder::Contract::reportFailure("assertion failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#endif

namespace Vlinder { namespace Contract {
	class ContractError : public Bug
	{
	public :
		explicit ContractError(
			const std::string &error_message,
			const std::string &filename,
			int line,
			const std::string &function)
			: Bug(error_message)
			, filename_(filename)
			, line_(line)
			, function_(function)
		{ /* no-op */ }

		~ContractError() throw() {}

		std::string getFilename() const { return filename_; }
		int getLine() const { return line_; }
		std::string getFunction() const { return function_; }

	private :
		std::string filename_;
		int line_;
		std::string function_;
	};

	exceptions_EXPORT void reportFailure(const char *preamble, const char *expression, const char *file, int line, const char *function);
}}

#endif

