#include <iostream>
#include "syntax_nodes.h"

using namespace std;

NodeSubroutineBlock::NodeSubroutineBlock():
   NodeBlock(ntSubroutineBlock),
   exitLabel(nullptr)
{}

void NodeSubroutineBlock::AddBody(NodeBlock* ABlock)
{
	name       = ABlock->name;
	statements = ABlock->statements;
}

void NodeSubroutineBlock::Generate(AsmCode& asmCode)
{
   exitLabel = asmCode.GenLabel("exit");
   NodeBlock::Generate(asmCode);
   asmCode.AddLabel(exitLabel);
}

AsmStrImmediate* NodeSubroutineBlock::GetExitLabel() const
{
   return exitLabel;
}

NodeExpr::NodeExpr(TokenPtr ptr, NodeType AType, unsigned ADepth):
   token(ptr),
   SyntaxNode(AType, ADepth)
{}

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

NodeIntegerNumber::NodeIntegerNumber(TokenPtr ptr):
   NodeExpr(ptr, ntIntegerNumber, 0)
{}

Symbol* NodeIntegerNumber::GetType()
{
   return typeInteger;
}

void NodeIntegerNumber::Generate(AsmCode& asmCode)
{
   asmCode.AddCmd(PUSH, dynamic_cast<IntegerNumber*>(token.get())->value);
}

NodeRealNumber::NodeRealNumber(TokenPtr ptr):
   NodeExpr(ptr, ntRealNumber, 0)
{}

Symbol* NodeRealNumber::GetType()
{
   return typeFloat;
}

void NodeRealNumber::GenerateData(AsmCode& asmCode)
{
   constLabel = asmCode.AddData("v", dynamic_cast<RealNumber*>(token.get())->value);
}

void NodeRealNumber::Generate(AsmCode& asmCode)
{
   asmCode.AddCmd(PUSH, constLabel);
}

NodeCharacterString::NodeCharacterString(TokenPtr ptr, unsigned ADepth):
   NodeExpr(ptr, ntCharacterString, ADepth)
{}

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

void NodeCharacterString::Generate(AsmCode& asmCode)
{
   asmCode.AddCmd(PUSH, AsmVarAddr(asmCode.AddData(asmCode.GenStrLabel("str"), token->getValue())));
}

NodeVar::NodeVar(TokenPtr ptr, Symbol* ASymbol, unsigned ADepth):
   NodeExpr(ptr, ntVar, ADepth),
   symbol(ASymbol)
{}

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

void NodeVar::Generate(AsmCode& asmCode)
{
   symbol->Generate(asmCode, depth);
}

void NodeVar::GenerateLValue(AsmCode& asmCode) const
{
   symbol->GenerateLValue(asmCode, depth);
}

NodeUnaryOp::NodeUnaryOp(TokenPtr ptr, NodeExpr* NodeExpr_child, unsigned ADepth):
   NodeExpr(ptr, ntUnaryOp, ADepth),
   arg(NodeExpr_child)
{}

NodeUnaryOp::NodeUnaryOp(TokenPtr ptr, NodeExpr* NodeExpr_child, NodeType AType, unsigned ADepth):
   NodeExpr(ptr, AType, ADepth),
   arg(NodeExpr_child)
{}

Symbol* NodeUnaryOp::GetType()
{
	Symbol* result = arg->GetType();
	if (*token == ttOperator && (*result != stTypeInteger && *result != stTypeFloat)) {
		result = nullptr;
	}
	return result;
}

void NodeUnaryOp::Generate(AsmCode& asmCode)
{
   arg->Generate(asmCode);
   if (*(arg->GetType()) == stTypeInteger) {
      GenerateForInt(asmCode);
   } else {
      GenerateForReal(asmCode);
   }
}

void NodeUnaryOp::PrintNode(int d)
{
	arg->PrintNode(d + 1);
	NodeExpr::PrintNode(d);
}

void NodeUnaryOp::GenerateForInt(AsmCode& asmCode) const
{
   asmCode.AddCmd(POP, EAX);
   switch (token->tag) {
      case Tag::NEGATION:
         asmCode.AddCmd(TEST, EAX, EAX);
         asmCode.AddCmd(SETE, AL);
         asmCode.AddCmd(MOVZX, EAX, AL);
         break;
      case Tag::ADDITION:
         break;
      case Tag::SUBTRACTION:
         asmCode.AddCmd(NEG, EAX);
         break;
   }
   asmCode.AddCmd(PUSH, EAX);
}

