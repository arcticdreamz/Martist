#include "martist.hpp"
#include "parser.hpp"
#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <sstream>


int main(){
	double* buffer = nullptr;
	size_t height = 400;
	size_t width = 400;
	int reddepth,greendepth,bluedepth;
	std::cout <<"reddepth:";
	std::cin >> reddepth;

	std::cout <<"greendepth:";
	std::cin >> greendepth;

	std::cout <<"bluedepth:";
	std::cin >> bluedepth;
	std::cout << "" << std::endl;

	Martist martist(buffer,height,width,reddepth,greendepth,bluedepth);

	//std::string myString = martist.getExpression(100);
	//std::cout << myString;

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