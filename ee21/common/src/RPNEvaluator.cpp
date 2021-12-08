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


[[nodiscard]] Operand::pointer_type RPNEvaluator::evaluate( TokenList const& rpnExpression ) {
	
	std::stack<Token::pointer_type> stack;
	TokenList values;
	if (rpnExpression.empty())
		throw std::exception ("Error: insufficient operands");
	for (auto tk : rpnExpression)
	{
		if (is<Operand>(tk))
			stack.push(tk);
		else
		{
			auto operTk = convert<Operation>(tk);
			auto operationNum = operTk->number_of_args();
			if (operationNum > stack.size())
				throw std::exception("Insufficient # operands of operation");
			for (unsigned i = 0; i < operationNum; i++) 
			{
				values.push_back(stack.top());
				stack.pop();
			}
			stack.push(operTk->perform(values));
		}//else
	}//for
	if (stack.size() > 1)
		throw std::exception("Error: too many operands");
	if (stack.empty())
		throw std::exception("Too many operations for the number of operands.");
	
	return convert<Operand>(stack.top());
}

