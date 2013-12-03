#include "simple_parser.h"
#include "error.h"

SimpleParser::SimpleParser(const Scanner& AScanner): scanner(AScanner) {}

TokenPtr SimpleParser::getToken()
{
	TokenPtr result;
	if (tokens.size() != 0) {
		result = tokens.front();
		tokens.pop();
	} else {
		scanner.Next();
		result = scanner.Get();
	}
	return result;
}

void SimpleParser::Parse()
{
	root = ParseExpr();
}

void SimpleParser::PrintTree()
{
	if (root != nullptr) root->PrintNode(0);
}

NodeExpr* SimpleParser::ParseExpr()
{
	NodeExpr* result = ParseTerm();
	TokenPtr token = getToken();
	if (*token == Tag::ADDITION || *token == Tag::SUBTRACTION) {
		result = new NodeBinaryOp(token, result, ParseExpr());
	} else {
		tokens.push(token);
	}
	return result;
}

NodeExpr* SimpleParser::ParseTerm()
{
	NodeExpr* result = ParseFactor();
	TokenPtr token = getToken();
	if (*token == Tag::MULTIPLICATION || *token == Tag::DIVISION) {
		result = new NodeBinaryOp(token, result, ParseTerm());
	} else {
		tokens.push(token);
	}
	return result;
}

NodeExpr* SimpleParser::ParseFactor()
{
	NodeExpr* root = nullptr;
	TokenPtr token = getToken();
	if (*token == ttIntegerNumber || *token == ttRealNumber || *token == ttIdentificator) {
		root = new NodeVar(token, nullptr);
	} else if (*token == Tag::LPARENTHESIS) {
			root = ParseExpr();
			token = getToken();
			if (*token != ttSeparator || *token != Tag::RPARENTHESIS) {
				throw CompilerException(scanner.fname, token->line, errorSyntax);	
			}
	} else {
		throw CompilerException(scanner.fname, token->line, errorSyntax);
	}
	return root;
}