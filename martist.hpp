
#ifndef _MARTIST_H
#define _MARTIST_H
#include <string>
#include "parser.hpp"



class Martist {	
public:
	explicit Martist(double* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth);
	~Martist();
	
	std::string getExpression(int depth);

	void redDepth(int depth);
	int redDepth();
	void greenDepth(int depth);
	int greenDepth();
	void blueDepth(int depth);
	int blueDepth();	
	void seed(int seed);
	void changeBuffer(double* buffer, size_t width, size_t height);
	void paint();
	
private:
	double* myBuffer;
	size_t height;
	size_t width;
	int rdepth,gdepth,bdepth;
	//int seed;
	std::string red,green,blue;


	//std::string getExpression(int depth);
	double evaluateExpression(Exp& exp,double xpos, double ypos);

};

#endif
