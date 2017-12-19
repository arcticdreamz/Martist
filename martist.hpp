
#ifndef _MARTIST_H
#define _MARTIST_H
#include <string>
#include "parser.hpp"
#include <iostream>



class Martist {	
friend std::istream& operator>>(std::istream&, Martist&);
friend std::ostream& operator<<(std::ostream&, const Martist&);

public:
	explicit Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth);

	void redDepth(int depth);
	int redDepth() const;
	void greenDepth(int depth);
	int greenDepth() const;
	void blueDepth(int depth);
	int blueDepth() const;	
	void seed(int seed);
	void changeBuffer(unsigned char* buffer, size_t width, size_t height);
	void paint();
	
private:
	unsigned char* myBuffer;
	size_t height;
	size_t width;
	int rdepth,gdepth,bdepth;

	std::string redExpression, greenExpression, blueExpression;

	Exp redParsed, greenParsed, blueParsed;

	std::string getExpression(int depth);
	unsigned char evaluateExpression(Exp& exp,double xpos, double ypos);
	void randomInitialisation();



};

#endif
