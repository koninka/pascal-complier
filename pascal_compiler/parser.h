#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include "scanner.h"
#include "symbols.h"
#include "symbol_table.h"
#include "syntax_node.h"
#include "syntax_nodes.h"
#include "CodeGen.h"

const int PRIORITIES_NUMBER = 4;

typedef vector<vector<int>> priorityTable;

enum priorityType {
	ptLowest = 0,
	ptThird = 1,
	ptSecond = 2,
	ptHighest = 3
};

struct Identifier {
	int line;
	string name;
	Identifier(string AName, int ALine): name(AName), line(ALine) {}
};

class Parser {
	typedef vector<Identifier> IdentifierList;
	typedef void (Parser::* parseFunc)();
	typedef double (Parser::* computeUnFunc)(double);
	typedef double (Parser::* computeBinaryFunc)(double, double);
	typedef unordered_map<int, parseFunc> DeclarationParseList;
	typedef unordered_map<int, computeUnFunc> ComputableUnaryFuncs;
	typedef unordered_map<int, computeBinaryFunc> ComputableBinaryFuncs;

	int _line;	
   bool _isGlobalNamespace;
   AsmCode asmCode;
	SyntaxNode* root;
	SymTable* symTable;
	queue<TokenPtr> tokens;
	SymTableStack tableStack;
	vector<NodeStmt*> loopStack;
	priorityTable _priorities;
	DeclarationParseList declParseList;
	ComputableUnaryFuncs computable_unary_op;
	ComputableBinaryFuncs computable_binary_op;

	void DoRight2LeftSimpleTypecast(Symbol*, NodeExpr**);
	void PutToken(const TokenPtr);
	void CheckNameForUnique(string&, int = -1);
	void CheckExpectedToken(Tag::identificators, bool = true);
	void CheckExpectedType(Symbol*, SymbolType);
	void CheckExpectedVarType(Symbol*, SymbolType);
	void CheckExpectedExpressionType(Symbol*, SymbolType);
	void CheckExpectedSubroutineType(Symbol*);
	void CheckVariableForLoopUsage(Symbol*);
	void CheckSubrangeBoundType(Symbol*, int);
	void ReserveOperationPriority(priorityType, int);
	void ParseBlock(string);
	void ParseDeclarationPart();
	void ParseConstantDefinition();
	void ParseTypeDefinition(); 
	void ParseProcedureDefinition();
	void ParseFunctionDefinition();
	void ParseVariableDeclaration();
	void ParseStatementSequence(NodeBlock*);

	bool IsTokenVariable();
	bool CheckPriorityByTag(int, int);
	bool CheckNextTokenTag(int);

	double ComputeUnaryOrd(double);
	double ComputeUnaryAddition(double);
	double ComputeUnarySubtraction(double);
	double ComputeUnaryNeagtion(double);
	double ComputeBinaryMultiplication(double, double);
	double ComputeBinaryDivision(double, double);
	double ComputeBinaryDiv(double, double);
	double ComputeBinaryMod(double, double);
	double ComputeBinaryAnd(double, double);
	double ComputeBinaryShl(double, double);
	double ComputeBinaryShr(double, double);
	double ComputeBinaryAddition(double, double);
	double ComputeBinarySubtraction(double, double);
	double ComputeBinaryOr(double, double);
	double ComputeBinaryXor(double, double);
	double ComputeBinaryEq(double, double);
	double ComputeBinaryNe(double, double);
	double ComputeBinaryLt(double, double);
	double ComputeBinaryGt(double, double);
	double ComputeBinaryLe(double, double);
	double ComputeBinaryGe(double, double);
	double ComputeConstantExpression(NodeExpr*, int);
	
	TokenPtr GetToken();

	string GetSubroutineName();

	IdentifierList ParseIdentifierList();

	Args ParseFuncArgs();
	Args ParseCommaSeparated();

	Symbol* FindSymbolByName(string, bool = false);
	Symbol* CreateConstExprSymbol(NodeExpr*, int);
	Symbol* ParseConstantExpression();
	Symbol* ParseArrayDeclaration(bool);
	Symbol* ParseRecordDeclaration();
	Symbol* ParseSubrangeType();
	Symbol* ParseType(bool = false);

	SymTable* ParseFormalParameterList();
	SymTable* ParseProcFuncBlock(SymTable*, string&, Symbol* = nullptr);

	NodeExpr* ParseExpression(int = 0);
	NodeExpr* ParseFactor();
	NodeExpr* ParseIdentifier(TokenPtr = nullptr, bool = true, bool = false);
	
	SyntaxNode* ParseStatement();
	SyntaxNode* ParseIfStatement();
	SyntaxNode* ParseWhileStatement();
	SyntaxNode* ParseForStatement();
	SyntaxNode* ParseRepeatStatement();
	SyntaxNode* ParseJumpStatement(TokenPtr);

	NodeBlock* ParseCompoundStatement(string);

	NodeCall* CreateCallNode(NodeExpr*, Args);

	NodeArrIdx* CreateArrIdxNode(NodeExpr*, Args);

   NodeWriteBase* CreateWriteNode(TokenPtr);

	NodeAssignOp* CreateAssignmentStatement(TokenPtr, NodeExpr*, NodeExpr*);
public:
	bool isDeclarationParse;
	Scanner scanner;
	Parser(const Scanner&);
   void Generate();
	void ParseProgram();
	void PrintTree();
	void PrintBlock();
	void PrintSymTable();
   
};