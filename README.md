# Expression-Evaluator
Copyright: Garth Santor

## Project Description
Visual C++ 2019/C++ 20 console application project that implements the Expression Evaluator that reads integers and real numbers, and outputs the result. 
This project implements the infix to postfix algorithm [Shunting yard algorithm by Edsger Dijkstra](https://en.wikipedia.org/wiki/Shunting-yard_algorithm), then implement a postfix to result algorithm [Postfix algorithm](https://en.wikipedia.org/wiki/Reverse_Polish_notation) and then evaluates the result. 

## Suported Types
It suports:
* Real data type.
* Mixed integer and real expressions.
*	Boolean data type along with its appropriate operators (AND, OR, NOT, XOR, NAND, NOR, XNOR) and real data types from the console and outputs the result.  
*	Mathematical functions like arctan, max, min, abs, arccos, arcsin, ceil, cos, exp, floor, lb, ln, log, sin, sqrt, tan.

*	Variables
*	Stored Results - It stores the results of operations that can be used after just calling, for example, Result (# of result), eg. Result (1).


## Design approach
There are several ways to implement this project such as:
* The Big If
* Polimorph on Operand
* Polimorph on Operators
* Double dispatch polimorphism
* Lookup table

Each of these options has its pros and cons. This project used the **Polymorph on Operator** design type.