void NodeUnaryOp::GenerateForReal(AsmCode& asmCode) const
{
   if (token->tag != Tag::SUBTRACTION) return;
   asmCode.AddCmd(FLD, AsmMemory(ESP, 0, szDWORD));
   asmCode.AddCmd(FCHS);
   asmCode.AddCmd(FSTP, AsmMemory(ESP, 0, szDWORD));
}

NodeTypecast::NodeTypecast(NodeExpr* AArg, NodeType AType):
   NodeUnaryOp(nullptr, AArg, AType)
{}

void NodeTypecast::GenerateRealTypecast(AsmCode& asmCode)
{
   arg->Generate(asmCode);
   asmCode.AddCmd(FILD, AsmMemory(ESP, 0, szDWORD));
   asmCode.AddCmd(FSTP, AsmMemory(ESP, 0, szDWORD));
}

void NodeTypecast::GenerateIntegerTypecast(AsmCode& asmCode)
{
   arg->Generate(asmCode);
}

NodeIntegerTypecast::NodeIntegerTypecast(NodeExpr* AArg):
   NodeTypecast(AArg, ntIntTypeCast)
{}

Symbol* NodeIntegerTypecast::GetType()
{
   return typeInteger;
}

void NodeIntegerTypecast::Generate(AsmCode& asmCode)
{
   GenerateIntegerTypecast(asmCode);
}

void NodeIntegerTypecast::PrintNode(int d)
{
   arg->PrintNode(d + 1);
   SyntaxNode::PrintText(d, "int typecast");
}

NodeRealTypecast::NodeRealTypecast(NodeExpr* AArg):
   NodeTypecast(AArg, ntRealTypeCast)
{}

Symbol* NodeRealTypecast::GetType()
{
   return typeFloat;
}

void NodeRealTypecast::Generate(AsmCode& asmCode)
{
   if (*(arg->GetType()) == stTypeChar) {
      GenerateIntegerTypecast(asmCode);
   }
   GenerateRealTypecast(asmCode);
}

void NodeRealTypecast::PrintNode(int d)
{
	arg->PrintNode(d + 1);
	SyntaxNode::PrintText(d, "real typecast");
}

NodeOrd::NodeOrd(TokenPtr ptr, NodeExpr* AArg, unsigned ADepth):
   NodeUnaryOp(ptr, AArg, ntOrd, ADepth)
{}

Symbol* NodeOrd::GetType()
{
	Symbol* symbol(nullptr);
	if (*(arg->GetType()) == stTypeChar) {
		symbol = typeInteger;
	}
	return symbol;
}

NodeChr::NodeChr(TokenPtr ptr, NodeExpr* AArg, unsigned ADepth):
   NodeUnaryOp(ptr, AArg, ntChr, ADepth)
{}

Symbol* NodeChr::GetType()
{
	Symbol* symbol(nullptr);
	if (*(arg->GetType()) == stTypeInteger) {
		symbol = typeChar;
	}
	return symbol;
}

NodeBinary::NodeBinary(TokenPtr ptr, NodeExpr* l, NodeExpr* r, NodeType AType, unsigned ADepth):
   NodeExpr(ptr, AType, ADepth),
   left(l),
   right(r)
{}

NodeExpr* NodeBinary::GetLeft() const
{
   return left;
}

NodeExpr* NodeBinary::GetRight() const
{
   return right;
}

Symbol* NodeBinary::GetType()
{
	Symbol* result(nullptr);
	Symbol* leftType = left->GetType();
	Symbol* rightType = right->GetType();
	if (*leftType == *rightType && (*leftType == stTypeInteger || *leftType == stTypeFloat)) {
		result = leftType;
	} else if (*leftType == stTypeInteger && *rightType == stTypeFloat) {
		result = rightType;
		left = new NodeRealTypecast(left);
	} else if (*leftType == stTypeFloat && *rightType == stTypeInteger) {
		result = leftType;
		right = new NodeRealTypecast(right);
	}
   if (result != nullptr && token->tag == Tag::DIVISION) {
      right = *(right->GetType()) == stTypeInteger ? new NodeRealTypecast(right) : right;
      left = *(left->GetType()) == stTypeInteger ? new NodeRealTypecast(left) : left;
      result = typeFloat;
   }
	return result != nullptr ? GetReferenceType(result) : result;	
}

