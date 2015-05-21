/* Exceptions library - Generic support for exceptions and Contract theory
 * Copyright (C) $$__YEAR__$$  Vlinder Software
 *
 * $$__LICENSE__$$
 *
 * To obtain a different license, or for more information about this
 * and related software, contact us at <support@vlinder.ca>
 */
#include "contract.hpp"
#include <sstream>
using namespace std;

namespace Vlinder { namespace Contract {
	EXCEPTIONS_API void reportFailure(const char *preamble, const char *expression, const char *file, int line, const char *function)
	{
		stringstream ss;
		ss
			<< file
			<< "("
			<< line
			<< ")"
			<< "BUG: "
			<< "(" 
			<< function 
			<< ")"
			<< preamble
			<< ": "
			<< expression
			;
		throw ContractError(ss.str(), file, line, function);
	}
}}

