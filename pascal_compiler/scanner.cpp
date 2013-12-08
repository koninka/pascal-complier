#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>
#include "scanner.h"
#include "error.h"

enum stComment {
   commentStart,
   commentMultiline,
   commentEndMultiLine
};

enum stLiteral {
   literalStartedOrdinal,
   literalStartedString,
   literalEndedString
};

string to_lower(string& str)
{
   string result(str);
   transform(result.begin(), result.end(), result.begin(), ::tolower);
   return result;
}

Scanner::Scanner(const char* _fname):
            _line(1),
            _peek(' '),
            _isEof(false),
            fname(_fname),
            _token(nullptr),
            _fin(ifstream(_fname)),
            _tmp_peeks(vector<char>()),
            _separatorSymbols(string(".,:;()[]")),
            _operatorSymbols(string("+-*/=<>"))
{
   if (_fin.fail()) {
      throw SimpleException(fname, 0, "File not found!");
   }

   reserve<Word>(_keywords, Word(Tag::ARRAY,     "array"));
   reserve<Word>(_keywords, Word(Tag::BEGIN,     "begin"));
	reserve<Word>(_keywords, Word(Tag::BREAK,     "break"));
   reserve<Word>(_keywords, Word(Tag::CASE,      "case"));
	reserve<Word>(_keywords, Word(Tag::CHR,       "chr"));
   reserve<Word>(_keywords, Word(Tag::CONST,     "const"));
	reserve<Word>(_keywords, Word(Tag::CONTINUE,  "continue"));
   reserve<Word>(_keywords, Word(Tag::DO,        "do"));
   reserve<Word>(_keywords, Word(Tag::DOWNTO,    "downto"));
   reserve<Word>(_keywords, Word(Tag::ELSE,      "else"));
   reserve<Word>(_keywords, Word(Tag::END,       "end"));        
   reserve<Word>(_keywords, Word(Tag::EXIT,      "exit"));
   reserve<Word>(_keywords, Word(Tag::FOR,       "for"));    
   reserve<Word>(_keywords, Word(Tag::FALSE,     "false"));
   reserve<Word>(_keywords, Word(Tag::FUNTCTION, "function"));
   reserve<Word>(_keywords, Word(Tag::GOTO,      "goto"));
   reserve<Word>(_keywords, Word(Tag::IF,        "if"));
   reserve<Word>(_keywords, Word(Tag::NIL,       "nil"));
   reserve<Word>(_keywords, Word(Tag::OF,        "of"));
	reserve<Word>(_keywords, Word(Tag::ORD,       "ord"));
   reserve<Word>(_keywords, Word(Tag::PROCEDURE, "procedure"));   
   reserve<Word>(_keywords, Word(Tag::PROGRAM,   "program"));
   reserve<Word>(_keywords, Word(Tag::RECORD,    "record"));
   reserve<Word>(_keywords, Word(Tag::REPEAT,   "repeat"));
   reserve<Word>(_keywords, Word(Tag::STRING,    "string"));
   reserve<Word>(_keywords, Word(Tag::THEN,      "then"));
   reserve<Word>(_keywords, Word(Tag::TO,        "to"));
   reserve<Word>(_keywords, Word(Tag::TRUE,      "true"));
   reserve<Word>(_keywords, Word(Tag::TYPE,      "type"));
   reserve<Word>(_keywords, Word(Tag::UNTIL,     "until"));
   reserve<Word>(_keywords, Word(Tag::VAR,       "var"));
   reserve<Word>(_keywords, Word(Tag::WHILE,     "while"));
	reserve<Word>(_keywords, Word(Tag::WRITE,		 "write"));
   reserve<Word>(_keywords, Word(Tag::WRITELN,   "writeln"));

   reserve<Operator>(_operators, Operator(Tag::ADDITION,                  operatorArithmetic, "+"));
   reserve<Operator>(_operators, Operator(Tag::ADDITION_ASSIGNMENT,       operatorArithmetic, "+="));
   reserve<Operator>(_operators, Operator(Tag::AND,                       operatorBoolean,    "and"));
   reserve<Operator>(_operators, Operator(Tag::ASSIGNMENT,                operatorAssignment, ":="));
   reserve<Operator>(_operators, Operator(Tag::DIV,                       operatorArithmetic, "div"));
   reserve<Operator>(_operators, Operator(Tag::DIVISION,                  operatorArithmetic, "/"));
   reserve<Operator>(_operators, Operator(Tag::DIVISION_ASSIGNMENT,       operatorArithmetic, "/="));
   reserve<Operator>(_operators, Operator(Tag::EQ,                        operatorRelational, "="));
   reserve<Operator>(_operators, Operator(Tag::GE,                        operatorRelational, ">="));
   reserve<Operator>(_operators, Operator(Tag::GT,                        operatorRelational, ">"));
   reserve<Operator>(_operators, Operator(Tag::LE,                        operatorRelational, "<="));
   reserve<Operator>(_operators, Operator(Tag::LT,                        operatorRelational, "<"));
   reserve<Operator>(_operators, Operator(Tag::MOD,                       operatorArithmetic, "mod"));
   reserve<Operator>(_operators, Operator(Tag::MULTIPLICATION,            operatorArithmetic, "*"));
   reserve<Operator>(_operators, Operator(Tag::MULTIPLICATION_ASSIGNMENT, operatorArithmetic, "*="));
   reserve<Operator>(_operators, Operator(Tag::NE,                        operatorRelational, "<>"));
   reserve<Operator>(_operators, Operator(Tag::NEGATION,                  operatorBoolean,    "not"));
   reserve<Operator>(_operators, Operator(Tag::OR,                        operatorBoolean,    "or"));
   reserve<Operator>(_operators, Operator(Tag::SHL,                       operatorLogical,    "shl"));
   reserve<Operator>(_operators, Operator(Tag::SHR,                       operatorLogical,    "shr"));
   reserve<Operator>(_operators, Operator(Tag::SUBTRACTION,               operatorArithmetic, "-"));
   reserve<Operator>(_operators, Operator(Tag::SUBTRACTION_ASSIGNMENT,    operatorArithmetic, "-="));
   reserve<Operator>(_operators, Operator(Tag::XOR,                       operatorBoolean,    "xor")); 

	reserve<Separator>(_separators, Separator(Tag::DOT,			 "."));
	reserve<Separator>(_separators, Separator(Tag::DOUBLE_DOT,	 ".."));
	reserve<Separator>(_separators, Separator(Tag::COMMA,			 ","));
	reserve<Separator>(_separators, Separator(Tag::COLON,			 ":"));
	reserve<Separator>(_separators, Separator(Tag::SEMICOLON,	 ";"));
	reserve<Separator>(_separators, Separator(Tag::LPARENTHESIS, "("));
	reserve<Separator>(_separators, Separator(Tag::RPARENTHESIS, ")"));
	reserve<Separator>(_separators, Separator(Tag::LBRACKET,		 "["));
	reserve<Separator>(_separators, Separator(Tag::RBRACKET,		 "]"));
}