void NodeBinary::PrintNode(int d)
{
	right->PrintNode(d + 1);
	NodeExpr::PrintNode(d);
	left->PrintNode(d + 1);
}

NodeBinaryOp::NodeBinaryOp(TokenPtr ptr, NodeExpr* l, NodeExpr* r, unsigned ADepth):
   NodeBinary(ptr, l, r, ntBinaryOp, ADepth)
{}

void NodeBinaryOp::Generate(AsmCode& asmCode)
{
   left->Generate(asmCode);
   right->Generate(asmCode);
   if (*(left->GetType()) == stTypeInteger) {
      GenerateForInt(asmCode);
   } else {
      GenerateForReal(asmCode);
   }
}

void NodeBinaryOp::GenerateForInt(AsmCode& asmCode) const
{
   asmCode.AddCmd(POP, EBX);
   asmCode.AddCmd(POP, EAX);
   switch (token->tag) {
      case Tag::ADDITION:
         asmCode.AddCmd(ADD, EAX, EBX);
         break;
      case Tag::SUBTRACTION:
         asmCode.AddCmd(SUB, EAX, EBX);
         break;
      case Tag::MULTIPLICATION:
         asmCode.AddCmd(IMUL, EBX);
         break;
      case Tag::DIVISION:
         asmCode.AddCmd(XOR, EDX, EDX);
         asmCode.AddCmd(IDIV, EBX);
         break;
      case Tag::MOD:
         asmCode.AddCmd(XOR, EDX, EDX);
         asmCode.AddCmd(IDIV, EBX);
         asmCode.AddCmd(PUSH, EDX);
         return;
      case Tag::AND:
         asmCode.AddCmd(AND, EAX, EBX);
         break;
      case Tag::OR:
         asmCode.AddCmd(OR, EAX, EBX);
         break;
      case Tag::XOR:
         asmCode.AddCmd(XOR, EAX, EBX);
         break;
      case Tag::SHR:
         //asmCode.AddCmd(SAR, EAX, EBX);
         //asmCode.AddCmd(SAR, EBX, EAX);
         //asmCode.AddCmd(PUSH, EBX);
         //return;
         break;
      case Tag::SHL:
         //asmCode.AddCmd(SAL, EAX, EBX);
         //asmCode.AddCmd(PUSH, EBX);
         //return;
         break;
      case Tag::NEGATION:
         asmCode.AddCmd(NOT, EAX, EBX);
         break;
      default:
         GenerateForIntRelationalOp(asmCode);
   }
   asmCode.AddCmd(PUSH, EAX);
}

void NodeBinaryOp::GenerateForReal(AsmCode& asmCode) const
{
   asmCode.AddCmd(FLD, AsmMemory(ESP, 4, szDWORD));
   asmCode.AddCmd(FLD, AsmMemory(ESP, 0, szDWORD));
   asmCode.AddCmd(ADD, ESP, 4);
   switch (token->tag) {
      case Tag::ADDITION:
         asmCode.AddCmd(FADDP, ST1, ST);
         break;
      case Tag::SUBTRACTION:
         asmCode.AddCmd(FSUBP, ST1, ST);
         break;
      case Tag::MULTIPLICATION:
         asmCode.AddCmd(FMULP, ST1, ST);
         break;
      case Tag::DIVISION:
         asmCode.AddCmd(FDIVP, ST1, ST);
         break;
      default:
         GenerateForRealRelationalOp(asmCode);
         return;
   }
   asmCode.AddCmd(FSTP, AsmMemory(ESP, 0, szDWORD));
}

void NodeBinaryOp::GenerateForIntRelationalOp(AsmCode& asmCode) const
{
   asmCode.AddCmd(CMP, EAX, EBX);
   switch (token->tag) {
      case Tag::GT:
         asmCode.AddCmd(SETG, AL);
         break;
      case Tag::GE:
         asmCode.AddCmd(SETGE, AL);
         break;
      case Tag::LT:
         asmCode.AddCmd(SETL, AL);
         break;
      case Tag::LE:
         asmCode.AddCmd(SETLE, AL);
         break;
      case Tag::EQ:
         asmCode.AddCmd(SETE, AL);
         break;
      case Tag::NE:
         asmCode.AddCmd(SETNE, AL);
   }
   asmCode.AddCmd(MOVZX, EAX, AL);
}

