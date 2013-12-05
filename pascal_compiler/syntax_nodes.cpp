#include <iostream>
#include "syntax_nodes.h"

using namespace std;

NodeBlock::NodeBlock(string AName): SyntaxNode(ntBlock), name(AName) {}

NodeBlock::NodeBlock(NodeType AType): SyntaxNode(AType) {}

NodeBlock::NodeBlock(Statements AStatements, string AName, NodeType AType):
		SyntaxNode(AType), name(AName), statements(AStatements) {}

void NodeBlock::AddStatement(SyntaxNode* statement)
{
	if (statement != nullptr) {
		statements.push_back(statement);
	}
}

void NodeBlock::PrintNode(int d)
{
	for (size_t i = 0; i < statements.size(); i++) {
		if (i == statements.size() % 2 + 1) {
			SyntaxNode::PrintText(d, name);
		}
		statements[i]->PrintNode(d + 1);
	}
	if (statements.size() == 0) {
		SyntaxNode::PrintText(d + 1, "empty block");
		SyntaxNode::PrintText(d, name);
	} else if (statements.size() == 1) {
		SyntaxNode::PrintText(d, name);
	}
}

NodeSubroutineBlock::NodeSubroutineBlock(): NodeBlock(ntSubroutineBlock) {}

void NodeSubroutineBlock::AddBody(NodeBlock* ABlock)
{
	name = ABlock->name;
	statements = ABlock->statements;
}

NodeExpr::NodeExpr(TokenPtr ptr, NodeType AType): token(ptr), SyntaxNode(AType) {}

void NodeExpr::PrintNode(int d)
{
	SyntaxNode::PrintText(d, *token != ttOperator && *token != ttCharacterString ? token->getValue() : token->text);
}

Symbol* NodeExpr::GetType()
{
	return nullptr;
}

Symbol* NodeExpr::GetSymbol()
{
	return nullptr;
}

bool NodeExpr::IsLValue()
{
	return false;
}

bool NodeExpr::IsSubroutineCall()
{
	return false;
}

NodeNumber::NodeNumber(TokenPtr ptr): NodeExpr(ptr, ntNumber) {}

Symbol* NodeNumber::GetType()
{
	Symbol* symbol(nullptr);
	if (*token == ttIntegerNumber) {
		symbol = typeInteger;
	} else {
		symbol = typeFloat;
	}
	return symbol;
}

NodeCharacterString::NodeCharacterString(TokenPtr ptr): NodeExpr(ptr, ntCharacterString) {}

Symbol* NodeCharacterString::GetType()
{
	Symbol* symbol(nullptr);
	if (dynamic_cast<CharacterString*>(token.get())->value.length() == 1) {
		symbol = typeChar;
	} else {
		symbol = new SymType(stConstCharacterString);
	}
	return symbol;
}

NodeVar::NodeVar(TokenPtr ptr, Symbol* ASymbol): NodeExpr(ptr, ntVar), symbol(ASymbol) {}

Symbol* NodeVar::GetType()
{
	SymVar* symVar = dynamic_cast<SymVar*>(symbol);
	return symVar != nullptr ? GetReferenceType(symVar->type.get()) : symbol->GetType();
}

Symbol* NodeVar::GetSymbol()
{
	return symbol;
}

bool NodeVar::IsLValue()
{
	return
		*symbol != stConstChar
	&& *symbol != stConstFloat
	&& *symbol != stConstInteger
	&& *symbol != stConstCharacterString;
}

NodeUnaryOp::NodeUnaryOp(TokenPtr ptr, NodeExpr* NodeExpr_child): NodeExpr(ptr, ntUnaryOp), arg(NodeExpr_child) {}

NodeUnaryOp::NodeUnaryOp(TokenPtr ptr, NodeExpr* NodeExpr_child, NodeType AType): NodeExpr(ptr, AType), arg(NodeExpr_child) {}

Symbol* NodeUnaryOp::GetType()
{
	Symbol* result = arg->GetType();
	if (*token == ttOperator && (*result != stTypeInteger && *result != stTypeFloat)) {
		result = nullptr;
	}
	return result;
}

void NodeUnaryOp::PrintNode(int d)
{
	arg->PrintNode(d + 1);
	NodeExpr::PrintNode(d);
}

NodeInt2Float::NodeInt2Float(NodeExpr* AArg): NodeUnaryOp(nullptr, AArg, ntInt2Float) {}

void NodeInt2Float::PrintNode(int d)
{
	arg->PrintNode(d + 1);
	SyntaxNode::PrintText(d, "i2f");
}

Symbol* NodeInt2Float::GetType()
{
	return typeFloat;
}

