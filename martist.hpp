#ifndef _MARTIST_H
#define _MARTIST_H
#include <string>
#include <iostream>

#include "expression.hpp"


/***********************************************************************
*Martist class, generates an image from 3 mathematical expressions
************************************************************************/
class Martist {	
/***********************************************************************
* Overload of the input operator >>, takes in the 3 expressions
* one per color (RGB) and updates the depth of the expression in the class
* Also fills the image buffer with the values from these expressions
*
*ARGUMENTS:
* -reference to an istream
* -reference to an instance of a Martist class
************************************************************************/
friend std::istream& operator>>(std::istream&, Martist&);
/***********************************************************************
* Overload of the output operator <<, outputs the 3 expressions
* one per color (RGB)
*
*ARGUMENTS:
*-reference to an ostream
*-const reference to an instance of a Martist class
************************************************************************/
friend std::ostream& operator<<(std::ostream&, const Martist&);

public:
	/***********************************************************************
	*Constructor
	*
	*ARGUMENTS:
	*- buffer that will contai the pixel values, must be correct size
	*- height and width of the image
	*- maximal depth of the mathematical expressions, one for each color
	************************************************************************/
	explicit Martist(unsigned char* buffer, size_t height, size_t width, int rdepth, int gdepth,int bdepth);

	void redDepth(int depth);
	/**********************************************************************	
	* Returns the maximal depth of the red epxression
	*
	* NO ARGUMENTS
	***********************************************************************/
	int redDepth() const;
	void greenDepth(int depth);
	/**********************************************************************	
	* Returns the maximal depth of the green epxression
	*
	* NO ARGUMENTS
	***********************************************************************/
	int greenDepth() const;
	void blueDepth(int depth);
	/**********************************************************************	
	* Returns the maximal depth of the blue epxression
	*
	* NO ARGUMENTS
	***********************************************************************/
	int blueDepth() const;	
	/**********************************************************************	
	* Seeds the randomness
	*
	* ARGUMENTS:
	* - seed to seed the randomness
	***********************************************************************/
	void seed(int seed);
	/**********************************************************************	
	* Method changing the image buffer used by the Martist class
	* 
	* ARGUMENTS:
	* - pointer to the buffer (size is supposed to be correct)
	* - width of the image
	* - height of the image
	***********************************************************************/
	void changeBuffer(unsigned char* buffer, size_t width, size_t height);
	/**********************************************************************	
	* Method generating 3 random expressions from the 3 maximal depths already
	* in the class. Also fills the image buffer
	* 
	* NO ARGUMENTS
	***********************************************************************/
	void paint();
	
private:

	unsigned char* myBuffer;
	size_t m_height;
	size_t m_width;
	int rdepth,gdepth,bdepth;
	/***********************************************************************
	* Method filling up the image buffer with RGB values for each pixel
	* The expressions used are available as a private variable of the class
	*
	* NO ARGUMENTS
	* ***********************************************************************/
	void updateBuffer();
	Expression red;
	Expression green;
	Expression blue;
};

#endif