void NodeBinaryOp::GenerateForRealRelationalOp(AsmCode& asmCode) const
{
   asmCode.AddCmd(FCOMPP);
   asmCode.AddCmd(FNSTSW, AX);
   switch (token->tag) {
      case Tag::GT:
         asmCode.AddCmd(SAHF);
         asmCode.AddCmd(SETB, AL);
         break;
      case Tag::GE:
         asmCode.AddCmd(SAHF);
         asmCode.AddCmd(SETBE, AL);
         break;
      case Tag::LT:
         asmCode.AddCmd(SAHF);
         asmCode.AddCmd(SETA, AL);
         break;
      case Tag::LE:
         asmCode.AddCmd(SAHF);
         asmCode.AddCmd(SETAE, AL);
         break;
      case Tag::EQ:
         asmCode.AddCmd(SAHF);
         asmCode.AddCmd(SETE, AL);
         break;
      case Tag::NE:
         asmCode.AddCmd(SAHF);
         asmCode.AddCmd(SETNE, AL);
   }
   asmCode.AddCmd(MOVZX, EAX, AL);
   asmCode.AddCmd(MOV, AsmMemory(ESP), EAX);
}

NodeAssignOp::NodeAssignOp(TokenPtr ptr, NodeExpr* l, NodeExpr* r):
   NodeBinary(ptr, l, r, ntAssignOp, 0)
{}

void NodeAssignOp::Generate(AsmCode& asmCode)
{
   right->Generate(asmCode);
   left->GenerateLValue(asmCode);
   asmCode.AddCmd(POP, EAX);
   size_t size = left->GetType()->GetSize();
   if (size <= 16) {
      for (size_t i = 0; i < size; i += 4) {
         asmCode.AddCmd(POP, EBX);
         asmCode.AddCmd(MOV, AsmMemory(EAX, i), EBX);
      }
   } else {
      AsmStrImmediate* labelBegin = asmCode.GenLabel("assignBegin");
      AsmStrImmediate* labelEnd   = asmCode.GenLabel("assignEnd");
      asmCode.AddCmd(SUB, EAX, 4);
      asmCode.AddCmd(MOV, EBX, 0);
      asmCode.AddCmd(MOV, ECX, size);
      asmCode.AddLabel(labelBegin);
      asmCode.AddCmd(CMP, EBX, ECX);
      asmCode.AddCmd(JGE, labelEnd);
      asmCode.AddCmd(ADD, EAX, 4);
      asmCode.AddCmd(POP, EDX);
      asmCode.AddCmd(MOV, AsmMemory(EAX), EDX);
      asmCode.AddCmd(ADD, EBX, 4);
      asmCode.AddCmd(JMP, labelBegin);
      asmCode.AddLabel(labelEnd);
   }
}

NodeRecordAccess::NodeRecordAccess(TokenPtr ptr, NodeExpr* l, NodeExpr* r, unsigned ADepth):
   NodeBinary(ptr, l, r, ntRecordAccess, ADepth)
{}

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

void NodeRecordAccess::Generate(AsmCode& asmCode)
{
   GenerateLValue(asmCode);
   asmCode.PushMemory(dynamic_cast<NodeVar*>(right)->symbol->GetType()->GetSize());
}

void NodeRecordAccess::GenerateLValue(AsmCode& asmCode) const
{
   left->GenerateLValue(asmCode);
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(ADD, EAX, dynamic_cast<NodeVar*>(right)->symbol->GetOffset());
   asmCode.AddCmd(PUSH, EAX);
}

NodeArgs::NodeArgs(Args AArgs, NodeType AType, unsigned ADepth):
   args(AArgs),
   NodeExpr(nullptr, AType, ADepth)
{}

void NodeArgs::PrintNode(int d)
{
	for (int i = args.size() - 1; i >= 0; i--) {
		args[i]->PrintNode(d);
	}
}

NodeWriteBase::NodeWriteBase(Args AArgs, NodeType AType, unsigned ADepth):
   NodeArgs(AArgs, AType, ADepth)
{}

