#pragma once

#include "syntax_node.h"
#include "symbols.h"
#include "symbol_table.h"

class NodeSubroutineBlock: public NodeBlock {
   AsmLabel* exitLabel;
public:
   NodeSubroutineBlock();
	void AddBody(NodeBlock*);
   void Generate(AsmCode&)override;
   AsmLabel* GetExitLabel() const;
};

struct NodeExpr: public SyntaxNode {
	TokenPtr token;
	NodeExpr(TokenPtr, NodeType, unsigned);
	void PrintNode(int) override;
	virtual Symbol* GetType();
	virtual Symbol* GetSymbol();
	virtual bool IsLValue();
	virtual bool IsSubroutineCall();
};

typedef vector<NodeExpr*> Args;

struct NodeIntegerNumber: public NodeExpr {
   NodeIntegerNumber(TokenPtr);
   Symbol* GetType() override;
   void Generate(AsmCode&) override;
};

class NodeRealNumber: public NodeExpr {
   AsmStrImmediate* constLabel;
public:
   NodeRealNumber(TokenPtr);
   Symbol* GetType() override;
   void GenerateData(AsmCode&);
   void Generate(AsmCode&) override;
};

struct NodeCharacterString: public NodeExpr {
	NodeCharacterString(TokenPtr, unsigned);
	Symbol* GetType() override;
   void Generate(AsmCode&) override;
};

struct NodeVar: public NodeExpr {
	Symbol* symbol;
	NodeVar(TokenPtr, Symbol*, unsigned);
	Symbol* GetType() override;
	Symbol* GetSymbol();   
	bool IsLValue() override;
   void Generate(AsmCode&) override;
   void GenerateLValue(AsmCode&) const override;
};

class NodeUnaryOp: public NodeExpr {
   void GenerateForInt(AsmCode&) const;
   void GenerateForReal(AsmCode&) const;
public:
	NodeExpr* arg;
	NodeUnaryOp(TokenPtr, NodeExpr*, unsigned);
	NodeUnaryOp(TokenPtr, NodeExpr*, NodeType, unsigned);
   Symbol* GetType() override;
   void Generate(AsmCode&) override;
	void PrintNode(int) override;
};

class NodeTypecast: public NodeUnaryOp {
protected:
   void GenerateRealTypecast(AsmCode&);
   void GenerateIntegerTypecast(AsmCode&);
public:
   NodeTypecast(NodeExpr*, NodeType);
};

struct NodeIntegerTypecast: public NodeTypecast {
   NodeIntegerTypecast(NodeExpr*);
   Symbol* GetType() override;
   void Generate(AsmCode&) override;
   void PrintNode(int) override;
};

struct NodeRealTypecast: public NodeTypecast {
   NodeRealTypecast(NodeExpr*);
   Symbol* GetType() override;
   void Generate(AsmCode&) override;
   void PrintNode(int) override;
};

struct NodeOrd: public NodeUnaryOp {
   NodeOrd(TokenPtr, NodeExpr*, unsigned);
	Symbol* GetType() override;
};

struct NodeChr: public NodeUnaryOp {
   NodeChr(TokenPtr, NodeExpr*, unsigned);
	Symbol* GetType() override;
};

class NodeBinary: public NodeExpr {
protected:
	NodeExpr* left;
	NodeExpr* right;
public:
   NodeBinary(TokenPtr, NodeExpr*, NodeExpr*, NodeType, unsigned);
   NodeExpr* GetLeft() const;
   NodeExpr* GetRight() const;
	Symbol* GetType() override;
	void PrintNode(int) override;
};

class NodeBinaryOp: public NodeBinary {
   void GenerateForInt(AsmCode&) const;
   void GenerateForReal(AsmCode&) const;
   void GenerateForIntRelationalOp(AsmCode&) const;
   void GenerateForRealRelationalOp(AsmCode&) const;
public:
   NodeBinaryOp(TokenPtr, NodeExpr*, NodeExpr*, unsigned);
   void Generate(AsmCode&) override;
};

struct NodeAssignOp: public NodeBinary {
   NodeAssignOp(TokenPtr, NodeExpr*, NodeExpr*);
   void Generate(AsmCode&) override;
};

