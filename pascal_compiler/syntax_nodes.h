#pragma once

#include "syntax_node.h"
#include "symbols.h"

typedef vector<SyntaxNode*> Statements;

struct NodeBlock: public SyntaxNode {
	string name;
	Statements statements;
	NodeBlock(string);
	NodeBlock(NodeType);
	NodeBlock(Statements, string, NodeType);
	void AddStatement(SyntaxNode*);
	void PrintNode(int) override;
};

struct NodeSubroutineBlock: public NodeBlock {
	NodeSubroutineBlock();
	void AddBody(NodeBlock*);
};

struct NodeExpr: public SyntaxNode {
	TokenPtr token;
	NodeExpr(TokenPtr, NodeType);
	void PrintNode(int) override;
	virtual Symbol* GetType();
	virtual Symbol* GetSymbol();
	virtual bool IsLValue();
	virtual bool IsSubroutineCall();
};

typedef vector<NodeExpr*> Args;

struct NodeNumber: public NodeExpr {
	NodeNumber(TokenPtr);
	Symbol* GetType() override;
};

struct NodeCharacterString: public NodeExpr {
	NodeCharacterString(TokenPtr);
	Symbol* GetType() override;
};

struct NodeVar: public NodeExpr {
	Symbol* symbol;
	NodeVar(TokenPtr, Symbol*);
	Symbol* GetType() override;
	Symbol* GetSymbol();
	bool IsLValue() override;
};

struct NodeUnaryOp: public NodeExpr {
	NodeExpr* arg;
	NodeUnaryOp(TokenPtr, NodeExpr*);
	NodeUnaryOp(TokenPtr, NodeExpr*, NodeType);
	void PrintNode(int) override;
	Symbol* GetType() override;
};

struct NodeInt2Float: public NodeUnaryOp {
	NodeInt2Float(NodeExpr*);
	void PrintNode(int) override;
	Symbol* GetType() override;
};

struct NodeFloat2Int: public NodeUnaryOp {
	NodeFloat2Int(NodeExpr*);
	void PrintNode(int) override;
	Symbol* GetType() override;
};

struct NodeOrd: public NodeUnaryOp {
	NodeOrd(TokenPtr, NodeExpr*);
	Symbol* GetType() override;
};

struct NodeChr: public NodeUnaryOp {
	NodeChr(TokenPtr, NodeExpr*);
	Symbol* GetType() override;
};

struct NodeBinary: public NodeExpr {
	NodeExpr* left;
	NodeExpr* right;
	NodeBinary(TokenPtr, NodeExpr*, NodeExpr*, NodeType);
	Symbol* GetType() override;
	void PrintNode(int) override;
};

struct NodeBinaryOp: public NodeBinary {
	NodeBinaryOp(TokenPtr, NodeExpr*, NodeExpr*);
};

struct NodeAssignOp: public NodeBinary {
	NodeAssignOp(TokenPtr, NodeExpr*, NodeExpr*);
};

struct NodeRecordAccess: public NodeBinary {
	NodeRecordAccess(TokenPtr, NodeExpr*, NodeExpr*);
	Symbol* GetType() override;
	Symbol* GetSymbol() override;
	bool IsLValue() override;
};

struct NodeArgs: public NodeExpr {
	Args args;
	NodeArgs(Args, NodeType);
	void PrintNode(int) override;
};

struct NodeWrite: public NodeArgs {
   NodeWrite(Args);
   void PrintNode(int) override;
};

struct NodeCall: public NodeArgs {
	Symbol* resultType;
	NodeExpr* callName;
	NodeCall(NodeExpr*, Args, Symbol*);
	void PrintNode(int) override;
	bool IsSubroutineCall() override;
	Symbol* GetType() override;
};

struct NodeArrIdx: public NodeArgs {
	NodeExpr* arrName;
	NodeArrIdx(NodeExpr*, Args);
	void PrintNode(int) override;
	Symbol* GetType() override;
	bool IsLValue() override;
};

struct NodeStmt: public SyntaxNode {
	NodeStmt(NodeType);
	bool virtual IsForLoop();
};

struct NodeExitStmt: public NodeStmt {
	SyntaxNode* block;
	NodeExitStmt(SyntaxNode*);
	void PrintNode(int) override;
};

struct NodeJumpStmt: public NodeStmt {
	NodeStmt* loop;
	NodeJumpStmt(NodeStmt*, NodeType);
};

struct NodeBreakStmt: public NodeJumpStmt {
	NodeBreakStmt(NodeStmt*);
	void PrintNode(int) override;
};

struct NodeContinueStmt: public NodeJumpStmt {
	NodeContinueStmt(NodeStmt*);
	void PrintNode(int) override;
};

struct NodeExprStmt: public NodeStmt {
	NodeExpr* expr;
	NodeExprStmt(NodeExpr*, NodeType);
};

struct NodeIfStmt: public NodeExprStmt {
	SyntaxNode* then_stmt;
	SyntaxNode* else_stmt;
	NodeIfStmt(NodeExpr*, SyntaxNode*, SyntaxNode*);
	void PrintNode(int) override;
};

struct NodeWhileStmt: public NodeExprStmt {
	SyntaxNode* stmt;
	NodeWhileStmt(NodeExpr*);
	void SetStatement(SyntaxNode*);
	void PrintNode(int) override;
};

struct NodeRepeateStmt: public NodeExprStmt {
	NodeBlock* stmt_seq;
	NodeRepeateStmt();
	void SetLoopInfo(NodeBlock*, NodeExpr*);
	void PrintNode(int) override;
};

enum LoopForType {
	loopTo,
	loopDownto
};

struct NodeForStmt: public NodeStmt {
	Symbol* var;
	LoopForType loopType;
	NodeExpr* initialExpr;
	NodeExpr* finalExpr;
	SyntaxNode* stmt;
	NodeForStmt(Symbol*, NodeExpr*, NodeExpr*, LoopForType);
	void SetStatement(SyntaxNode*);
	void PrintNode(int) override;
	bool IsForLoop() override;
};