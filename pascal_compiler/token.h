#pragma once

#include <string>
#include <sstream>

using namespace std;

namespace Tag {

   enum identificators {
		ADDITION,
		ADDITION_ASSIGNMENT,
		AND,
		ARRAY,
		ASSIGNMENT,
		BEGIN,
		BREAK,
		CASE,
		CHR,
		COLON,
		COMMA,
		CONST,
		CONTINUE,
		DOT,
		DIV,
		DIVISION,
		DIVISION_ASSIGNMENT,
		DO,
		DOUBLE_DOT,	
		DOWNTO,
		ELSE,
		END,
		ENDOF,
		EXIT,
		EQ,
		FOR,
		FALSE,
		FUNTCTION,
		GOTO,
		GE,
		GT,
		IDENTIFICATOR,
		IF,
		INTEGER_NUM,
		LBRACKET,
		LE,
		LT,
		LITERAL,
		LPARENTHESIS,
		MOD,
		MULTIPLICATION,
		MULTIPLICATION_ASSIGNMENT,
		NE,
		NEGATION,
		NIL,
		OF,
		OR,
		ORD,
		PROCEDURE,
		PROGRAM,
		RBRACKET,
		REAL_NUM,
		RECORD,
		REPEAT,
		RPARENTHESIS,
		SEMICOLON,
		SEPARATOR,
		SHL,
		SHR,
		STRING,
		SUBTRACTION,
		SUBTRACTION_ASSIGNMENT,
		THEN,
		TO,
		TRUE,
		TYPE,
		UNTIL,
		VAR,
		WHILE,
		XOR 
   };

};

enum OperatorType {
	operatorArithmetic,
	operatorLogical,
	operatorBoolean,
	operatorRelational,
   operatorAssignment
};

enum tokenType {
	ttToken,
	ttSeparator,
	ttOperator,
	ttIntegerNumber,
	ttRealNumber,
	ttKeyWord,
	ttIdentificator,
	ttCharacterString,
	ttEndOfFile
};

struct Token {
	string text;
	int line, tag;
	tokenType type;
	string token_name;
   Token(int, string&, tokenType);
	Token(int, int, string&, tokenType);
   virtual ~Token() {};
	virtual string getValue();
	virtual string getName() const;
	virtual bool isEndOfFile() const;
	bool operator ==(const int);
	bool operator ==(const tokenType);
	bool operator !=(const int);
	bool operator !=(const tokenType);
};

struct Separator: public Token {
   Separator(int, string);
};

struct Operator: public Token {
   OperatorType opType;
   Operator(int, OperatorType, string);
};

struct IntegerNumber: public Token {
   int value;
   IntegerNumber(int, int, string&);
	string getValue() override;
};

struct RealNumber: public Token {
   double value;
   RealNumber(int, double, string&);
	string getValue() override;
};

struct Word: public Token {
   Word(int, string);
   Word(int, int, string&);
};

struct CharacterString: public Token {
	string value;
   CharacterString(int, string&, string&);
	string getValue() override;
};

struct EndOfFile: public Token {
	string value;
	EndOfFile(int);
	bool isEndOfFile() const override;
};

template <class T>
string to_string(T val)
{
   stringstream stream;
   stream << val;
   return stream.str();
}