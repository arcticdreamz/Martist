//#include "martist.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <iostream>


std::string getExpression(int depth){

	std::string expressions[4] = {"sin","cos","avg","("};
	std::string exp;

	if(depth > 1) {
		int choice = std::rand()%4;
		exp = expressions[choice];
		int expr1_depth =  std::rand() %(depth-1) + 1; //depth between [1,depth-1]
		int expr2_depth = depth - expr1_depth;
	
		//sin & cos have expr1 
		if(exp == "sin" || exp == "cos") {
			exp.append("(pi*");
			exp.append(getExpression(expr1_depth));
			exp.append(")");
		}
		//avg and product have expr1 and expr2
		else if(exp == "avg") {
			exp.append("(");
			exp.append(getExpression(expr1_depth));
			exp.append(",");
			exp.append(getExpression(expr2_depth));
			exp.append(")");
		}
		else if(exp =="(" ){
			exp.append(getExpression(expr1_depth));
			exp.append("*");
			exp.append(getExpression(expr2_depth));
			exp.append(")");
		}
	}
	//depth == 1
	else
		exp = (std::rand()%2 == 0) ? "x" : "y";

	return exp;
}

int main(){
/*	unsigned char* buffer = nullptr;
	Martist martist(buffer,200,200,4,4,4);
*/
	int depth = 1;
	std::cout << "" << std::endl;
	std::cout << "Insert depth of the expression: ";
	std::cin >> depth;
	std::string myString = getExpression(depth);
	std::cout << myString << std::endl;

	return 0;
}