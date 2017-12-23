#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>    // std::rand
#include <algorithm>    // std::all_of
#include <iostream>
#include <vector>

#include "martist.hpp"
#include "expression.hpp"




/***********************************************************************
*Martist constructor
* ***********************************************************************/
Martist::Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth)
				: myBuffer(buffer), m_height(height), m_width(width), rdepth(rdepth), gdepth(gdepth), bdepth(bdepth) {

	if(height <= 0 || width <= 0)
		throw std::domain_error("Height and width must be positive");

	if(rdepth < 0 || gdepth < 0 || bdepth < 0)
		throw std::domain_error("Depth can't be negative");

}


/***********************************************************************
* Input and output operators
* ***********************************************************************/

std::ostream& operator<<(std::ostream& out, const Martist& m){
	out << "red: " << m.red.getExpression() << std::endl;
	out << "green: " << m.green.getExpression() << std::endl;
	out << "blue: " << m.blue.getExpression() << std::endl;
	
	return out;
}

std::istream& operator>>(std::istream& in, Martist& m){
	std::string color[3] = {"red: ","green: ","blue: "};

	if(in){
		for(int i = 0; i < 3; i++){

			std::cout << color[i];

			char sequence[1024];
			in.getline(sequence,1024);
			std::string input(sequence);

			std::istringstream stringstream(input);
			switch(i){
				case 0 :if(std::all_of(input.begin(),input.end(),isspace) || input == "\n"){
							m.red = Expression(0);
						}
						else{
							m.red = Expression(stringstream);
							m.rdepth = m.red.calculateDepth();
						}
						break;
				case 1 :if(std::all_of(input.begin(),input.end(),isspace) || input == "\n"){
							m.green = Expression(0);
						}
						else{
							m.green = Expression(stringstream);
							m.gdepth = m.green.calculateDepth();
						}
						break;
				case 2 : if(std::all_of(input.begin(),input.end(),isspace) || input == "\n"){
							m.blue = Expression(0);
						}
						else{
							m.blue = Expression(stringstream);
							m.bdepth = m.blue.calculateDepth();
						}
						break;
  			}
		}

		m.updateBuffer();	

	}
	return in;
}




/***********************************************************************
* Public classes
* ***********************************************************************/

void Martist::redDepth(int depth){

	if(depth < 0 )
		throw std::domain_error("Depth can't be negative");
	red = Expression(depth);
	rdepth = depth;
}
int Martist::redDepth() const{
	return red.calculateDepth();
}
void Martist::greenDepth(int depth){

	if(depth < 0 )
		throw std::domain_error("Depth can't be negative");	
	green = Expression(depth);
	gdepth = depth;
}
int Martist::greenDepth() const{
	return green.calculateDepth();
}
void Martist::blueDepth(int depth){

	if(depth < 0 )
		throw std::domain_error("Depth can't be negative");	
	blue = Expression(depth);
	bdepth = depth;
}
int Martist::blueDepth() const{
	return blue.calculateDepth();
}
void Martist::seed(int seed){
	srand(seed);
}

void Martist::changeBuffer(unsigned char* buffer, size_t width, size_t height){
		m_width = width;
		m_height = height;
		if(buffer == nullptr)
			throw std::domain_error("Buffer not initialised");
		if(height <= 0 || width <= 0)
			throw std::domain_error("Height and width must be positive");
		myBuffer = buffer;
}
void Martist::paint(){
	red = Expression(rdepth);
	green = Expression(gdepth);
	blue = Expression(bdepth);

	updateBuffer();
}


/***********************************************************************
* Private classes
* ***********************************************************************/
void Martist::updateBuffer(){
	if(myBuffer == nullptr)
		throw std::domain_error("Buffer not initialised");

	for(double k = 0; k < m_height; k++){
		for(double m = 0; m < m_width; m++){
			size_t index = (m + k*m_width)*3;
			double x_pos = (2*m)/(m_width-1) - 1;
			double y_pos = (2*k)/(m_height-1) - 1;

				myBuffer[index] = (unsigned char) 255/2*(1 + red.evaluateExpression(x_pos,y_pos));	//R
				myBuffer[index+1] = (unsigned char) 255/2*(1 + green.evaluateExpression(x_pos,y_pos)); //G
				myBuffer[index+2] = (unsigned char) 255/2*(1 + blue.evaluateExpression(x_pos,y_pos));	//B

		}
	}
}