NodeFloat2Int::NodeFloat2Int(NodeExpr* AArg): NodeUnaryOp(nullptr, AArg, ntFloat2Int) {}

void NodeFloat2Int::PrintNode(int d)
{
	arg->PrintNode(d + 1);
	SyntaxNode::PrintText(d, "f2i");
}

Symbol* NodeFloat2Int::GetType()
{
	return typeInteger;
}

NodeOrd::NodeOrd(TokenPtr ptr, NodeExpr* AArg): NodeUnaryOp(ptr, AArg, ntOrd) {}

Symbol* NodeOrd::GetType()
{
	Symbol* symbol(nullptr);
	if (*(arg->GetType()) == stTypeChar) {
		symbol = typeInteger;
	}
	return symbol;
}

NodeChr::NodeChr(TokenPtr ptr, NodeExpr* AArg): NodeUnaryOp(ptr, AArg, ntChr) {}

Symbol* NodeChr::GetType()
{
	Symbol* symbol(nullptr);
	if (*(arg->GetType()) == stTypeInteger) {
		symbol = typeChar;
	}
	return symbol;
}

NodeBinary::NodeBinary(TokenPtr ptr, NodeExpr* l , NodeExpr* r, NodeType AType): NodeExpr(ptr, AType), left(l), right(r) {}

Symbol* NodeBinary::GetType()
{
	Symbol* result(nullptr);
	Symbol* leftType = left->GetType();
	Symbol* rightType = right->GetType();
	if (*leftType == *rightType && (*leftType == stTypeInteger || *leftType == stTypeFloat)) {
		result = leftType;
	} else if (*leftType == stTypeInteger && *rightType == stTypeFloat) {
		result = rightType;
		left = new NodeInt2Float(left);
	} else if (*leftType == stTypeFloat && *rightType == stTypeInteger) {
		result = leftType;
		right = new NodeFloat2Int(right);
	}
	return result != nullptr ? GetReferenceType(result) : result;	
}

void NodeBinary::PrintNode(int d)
{
	right->PrintNode(d + 1);
	NodeExpr::PrintNode(d);
	left->PrintNode(d + 1);
}

NodeBinaryOp::NodeBinaryOp(TokenPtr ptr, NodeExpr* l, NodeExpr* r): NodeBinary(ptr, l, r, ntBinaryOp) {}

NodeAssignOp::NodeAssignOp(TokenPtr ptr, NodeExpr* l, NodeExpr* r): NodeBinary(ptr, l, r, ntAssignOp) {}

NodeRecordAccess::NodeRecordAccess(TokenPtr ptr, NodeExpr* l, NodeExpr* r): NodeBinary(ptr, l, r, ntRecordAccess) {}

Symbol* NodeRecordAccess::GetType()
{
	return right->GetType();
}

Symbol* NodeRecordAccess::GetSymbol()
{
	return right->GetSymbol();
}

bool NodeRecordAccess::IsLValue()
{
	return true;
}

NodeArgs::NodeArgs(Args AArgs, NodeType AType): args(AArgs), NodeExpr(nullptr, AType)  {}

void NodeArgs::PrintNode(int d)
{
	for (int i = args.size() - 1; i >= 0; i--) {
		args[i]->PrintNode(d);
	}
}

NodeWrite::NodeWrite(Args AArgs): NodeArgs(AArgs, ntWrite) {}

void NodeWrite::PrintNode(int d)
{
   NodeArgs::PrintNode(d + 1);
   SyntaxNode::PrintText(d, "write");
}

NodeCall::NodeCall(NodeExpr* ACallName, Args AArgs, Symbol* AResultType):
		NodeArgs(AArgs, ntCall), callName(ACallName), resultType(AResultType) {}

void NodeCall::PrintNode(int d)
{
	NodeArgs::PrintNode(d + 1);
	SyntaxNode::PrintText(d, "call");
	callName->PrintNode(d + 1);
}

bool NodeCall::IsSubroutineCall()
{
	return true;
}

Symbol* NodeCall::GetType()
{
	return resultType != nullptr ? GetReferenceType(resultType) : typeDefault;
}

NodeArrIdx::NodeArrIdx(NodeExpr* AArrName, Args AArgs): NodeArgs(AArgs, ntArrIdx), arrName(AArrName) {}

void NodeArrIdx::PrintNode(int d)
{
	NodeArgs::PrintNode(d + 1);
	SyntaxNode::PrintText(d, "[]");
	arrName->PrintNode(d + 1);
}

Symbol* NodeArrIdx::GetType()
{
	Symbol* arrType = arrName->GetType();
	for (size_t i = 0; i < args.size() && *(GetReferenceType(arrType)) == stTypeArray; i++) {
		arrType = dynamic_cast<SymTypeArry*>(arrType)->elemType;
	}
	return GetReferenceType(arrType);
}