Scanner::Scanner(const Scanner& scanner):
   _line(1),
   _peek(' '),
   _isEof(false),
   fname(scanner.fname),
   _token(nullptr),
   _tmp_peeks(vector<char>()),
	_keywords(scanner._keywords),
	_fin(ifstream(scanner.fname)),
	_operators(scanner._operators),
	_separators(scanner._separators),
	_separatorSymbols(scanner._separatorSymbols),
	_operatorSymbols(scanner._operatorSymbols) {}

Scanner::~Scanner()
{
   _fin.close();
   for (key_t::iterator i = _keywords.begin(); i != _keywords.end(); i++) {
      i->second.reset();
   }
}

bool Scanner::Next()
{
	if (_token != nullptr && _token->type == ttEndOfFile) {
		return false;
	}
   for(bool isWS = true; isWS; readch()) {
      switch (_peek) {
         case ' ': case '\t': case '\n':
            incLine();
            continue;
         case '{':
            do { 
               readch();
               incLine();
            } while (_peek != '}' && !_isEof);
            break;
         case '(':
            {
               stComment state = commentStart;
               bool isCommentScan = true;
               while (isCommentScan && !_isEof) {
                  readch();
                  switch (state) {
                     case commentStart:
                        if (_peek == '*') {
                           state = commentMultiline;
                        } else {
									setToken(_separators["("], _line);
                           return true;
                        }
                        break;
                     case commentMultiline:
                        if (_peek == '*')
                           state = commentEndMultiLine;
                        else
                           incLine();
                        break;
                     case commentEndMultiLine:
                        if (_peek == ')')
                           isCommentScan = false;
                        else
                           state = commentMultiline;
                        break;
                  }
               }
            }
            break;
         case '/':
            readch();
            if (_peek != '/') {
               isWS = false;
               addCharToBuffer('/');
               addCharToBuffer(_peek);
               break;
            }
            do {
               readch();
            } while (_peek != '\n' && !_isEof);
            addCharToBuffer('\n');
            break;
         default:
            isWS = false;
            addCharToBuffer(_peek);
            break;
      }
   }
   if (isOperationSymbol() || _peek == ':') {
      char c = _peek;
      string cc(1, c);
      key_t::iterator it = _operators.end();
      readch();
      if (isOperationSymbol()) {
         it = _operators.find(string(1, c) + _peek);
         if (it != _operators.end()) {
            clearPeek();
         }
      } else if (c == ':') {
			setToken(_separators[":"], _line);
         return true;
      }
      it = it != _operators.end() ? it : _operators.find(string(1, c));
      setToken(it->second, _line);
      return true;
   }
   if (isBeginsLiteral()) {
      string text, value;
      bool isEndLiteral = false;
      stLiteral state = _peek == '\'' ? literalStartedString : literalStartedOrdinal;
      while (!isEndLiteral) {
         readch();
         switch (state) {
            case literalStartedOrdinal:
               if (!isDecimalDigit()) {
                  throw CompilerException(fname, _line, errorIllegalCharConstant);
               }
               {
                  string buffer;
                  int num = readNumber(buffer);
                  value += static_cast<char>(num);
                  text += '#' + buffer;
                  if (isBeginsLiteral()) {
                     state = _peek == '\'' ? literalStartedString : literalStartedOrdinal;
                  } else {
                     isEndLiteral = true;
                  }
               }
               break;
            case literalStartedString:
               {
                  string tmp_val, tmp_text;
                  while (_peek != '\n' && !_isEof) {
                     if (_peek == '\'') {
                        readch();
                        if (_peek != '\'') {
                           state = literalEndedString;
                           break;
                        }
                        tmp_text += _peek;
                     }
                     tmp_val += _peek;
                     tmp_text += _peek;
                     readch();
                  }
                  if (state != literalEndedString && (_peek == '\n' || _isEof)) {
                     throw CompilerException(fname, _line, errorStringExceedsLine);
                  }
                  value += tmp_val;
                  text += '\'' + tmp_text + '\'';
                  if (_peek == '#') {
                     state = literalStartedOrdinal;
                     break;
                  }
                  isEndLiteral = true;
               }
               break;
         }
      }
      setToken(new CharacterString(_line, text, value));
      return true;
   }
	if (isBeginsNumber()) {
      int value;
      string text;
      char c = _peek;
      bool isDecimal = true;
      switch (_peek) {
         // Hexadecimal format
         case '$':
            value = readHexadecimal(text);
            isDecimal = false;
            break;
         // Octal format
         case '&':
            value = readOctal(text);
            isDecimal = false;
            break;
         // Binary format
         case '%':
            value = readBinary(text);
            isDecimal = false;
            break;
      }
      if (!isDecimal) {
         setToken(new IntegerNumber(_line, value, c + text));
         return true;
      }
      value = readNumber(text);
      if (!(isWhitespace() || isSeparator() || isOperationSymbol())) {
         throw CompilerException(fname, _line, errorRecordNumber);
      }
      if (_peek != '.') {
         setToken(new IntegerNumber(_line, value, text));
         return true;
      }
		readch();
		if (_peek == '.') {
			addCharToBuffer(_peek);
			setToken(new IntegerNumber(_line, value, text));
			return true;
		}
      if (!isDecimalDigit()) {
         throw CompilerException(fname, _line, errorRecordNumber);
      }
      string sfrac;
      int ifrac = readNumber(sfrac);
      double real_num = value + ifrac * pow(10.0, -((double) sfrac.size()));
      text += '.' + sfrac;
      if (_peek == 'e') {
         text += 'e';
         readch();
         if (isDecimalDigit() || _peek == '-') {
            char c = _peek;
            if (c == '-') {
               text += '-';
               readch();
            }
            if (!isDecimalDigit()) {
               throw CompilerException(fname, _line, errorRecordNumber);
               return false;
            }
            value = readNumber(text);
            real_num = real_num * pow(10.0, c != '-' ? value : -value);
         }
      }
      if (!(isWhitespace() || isSeparator() || isOperationSymbol())) {
         throw CompilerException(fname, _line, errorRecordNumber);
         return false;
      }
      setToken(new RealNumber(_line, real_num, text));
      return true;
   }
   if (isLetter()) {
      string buffer;
      do {
         buffer += _peek;
         readch();
      } while (isLetterOrDigit());
      bool isKeyword = false, isOperator = false;
      string tmp = to_lower(buffer);
      key_t::iterator it = _keywords.find(tmp);
      isKeyword = it != _keywords.end();
      if (!isKeyword) {
         it = _operators.find(tmp);
         isOperator = it != _operators.end();
      }
      if (isKeyword || isOperator) {
         setToken(it->second, _line);
      } else {
			setToken(new Word(_line, Tag::IDENTIFICATOR, to_lower(buffer)));
      }
      return true;
   }
   if (isSeparator()) {
		string sep(1, _peek);
		if (_peek == '.') {
			readch();
			if (_peek == '.') {
				sep += _peek;
			} else {
				addCharToBuffer(_peek);
			}
		}
		key_t::iterator it =  _separators.find(sep);
      setToken(it->second, _line);
      clearPeek();
   } else if (!_isEof) {
      throw CompilerException(fname, _line, errorIllegalCharacter);
   } else {
		_token = TokenPtr(new EndOfFile(_line));
	}
	return _token->type != ttEndOfFile;
}

