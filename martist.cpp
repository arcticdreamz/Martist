#include "martist.hpp"
#include "parser.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <math.h>
#include <sstream>
#include <vector>
#include "CImg.h"
using namespace cimg_library;





Martist::Martist(double* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth)
				:height(height),width(width),rdepth(rdepth),gdepth(gdepth),bdepth(bdepth){
	
	changeBuffer(buffer,width,height);

}
Martist::~Martist() { delete[] myBuffer; }

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
			throw std::domain_error("Buffer not initialised");
		myBuffer = buffer;
}
void Martist::paint(){
	Exp redParsed;
	Exp greenParsed;
	Exp blueParsed;

  	std::istringstream redIN(getExpression(rdepth));
  	std::istringstream greenIN(getExpression(gdepth));
  	std::istringstream blueIN(getExpression(bdepth));

	Parser redParser(redIN);
	Parser greenParser(greenIN);
	Parser blueParser(blueIN);



	if(rdepth == 0) 
		redParsed.push_back("zero");
	else
		redParser.parse(redParsed);
	
	if(gdepth == 0) 
		greenParsed.push_back("zero");
	else
		greenParser.parse(greenParsed);

	if(bdepth == 0) 
		blueParsed.push_back("zero");
	else
		blueParser.parse(blueParsed);





/*	redParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";
	greenParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";
	blueParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";

	*/

	for(double y = 0; y < height; y++){
		for(double x = 0; x < width; x++){
			size_t index = (x + y*width)*3;
			myBuffer[index] = evaluateExpression(redParsed,x,y);	//R
			myBuffer[index+1] = evaluateExpression(greenParsed,x,y);//G
			myBuffer[index+2] = evaluateExpression(blueParsed,x,y);	//B
			//std::cout << myBuffer[index] << " " << myBuffer[index+1] << " " << myBuffer[index+2];
		}
		//std::cout << "" << std::endl;
	}


	CImg<double> img(myBuffer,height,width,1,3,false);
	img.display();
}

double Martist::evaluateExpression(Exp& exp, double xpos, double ypos){

	if(*exp.begin() == "zero")
		return 0.0;

	std::vector<double> numberStack;

	auto c = exp.begin();
	while(c != exp.end()) {

		//Operands
		if(*c == "x" || *c == "y" || *c == "2" || *c == "pi" || *c == "enter"){
			if(*c == "x")
				numberStack.push_back(xpos/width);
			else if(*c == "y")
				numberStack.push_back(ypos/height);
			else if(*c == "2")
				numberStack.push_back(2);
			else if(*c == "pi") //pi
				numberStack.push_back(3.1415);
			else if(*c == "enter"){}//enter
			
		//Operators
		}else{
			if(*c == "sin"){ //sin
				double op = numberStack.back();
				numberStack.pop_back();
				numberStack.push_back(sin(op));
			}
			else if(*c == "cos"){//cos
				double op = numberStack.back();
				numberStack.pop_back();
				numberStack.push_back(cos(op));
			}
			else if(*c == "*"){
				double op = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op * op2);
			}
			else if(*c == "/"){
				double op = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op / op2);
			}				
			else if(*c == "+"){
				double op = numberStack.back();
				numberStack.pop_back();
				double op2 = numberStack.back();
				numberStack.pop_back();

				numberStack.push_back(op + op2);
			}
		}

		++c;

	}
	double result = numberStack.back();
	return result;

}