struct NodeRecordAccess: public NodeBinary {
   NodeRecordAccess(TokenPtr, NodeExpr*, NodeExpr*, unsigned);
	Symbol* GetType() override;
	Symbol* GetSymbol() override;
	bool IsLValue() override;
   void Generate(AsmCode&) override;
   void GenerateLValue(AsmCode&) const override;
};

struct NodeArgs: public NodeExpr {
	Args args;
	NodeArgs(Args, NodeType, unsigned);
	void PrintNode(int) override;
};

struct NodeWriteBase: public NodeArgs {
   NodeWriteBase(Args, NodeType, unsigned);
   void Generate(AsmCode&) override;
};

struct NodeWrite: public NodeWriteBase {
   NodeWrite(Args, unsigned);
   void PrintNode(int) override;
};

struct NodeWriteln: public NodeWriteBase {
   NodeWriteln(Args, unsigned);
   void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

class NodeCall: public NodeArgs {
   NodeExpr* callName;
public:
   NodeCall(NodeExpr*, Args, unsigned);
	void PrintNode(int) override;
	bool IsSubroutineCall() override;
	Symbol* GetType() override;
   Symbol* GetSymbol() override;
   void Generate(AsmCode&) override;
};

class NodeArrIdx: public NodeArgs {
   void ComputeIndexToEax(AsmCode&) const;
public:
	NodeExpr* arrName;
   NodeArrIdx(NodeExpr*, Args, unsigned);
	void PrintNode(int) override;
	Symbol* GetType() override;
   Symbol* GetSymbol() override;
	bool IsLValue() override;
   void Generate(AsmCode&) override;
   void GenerateLValue(AsmCode&) const override;
};

struct NodeStmt: public SyntaxNode {
   NodeStmt(NodeType, unsigned);
	bool virtual IsForLoop();
};

struct NodeExitStmt: public NodeStmt {
	SyntaxNode* block;
	NodeExitStmt(SyntaxNode*);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

struct NodeJumpStmt: public NodeStmt {
	NodeStmt* loop;
	NodeJumpStmt(NodeStmt*, NodeType);
};

struct NodeBreakStmt: public NodeJumpStmt {
	NodeBreakStmt(NodeStmt*);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

struct NodeContinueStmt: public NodeJumpStmt {
	NodeContinueStmt(NodeStmt*);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

class NodeExprStmt: public NodeStmt {
protected:
	NodeExpr* expr;
public:
   NodeExprStmt(NodeExpr*, NodeType, unsigned);
};

class NodeIfStmt: public NodeExprStmt {
	SyntaxNode* thenStmt;
	SyntaxNode* elseStmt;
public:
   NodeIfStmt(NodeExpr*, SyntaxNode*, SyntaxNode*, unsigned);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

class NodeLoopStmtBase {
protected:
   AsmLabel* breakLabel;
   AsmLabel* continueLabel;
   void GenerateLoopLabels(AsmCode&);
public:
   AsmLabel* GetBreakLabel() const;
   AsmLabel* GetContinueLabel() const;
};

class NodeWhileStmt: public NodeLoopStmtBase, public NodeExprStmt {
	SyntaxNode* stmt;
public:
   NodeWhileStmt(NodeExpr*, unsigned);
	void SetStatement(SyntaxNode*);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

class NodeRepeateStmt: public NodeLoopStmtBase, public NodeExprStmt {
	NodeBlock* stmtSeq;
public:
   NodeRepeateStmt(unsigned);
	void SetLoopInfo(NodeBlock*, NodeExpr*);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
};

enum LoopForType {
	loopTo,
	loopDownto
};

class NodeForStmt: public NodeLoopStmtBase, public NodeStmt {
   LoopForType loopType;
   NodeExpr* initialExpr;
   NodeExpr* finalExpr;
   SyntaxNode* stmt;
public:
	Symbol* var;
   NodeForStmt(Symbol*, NodeExpr*, NodeExpr*, LoopForType, unsigned);
	void SetStatement(SyntaxNode*);
	void PrintNode(int) override;
   void Generate(AsmCode&) override;
	bool IsForLoop() override;   
};