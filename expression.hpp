
#ifndef _EXPRESSION_H
#define _EXPRESSION_H
#include <string>
#include "parser.hpp"
#include <iostream>



class Expression {	

public:
	explicit Expression(std::istream& in);
	explicit Expression(int depth);

	unsigned char evaluateExpression(double xpos, double ypos);
	int calculateDepth() const{};
	Exp getParsed() const;
	std::string getExpression() const;

private:

	std::string randomExpression(int depth);

	std::string exp;
	Exp parsedExp;
};

#endif
