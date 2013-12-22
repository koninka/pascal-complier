#pragma once

#include "scanner.h"
#include "CodeGen.h"

#define FACTOR   6
#define TAIL_LEN 4

enum NodeType {
	ntNode,
	ntNumber,
	ntCharacterString,
	ntVar,
	ntBinary,
	ntUnaryOp,
	ntBinaryOp,
	ntAssignOp,
	ntRecordAccess,
	ntCall,
   ntWrite,
   ntWriteln,
	ntOrd,
	ntChr,
	ntArrIdx,
	ntBlock,
	ntSubroutineBlock,
	ntDeclaration,
	ntDeclarationContainer,
	ntExitStmt,
	ntBreakStmt,
	ntContinueStmt,
	ntIfStmt,
	ntWhileStmt,
	ntForStmt,
	ntRepeateStmt,
   ntIntTypeCast,
	ntInt2Float,
	ntFloat2Int
};

class SyntaxNode {
protected:
	NodeType type;
public:
   unsigned depth;
	SyntaxNode(NodeType, unsigned);
	virtual ~SyntaxNode() {};
	virtual void PrintNode(int) {};
   virtual void Generate(AsmCode&) {};
   virtual void GenerateLValue(AsmCode&) const {};
	void PrintText(int, string);
	bool operator == (NodeType);
	bool operator != (NodeType);
};

typedef vector<SyntaxNode*> Statements;

struct NodeBlock: public SyntaxNode {
   string name;
   Statements statements;
   NodeBlock(string);
   NodeBlock(NodeType);
   NodeBlock(Statements, string, NodeType);
   void AddStatement(SyntaxNode*);
   void Generate(AsmCode&) override;
   void PrintNode(int) override;
};