#include "martist.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand



Martist::Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth)
				: height(height),width(width),rdepth(rdepth),gdepth(gdepth),bdepth(bdepth){
	
	changeBuffer(buffer,width,height);
	red = getExpression(rdepth);
	green = getExpression(gdepth);
	blue = getExpression(bdepth);
}

std::string Martist::getExpression(int depth){

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

void Martist::changeBuffer(unsigned char* buffer, size_t width, size_t height){
		size_t bufferSize = width*height*3;
		buffer[bufferSize] =  (char*) malloc(bufferSize*sizeof(float)); 
		if(buffer == NULL)
			throw domain_error ("Buffer not initialised");
}
void Martist::paint(){}