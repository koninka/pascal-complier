#pragma once

#include "scanner.h"

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
	ntInt2Float,
	ntFloat2Int
};

struct SyntaxNode {
	NodeType type;
	SyntaxNode(NodeType);
	virtual ~SyntaxNode() {};
	virtual void PrintNode(int) {};
	void PrintText(int, string);
	bool operator == (NodeType);
	bool operator != (NodeType);

};