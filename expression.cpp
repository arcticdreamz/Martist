#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>    // std::rand
#include <math.h>
#include <iostream>
#include <vector>

#include "parser.hpp"
#include "expression.hpp"


/***********************************************************************
* Constructors
***********************************************************************/
Expression::Expression(){}

Expression::Expression(int depth){
	if(depth < 0 )
		throw std::domain_error("Depth can't be negative");

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

		for(auto it = parsedExp.begin();it != parsedExp.end();it++){
			std::cout<< *it << " ";
		}
		std::cout << " " <<std::endl;

}


/***********************************************************************
* Public classes
***********************************************************************/
std::string Expression::getExpression() const{
	return exp;
}





double Expression::evaluateExpression(double xpos, double ypos){
	if(*parsedExp.begin() == "zero")
		return -1;

	std::vector<double> numberStack;

	Exp::iterator s = parsedExp.begin();
	while(s != parsedExp.end()) {

		//Operands
		if(*s == "x" || *s == "y" || *s == "2" || *s == "pi" || *s == "enter"){
			if(*s == "x")
				numberStack.push_back(xpos);
			else if(*s == "y")
				numberStack.push_back(ypos);
			else if(*s == "2")
				numberStack.push_back(2.0);
			else if(*s == "pi") //pi
				numberStack.push_back(3.14159265359);
			else if(*s == "enter"){}//enter
			
		//Operators
		}else{
			if(numberStack.empty())
				throw std::domain_error("Error during evaluateExpression");

			if(*s == "sin"){ //sin
				double op1 = numberStack.back();
				numberStack.pop_back();
				numberStack.push_back(sin(op1));
			}
			else if(*s == "cos"){//cos
				double op1 = numberStack.back();
				numberStack.pop_back();
				numberStack.push_back(cos(op1));
			}
			else if(*s == "*"){
				double op1 = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op2 * op1);
			}
			else if(*s == "/"){
				double op1 = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op2 / op1);
			}				
			else if(*s == "+"){
				double op1 = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op2 + op1);
			}
		}

		++s;

	}
	double result = numberStack.back();
	return result;

}



int Expression::calculateDepth() const{
	int par = 1;
	int depth = 0;
	std::string::const_iterator c = exp.begin();
	while(c != exp.end()){
		if(*c == '(')
			par++;

		depth = std::max(par,depth);

		if(*c == ')')
			par--;

		c++;

	}
	return depth;
}




/***********************************************************************
* Private classes
***********************************************************************/
std::string Expression::randomExpression(int depth){

	std::string expressions[4] = {"avg","cos","(","sin",};
	std::string exp;
	//Random chance(1/10) of getting an x/y in a complex expression
	// because I thought that 2/6 was too much
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