#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <iostream>

#include "martist.hpp"
#include "CImg.h"
using namespace cimg_library;

int main(){
	size_t height =400;
	size_t width = 400;
	int reddepth = 0;
	int greendepth = 0;
	int bluedepth = 0;

	unsigned char* buffer = (unsigned char*) malloc(3*width*height*sizeof(unsigned char));

	Martist martist(buffer,height,width,reddepth,greendepth,bluedepth);


	// INPUT EXPRESSIONS
	std::cin.clear();
	std::cin >> martist;

	// OUTPUT EXPRESSIONS
	std::cout << martist;

	// OUTPUT DEPTH
	std::cout <<"reddepth:";
	std::cout << martist.redDepth() <<std::endl;

	std::cout <<"greendepth:";
	std::cout << martist.greenDepth() <<std::endl;

	std::cout <<"bluedepth:";
	std::cout << martist.blueDepth() <<std::endl;

	CImg<unsigned char> boardA(buffer,3,width,height);
    boardA.permute_axes("yzcx");
    boardA.display("Martist");


	
	free(buffer);
	return 0;
}