void NodeWriteBase::Generate(AsmCode& asmCode)
{
   for (auto &arg : args) {
      if (arg->IsLValue()) {
         arg->GenerateLValue(asmCode);
         asmCode.AddCmd(POP, EAX);
         asmCode.AddCmd(PUSH, AsmMemory(EAX, 0, szDWORD));
      } else {
         arg->Generate(asmCode);
      }
      Symbol* type = arg->GetType();
      if (*type == stTypeInteger) {
         asmCode.GenCallWriteForInt();
      } else if (*type == stTypeFloat) {
         asmCode.GenCallWriteForReal();
      } else {
         asmCode.GenCallWriteForStr();
      }
   }
}

NodeWrite::NodeWrite(Args AArgs, unsigned ADepth):
   NodeWriteBase(AArgs, ntWrite, ADepth)
{}

void NodeWrite::PrintNode(int d)
{
   NodeArgs::PrintNode(d + 1);
   SyntaxNode::PrintText(d, "write");
}

NodeWriteln::NodeWriteln(Args AArgs, unsigned ADepth):
   NodeWriteBase(AArgs, ntWriteln, ADepth)
{}

void NodeWriteln::PrintNode(int d)
{
   NodeArgs::PrintNode(d + 1);
   SyntaxNode::PrintText(d, "writeln");
}

void NodeWriteln::Generate(AsmCode& asmCode)
{
   NodeWriteBase::Generate(asmCode);
   asmCode.GenWriteNewLine();
}

NodeCall::NodeCall(NodeExpr* ACallName, Args AArgs, unsigned ADepth):
		NodeArgs(AArgs, ntCall, ADepth),
      callName(ACallName)
{}

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
   Symbol* symbol = GetSymbol();
   return *symbol == stFunction ? GetReferenceType(dynamic_cast<SymFunction*>(symbol)->GetResultType()) : typeDefault;
}

Symbol* NodeCall::GetSymbol()
{
   return callName->GetSymbol();
}

void NodeCall::Generate(AsmCode& asmCode)
{
   SymSubroutine* subroutine = dynamic_cast<SymSubroutine*>(callName->GetSymbol());
   if (*subroutine == stFunction) {
      asmCode.AddCmd(SUB, ESP, dynamic_cast<SymFunction*>(subroutine)->GetResultType()->GetSize());
   }
   size_t size = 0;
   for (int i = args.size() - 1; i >= 0; i--) {
      if (subroutine->GetArg(i)->IsByRef()) {
         size += 4;
         args[i]->GenerateLValue(asmCode);
      } else {
         Symbol* symbol = args[i]->GetType();
         args[i]->Generate(asmCode);
         if (symbol != nullptr && *(symbol) == stTypeArray) {
            asmCode.AddCmd(PUSH, symbol->GetSize());
            size += 4;
         }
         size += args[i]->GetType()->GetSize();
      }
   }
   asmCode.AddCmd(PUSH, EBP);
   asmCode.AddCmd(CALL, subroutine->GetLabel());
   asmCode.AddCmd(ADD, ESP, size);
}

NodeArrIdx::NodeArrIdx(NodeExpr* AArrName, Args AArgs, unsigned ADepth):
   NodeArgs(AArgs, ntArrIdx, ADepth),
   arrName(AArrName)
{}

void NodeArrIdx::PrintNode(int d)
{
	NodeArgs::PrintNode(d + 1);
	SyntaxNode::PrintText(d, "[]");
	arrName->PrintNode(d + 1);
}

Symbol* NodeArrIdx::GetType()
{
	Symbol* arrType = arrName->GetType();
   for (size_t i = 0; i < args.size() && (*(GetReferenceType(arrType)) == stTypeArray || *(GetReferenceType(arrType)) == stTypeOpenArray); i++) {
      arrType = dynamic_cast<SymTypeArry*>(GetReferenceType(arrType))->elemType;
	}
	return GetReferenceType(arrType);
}

Symbol* NodeArrIdx::GetSymbol()
{
   return arrName->GetSymbol();
}

bool NodeArrIdx::IsLValue()
{
	return arrName->IsLValue();
}

void NodeArrIdx::Generate(AsmCode& asmCode)
{
   ComputeIndexToEax(asmCode);
   size_t size = dynamic_cast<SymTypeArry*>(arrName->GetSymbol()->GetType())->elemType->GetSize();
   asmCode.PushMemory(size);
}

