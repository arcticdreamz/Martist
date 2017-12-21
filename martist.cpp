#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>    // std::rand
#include <math.h>
#include <iostream>
#include <vector>

#include "CImg.h"
using namespace cimg_library;
#include "martist.hpp"
#include "expression.hpp"




Martist::Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth)
				: height(height), width(width), rdepth(rdepth), gdepth(gdepth), bdepth(bdepth),
				red(rdepth), green(gdepth), blue(bdepth) {

	if((isdigit(rdepth) && isdigit(gdepth) && isdigit(bdepth)))
		throw std::domain_error("Depth must be a digit");
	if(rdepth < 0 || gdepth < 0 || bdepth < 0)
		throw std::domain_error("Depth can't be negative");


	changeBuffer(buffer,width,height);

}

std::ostream& operator<<(std::ostream& out, const Martist& m){
	
	out << "redExpression: " << m.red.getExpression() << std::endl;
	out << "" << std::endl;
	out << "greenExpression: " << m.green.getExpression() << std::endl;
	out << "" << std::endl;
	out << "blueExpression: " << m.blue.getExpression() << std::endl;
	out << "" << std::endl;
			
	return out;
}

std::istream& operator>>(std::istream& in, Martist& m){
	std::string color[3] = {"red: ","green: ","blue: "};

	try{
		for(int i = 0; i < 3; i++){
			std::cout << color[i];
			std::string input;
			in >> input;
			std::istringstream inp(input);
			switch(i){
				case 0 :m.red = Expression(inp);
						break;
				case 1 :m.green = Expression(inp);
						break;
				case 2 :m.blue = Expression(inp);
						break;
  			}
		}
	}catch(const std::domain_error& e){
		std::cout << "Caught error: " << e.what() << std::endl;
	}

	return in;
}






void Martist::redDepth(int depth){
	red = Expression(depth);
	rdepth = depth;
}
int Martist::redDepth() const{
	return rdepth;
}
void Martist::greenDepth(int depth){
	green = Expression(depth);
	gdepth = depth;
}
int Martist::greenDepth() const{
	return gdepth;
}
void Martist::blueDepth(int depth){
	blue = Expression(depth);
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
		for(double y = 0; y < height; y++){
			for(double x = 0; x < width; x++){
				size_t index = (x + y*width)*3;
				double x_pos = (2*x)/(width-1) - 1;
				double y_pos = (2*x)/(height-1) - 1;

				if(*red.getParsed().begin() == "zero")
					myBuffer[index] = 0.0;
				else
					myBuffer[index] = red.evaluateExpression(x_pos,y_pos);	//R

				if(*green.getParsed().begin() == "zero")
					myBuffer[index+1] = 0.0;
				else
					myBuffer[index+1] = green.evaluateExpression(x_pos,y_pos); //G

				if(*blue.getParsed().begin() == "zero")
					myBuffer[index+2] = 0.0;
				else
					myBuffer[index+2] = blue.evaluateExpression(x_pos,y_pos);	//B

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





