#pragma once

#include <string>
#include "symbols.h"
#include "token.h"

using namespace std;

enum errorType {
	errorSyntax,
   errorStringExceedsLine,
   errorIllegalCharConstant,
   errorIllegalCharacter,
   errorRecordNumber
};

enum operatorErrType {
	optConstantString,
	optAnd,
	optOr,
	optXor
};

class SimpleException {
	int _line;
   string _message;
	string fname;
public:
   SimpleException(string&, int, const char*);
   string getMessage() const;
};

class CompilerException {
   char _ch;
   errorType _errType;
   int _line;
public:
   string fname;
   CompilerException(string&, int, errorType);
   CompilerException(string&, int, errorType, char);
   string getMessage() const;
};

class SyntaxException {
	int tag;
	int _line;
	string found;
public:
	string fname;
	SyntaxException(string&, string&, int, int);
	string getMessage() const;
};

class DuplicateException {
	int _line;
	string found;
public:
	string fname;
	DuplicateException(string&, string&, int);
	string getMessage() const;
};

class OperatorException {
	int _line;
	string op;
	operatorErrType type;
public:
	string fname;
	OperatorException(string&, string, int, operatorErrType);
	string getMessage() const;
};


class IdentifierNotFoundException {
	int _line;
	string id;
public:
	string fname;
	IdentifierNotFoundException(string&, string, int);
	string getMessage() const;
};

class IllegalExprException {
	int _line;
public:
	string fname;
	IllegalExprException(string&, int);
	string getMessage() const;
};

class IncompatibleTypesException {
	SymbolType type;
	int _line;
public:
	string fname;
	IncompatibleTypesException(string&, int, SymbolType);
	string getMessage();
};

class IncompatibleTypeArgException {
	SymbolType type;
	int _line, num;
	bool isVar;
public:
	string fname;
	IncompatibleTypeArgException(string&, int, int, SymbolType, bool = false);
	string getMessage();
};

class TypeDefinitionException {
	int _line;
public:
	string fname;
	TypeDefinitionException(string&, int);
	string getMessage() const;
};

class WrongParametersException {
	int _line;
	string subroutineName;
public:
	string fname;
	WrongParametersException(string&, int, string&);
	string getMessage() const;
};

class JumpNotAllowedException {
	int _line;
	int tag;
public:
	string fname;
	JumpNotAllowedException(string&, int, int);
	string getMessage() const;
};

class IllegalTypeConversionException {
   int _line;
public:
   string fname;
   IllegalTypeConversionException(string&, int);
   string getMessage() const;
};