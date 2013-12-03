#pragma once

#include <queue>
#include "scanner.h"
#include "syntax_nodes.h"

class SimpleParser {
	queue<TokenPtr> tokens;
	SyntaxNode* root;
	TokenPtr getToken();
	NodeExpr* ParseExpr();
	NodeExpr* ParseTerm();
	NodeExpr* ParseFactor();
public:
	Scanner scanner;
	SimpleParser(const Scanner&);
	void Parse();
	void PrintTree();
};