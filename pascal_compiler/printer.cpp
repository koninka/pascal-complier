#include <iostream>
#include <sstream>
#include <cstdio>
#include "printer.h"
#include "token.h"

const int TOKEN_TEXT_LEN = 32;
const int TOKEN_TYPE_LEN = 22;
const int TOKEN_VALUE_LEN = 32;
const int TOKEN_LINE_LEN = 7;

void Printer::printCell(string str, int len, int n = 2)
{
   cout << " " << str;
   int cnt = len - str.length() - n;
   string tmp(cnt >= 0 ? cnt : 0, ' ');
   cout << tmp << _cellSeparator;
}

void Printer::printLine(string type, string line, string text, string val)
{
   cout << _cellSeparator;
   printCell(type, TOKEN_TYPE_LEN);
   printCell(line, TOKEN_LINE_LEN);
   printCell(text, TOKEN_TEXT_LEN);
   size_t lpos = 0, rpos;
   while ((rpos = val.find('\n', lpos)) != string::npos) {
      printCell(val.substr(lpos, rpos - 1), TOKEN_VALUE_LEN, 1);
      cout << endl << '|';
      lpos = rpos + 1;
      printCell("", TOKEN_TYPE_LEN);
      printCell("", TOKEN_LINE_LEN);
      printCell("", TOKEN_TEXT_LEN);
   }
   rpos = rpos != string::npos ? rpos : val.length();
   printCell(val.substr(lpos, rpos), TOKEN_VALUE_LEN, 1);
   cout << endl;
}

void Printer::printTestToFile(Scanner& scanner, bool withTable)
{
   string tmp = scanner.fname.substr(0, scanner.fname.find('.') + 1) + "comp";
   freopen(tmp.c_str(), "w", stdout);
   printLexicalTable(scanner, withTable);
}

void Printer::printLexicalTable(Scanner& scanner, bool withTable)
{
	_cellSeparator = withTable ? '|' : ' ';
	int t_len = withTable ? TOKEN_TEXT_LEN + TOKEN_TYPE_LEN + TOKEN_VALUE_LEN + TOKEN_LINE_LEN : 0;
   string tframe(t_len, '-');
	if (withTable) {
		cout << "Table for " << scanner.fname << endl << endl;
		tframe = '*' + tframe + '*';
		cout << tframe << endl;
	}
   printLine("Type", "Line", "Text", "Value");
   cout << tframe << endl;
   TokenPtr token;
   while (scanner.Next()) {
      token = scanner.Get();
      string type = token->getName(),
             line = to_string(token->line),
             text = token->text,
				 value = token->getValue();
      printLine(type, line, text, value);
      cout << tframe << endl;
   }
}

void Printer::printDeclarationTable(Parser& parser, bool toFile)
{
	if (toFile) {
		string tmp = parser.scanner.fname.substr(0, parser.scanner.fname.find('.') + 1) + "comp";
		freopen(tmp.c_str(), "w", stdout);
	}
	parser.isDeclarationParse = true;
	parser.ParseProgram();
	parser.PrintSymTable();
}

void Printer::printAsmCode(Parser& parser)
{
   string tmp = parser.scanner.fname.substr(0, parser.scanner.fname.find('.') + 1) + "asm";
   freopen(tmp.c_str(), "w", stdout);
   parser.isDeclarationParse = false;
   parser.ParseProgram();
   parser.Generate();
}

void Printer::printProgramParseTree(Parser& parser)
{
	string tmp = parser.scanner.fname.substr(0, parser.scanner.fname.find('.') + 1) + "comp";
	freopen(tmp.c_str(), "w", stdout);
	parser.isDeclarationParse = false;
	parser.ParseProgram();
	parser.PrintBlock();
}