
#ifndef _MARTIST_H
#define _MARTIST_H
#include <string>




class Martist {	
public:
	explicit Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth);
	//~Martist();

	void redDepth(int depth);
	int redDepth();
	void greenDepth(int depth);
	int greenDepth();
	void blueDepth(int depth);
	int blueDepth();	
	void seed(int seed);
	void changeBuffer(unsigned char* buffer, size_t width, size_t height);
	void paint();
	
private:
	std::istream& in;
	unsigned char* buffer;
	size_t height;
	size_t width;
	int rdepth,gdepth,bdepth;
	int seed;
	std::string red,green,blue;


	std::string getExpression(int depth);
	double evaluateExpression(std::string exp,size_t position);

}

#endif
