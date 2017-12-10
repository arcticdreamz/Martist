#include "martist.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <math.h>


Martist::Martist(double* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth)
				: height(height),width(width),rdepth(rdepth),gdepth(gdepth),bdepth(bdepth){
	
	changeBuffer(buffer,width,height);

}

std::string Martist::getExpression(int depth){

	std::string expressions[4] = {"sin","cos","avg","("};
	std::string exp;


	if(depth > 1) {

		int choice = std::rand()%4;
		exp = expressions[choice];

	
		//sin & cos have expr1 
		if(exp == "sin" || exp == "cos") {
			exp.append("(pi*");
			exp.append(getExpression(depth-1));
			exp.append(")");
		}
		//avg and product have expr1 and expr2
		else if(exp == "avg") {
			int expr1_depth =  std::rand() %(depth-1) + 1; //depth between [1,depth-1]
			int expr2_depth = depth - expr1_depth;
			exp.append("(");
			exp.append(getExpression(expr1_depth));
			exp.append(",");
			exp.append(getExpression(expr2_depth));
			exp.append(")");
		}
		else if(exp =="(" ){
			int expr1_depth =  std::rand() %(depth-1) + 1; //depth between [1,depth-1]
			int expr2_depth = depth - expr1_depth;
			exp.append(getExpression(expr1_depth));
			exp.append("*");
			exp.append(getExpression(expr2_depth));
			exp.append(")");
		}
	}
	//depth == 1
	else{
		exp = (std::rand()%2 == 0) ? "x" : "y";
	}
	return exp;
}


void Martist::redDepth(int depth){
	rdepth = depth;
}
int Martist::redDepth(){
	return rdepth;
}
void Martist::greenDepth(int depth){
	gdepth = depth;
}
int Martist::greenDepth(){
	return gdepth;
}
void Martist::blueDepth(int depth){
	bdepth = depth;
}
int Martist::blueDepth(){
	return bdepth;
}
void Martist::seed(int seed){}

void Martist::changeBuffer(double* buffer, size_t width, size_t height){
		size_t bufferSize = width*height*3;
		buffer  = new double[bufferSize];  // Creates 5 elements
		if(buffer == NULL)
			throw domain_error ("Buffer not initialised");
}
void Martist::paint(){

	std::string redExpression = getExpression(rdepth);
	std::string greenExpression = getExpression(gdepth);
	std::string blueExpression = getExpression(bdepth);

	std::string redParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";
	std::string greenParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";
	std::string blueParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";

	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			index = (x + y*width)*3;
			buffer[index] = evaluateExpression(redParsed,x,y); 		//R
			buffer[index+1] = evaluateExpression(greenParsed,x,y);	//G
			buffer[index+2] = evaluateExpression(blueParsed,x,y);	//B
	}
}

double Martist::evaluateExpression(std::string exp,int xpos, int ypos){

	std::vector<double> numberStack;

	auto c = exp.begin();
	while(c != exp.end()) {
		//Whitespace
		if(isspace(*c)){
			++c;
			continue;
		}

		//Operands
		if(*c == 'x' || *c == 'y' || *c == '2' || *c == 'p' || *c == 'e'){
			else if(*c == 'x')
				numberStack.push_back(xpos/width);
			else if(*c == 'y')
				numberStack.push_back(ypos/height);
			else if(*c == '2')
				numberStack.push_back(2);
			else if(*c == 'p'){ //pi
				c = c + 2;
				numberStack.push_back(3.1415);
				continue;
			}
			else if(*c == 'e'){ //enter
				c = c + 5;
				continue;
			}
		//Operators
		}else{

			double op1 = numberStack.back();
			numberStack.pop_back();
			double op2 = numberStack.back();
			numberStack.pop_back();

			if(*c == 's'){
				c = c + 3
				numberStack.push_back(sin(op1 * op2));
				continue;
			}
			else if(*c == 'c'){
				c = c + 3
				numberStack.push_back(cos(op1 * op2));
				continue;
			}
			else if(*c == '*')
				numberStack.push_back(op1 * op2);
			else if(*c == '/')
				numberStack.push_back(op1 / op2);
			else if(*c == '+')
				numberStack.push_back(op1 + op2);
		}

		++c;

	}

	return numberStack.back();

}




