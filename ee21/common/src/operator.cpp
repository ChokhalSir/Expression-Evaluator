/*!	\file	operator.cpp
	\brief	Operator classes implementations.
	\author	Garth Santor
	\date	2021-10-29
	\copyright	Garth Santor, Trinh Han

=============================================================
Implementation of the Operator class derived from Token and the
supporting utilities.

=============================================================
Revision History
-------------------------------------------------------------

Version 2021.10.02
	C++ 20 validated

Version 2019.11.05
	C++ 17 cleanup

Version 2012.11.13
	C++ 11 cleanup

Version 0.1.0: 2010-11-08
	Added exception for assignment to a non-variable.

Version 2009.12.14
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

#include <ee/operator.hpp>
#include <ee/operand.hpp>
#include <ee/integer.hpp>
#include <ee/real.hpp>
#include <ee/variable.hpp>
#include <ee/boolean.hpp>
#include <cassert>


//fast power function for Integer
Integer::value_type fast_power(Integer::value_type base, Integer::value_type exponent) { // exponent >= 0
	if (exponent.is_zero())
		return Integer::value_type(1);

	auto x = fast_power(base, exponent / 2);
	if (exponent % 2 == 0)
		return x * x;
	else
		return base * x * x;
}


//fast power function for Real
Real::value_type fast_power(Real::value_type base, Real::value_type exponent) { // exponent >= 0
	if (exponent.is_zero())
		return Real::value_type(1);

	auto x = fast_power(base, exponent / 2);
	if (fmod(exponent, 2) == 0)
		return x * x;
	else
		return base * x * x;
}



//power operations
Token::pointer_type Power::perform(TokenList& values){
	if (is<Integer>(values[0]) && is<Integer>(values[1]))
	{
		auto exp = value_of<Integer>(values[0]);
		auto base = value_of<Integer>(values[1]);
		if (exp < 0)
			return make<Real>(1.0 / static_cast<Real::value_type>(fast_power(base, exp * (-1))));

		else 
			return make<Integer>(fast_power(base, exp));
	}
	else
	{
		auto exp = value_of<Real>(values[0]);
		auto base = value_of<Real>(values[1]);
		if (exp < 0)
			return make<Real>(1.0 / (pow(base, exp * (-1))));
		else
			return make<Real>(pow(base, exp));
	}
}

//Assignment operation
Token::pointer_type Assignment::perform(TokenList& values) {
	if (is<Variable>(values[1])) {
		auto x = convert<Variable>(values[1]);
		x->set(convert<Operand>(values[0]));
		return x;
	}
	else
		throw std::exception("Error: assignment to a non-variable.");
}

//Addition operation
Token::pointer_type Addition::perform(TokenList& values){
	if (is<Integer>(values[0]) && is<Integer>(values[1]))
	{
		auto val2 = value_of<Integer>(values[0]);
		auto val1 = value_of<Integer>(values[1]);
		return make<Integer>(val1 + val2);
	}
	else
	{
		auto val2 = value_of<Real>(values[0]);
		auto val1 = value_of<Real>(values[1]);
		return make<Real>(val1 + val2);
	}
}

//Division operation
Token::pointer_type Division::perform(TokenList& values){
	if (is<Integer>(values[0]) && is<Integer>(values[1]))
	{
		auto val2 = value_of<Integer>(values[0]);
		auto val1 = value_of<Integer>(values[1]);
		return make<Integer>(val1 / val2);
	}
	else
	{
		auto val2 = value_of<Real>(values[0]);
		auto val1 = value_of<Real>(values[1]);
		return make<Real>(val1 / val2);
	}
}

//Multiplication operation
Token::pointer_type Multiplication::perform(TokenList& values) {
	if (is<Integer>(values[0]) && is<Integer>(values[1]))
	{
		auto val2 = value_of<Integer>(values[0]);
		auto val1 = value_of<Integer>(values[1]);
		return make<Integer>(val1 * val2);
	}
	else
	{
		auto val2 = value_of<Real>(values[0]);
		auto val1 = value_of<Real>(values[1]);
		return make<Real>(val1 * val2);		
	}
}


//Modulus division operation
Token::pointer_type Modulus::perform(TokenList& values){
	if (is<Integer>(values[0]) && is<Integer>(values[1]))
	{
		auto val2 = value_of<Integer>(values[0]);
		auto val1 = value_of<Integer>(values[1]);
		return make<Integer>(val1 % val2);
	}
}

//Subtraction operation
Token::pointer_type Subtraction::perform(TokenList& values){
	if (is<Integer>(values[0]) && is<Integer>(values[1]))
	{
		auto val2 = value_of<Integer>(values[0]);
		auto val1 = value_of<Integer>(values[1]);
		return make<Integer>(val1 - val2);
	}
	else
	{
		auto val2 = value_of<Real>(values[0]);
		auto val1 = value_of<Real>(values[1]);
		return make<Real>(val1 - val2);
	}
}


//Identity operation
Token::pointer_type Identity::perform(TokenList& values) {
	if (is<Integer>(values[0]))
	{
		auto value = value_of<Integer>(values[0]);
		return make<Integer>(value);
	}
	else if (is<Real>(values[0]))
	{
		auto value = value_of<Real>(values[0]);
		return make<Real>(value);
	}
}

//Negation operation
Token::pointer_type Negation::perform(TokenList& values) {
	if (is<Integer>(values[0]))
	{
		auto value = value_of<Integer>(values[0]) * (-1);
		return make<Integer>(value);
	}
	else if (is<Real>(values[0]))
	{
		auto value = value_of<Real>(values[0]) * (-1);
		return make<Real>(value);
	}
}

//Factorial Operation
Token::pointer_type Factorial::perform(TokenList& values) {
	if (is<Integer>(values[0]))
	{
		auto value = value_of<Integer>(values[0]);
		Integer::value_type res = 1;
		for (Integer::value_type i = 2; i <= value; ++i) {
			res *= i;
		}
		return make<Integer>(res);
	}
}

//Not operation
Token::pointer_type Not::perform(TokenList& values) {
	auto a = convert<Boolean>(values[0]);
	return value_of<Boolean>(a) == true ? make<False>() : make<True>();
}

//And operation
Token::pointer_type And::perform(TokenList& values) {
	if((is<False>(values[1])) || (is<False>(values[0])))
		return make<Boolean>(false);
	else
		return make<Boolean>(true);
}

//Nand operation
Token::pointer_type Nand::perform(TokenList& values) {
	if ((is<False>(values[1])) || (is<False>(values[0])))
		return make<Boolean>(true);
	else
		return make<Boolean>(false);
}

//Nor operation
Token::pointer_type Nor::perform(TokenList& values) {
	if (is<True>(values[1]) || is<True>(values[0]))
		return make<Boolean>(false);
	else
		return make<Boolean>(true);
}

//Or operation
Token::pointer_type Or::perform(TokenList& values) {
	if (is<True>(values[1]) || is<True>(values[0]))
		return make<Boolean>(true);
	else
		return make<Boolean>(false);
}

//Xor operation
Token::pointer_type Xor::perform(TokenList& values) {
	if (value_of<Boolean>(values[0]) == value_of<Boolean>(values[1]))
		return make<Boolean>(false);
	else
		return make<Boolean>(true);
}

//Xnor operation
Token::pointer_type Xnor::perform(TokenList& values) {
	if (value_of<Boolean>(values[0]) == value_of<Boolean>(values[1]))
		return make<Boolean>(true);
	else
		return make<Boolean>(false);
}

//Equality operation
Token::pointer_type Equality::perform(TokenList& values) {
	if (values[0] == values[1])
		return make<Boolean>(true);
	else
		return make<Boolean>(false);
}

//Inequality operation
Token::pointer_type Inequality::perform(TokenList& values) {
	if (values[0] != values[1])
		return make<Boolean>(true);
	else
		return make<Boolean>(false);
}

//Greater operation
Token::pointer_type Greater::perform(TokenList& values) {
	if (is<Integer>(values[1])) {
		if(value_of<Integer>(values[1]) > value_of<Integer>(values[0]))
			return make<True>();
		else
			return make<False>();
	}
	auto a = is<Boolean>(values[1]) ? value_of<Boolean>(values[1]) : value_of<Real>(values[1]);
	auto b = is<Boolean>(values[0]) ? value_of<Boolean>(values[0]) : value_of<Real>(values[0]);
	if (a > b)
		return make<True>();
	else
		return make<False>();
}

//Greater equal operation
Token::pointer_type GreaterEqual::perform(TokenList& values) {
	if (is<Integer>(values[1])) {
		if (value_of<Integer>(values[1]) >= value_of<Integer>(values[0]))
			return make<True>();
		else
			return make<False>();
	}
	auto a = is<Boolean>(values[1]) ? value_of<Boolean>(values[1]) : value_of<Real>(values[1]);
	auto b = is<Boolean>(values[0]) ? value_of<Boolean>(values[0]) : value_of<Real>(values[0]);
	if (a >= b)
		return make<True>();
	else
		return make<False>();
}

//Less operation
Token::pointer_type Less::perform(TokenList& values) {
	if (is<Integer>(values[1])) {
		if (value_of<Integer>(values[1]) < value_of<Integer>(values[0]))
			return make<True>();
		else
			return make<False>();
	}
	auto a = is<Boolean>(values[1]) ? value_of<Boolean>(values[1]) : value_of<Real>(values[1]);
	auto b = is<Boolean>(values[0]) ? value_of<Boolean>(values[0]) : value_of<Real>(values[0]);
	if (a < b)
		return make<True>();
	else
		return make<False>();
}

//Less equal operation
Token::pointer_type LessEqual::perform(TokenList& values) {
	if (is<Integer>(values[1])) {
		if (value_of<Integer>(values[1]) <= value_of<Integer>(values[0]))
			return make<True>();
		else
			return make<False>();
	}
	auto a = is<Boolean>(values[1]) ? value_of<Boolean>(values[1]) : value_of<Real>(values[1]);
	auto b = is<Boolean>(values[0]) ? value_of<Boolean>(values[0]) : value_of<Real>(values[0]);
	if (a <= b)
		return make<True>();
	else
		return make<False>();;
}


