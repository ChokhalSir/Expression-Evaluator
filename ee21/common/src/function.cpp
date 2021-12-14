/*!	\file	function.cpp
	\brief	Function class implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Declarations of the Function classes derived from Operation.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2016.11.02
	Added 'override' keyword where appropriate.

Version 2014.10.30
	Removed binary function

Version 2012.11.13
	C++ 11 cleanup

Version 2009.11.26
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


#include <ee/function.hpp>
#include <ee/operator.hpp>
#include <ee/integer.hpp>
#include <ee/boolean.hpp>
#include <ee/real.hpp>
#include <ee/RPNEvaluator.hpp>

//Abs operation
Token::pointer_type Abs::perform(TokenList& values) {
	if(is<Integer>(values[0]))
		return make<Integer>(abs(value_of<Integer>(values[0])));
	else
		return make<Real>(abs(value_of<Real>(values[0])));	
}

//Arccos operation
Token::pointer_type Arccos::perform(TokenList& values) {
	return make<Real>(acosh(value_of<Real>(values[0])));
}

//Arcsin operation
Token::pointer_type Arcsin::perform(TokenList& values) {
	return make<Real>(asin(value_of<Real>(values[0])));
}

//Arctan operation
Token::pointer_type Arctan::perform(TokenList& values) {
	return make<Real>(atanh(value_of<Real>(values[0])));
}

//Ceil operation
Token::pointer_type Ceil::perform(TokenList& values) {
	return make<Real>(ceil(value_of<Real>(values[0])));
}

//Cos operation
Token::pointer_type Cos::perform(TokenList& values) {
	return make<Real>(cos(value_of<Real>(values[0])));
}

//Exp operation
Token::pointer_type Exp::perform(TokenList& values) {
	return make<Real>(exp(value_of<Real>(values[0])));
}

//Floor operation
Token::pointer_type Floor::perform(TokenList& values) {
	return make<Real>(floor(value_of<Real>(values[0])));
}


//Lb - logarithm base 2 operation
Token::pointer_type Lb::perform(TokenList& values) {
	return make<Real>(log2(value_of<Real>(values[0])));
}

//Ln - natural logarithm operation
Token::pointer_type Ln::perform(TokenList& values) {
	return make<Real>(log(value_of<Real>(values[0])));
}

//Log - logarithm base 10 operation
Token::pointer_type Log::perform(TokenList& values) {
	return make<Real>(log10(value_of<Real>(values[0])));
}


//Sin operation
Token::pointer_type Sin::perform(TokenList& values) {
	return make<Real>(sin(value_of<Real>(values[0])));
}

//Sqrt operation
Token::pointer_type Sqrt::perform(TokenList& values) {
	return make<Real>(sqrt(value_of<Real>(values[0])));
}

//Tan operation
Token::pointer_type Tan::perform(TokenList& values) {
	return make<Real>(tan(value_of<Real>(values[0])));
}


//Two argument functions

//Max operation
Token::pointer_type Max::perform(TokenList& values) {
	if(is<Integer>(values[0]))
		return make<Integer>(value_of<Integer>(values[0]) > value_of<Integer>(values[1]) 
			? value_of<Integer>(values[0]) 
			: value_of<Integer>(values[1]));
	else
		return make<Real>(value_of<Real>(values[0]) > value_of<Real>(values[1])
			? value_of<Real>(values[0])
			: value_of<Real>(values[1]));
}

//Min operation
Token::pointer_type Min::perform(TokenList& values) {
	if (is<Integer>(values[0]))
		return make<Integer>(value_of<Integer>(values[0]) < value_of<Integer>(values[1])
			? value_of<Integer>(values[0])
			: value_of<Integer>(values[1]));
	else
		return make<Real>(value_of<Real>(values[0]) < value_of<Real>(values[1])
			? value_of<Real>(values[0])
			: value_of<Real>(values[1]));
}

//Pow operation
Token::pointer_type Pow::perform(TokenList& values) {
	Power power;
	return power.perform(values);
}

//Arctan2 operation
Token::pointer_type Arctan2::perform(TokenList& values) {
	return make<Real>(atan2(value_of<Real>(values[1]),value_of<Real>(values[0])));
}

//declaration of results
std::map<Integer::value_type, Operand::pointer_type> Result::results_;

//Result operation
Token::pointer_type Result::perform(TokenList& values) {
	auto key = value_of<Integer>(values[0]);
	auto result = results_.find(key);
	if (result != results_.end()) {
		if(is<Integer>(result->second))
			return make<Integer>(value_of<Integer>(result->second));
		else if(is<Real>(result->second))
			return make<Real>(value_of<Real>(result->second));
		else
			return make<Boolean>(value_of<Boolean>(result->second));
	}
	else
		return Token::pointer_type();
}

//Save results
void Result::saveResults(Operand::pointer_type const& value) {
	Integer::value_type key = Result::results_.size() + 1;
	Result::results_[key] = value;
}

void Result::clearResults() {
	Result::results_.clear();
}