void NodeArrIdx::GenerateLValue(AsmCode& asmCode) const
{
   ComputeIndexToEax(asmCode);
}

void NodeArrIdx::ComputeIndexToEax(AsmCode& asmCode) const
{
   arrName->GenerateLValue(asmCode);
   SymTypeArry* type = dynamic_cast<SymTypeArry*>(arrName->GetSymbol()->GetType());
   for (auto &arg : args) {
      arg->Generate(asmCode);
      asmCode.AddCmd(MOV, EBX, type->elemType->GetSize());
      asmCode.AddCmd(POP, EAX);
      asmCode.AddCmd(SUB, EAX, type->GetLow());
      asmCode.AddCmd(IMUL, EAX, EBX);
      asmCode.AddCmd(POP, EBX);
      asmCode.AddCmd(ADD, EAX, EBX);
      asmCode.AddCmd(PUSH, EAX);
      SymTypeArray* arry = dynamic_cast<SymTypeArray*>(GetReferenceType(type->elemType));
      type = arry != nullptr ? arry : type;
   }
}

NodeStmt::NodeStmt(NodeType AType, unsigned ADepth):
   SyntaxNode(AType, ADepth)
{}

bool NodeStmt::IsForLoop()
{
	return false;
}

NodeExitStmt::NodeExitStmt(SyntaxNode* ABlock):
   NodeStmt(ntExitStmt, 0),
   block(ABlock)
{}

void NodeExitStmt::PrintNode(int d)
{
	PrintText(d, "exit");
}

void NodeExitStmt::Generate(AsmCode& asmCode)
{
   asmCode.AddCmd(JMP, dynamic_cast<NodeSubroutineBlock*>(block)->GetExitLabel());
}

NodeJumpStmt::NodeJumpStmt(NodeStmt* ALoop, NodeType AType):
   NodeStmt(AType, 0),
   loop(ALoop)
{}


NodeBreakStmt::NodeBreakStmt(NodeStmt* ALoop):
   NodeJumpStmt(ALoop, ntBreakStmt)
{}

void NodeBreakStmt::PrintNode(int d)
{
	PrintText(d, "break");
}

void NodeBreakStmt::Generate(AsmCode& asmCode)
{
   asmCode.AddCmd(JMP, dynamic_cast<NodeLoopStmtBase*>(loop)->GetBreakLabel());
}

NodeContinueStmt::NodeContinueStmt(NodeStmt* ALoop):
   NodeJumpStmt(ALoop, ntContinueStmt)
{}

void NodeContinueStmt::PrintNode(int d)
{
	PrintText(d, "continue");
}

void NodeContinueStmt::Generate(AsmCode& asmCode)
{
   asmCode.AddCmd(JMP, dynamic_cast<NodeLoopStmtBase*>(loop)->GetContinueLabel());
}

NodeExprStmt::NodeExprStmt(NodeExpr* AExpr, NodeType AType, unsigned ADepth):
   NodeStmt(AType, ADepth),
   expr(AExpr)
{}

NodeIfStmt::NodeIfStmt(NodeExpr* AExpr, SyntaxNode* AThenStmt, SyntaxNode* AElseStmt, unsigned ADepth):
		NodeExprStmt(AExpr, ntIfStmt, ADepth),
      thenStmt(AThenStmt),
      elseStmt(AElseStmt)
{}

void NodeIfStmt::PrintNode(int d)
{
	expr->PrintNode(d + 2);
	SyntaxNode::PrintText(d + 1, "expr");
	cout << endl;
	SyntaxNode::PrintText(d, "if block");
	cout << endl;
	SyntaxNode::PrintText(d + 1, "then");
	if (thenStmt != nullptr) {
		thenStmt->PrintNode(d + 2);
	}
	if (elseStmt != nullptr) {
		SyntaxNode::PrintText(d + 1, "else");
		cout << endl;
		elseStmt->PrintNode(d + 2);
	}
}

void NodeIfStmt::Generate(AsmCode& asmCode)
{
   expr->Generate(asmCode);
   bool hasElse = elseStmt != nullptr;
   AsmStrImmediate* endIfLbl = asmCode.GenLabel("endif");
   AsmStrImmediate* elseLbl  = hasElse ? asmCode.GenLabel("else") : nullptr;
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(MOV, EBX, 0);
   asmCode.AddCmd(CMP, EAX, EBX);
   asmCode.AddCmd(JE, hasElse ? elseLbl : endIfLbl);
   thenStmt->Generate(asmCode);
   if (hasElse) {
      asmCode.AddCmd(JMP, endIfLbl);
      asmCode.AddLabel(elseLbl);
      elseStmt->Generate(asmCode);
      asmCode.AddCmd(JMP, endIfLbl);
   }
   asmCode.AddLabel(endIfLbl);
}

