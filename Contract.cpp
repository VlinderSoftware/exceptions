#include "Contract.h"
#include <sstream>

using namespace std;

namespace Vlinder { namespace Contract {
	void reportFailure(const char *preamble, const char *expression, const char *file, int line, const char *function)
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