TokenPtr Scanner::Get() const
{
   return _token;
}

int Scanner::readBinary(string& text)
{
   while (true) {
      readch();
      if (!isBinaryDigit()) break;
      text += _peek;
   }
   if (!(isWhitespace() || isSeparator() || isOperationSymbol())
         || (isDecimalDigit() && (_peek == '0' || _peek == '1') || text.length() == 0)) {
      throw CompilerException(fname, _line, errorRecordNumber);
   }
   int value = 0, pow = 1;
   for (int i = text.length() - 1; i >= 0; --i, pow <<= 1 ) {
      value += (text[i] - '0') * pow;
   }
   return value;
}

int Scanner::readHexadecimal(string& text)
{
   while (true) {
      readch();
      if (!isHexadecimalDigit()) break;
      text += _peek;
   }
   if (!(isWhitespace() || isSeparator() || isOperationSymbol()) || text.length() == 0) {
      // $ffG $24G $23' $23
      throw CompilerException(fname, _line, errorRecordNumber);
   }
   stringstream stream;
   stream << text;
   int value;
   stream >> hex >> value;
   return value;
}

int Scanner::readNumber(string& text)
{
   int v = 0;
   do {
      v = v * 10 + (_peek - '0');
      text += _peek;
      readch();
   } while (isDecimalDigit());
   return v;
}

