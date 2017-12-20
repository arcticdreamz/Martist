#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>    // std::rand
#include <math.h>
#include <iostream>
#include <vector>

#include "parser.hpp"
#include "expression.hpp"
#include "martist.hpp"


Expression::Expression(int depth){

	if(depth == 0){
		parsedExp.push_back("zero");
		exp.append("");
	}
	else{
		exp = randomExpression(depth);
		std::istringstream is(exp);
		Parser parser(is);
		parser.parse(parsedExp,exp);
	}
}

Expression::Expression(std::istream& in){
		Parser parser(in);
		parser.parse(parsedExp,exp);

		if(parsedExp.empty())
			parsedExp.push_back("zero");
}

std::string Expression::getExpression() const{
	return exp;
}
Exp Expression::getParsed() const{
	return parsedExp;
}


std::string Expression::randomExpression(int depth){

	std::string expressions[4] = {"avg","cos","(","sin",};
	std::string exp;
	//Random chance(1/10) of getting an x/y in a complex expression
	if(std::rand()%10 == 0){
		depth = 1;
	}


	if(depth > 1) {

		int choice = std::rand()%4;
		exp = expressions[choice];

	
		//sin & cos have expr1 
		if(exp == "sin" || exp == "cos") {
			exp.append("(pi*");
			exp.append(randomExpression(depth-1));
			exp.append(")");
		}
		//avg and product have expr1 and expr2
		else if(exp == "avg") {
			exp.append("(");
			exp.append(randomExpression(depth - 1));
			exp.append(",");
			exp.append(randomExpression(depth - 1));
			exp.append(")");
		}
		else if(exp =="(" ){

			exp.append(randomExpression(depth - 1));
			exp.append("*");
			exp.append(randomExpression(depth - 1));
			exp.append(")");
		}
	}
	//depth == 1
	else{
		exp = (std::rand()%2 == 0) ? "x" : "y";
	}
	return exp;
}


unsigned char Expression::evaluateExpression(double xpos, double ypos){

	if(*parsedExp.begin() == "zero")
		return 0.0;

	std::vector<double> numberStack;

	auto s = parsedExp.begin();
	while(s != parsedExp.end()) {

		//Operands
		if(*s == "x" || *s == "y" || *s == "2" || *s == "pi" || *s == "enter"){
			if(*s == "x")
				numberStack.push_back(xpos);
			else if(*s == "y")
				numberStack.push_back(ypos);
			else if(*s == "2")
				numberStack.push_back(2);
			else if(*s == "pi") //pi
				numberStack.push_back(3.1415);
			else if(*s == "enter"){}//enter
			
		//Operators
		}else{
			if(*s == "sin"){ //sin
				double op = numberStack.back();
				numberStack.pop_back();
				numberStack.push_back(sin(op));
			}
			else if(*s == "cos"){//cos
				double op = numberStack.back();
				numberStack.pop_back();
				numberStack.push_back(cos(op));
			}
			else if(*s == "*"){
				double op = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op * op2);
			}
			else if(*s == "/"){
				double op = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op / op2);
			}				
			else if(*s == "+"){
				double op = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op + op2);
			}
		}

		++s;

	}
	int result = numberStack.back();
	return (unsigned char)255*(0.5 + 0.5 * result);

}

int calculateDepth() const{}