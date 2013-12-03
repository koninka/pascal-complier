#include "token.h"

Token::Token(int ATag, string& AText, tokenType AType): tag(ATag), text(AText), type(AType), line(-1) {}

Token::Token(int ALine, int ATag, string& AText, tokenType AType): line(ALine), tag(ATag), text(AText), type(AType) {}

string Token::getValue()
{
	return text;
}

string Token::getName() const
{
	return token_name;
}

bool Token::isEndOfFile() const
{
	return false;
}

bool Token::operator ==(const int _tag)
{
	return tag == _tag;
}

bool Token::operator ==(const tokenType _type)
{
	return type == _type;
}

bool Token::operator !=(const int _tag)
{
	return tag != _tag;
}

bool Token::operator !=(const tokenType _type)
{
	return type != _type;
}

Separator::Separator(int ATag, string AText): Token(ATag, AText, ttSeparator)
{
	token_name = "Separator";
}

Operator::Operator(int ATag, OperatorType AType, string AText): Token(ATag, AText, ttOperator), opType(AType)
{
	token_name = "Operator";
}

IntegerNumber::IntegerNumber(int ALine, int AValue, string& AText): Token(ALine, Tag::INTEGER_NUM, AText, ttIntegerNumber), value(AValue)
{
	token_name = "Integer number";
}

string IntegerNumber::getValue()
{
	return to_string<int>(value);
}

RealNumber::RealNumber(int ALine, double AValue, string& AText): Token(ALine, Tag::REAL_NUM, AText, ttRealNumber), value(AValue)
{
	token_name = "Real number";
}

string RealNumber::getValue()
{
	return to_string<double>(value);
}

Word::Word(int ATag, string AText): Token(ATag, AText, ATag == Tag::IDENTIFICATOR ? ttIdentificator : ttKeyWord)
{
	token_name = ATag == Tag::IDENTIFICATOR ? "Identificator" : "Keyword";
}

Word::Word(int ALine, int ATag, string& AText): Token(ALine, ATag, AText, ATag == Tag::IDENTIFICATOR ? ttIdentificator : ttKeyWord)
{
	token_name = ATag == Tag::IDENTIFICATOR ? "Identificator" : "Keyword";
}

CharacterString::CharacterString(int ALine, string& AText, string& AValue): Token(ALine, Tag::LITERAL, AText, ttCharacterString), value(AValue)
{
	token_name = "Character string";
}

string CharacterString::getValue()
{
	return value;
}

EndOfFile::EndOfFile(int ALine): Token(ALine, Tag::ENDOF, string("end of file"), ttEndOfFile) {}

bool EndOfFile::isEndOfFile() const
{
	return true;
}