bool NodeArrIdx::IsLValue()
{
	return arrName->IsLValue();
}

NodeStmt::NodeStmt(NodeType AType): SyntaxNode(AType) {}

bool NodeStmt::IsForLoop()
{
	return false;
}

NodeExitStmt::NodeExitStmt(SyntaxNode* ABlock): NodeStmt(ntExitStmt), block(ABlock) {}

void NodeExitStmt::PrintNode(int d)
{
	PrintText(d, "exit");
}

NodeJumpStmt::NodeJumpStmt(NodeStmt* ALoop, NodeType AType): NodeStmt(AType), loop(ALoop) {}

NodeBreakStmt::NodeBreakStmt(NodeStmt* ALoop): NodeJumpStmt(ALoop, ntBreakStmt) {}

void NodeBreakStmt::PrintNode(int d)
{
	PrintText(d, "break");
}

NodeContinueStmt::NodeContinueStmt(NodeStmt* ALoop): NodeJumpStmt(ALoop, ntContinueStmt) {}

void NodeContinueStmt::PrintNode(int d)
{
	PrintText(d, "continue");
}

NodeExprStmt::NodeExprStmt(NodeExpr* AExpr, NodeType AType): NodeStmt(AType), expr(AExpr) {}

NodeIfStmt::NodeIfStmt(NodeExpr* AExpr, SyntaxNode* AThen_stmt, SyntaxNode* AElse_stmt):
		NodeExprStmt(AExpr, ntIfStmt), then_stmt(AThen_stmt), else_stmt(AElse_stmt) {}

void NodeIfStmt::PrintNode(int d)
{
	expr->PrintNode(d + 2);
	SyntaxNode::PrintText(d + 1, "expr");
	cout << endl;
	SyntaxNode::PrintText(d, "if block");
	cout << endl;
	SyntaxNode::PrintText(d + 1, "then");
	if (then_stmt != nullptr) {
		then_stmt->PrintNode(d + 2);
	}
	if (else_stmt != nullptr) {
		SyntaxNode::PrintText(d + 1, "else");
		cout << endl;
		else_stmt->PrintNode(d + 2);
	}
}

NodeWhileStmt::NodeWhileStmt(NodeExpr* AExpr): NodeExprStmt(AExpr, ntWhileStmt) {}

void NodeWhileStmt::SetStatement(SyntaxNode* AStmt)
{
	stmt = AStmt;
}

void NodeWhileStmt::PrintNode(int d)
{
	expr->PrintNode(d + 2);
	SyntaxNode::PrintText(d + 1, "expr");
	cout << endl;
	SyntaxNode::PrintText(d, "while block");
	cout << endl;
	SyntaxNode::PrintText(d + 1, "do");
	if (stmt != nullptr) {
		stmt->PrintNode(d + 2);
	}
}

NodeRepeateStmt::NodeRepeateStmt(): NodeExprStmt(nullptr, ntRepeateStmt) {}

void NodeRepeateStmt::SetLoopInfo(NodeBlock* AStmt_seq, NodeExpr* AExpr)
{
	expr = AExpr;
	stmt_seq = AStmt_seq;
}

void NodeRepeateStmt::PrintNode(int d)
{
	stmt_seq->PrintNode(d + 1);
	cout << endl;
	SyntaxNode::PrintText(d, "repeate block");
	cout << endl;
	SyntaxNode::PrintText(d + 1, "until");
	expr->PrintNode(d + 2);
}

NodeForStmt::NodeForStmt(Symbol* AVar, NodeExpr* AInitialExpr, NodeExpr* AFinalExpr, LoopForType AType):
	NodeStmt(ntForStmt), var(AVar), initialExpr(AInitialExpr), finalExpr(AFinalExpr), loopType(AType) {}

void NodeForStmt::SetStatement(SyntaxNode* AStmt)
{
	stmt = AStmt;
}

void NodeForStmt::PrintNode(int d)
{
	finalExpr->PrintNode(d + 2);
	SyntaxNode::PrintText(d + 1, "final expr");
	cout << endl;
	SyntaxNode::PrintText(d + 1, "initial expr");
	initialExpr->PrintNode(d + 2);
	cout << endl;
	SyntaxNode::PrintText(d + 1, "var " + var->name);
	cout << endl;
	SyntaxNode::PrintText(d, "for block");
	cout << endl;
	string toLoop = (loopType == loopTo ? "to" : "downto");
	SyntaxNode::PrintText(d + 1, toLoop + " do");
	stmt->PrintNode(d + 2);
}

bool NodeForStmt::IsForLoop()
{
	return true;
}
