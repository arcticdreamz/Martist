#include "martist.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand



Martist::Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth){
	changeBuffer(buffer,width,height);
	height = height;
	width = width;
	rdepth = rdepth;
	gdepth = gdepth;
	bdepth = bdepth;
}

std::string Martist::getExpression(int depth,std::string exp){
	expr1_depth =  std::rand() %(depth-1) + 1; //depth between [1,depth-1]
	expr2_depth = 1 - expr1_depth;
	if(exp == 'sin' || exp == "cos") {

	}

	if(exp == "avg" || exp =="(" {
	})


	std::string expr1 = randExpression(expr1_depth);

	//sin & cos have expr1 
	//avg and product have expr1 and expr2


}

std::string Martist::randExpression(int depth){
	
	std::string exp
	std::string expressions[4] = {"sin","cos","avg","("};

	if(depth > 1) {
		int choice = std::rand()%4;
		exp = expressions[choice];

	}
	//depth == 1
	else
		exp = (std::rand()%2 == 0) ? "x" : "y";

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