void NodeLoopStmtBase::GenerateLoopLabels(AsmCode& asmCode)
{
   breakLabel = asmCode.GenLabel("lend");
   continueLabel = asmCode.GenLabel("lcontinue");
}

AsmStrImmediate* NodeLoopStmtBase::GetBreakLabel() const
{
   return breakLabel;
}

AsmStrImmediate* NodeLoopStmtBase::GetContinueLabel() const
{
   return continueLabel;
}

NodeWhileStmt::NodeWhileStmt(NodeExpr* AExpr, unsigned ADepth):
   NodeExprStmt(AExpr, ntWhileStmt, ADepth)
{}

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

void NodeWhileStmt::Generate(AsmCode& asmCode)
{
   GenerateLoopLabels(asmCode);
   asmCode.AddLabel(continueLabel);
   expr->Generate(asmCode);
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(MOV, EBX, 0);
   asmCode.AddCmd(CMP, EAX, EBX);
   asmCode.AddCmd(JE, breakLabel);
   stmt->Generate(asmCode);
   asmCode.AddCmd(JMP, continueLabel);
   asmCode.AddLabel(breakLabel);
}

NodeRepeateStmt::NodeRepeateStmt(unsigned ADepth):
   NodeExprStmt(nullptr, ntRepeateStmt, ADepth)
{}

void NodeRepeateStmt::SetLoopInfo(NodeBlock* AStmtSeq, NodeExpr* AExpr)
{
	expr = AExpr;
	stmtSeq = AStmtSeq;
}

void NodeRepeateStmt::PrintNode(int d)
{
	stmtSeq->PrintNode(d + 1);
	cout << endl;
	SyntaxNode::PrintText(d, "repeate block");
	cout << endl;
	SyntaxNode::PrintText(d + 1, "until");
	expr->PrintNode(d + 2);
}

void NodeRepeateStmt::Generate(AsmCode& asmCode)
{
   GenerateLoopLabels(asmCode);
   asmCode.AddLabel(continueLabel);
   stmtSeq->Generate(asmCode);
   expr->Generate(asmCode);
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(MOV, EBX, 0);
   asmCode.AddCmd(CMP, EAX, EBX);
   asmCode.AddCmd(JE, continueLabel);
   asmCode.AddCmd(JMP, breakLabel);
   asmCode.AddLabel(breakLabel);
}

NodeForStmt::NodeForStmt(Symbol* AVar, NodeExpr* AInitialExpr, NodeExpr* AFinalExpr, LoopForType AType, unsigned ADepth):
	NodeStmt(ntForStmt, ADepth),
   var(AVar),
   initialExpr(AInitialExpr),
   finalExpr(AFinalExpr),
   loopType(AType)
{}

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

void NodeForStmt::Generate(AsmCode& asmCode)
{   
   initialExpr->Generate(asmCode);
   var->GenerateLValue(asmCode, depth);
   asmCode.AddCmd(POP, EBX);
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(MOV, AsmMemory(EBX), EAX);
   AsmStrImmediate* loopBegin = asmCode.GenLabel("forloop");
   GenerateLoopLabels(asmCode);
   asmCode.AddLabel(loopBegin);
   var->Generate(asmCode, depth);
   finalExpr->Generate(asmCode);
   asmCode.AddCmd(POP, EBX);
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(CMP, EAX, EBX);
   asmCode.AddCmd(loopType == loopTo ? JG : JL, breakLabel);
   stmt->Generate(asmCode);
   asmCode.AddLabel(continueLabel);
   var->GenerateLValue(asmCode, depth);
   asmCode.AddCmd(POP, EAX);
   asmCode.AddCmd(loopType == loopTo ? ADD : SUB, AsmMemory(EAX), 1);
   asmCode.AddCmd(JMP, loopBegin);
   asmCode.AddLabel(breakLabel);
}

bool NodeForStmt::IsForLoop()
{
	return true;
}
