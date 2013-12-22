#pragma once

#include <iostream>
#include "scanner.h"
#include "parser.h"

class Printer {
   void printCell(string, int, int);
   void printLine(string, string, string, string);
   template<class T>
   void printToken(TokenPtr token);
	char _cellSeparator;
public:
   void printLexicalTable(Scanner&, bool = true);
   void printTestToFile(Scanner&, bool = true);
	void printDeclarationTable(Parser&, bool = false);
   void printAsmCode(Parser&);
	void printProgramParseTree(Parser&);
};
