#include "martist.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand


std::string getExpression(int depth){

	std::string expressions[4] = {"sin","cos","avg","("};
	std::string exp;

	if(depth > 1) {
		int choice = std::rand()%4;
		exp = expressions[choice];
		expr1_depth =  std::rand() %(depth-1) + 1; //depth between [1,depth-1]
		expr2_depth = 1 - expr1_depth;
	}
	//depth == 1
	else
		exp = (std::rand()%2 == 0) ? "x" : "y";

	//sin & cos have expr1 
	if(exp == 'sin' || exp == "cos") {
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

	return exp;
}

int main(){
/*	unsigned char* buffer = nullptr;
	Martist martist(buffer,200,200,4,4,4);
*/

	std::string myString = getExpression(5);


	return 0;
}