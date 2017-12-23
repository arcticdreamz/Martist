
#ifndef _EXPRESSION_H
#define _EXPRESSION_H
#include <string>
#include "parser.hpp"
#include <iostream>


/***********************************************************************
* Class used as a mathematical expression, both in infix and postfix format
***********************************************************************/
class Expression {	

public:
	/**********************************************************************	
	* Constructors
	***********************************************************************/
	Expression();
	/**********************************************************************	
	* Creates an Expression object with a expressio taken from an istream
	***********************************************************************/
	explicit Expression(std::istream& in);
	/**********************************************************************	
	* Creates an Expression object with a random expressio from a given depth
	***********************************************************************/
	explicit Expression(int depth);

	/**********************************************************************	
	* Evaluates the postfix expression using the given xpos and ypos values
	*
	* ARGUMENTS:
	* -two values in the [-1,1] range
	***********************************************************************/
	double evaluateExpression(double xpos, double ypos);
	/**********************************************************************	
	* Calculates the depth of the expression
	*
	* NO ARGUMENTS
	***********************************************************************/
	int calculateDepth() const;

	/**********************************************************************	
	* Returns the infix expression
	*
	* NO ARGUMENTS
	***********************************************************************/
	std::string getExpression() const;
	Exp getParsed();

private:

	/***********************************************************************
	* Generates a random expression of sin,cos,avg,x,y or product from a
	* maximum given depth
	*
	* ARGUMENTS
	*  - maximal depth of the expression
	* ***********************************************************************/
	std::string randomExpression(int depth);

	std::string exp; //Infix expression
	Exp parsedExp; //postfix expression
};

#endif
