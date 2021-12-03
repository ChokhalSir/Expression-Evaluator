/*!	\file	parser.cpp
	\brief	Parser class implementation.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han
=============================================================
Revision History
-------------------------------------------------------------

Version 2021.11.01
	C++ 20 validated
	Changed to GATS_TEST

Version 2014.10.31
	Visual C++ 2013

Version 2012.11.13
	C++ 11 cleanup

Version 2009.12.02
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

#include <ee/parser.hpp>
#include <ee/function.hpp>
#include <ee/operand.hpp>
#include <ee/operator.hpp>
#include <ee/pseudo_operation.hpp>
#include <stack>
#include <queue>
#include <string>

[[nodiscard]] TokenList Parser::parse(TokenList const& infixTokens) {
	
	std::stack<Token::pointer_type> operStack;
	TokenList postfixTokens;
	try{
		for (auto tk : infixTokens)
		{
			if (is<Operand>(tk))
				postfixTokens.push_back(tk);
			else if (is<Function>(tk))
				operStack.push(tk);
			else if (is<ArgumentSeparator>(tk))
			{
				while (!is<LeftParenthesis>(operStack.top()))
				{
					postfixTokens.push_back(operStack.top());
					operStack.pop();
				}
			}
			else if (is<LeftParenthesis>(tk))
				operStack.push(tk);
			else if (is<RightParenthesis>(tk))
			{
				while (!is<LeftParenthesis>(operStack.top()))
				{
					postfixTokens.push_back(operStack.top());
					operStack.pop();
				}
				if (operStack.empty())
					throw "Right parenthesis, has no matching left parenthesis.";

				operStack.pop();
				if (!operStack.empty() && is<Function>(operStack.top()))
				{
					postfixTokens.push_back(operStack.top());
					operStack.pop();
				}
			}
			else if (is<Operator>(tk))
			{
				while (!operStack.empty())
				{
					if (!is<Operator>(operStack.top()) || is<NonAssociative>(tk))
						break;
					if (is<LAssocOperator>(tk))
					{
						auto operatorTk = convert<Operator>(tk);
						auto operatorSt = convert<Operator>(operStack.top());
						if (operatorTk->precedence() > operatorSt->precedence())
							break;
					}
					if (is<RAssocOperator>(tk))
					{
						auto operatorTk = convert<Operator>(tk);
						auto operatorSt = convert<Operator>(operStack.top());
						if (operatorTk->precedence() >= operatorSt->precedence())
							break;
					}
					postfixTokens.push_back(operStack.top());
					operStack.pop();
				}//while
				operStack.push(tk);
			}//elseif
			else
				throw "Unkown token.";
		}//end for
		while (!operStack.empty())
		{
			if (is<LeftParenthesis>(operStack.top()))
				throw "Missing right-parenthesis.";
			postfixTokens.push_back(operStack.top());
			operStack.pop();
		}//while
	}//try
	catch (std::string e) {
		std::cout << e << std::endl;
	}
	return postfixTokens;
}
