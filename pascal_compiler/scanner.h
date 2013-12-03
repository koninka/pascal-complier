#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "error.h"
#include "token.h"

using namespace std;

typedef shared_ptr<Token> TokenPtr;
typedef unordered_map<string, shared_ptr<Token>> key_t;

class Scanner {
   int _line;
   char _peek;
   bool _isEof;
   ifstream _fin;
   TokenPtr _token;
   key_t _keywords, _separators, _operators;
   string _separatorSymbols, _operatorSymbols;
   vector<char> _tmp_peeks;

   int readBinary(string&);
   int readHexadecimal(string&);
   int readNumber(string&);
   int readOctal(string&);
   void setToken(Token*);
   void setToken(TokenPtr, int);
   void clearPeek();
   void addCharsToBuffer(const string&);
   void addCharToBuffer(const char);
   void incLine();
   void readch();
   bool isBinaryDigit() const;
   bool isDecimalDigit() const;
   bool isHexadecimalDigit() const;
   bool isOctalDigit() const;
	bool isBeginsNumber() const;
   bool isSeparator() const;
   bool isOperationSymbol() const;
   bool isLetter() const;
   bool isWhitespace() const;
   bool isLetterOrDigit() const;
   bool isBeginsLiteral() const;
   template<class T> void reserve(key_t&, const T);
public:
   string fname;

   Scanner(const char*);
	Scanner(const Scanner&);
   ~Scanner();
   bool Next();
   TokenPtr Get() const;
};

template<class T>
bool tryCastToken(TokenPtr tokenPtr)
{
   T* t = dynamic_cast<T*>(tokenPtr.get());
   return t != nullptr;
}

template<class T>
T* castToken(TokenPtr tokenPtr)
{
   return dynamic_cast<T*>(tokenPtr.get());
}