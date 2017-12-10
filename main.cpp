#include "martist.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <iostream>


int main(){
	double* buffer = nullptr;
	size_t height = 20;
	size_t width = 20;
	Martist martist(buffer,height,width,4,4,4);
	martist.paint();
	


	return 0;
}






/*	int depth;
	std::cout << "" << std::endl;
	std::cout << "Insert depth of the expression: ";
	std::cin >> depth;
	std::string myString = getExpression(depth);
	std::cout << myString << std::endl;
*/