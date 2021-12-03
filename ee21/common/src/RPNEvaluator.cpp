/*!	\file	RPNEvaluator.cpp
	\brief	RPN Evaluator class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated
	Changed to GATS_TEST

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.10
	Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han, Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <ee/RPNEvaluator.hpp>
#include <ee/integer.hpp>
#include <ee/operation.hpp>
#include <cassert>
#include <stack>
#include <algorithm>


[[nodiscard]] Operand::pointer_type RPNEvaluator::evaluate( TokenList const& rpnExpression ) {
	
	std::stack<Token::pointer_type> stack;
	for (auto tk : rpnExpression)
	{
		if (is<Operand>(tk))
			stack.push(tk);
		else
		{
			auto operTk = convert<Operation>(tk);
			auto operationNum = operTk->number_of_args();
			if (operationNum > stack.size())
				throw "Insufficient # operands of operation";
			for (unsigned i = 0; i < operationNum; i++) 
			{
				auto operand = stack.top();
				stack.pop();
				auto oper = tk.get();
				
			}
			auto operand = stack.top();
			stack.pop();
			auto operation = convert<Operation>(tk);
			operation->str();
		}
	}
	
	// The following line is just a placeholder until you have completed the parser.
	return Operand::pointer_type();
}

