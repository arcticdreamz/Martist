#include <stdexcept> //domain_error
#include <string>
#include <cstdlib>     // std::rand
#include <iostream>

#include "martist.hpp"

int main(){
	size_t height = 800;
	size_t width = 800;
	int reddepth = 1;
	int greendepth = 1;
	int bluedepth = 1;
	//int seed;
/*	std::cout <<"reddepth:";
	std::cin >> reddepth;

	std::cout <<"greendepth:";
	std::cin >> greendepth;

	std::cout <<"bluedepth:";
	std::cin >> bluedepth;
	std::cout << "" << std::endl;

*/

	unsigned char* buffer = (unsigned char*) malloc(3*width*height*sizeof(unsigned char));

	Martist martist(buffer,height,width,reddepth,greendepth,bluedepth);

/*	std::cout <<"reddepth:";
	std::cout << martist.redDepth() <<std::endl;

	std::cout <<"greendepth:";
	std::cout << martist.greenDepth() <<std::endl;

	std::cout <<"bluedepth:";
	std::cout << martist.blueDepth() <<std::endl;

	std::cout << martist;

	martist.redDepth(1);
	martist.greenDepth(1);
	martist.blueDepth(1);

	std::cout <<"reddepth:";
	std::cout << martist.redDepth() <<std::endl;

	std::cout <<"greendepth:";
	std::cout << martist.greenDepth() <<std::endl;

	std::cout <<"bluedepth:";
	std::cout << martist.blueDepth() <<std::endl;


	std::cout << martist;
*/
	std::cin.clear();
	std::cin >> martist;

	std::cout << martist;

	try{
		martist.paint(); 
	}catch(std::domain_error& e){
		std::cout << "Caught error (paint): " << e.what() << std::endl;
	}


	
	free(buffer);
	return 0;
}






/*	int depth;
	std::cout << "" << std::endl;
	std::cout << "Insert depth of the expression: ";
	std::cin >> depth;
	std::string myString = getExpression(depth);
	std::cout << myString << std::endl;
*/