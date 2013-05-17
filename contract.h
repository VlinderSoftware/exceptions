/* Exceptions library
 * Generic support for exceptions and Contract theory
 * Copyright (C) 2010-2012  Vlinder Software
 *
 * $$__LICENSE__$$
 *
 * To obtain a different license, or for more information about this
 * and related software, contact us at <support@vlinder.ca>
 */
#ifndef vlinder_contract_h
#define vlinder_contract_h

#include "details/prologue.h"
#include "bug.h"

#ifdef _MSC_VER //TODO make this check better
#define pre_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("pre-condition failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define require(x) ( (x) || ( Vlinder::Contract::reportFailure("requirement not met", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define post_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("post-condition failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define ensure(x) ( (x) || ( Vlinder::Contract::reportFailure("failed to ensure", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#define invariant(x) ( (x) || ( Vlinder::Contract::reportFailure("invariant failed", #x, __FILE__, __LINE__, "__func__ not supported" ), 0 ) )
#else
#define pre_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("pre-condition failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define require(x) ( (x) || ( Vlinder::Contract::reportFailure("requirement not met", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define post_condition(x) ( (x) || ( Vlinder::Contract::reportFailure("post-condition failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define ensure(x) ( (x) || ( Vlinder::Contract::reportFailure("failed to ensure", #x, __FILE__, __LINE__, __func__ ), 0 ) )
#define invariant(x) ( (x) || ( Vlinder::Contract::reportFailure("invariant failed", #x, __FILE__, __LINE__, __func__ ), 0 ) )
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

	EXCEPTIONS_API void reportFailure(const char *preamble, const char *expression, const char *file, int line, const char *function);
}}

#endif

