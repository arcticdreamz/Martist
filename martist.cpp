#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>    // std::rand
#include <math.h>
#include <iostream>
#include <vector>

#include "CImg.h"
using namespace cimg_library;
#include "martist.hpp"
#include "parser.hpp"




Martist::Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth)
				:height(height),width(width),rdepth(rdepth),gdepth(gdepth),bdepth(bdepth){
	if(rdepth < 0 || gdepth < 0 || bdepth < 0)
		throw std::domain_error("Depth can't be negative");

	changeBuffer(buffer,width,height);
	randomInitialisation();

	

}

std::ostream& operator<<(std::ostream& out, const Martist& m){
	
	out << "redExpression: " << m.redExpression << std::endl;
	out << "" << std::endl;
	out << "greenExpression: " << m.greenExpression << std::endl;
	out << "" << std::endl;
	out << "blueExpression: " << m.blueExpression << std::endl;
	out << "" << std::endl;
			
	return out;
}

std::istream& operator>>(std::istream& in, Martist& m){
	std::string color[3] = {"red: ","green: ","blue: "};
	Parser parser(in);
	if(in){
		for(int i = 0; i < 3; i++){
			std::cout << color[i];

			switch(i){

			case 0 :
					m.redParsed.clear();
					m.redExpression.clear();
					parser.parse(m.redParsed,m.redExpression);
					if(m.redParsed.empty())
						m.redParsed.push_back("zero");


			case 1 :
					m.greenParsed.clear();
					m.greenExpression.clear();
					parser.parse(m.greenParsed,m.greenExpression);
					if(m.greenParsed.empty())
						m.greenParsed.push_back("zero");

			case 2 :
					m.blueParsed.clear();
					m.blueExpression.clear();
					parser.parse(m.blueParsed,m.blueExpression);
					if(m.blueParsed.empty())
						m.blueParsed.push_back("zero");      					
			}
		}
	}
	return in;
}


std::string Martist::getExpression(int depth){

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
			exp.append(getExpression(depth-1));
			exp.append(")");
		}
		//avg and product have expr1 and expr2
		else if(exp == "avg") {
			exp.append("(");
			exp.append(getExpression(depth - 1));
			exp.append(",");
			exp.append(getExpression(depth - 1));
			exp.append(")");
		}
		else if(exp =="(" ){

			exp.append(getExpression(depth - 1));
			exp.append("*");
			exp.append(getExpression(depth - 1));
			exp.append(")");
		}
	}
	//depth == 1
	else{
		exp = (std::rand()%2 == 0) ? "x" : "y";
	}
	return exp;
}

void Martist::randomInitialisation(){
	redExpression = getExpression(rdepth);
	greenExpression = getExpression(gdepth);
	blueExpression = getExpression(bdepth);

	std::cout << "redExpression: " << redExpression << std::endl;
	std::cout << "" << std::endl;
	std::cout << "greenExpression: " << greenExpression << std::endl;	
	std::cout << "" << std::endl;
	std::cout << "blueExpression: " << blueExpression << std::endl;
	std::cout << "" << std::endl;


  	std::istringstream redIN(redExpression);
  	std::istringstream greenIN(greenExpression);
  	std::istringstream blueIN(blueExpression);

	Parser redParser(redIN);
	Parser greenParser(greenIN);
	Parser blueParser(blueIN);



	if(rdepth == 0) 
		redParsed.push_back("zero");
	else
		redParser.parse(redParsed,redExpression);
	
	if(gdepth == 0) 
		greenParsed.push_back("zero");
	else
		greenParser.parse(greenParsed,greenExpression);

	if(bdepth == 0) 
		blueParsed.push_back("zero");
	else
		blueParser.parse(blueParsed,blueExpression);


	std::cout << "redParsed: ";
	for(auto it = redParsed.begin(); it < redParsed.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "" << std::endl;

	std::cout << "greenParsed: ";
	for(auto it = greenParsed.begin(); it < greenParsed.end(); it++) {
		std::cout << *it << " " ;
	}
	std::cout << "" << std::endl;


	std::cout << "blueParsed: ";
	for(auto it = blueParsed.begin(); it < blueParsed.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "" << std::endl;
}

void Martist::redDepth(int depth){
	rdepth = depth;
}
int Martist::redDepth() const{
	return rdepth;
}
void Martist::greenDepth(int depth){
	gdepth = depth;
}
int Martist::greenDepth() const{
	return gdepth;
}
void Martist::blueDepth(int depth){
	bdepth = depth;
}
int Martist::blueDepth() const{
	return bdepth;
}
void Martist::seed(int seed){
	srand(seed);
}

void Martist::changeBuffer(unsigned char* buffer, size_t width, size_t height){
		width = width;
		height = height;
		if(buffer == nullptr)
			throw std::domain_error("Buffer not initialised");
		if(height <= 0 || width <= 0)
			throw std::domain_error("Height and width must be positive");
		myBuffer = buffer;
}
void Martist::paint(){
/*	redParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";
	greenParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";
	blueParsed = "pi pi pi x * cos * sin x x * + 2 / * cos";

	*/
	try{
		for(size_t y = 0; y < height; y++){
			for(size_t x = 0; x < width; x++){
				size_t index = (x + y*width)*3;
				if(*redParsed.begin() == "zero")
					myBuffer[index] = 0.0;
				else
					myBuffer[index] = evaluateExpression(redParsed,x,y);	//R

				if(*greenParsed.begin() == "zero")
					myBuffer[index+1] = 0.0;
				else
					myBuffer[index+1] = evaluateExpression(greenParsed,x,y); //G

				if(*blueParsed.begin() == "zero")
					myBuffer[index+2] = 0.0;
				else
					myBuffer[index+2] = evaluateExpression(blueParsed,x,y);	//B

			}
		}
	}catch(std::exception& e){
		std::cout << "Caught exception \"" << e.what() << "\"\n";
	}


/*
	for(size_t y = 0; y < height; y++){
		for(size_t x = 0; x < width; x++){
			size_t index = (x + y*width)*3;
			std::cout << myBuffer[index] << " " << myBuffer[index+1] << " " << myBuffer[index+2]  << " | ";
		}
		std::cout << "" << std::endl;
	}
*/

	//CImg stores the pixels in a "planar" form(R1R2R3...G1G2G3)
	//, not interleaved (R1G1B1 R2G2B2)
	//We thus need to invert the coords and do permute
	CImg<unsigned char> img(myBuffer,3,width,height);
	img.permute_axes("yzcx");
	img.display();
}

unsigned char Martist::evaluateExpression(Exp& exp, double xpos, double ypos){

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
	int result = numberStack.back();
	return (unsigned char)255*(0.5 + 0.5 * result);

}




