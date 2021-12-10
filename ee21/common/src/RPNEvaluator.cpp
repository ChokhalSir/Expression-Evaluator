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
#include <ee/real.hpp>
#include <ee/variable.hpp>
#include <ee/operation.hpp>
#include <ee/operator.hpp>
#include <cassert>
#include <algorithm>


[[nodiscard]] Operand::pointer_type RPNEvaluator::evaluate( TokenList const& rpnExpression ) {
	
	TokenList stack;
	TokenList values;
	if (rpnExpression.empty())
		throw std::exception ("Error: insufficient operands");
	for (auto tk : rpnExpression)
	{
		if (is<Operand>(tk))
			stack.push_back(tk);
		else
		{
			auto operTk = convert<Operation>(tk);
			auto operationNum = operTk->number_of_args();
			if (operationNum > stack.size())
				throw std::exception("Insufficient # operands of operation");
			//if there is a variable in the stack replace it with its value.
			auto variableId = std::find_if(stack.begin(), stack.end(), [](auto i) {return is<Variable>(i);});
			for (auto i : stack) 
			{
				if (variableId != stack.end() && !is<Assignment>(operTk))
				{
					auto var = convert<Variable>(*variableId);
					if (!var->value())
						throw std::exception("Error: variable not initialized");
					auto newId = stack.erase(variableId);
					stack.insert(newId, var->value());
				}
				variableId = std::find_if(stack.begin(), stack.end(), [](auto i) {return is<Variable>(i); });
			}
			//if there is a real number in the stack realId receive its iterator.
			auto realId = std::find_if(stack.begin(), stack.end(), [](auto i) {return is<Real>(i); });
			bool thereIsReal = realId != stack.end();
			for (unsigned i = 0; i < operationNum; i++) 
			{
				//if there is a real number in the stack and the top of stack is an integer -> convert it to real
				if (thereIsReal && is<Integer>(stack.back()))
				{
					auto val = make<Real>(static_cast<Real::value_type>(value_of<Integer>(stack.back())));
					values.push_back(val);
					stack.pop_back();
				}
				else {
					values.push_back(stack.back());
					stack.pop_back();
				}
				
			}
			if(values.size() == 1 && is<Variable>(values[0]))
				throw std::exception("Error: variable not initialized");
			stack.push_back(operTk->perform(values));
			values.clear();
		}//else
	}//for
	if (stack.size() > 1)
		throw std::exception("Error: too many operands");
	if (stack.empty())
		throw std::exception("Too many operations for the number of operands.");
	
	return convert<Operand>(stack.back());
}