int Scanner::readOctal(string& text)
{
   while (true) {
      readch();
      if (!isOctalDigit()) break;
      text += _peek;
   }
   if (!(isWhitespace() || isSeparator() || isOperationSymbol()) || _peek == '8' || _peek == '9' || text.length() == 0) {
      // &03G $23' $239 
      throw CompilerException(fname, _line, errorRecordNumber);
   }
   stringstream stream;
   stream << text;
   int value;
   stream >> oct >> value;
   return value;
}

void Scanner::setToken(Token* tok)
{
   _token = TokenPtr(tok);
}

void Scanner::setToken(TokenPtr tok, int l)
{
   _token = TokenPtr(tok);
   _token->line = l;
}

void Scanner::clearPeek()
{
   _peek = ' ';
   _isEof = false;
}

void Scanner::addCharsToBuffer(const string& tmp_buffer)
{
   vector<char> tmp(_tmp_peeks);
   _tmp_peeks.clear();
   for (int i = tmp_buffer.size() - 1; i >= 0; i--) {
      _tmp_peeks.push_back(tmp_buffer[i]);
   }
   _tmp_peeks.insert(_tmp_peeks.end(), tmp.begin(), tmp.end());
   _isEof = _tmp_peeks.size() == 0 && _fin.eof();
}

void Scanner::addCharToBuffer(const char c)
{
   if (c == EOF) return;
   addCharsToBuffer(string(1, c));
}

void Scanner::incLine()
{
   _line = _peek == '\n' ? _line + 1 : _line;
}

void Scanner::readch()
{
   if (_tmp_peeks.size() != 0) {
      _peek = _tmp_peeks.back();
      _tmp_peeks.pop_back();
   } else {
      _peek = _fin.get();
      if (_fin.eof()) {
         _peek = EOF;
         _isEof = true;
         return;
      }
   }
}

bool Scanner::isBinaryDigit() const
{
   return _peek == '0' || _peek == '1';
}

bool Scanner::isDecimalDigit() const
{
   return  '0' <=_peek && _peek <= '9';
}

bool Scanner::isHexadecimalDigit() const
{
   string s("abcdef");
   return isDecimalDigit() || s.find(tolower(_peek)) != string::npos;
}

bool Scanner::isOctalDigit() const
{
   return  '0' <=_peek && _peek <= '7';
}

bool Scanner::isBeginsNumber() const
{
	return isDecimalDigit() || _peek == '$' || _peek == '&' || _peek == '%';
}

bool Scanner::isSeparator() const
{
   return _separatorSymbols.find(_peek) != string::npos;
}

bool Scanner::isOperationSymbol() const
{
   return _operatorSymbols.find(_peek) != string::npos;
}

bool Scanner::isLetter() const
{
   char c = tolower(_peek);
   return c != EOF && ((c >='a' && c <= 'z') || c == '_');
}

bool Scanner::isWhitespace() const
{
   return _peek == ' ' || _peek == '\t' || _peek == '\n' || _peek == EOF;
}

bool Scanner::isLetterOrDigit() const
{
   return isLetter() || isDecimalDigit();
}

bool Scanner::isBeginsLiteral() const
{
   return _peek == '\'' || _peek == '#';
}

template<class T>
void Scanner::reserve(key_t& list, const T t)
{
   T* ptr = new T(t);
   list.insert(make_pair(ptr->text, TokenPtr(ptr)));
}