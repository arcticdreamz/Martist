#ifndef _PARSER_H
#define _PARSER_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>



class Lexer {	
	friend class Parser;
	public:
	enum token {X, Y, SIN, COS, PI, OPEN_PAR, CLOSE_PAR, TIMES, AVG, COMMA};
	explicit Lexer(std::istream& in);
	/* Method returning a token and updating a counter
	*	ARGUMENTS :
	* -reference to a string that will contain the whole infix expression
	*/
	token next(std::string& expression);
	token peek();
	std::streamoff count() const;
	void reset();


	private:
	std::istream& in;
	std::streamoff counter;


	/* Method returning a token corresponding to a given string
	*	ARGUMENTS :
	*	- one string, usually passed by extractString()
	*/
	token identifyToken(const std::string s);

	/* Method returning a 1 to 3 letter string read from an input stream
	*	-No arguments
	*/
	std::string extractString();
};



typedef std::vector<std::string> Exp;


class Parser {
    public:
	explicit Parser(std::istream& in);
	bool parse(Exp& exp,std::string& expression);

	private:
    Lexer lexer;
    // Stocks locations of open parentheses
	std::vector<std::streamoff> openParLocations;

	//Vector that will contain the sequence of tokens to be converted to RPN
	std::vector<Lexer::token> tokenVector;

 	const std::string tokenToText[10] = {"x", "y", "sin", "cos", "pi", "(", ")", "*", "AVG", ","};

	/* Method checking the syntax of a mathematical expression and returning true
	* if the syntax is correct and false if not
	* 
	* ARGUMENTS 
	*-reference to a string that will contain the whole infix expression
	*/
 	bool checkSyntax(std::string& expression);

	/* 4 methods checking the syntax of a mathemaical expression, namely
	*  an average, a product, a sine/cosine and a simple X or Y
	*  Returns true if the syntax is correct, false if not
	* 
	* ARGUMENTS 
	* -reference to a string that will contain the whole infix expression
	*/
 	bool checkAverage(std::string& expression);
 	bool checkProduct(std::string& expression);
 	bool checkSinCos(std::string& expression);
 	bool checkXY(std::string& expression);

	/* Method converting an infix expression given in the form of a 
	* vector of token to a postfix expression
	* 
	* ARGUMENTS :
	* -Reference to a container that will contain the converted expression
	* -Reference to the sequence of tokens to be converted
	*/
 	bool infixToRPN(Exp& exp,std::vector<Lexer::token>& tokenVector);


	/* Method checking the precedence of two operators
	* 
	* ARGUMENTS :
	* -an operator in the form of a token
	* -an operator in the form of a string
	*/
	bool checkPrecedence(const Lexer::token tok, const std::string s);
};

#endif
