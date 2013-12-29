#include <sstream>
#include "Error.h"

string GetMsgPart(SymbolType type)
{
	string result;
	switch (type) {
		case stTypeFloat:
			result = "\"Extended\"";
			break;
		case stTypeInteger:
			result = "\"Integer\"";
			break;
		case stTypeChar:
			result = "\"Char\"";
			break;
		case stTypeArray:
			result = "\"Array\"";
			break;
		case stTypeOpenArray:
			result = "\"Open Array\"";
			break;
		case stTypeRecord:
			result = "\"Record\"";
			break;
		default:
			result = "\"Untyped\"";
			break;
	}
	return result;
}

SimpleException::SimpleException(string& AFname, int ALine, const char* AMsg):
		fname(AFname), _line(ALine), _message(AMsg) {}

string SimpleException::getMessage() const
{
   stringstream msg;
   msg << fname;
	if (_line != 0) {
		msg << "(" << _line << ")";
	}
	msg << " Error: " << _message;
   return msg.str();
}

CompilerException::CompilerException(string& AFname, int ALine, errorType AType): fname(AFname),
         _line(ALine), _errType(AType) {}

CompilerException::CompilerException(string& AFname, int ALine, errorType AType, char ACh): fname(AFname),
         _line(ALine), _errType(AType), _ch(ACh) {}

string CompilerException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") ";
   switch (_errType) {
		case errorSyntax:
			msg << "Fatal: Syntax error";
			break;
      case errorIllegalCharConstant:
         msg << "Error: Illegal char constant";
         break;
      case errorStringExceedsLine:
         msg << "Fatal: String exceeds line";
         break;
      case errorRecordNumber:
         msg << "Error: Error in record of number";
         break;
      case errorIllegalCharacter:
         msg << "Fatal: Illegal character \"" << _ch << "\"";
         break;
   }
   return msg.str();
}

SyntaxException::SyntaxException(string& AFname, string& AFound, int ALine, int ATag):
		fname(AFname), found(AFound), _line(ALine), tag(ATag) {}

string SyntaxException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Fatal: Syntax error, ";
	switch (tag) {
		case Tag::IDENTIFICATOR:
			msg << "\"identifier\"";
			break;
		case Tag::SEMICOLON:
			msg << "\";\"";
			break;
		case Tag::EQ:
			msg << "\"=\"";
			break;
		case Tag::LBRACKET:
			msg << "\"[\"";
			break;
		case Tag::RBRACKET:
			msg << "\"]\"";
			break;
		case Tag::LPARENTHESIS:
			msg << "\"(\"";
			break;
		case Tag::RPARENTHESIS:
			msg << "\")\"";
			break;
		case Tag::OF:
			msg << "\"of\"";
			break;
		case Tag::BEGIN:
			msg << "\"begin\"";
			break;
		case Tag::END:
			msg << "\"end\"";
			break;
		case Tag::THEN:
			msg << "\"then\"";
			break;
		case Tag::DO:
			msg << "\"do\"";
			break;
		case Tag::UNTIL:
			msg << "\"until\"";
			break;
		case Tag::TO:
			msg << "\"to\"";
			break;
		case Tag::COLON:
			msg << "\":\"";
			break;
		case Tag::DOT:
			msg << "\".\"";
			break;
		case Tag::DOUBLE_DOT:
			msg << "\"..\"";
			break;
		case Tag::ASSIGNMENT:
			msg << "\":=\"";
			break;
   }
	msg << " expected but \"" << found << "\" found";
	//if (expctType == etSubrange) {
	//	msg.clear();
	//	msg.str("");
	//	msg << fname << "(" << _line << ") : Error in type definition";
	//}
   return msg.str();
}

DuplicateException::DuplicateException(string& AFname, string& AFound, int ALine):
		fname(AFname), found(AFound), _line(ALine) {}

string DuplicateException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Error: Duplicate identifier \"" << found << "\"";
   return msg.str();
}

OperatorException::OperatorException(string& AFname, string AOp, int ALine, operatorErrType AType):
		fname(AFname), op(AOp), _line(ALine), type(AType) {}

string OperatorException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Error: ";
	switch (type) {
		case optConstantString:
			msg << "Operator is not overloaded: " << op << " " << "\"Constant String\"";
			break;
		case optAnd:
		case optOr:
			msg << "Operation \"" << op << "\" is not supported for types \"Extended\" and \"Extended\"";
			break;
   }
   return msg.str();
}

IdentifierNotFoundException::IdentifierNotFoundException(string& AFname, string AId, int ALine):
			fname(AFname), id(AId), _line(ALine) {}

string IdentifierNotFoundException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Error: Identifier not found \"" << id << "\"";
   return msg.str();
}

IllegalExprException::IllegalExprException(string& AFname, int ALine): fname(AFname), _line(ALine) {}

string IllegalExprException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Error: Illegal expression";
   return msg.str();
}

IncompatibleTypesException::IncompatibleTypesException(string& AFname, int ALine, SymbolType AType):
		fname(AFname), _line(ALine), type(AType) {}


string IncompatibleTypesException::getMessage()
{
   stringstream msg;
	msg << fname << "(" << _line << ") Error: Incompatible types: Type " << GetMsgPart(type) << " expected";
   return msg.str();
}

IncompatibleTypeArgException::IncompatibleTypeArgException(string& AFname, int ALine, int ANum, SymbolType AType, bool AIsVar):
	fname(AFname), _line(ALine), num(ANum), type(AType), isVar(AIsVar) {}

string IncompatibleTypeArgException::getMessage()
{
   stringstream msg;
	msg << fname << "(" << _line << ") Error: Incompatible type for " << (isVar ? "var " : "") << "arg no. " << num;
	msg << " : Type " << GetMsgPart(type) << " expected";
   return msg.str();
}

TypeDefinitionException::TypeDefinitionException(string& AFname, int ALine): fname(AFname), _line(ALine) {}

string TypeDefinitionException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Error: Error in type definition";
   return msg.str();
}


WrongParametersException::WrongParametersException(string& AFname, int ALine, string& ASubroutineName):
		fname(AFname), _line(ALine), subroutineName(ASubroutineName) {}

string WrongParametersException::getMessage() const
{
   stringstream msg;
	msg << fname << "(" << _line << ") Error: Wrong number of parameters specified for call to \"" << subroutineName << "\"";
   return msg.str();
}

JumpNotAllowedException::JumpNotAllowedException(string& AFname, int ALine, int ATag):
		fname(AFname), _line(ALine), tag(ATag)
{}

string JumpNotAllowedException::getMessage() const
{
   stringstream msg;
	msg << fname << "(" << _line << ") Error: " << (tag == Tag::CONTINUE ? "continue" : "break") << " not allowed";
   return msg.str();
}

IllegalTypeConversionException::IllegalTypeConversionException(string& AFname, int ALine):
   fname(AFname), _line(ALine)
{}

string IllegalTypeConversionException::getMessage() const
{
   stringstream msg;
   msg << fname << "(" << _line << ") Error: Illegal type conversion";
   return msg.str();
}