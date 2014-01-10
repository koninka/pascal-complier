#include <iostream>
#include <cmath>
#include "parser.h"
#include "error.h"

double getFrac(double value)
{
	return value - (value >= 0 ? floor(value) : ceil(value));
}

Parser::Parser(const Scanner& AScanner): scanner(AScanner), _priorities(PRIORITIES_NUMBER),
		symTable(new SymTable),
      tableStack(SymTableStack()),
      _isGlobalNamespace(true),
      _isConstantParsing(false),
      isOptimize(false),
      isDeclarationParse(false)
{
	symTable->Add(typeChar);
	symTable->Add(typeFloat);
	symTable->Add(typeInteger);
	
	tableStack.Add(symTable);

	ReserveOperationPriority(ptHighest, Tag::ADDITION);
	ReserveOperationPriority(ptHighest, Tag::SUBTRACTION);
	ReserveOperationPriority(ptHighest, Tag::NEGATION);

	ReserveOperationPriority(ptSecond,  Tag::MULTIPLICATION);
	ReserveOperationPriority(ptSecond,  Tag::DIVISION);
	ReserveOperationPriority(ptSecond,  Tag::DIV);
	ReserveOperationPriority(ptSecond,  Tag::MOD);
	ReserveOperationPriority(ptSecond,  Tag::AND);
	ReserveOperationPriority(ptSecond,  Tag::SHL);
	ReserveOperationPriority(ptSecond,  Tag::SHR);

	ReserveOperationPriority(ptThird,   Tag::ADDITION);
	ReserveOperationPriority(ptThird,   Tag::SUBTRACTION);
	ReserveOperationPriority(ptThird,   Tag::OR);
	ReserveOperationPriority(ptThird,   Tag::XOR);

	ReserveOperationPriority(ptLowest,  Tag::EQ);
	ReserveOperationPriority(ptLowest,  Tag::NE);
	ReserveOperationPriority(ptLowest,  Tag::LT);
	ReserveOperationPriority(ptLowest,  Tag::GT);
	ReserveOperationPriority(ptLowest,  Tag::LE);
	ReserveOperationPriority(ptLowest,  Tag::GE);

	declParseList.insert(make_pair(Tag::CONST,	  &Parser::ParseConstantDefinition));
	declParseList.insert(make_pair(Tag::TYPE,		  &Parser::ParseTypeDefinition));
	declParseList.insert(make_pair(Tag::VAR,		  &Parser::ParseVariableDeclaration));
	declParseList.insert(make_pair(Tag::PROCEDURE, &Parser::ParseProcedureDefinition));
	declParseList.insert(make_pair(Tag::FUNTCTION, &Parser::ParseFunctionDefinition));

	computable_unary_op.insert(make_pair(Tag::ADDITION,	 &Parser::ComputeUnaryAddition));
	computable_unary_op.insert(make_pair(Tag::SUBTRACTION, &Parser::ComputeUnarySubtraction));
	computable_unary_op.insert(make_pair(Tag::NEGATION,	 &Parser::ComputeUnaryNeagtion));

	computable_binary_op.insert(make_pair(Tag::MULTIPLICATION, &Parser::ComputeBinaryMultiplication));
	computable_binary_op.insert(make_pair(Tag::DIVISION,		  &Parser::ComputeBinaryDivision));
	computable_binary_op.insert(make_pair(Tag::DIV,				  &Parser::ComputeBinaryDiv));
	computable_binary_op.insert(make_pair(Tag::MOD,				  &Parser::ComputeBinaryMod));
	computable_binary_op.insert(make_pair(Tag::AND,				  &Parser::ComputeBinaryAnd));
	computable_binary_op.insert(make_pair(Tag::SHL,				  &Parser::ComputeBinaryShl));
	computable_binary_op.insert(make_pair(Tag::SHR,				  &Parser::ComputeBinaryShr));
	computable_binary_op.insert(make_pair(Tag::ADDITION,		  &Parser::ComputeBinaryAddition));
	computable_binary_op.insert(make_pair(Tag::SUBTRACTION,	  &Parser::ComputeBinarySubtraction));
	computable_binary_op.insert(make_pair(Tag::OR,				  &Parser::ComputeBinaryOr));
	computable_binary_op.insert(make_pair(Tag::XOR,				  &Parser::ComputeBinaryXor));
	computable_binary_op.insert(make_pair(Tag::EQ,				  &Parser::ComputeBinaryEq));
	computable_binary_op.insert(make_pair(Tag::NE,				  &Parser::ComputeBinaryNe));
	computable_binary_op.insert(make_pair(Tag::LT,				  &Parser::ComputeBinaryLt));
	computable_binary_op.insert(make_pair(Tag::GT,				  &Parser::ComputeBinaryGt));
	computable_binary_op.insert(make_pair(Tag::LE,				  &Parser::ComputeBinaryLe));
	computable_binary_op.insert(make_pair(Tag::GE,				  &Parser::ComputeBinaryGe));
}

void Parser::Generate()
{
   symTable->GenerateDeclarations(asmCode);
   asmCode.AddCmd("main:");
   asmCode.AddCmd(MOV, EBP, ESP);
   symTable->block->Generate(asmCode);
   asmCode.AddCmd(MOV, ESP, EBP);
   asmCode.AddCmd(MOV, EAX, 0);
   asmCode.AddCmd(RET);
   if (isOptimize) {
      //asmCode.AddCmd(MOV, EBX, EBP);
      //asmCode.AddCmd(ADD, EBX, 12);
      //asmCode.AddCmd(PUSH, AsmMemory(EBX));
      //asmCode.AddCmd(MOV, EBX, EBP);
      //asmCode.AddCmd(MOV, EBX, AsmMemory(EBX, 8));
      //asmCode.AddCmd(ADD, EBX, 12);
      //asmCode.AddCmd(PUSH, EBX);
      //mov   ebx, dword ptr - 25
      //lea   eax, v_r
      //mov[eax], ebx
      //lea   eax, v_r
      //push  dword ptr[eax]
      Optimizator optimizator;
      optimizator.Optimize(asmCode);
   }
   asmCode.AddCmd("end main");
   asmCode.Print();
}

void Parser::ParseProgram()
{
	if (isDeclarationParse) {
		ParseBlock();
	} else {
		string programName = "main";
		TokenPtr token = GetToken();
		if (*token == Tag::PROGRAM) {
			CheckExpectedToken(Tag::IDENTIFICATOR, false);
			programName = GetToken()->text;
			CheckExpectedToken(Tag::SEMICOLON);
		} else {
			PutToken(token);
		}
		ParseBlock("program " + programName);
		CheckExpectedToken(Tag::DOT);
	}
}

void Parser::PrintTree()
{
 	if (root != nullptr) root->PrintNode(0);
}

void Parser::PrintBlock()
{
	symTable->PrintBlock(0);
}

void Parser::PrintSymTable()
{
	symTable->Print(0);
}

void Parser::DoRight2LeftSimpleTypecast(Symbol* ltype, NodeExpr** rPtr)
{
	Symbol* rtype = (*rPtr)->GetType();
	if (*ltype == stTypeFloat && rtype != nullptr && *rtype == stTypeInteger) {
		*rPtr = new NodeRealTypecast(*rPtr);
	}
}

void Parser::PutToken(const TokenPtr token)
{
	tokens.push(token);
}

void Parser::CheckNameForUnique(string& name, int line)
{
	if (symTable->FindSymbol(name)) {
		throw DuplicateException(scanner.fname, name, line == -1 ? _line : line);
	}
}

void Parser::CheckExpectedToken(Tag::identificators tag, bool isResetToken)
{
	TokenPtr token = GetToken();
	int tok_tag = token->tag;
	string value = token->getValue();
	if (isResetToken) {
		token.reset();
	} else {
		PutToken(token);
	}
   if (tok_tag != tag) {
      throw SyntaxException(scanner.fname, value, _line, tag);
   }
}

void Parser::CheckExpectedType(Symbol* symbol, SymbolType type)
{
	if (*symbol != type) {
		throw TypeDefinitionException(scanner.fname, _line);
	}
}

void Parser::CheckExpectedVarType(Symbol* symbol, SymbolType type)
{
	if (symbol != nullptr && *symbol != type) {
		throw IllegalExprException(scanner.fname, _line);
	}
}

void Parser::CheckExpectedExpressionType(Symbol* symbol, SymbolType type)
	{
	if (symbol != nullptr && *symbol != type) {
		throw IncompatibleTypesException(scanner.fname, _line, type);
	}
}

void Parser::CheckExpectedSubroutineType(Symbol* symbol)
{
	if (*symbol != stProcedure && *symbol != stFunction) {
		throw IllegalExprException(scanner.fname, _line);
	}
}

void Parser::CheckVariableForLoopUsage(Symbol* symbol)
{
	if (symbol != nullptr && *(symbol->GetType()) == stTypeInteger) {
		bool isLoopVar = false;
		for (auto i = loopStack.cbegin(); i != loopStack.cend() && !isLoopVar; i++) {
			if ((*i)->IsForLoop()) {
				isLoopVar = symbol->name == dynamic_cast<NodeForStmt*>(*i)->var->name;
			}
		}
		if (isLoopVar) {
			string s("Illegal assignment to variable " + symbol->name);
			throw SimpleException(scanner.fname, _line, s.c_str());
		}
	}
}

void Parser::CheckSubrangeBoundType(Symbol* symbol, int line)
{
	if (*symbol != stConstInteger) {
		throw TypeDefinitionException(scanner.fname, line);
	}
}

void Parser::ReserveOperationPriority(priorityType type, int tag)
{
	_priorities[type].push_back(tag);
}

void Parser::ParseBlock(string name, unsigned depth)
{
	ParseDeclarationPart(depth);
	if (!isDeclarationParse) {
		NodeSubroutineBlock* block = new NodeSubroutineBlock;
		symTable->block = block;
		block->AddBody(ParseCompoundStatement(name, depth));
	}
}

void Parser::ParseDeclarationPart(unsigned depth)
{
	DeclarationParseList::iterator it;
	TokenPtr token = GetToken();
	while ((it = declParseList.find(token->tag)) != declParseList.end()) {
		(this->*(it->second))(depth);
		token = GetToken();
	}
	PutToken(token);
}


void Parser::ParseConstantDefinition(unsigned depth)
{
	CheckExpectedToken(Tag::IDENTIFICATOR, false);
	while (CheckNextTokenTag(Tag::IDENTIFICATOR)) {
		TokenPtr token = GetToken();
		CheckNameForUnique(token->text);
		CheckExpectedToken(Tag::EQ);
		symTable->Add(ParseConstantExpression(), token->text);
		CheckExpectedToken(Tag::SEMICOLON);
	}
}

void Parser::ParseTypeDefinition(unsigned depth)
{
	CheckExpectedToken(Tag::IDENTIFICATOR, false);
	while (CheckNextTokenTag(Tag::IDENTIFICATOR)) {
		TokenPtr token = GetToken();
		CheckNameForUnique(token->text);
		CheckExpectedToken(Tag::EQ);
		Symbol* type = GetReferenceType(ParseType());
		symTable->Add(new SymTypeAlias(type), token->text);
		CheckExpectedToken(Tag::SEMICOLON);
	}
}

void Parser::ParseProcedureDefinition(unsigned depth)
{
	string name = GetSubroutineName();
	CheckNameForUnique(name);
	SymProcedure* proc = new SymProcedure(name);
   proc->GenerateLabel(asmCode);
	symTable->Add(proc);
   _isGlobalNamespace = false;
	SymTable* params = ParseFormalParameterList(proc, depth + 1);
	CheckExpectedToken(Tag::SEMICOLON);
	proc->SetParams(params);
	proc->SetVars(ParseProcFuncBlock(params, name, depth + 1));
   _isGlobalNamespace = true;
}

void Parser::ParseFunctionDefinition(unsigned depth)
{
	string name = GetSubroutineName();
	CheckNameForUnique(name);
	SymFunction* func = new SymFunction(name);
   func->GenerateLabel(asmCode);
	symTable->Add(func);
   _isGlobalNamespace = false;
	SymTable* params = ParseFormalParameterList(func, depth + 1);
	CheckExpectedToken(Tag::COLON);
	Symbol* resultType = ParseType();
	CheckExpectedToken(Tag::SEMICOLON);
   params->Add(new SymParamResult(SymbolPtr(resultType), params->GetSize(), func, depth + 1), "result");
	func->SetParams(params, resultType);
	func->SetVars(ParseProcFuncBlock(params, name, depth + 1));
   _isGlobalNamespace = true;
}

void Parser::ParseVariableDeclaration(unsigned depth)
{
	CheckExpectedToken(Tag::IDENTIFICATOR, false);
	while (CheckNextTokenTag(Tag::IDENTIFICATOR)) {
		IdentifierList list = ParseIdentifierList();
		CheckExpectedToken(Tag::COLON);
		SymbolPtr type(ParseType());
		CheckExpectedToken(Tag::SEMICOLON);
		for (auto &id: list) {
			CheckNameForUnique(id.name, id.line);
         if (_isGlobalNamespace) {
            symTable->Add(new SymVarGlobal(type, symTable->GetSize()), id.name);
         } else {
            symTable->Add(new SymVarLocal(type, symTable->GetSize(), depth), id.name);
         }
		}
	}
}

void Parser::ParseStatementSequence(NodeBlock* block, unsigned depth)
{
	TokenPtr token(nullptr);
	do {
		block->AddStatement(ParseStatement(depth));
	} while (*(token = GetToken()) == Tag::SEMICOLON);
	PutToken(token);
}

bool Parser::IsTokenVariable()
{
	return GetToken()->tag == Tag::VAR;
}

bool Parser::CheckPriorityByTag(int priority, int tag)
{
	return find(_priorities[priority].begin(), _priorities[priority].end(), tag) != _priorities[priority].end();
}

bool Parser::CheckNextTokenTag(int tag)
{
	TokenPtr token = GetToken();
	PutToken(token);
	return token->tag == tag;
}

double Parser::ComputeUnaryAddition(double value)
{
	return value;
}

double Parser::ComputeUnarySubtraction(double value)
{
	return -value;
}
double Parser::ComputeUnaryNeagtion(double value)
{
	if (getFrac(value)) {
		throw IncompatibleTypesException(scanner.fname, -1, stTypeFloat);
	}
	return ~int(value);
}

double Parser::ComputeBinaryMultiplication(double lval, double rval)
{
	return lval * rval;
}

double Parser::ComputeBinaryDivision(double lval, double rval)
{
	return lval / rval;
}

double Parser::ComputeBinaryDiv(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw IncompatibleTypesException(scanner.fname, -1, stTypeFloat);
	}
	return int(lval) / int(rval);
}

double Parser::ComputeBinaryMod(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw IncompatibleTypesException(scanner.fname, -1, stTypeFloat);
	}
	return int(lval) % int(rval);
}

double Parser::ComputeBinaryAnd(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw OperatorException(scanner.fname, "and", -1, optAnd);
	}
	return int(lval) & int(rval);
}

double Parser::ComputeBinaryShl(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw IncompatibleTypesException(scanner.fname, -1, stTypeFloat);
	}
	return int(lval) << int(rval);
}

double Parser::ComputeBinaryShr(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw IncompatibleTypesException(scanner.fname, -1, stTypeFloat);
	}
	return int(lval) >> int(rval);
}

double Parser::ComputeBinaryAddition(double lval, double rval)
{
	return lval + rval;
}

double Parser::ComputeBinarySubtraction(double lval, double rval)
{
	return lval - rval;
}

double Parser::ComputeBinaryOr(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw OperatorException(scanner.fname, "or", -1, optOr);
	}
	return int(lval) | int(rval);
}
	
double Parser::ComputeBinaryXor(double lval, double rval)
{
	if (getFrac(lval) != 0 || getFrac(rval) != 0) {
		throw OperatorException(scanner.fname, "xor", -1, optXor);
	}
	return int(lval) ^ int(rval);	
}

double Parser::ComputeBinaryEq(double lval, double rval)
{
	return lval == rval;
}

double Parser::ComputeBinaryNe(double lval, double rval)
{
	return lval != rval;
}

double Parser::ComputeBinaryLt(double lval, double rval)
{
	return lval < rval;
}

double Parser::ComputeBinaryGt(double lval, double rval)
{
	return lval > rval;
}

double Parser::ComputeBinaryLe(double lval, double rval)
{
	return lval <= rval;
}

double Parser::ComputeBinaryGe(double lval, double rval)
{
	return lval >= rval;
}

double Parser::ComputeConstantExpression(NodeExpr* node, int line)
{
	if (*node == ntCall || *node == ntRecordAccess || *node == ntArrIdx || *node == ntCharacterString) {
		throw IllegalExprException(scanner.fname, line);
	}
	double result;
	if (*node == ntUnaryOp) {
		auto it = computable_unary_op.find(node->token->tag);
		result = (this->*(it->second))(ComputeConstantExpression(dynamic_cast<NodeUnaryOp*>(node)->arg, line));
	} else if (*node == ntBinaryOp) {
		auto it = computable_binary_op.find(node->token->tag);
		result = (this->*(it->second))(
					ComputeConstantExpression(dynamic_cast<NodeBinaryOp*>(node)->GetLeft(), line),
					ComputeConstantExpression(dynamic_cast<NodeBinaryOp*>(node)->GetRight(), line));
	} else if (*node == ntRealNumber || *node == ntIntegerNumber) {
		result =
			*(node->token) == ttIntegerNumber
			? castToken<IntegerNumber>(node->token)->value
			: castToken<RealNumber>(node->token)->value;
	} else if (*node == ntVar) {
		Symbol* sym = FindSymbolByName(node->token->text);
		if (sym == nullptr) {
			throw IdentifierNotFoundException(scanner.fname, node->token->text, _line);
		}
		if (*sym != stConstFloat && *sym != stConstInteger) {
			throw IllegalExprException(scanner.fname, _line);
		}
		result = *sym == stConstInteger ? dynamic_cast<SymConstInteger*>(sym)->getValue() : dynamic_cast<SymConstFloat*>(sym)->getValue();
	}
	return result;
}

TokenPtr Parser::GetToken()
{
	TokenPtr result;
	if (tokens.size() != 0) {
		result = tokens.front();
		tokens.pop();
	} else {
		scanner.Next();
		result = scanner.Get();
	}
	_line = result->line;
	return result;
}

string Parser::GetSubroutineName()
{
	CheckExpectedToken(Tag::IDENTIFICATOR, false);
	return GetToken()->text;
}

Parser::IdentifierList Parser::ParseIdentifierList()
{
	TokenPtr token;
	IdentifierList list;
	do {
		CheckExpectedToken(Tag::IDENTIFICATOR, false);
		token = GetToken();
		list.push_back(Identifier(token->text, token->line));
	} while (*(token = GetToken()) == Tag::COMMA);
	PutToken(token);
	return list;
}

Args Parser::ParseFuncArgs(unsigned depth)
{
	Args result;
   if (!CheckNextTokenTag(Tag::RPARENTHESIS)) {
		result = ParseCommaSeparated(depth);
	}
	return result;
}

Args Parser::ParseCommaSeparated(unsigned depth)
{
	Args result;
	TokenPtr token;
	 do {
		result.push_back(ParseExpression(0, depth));
	} while (*(token = GetToken()) == Tag::COMMA);
	PutToken(token);
	return result;
}
Symbol* Parser::FindSymbolByName(string name, bool findInCurTable)
{
	Symbol* result(nullptr);
	if (symTable->FindSymbol(name)) {
		result = symTable->GetSymbol(name);
	} else if (!findInCurTable && tableStack.FindSymbol(name)) {
		result = tableStack.GetSymbol(name);
	}
	return result;
}

Symbol* Parser::CreateConstExprSymbol(int line)
{
   _isConstantParsing = true;
   NodeExpr* expr = ParseExpression(0, 0);
   _isConstantParsing = false;
	double value = ComputeConstantExpression(expr, line);
	if (getFrac(value) == 0) {
		return new SymConstInteger(int(value));
	} else {
		return new SymConstFloat(value);
	}
}

Symbol* Parser::ParseConstantExpression()
{
	TokenPtr token = GetToken();
	if (*token == ttCharacterString) {
		return new SymConstCharacterString(token->getValue());
	}
	PutToken(token);
	return CreateConstExprSymbol(_line);
}

Symbol* Parser::ParseArrayDeclaration(bool isOpenArray)
{
	SymTypeArry* arry(nullptr);
	SymTypeArry* result(nullptr);
	if (!isOpenArray) {
		CheckExpectedToken(Tag::LBRACKET);
		TokenPtr token;
		do {
			Symbol* subrange = ParseType();
			CheckExpectedType(GetReferenceType(subrange), stTypeSubrange);
			if (arry == nullptr) {
				arry = new SymTypeArray(subrange);
				result = arry;
			} else {
				arry->SetElementType(new SymTypeArray(subrange));
				arry = dynamic_cast<SymTypeArry*>(arry->elemType);
			}
		} while (*(token = GetToken()) == Tag::COMMA);
		PutToken(token);
		CheckExpectedToken(Tag::RBRACKET);
	} else {
		result = new SymTypeOpenArray;
	}
	CheckExpectedToken(Tag::OF);
	if (!isOpenArray) {
		arry->SetElementType(ParseType(isOpenArray));
	} else {
		result->SetElementType(ParseType(isOpenArray));
	}
	return result;
}

Symbol* Parser::ParseRecordDeclaration()
{
	symTable = new SymTable();
	tableStack.Add(symTable);
	ParseVariableDeclaration(0);
	CheckExpectedToken(Tag::END);
	Symbol* result = new SymTypeRecord(tableStack.Top());
	tableStack.Pop();
	symTable = tableStack.Top();
	return result;
}

Symbol* Parser::ParseSubrangeType()
{
	TokenPtr token = GetToken();
	int line = _line;
	PutToken(token);
	try {
		Symbol* lower_bound = ParseConstantExpression();
		CheckSubrangeBoundType(lower_bound, line);
		if (*(token = GetToken()) != Tag::DOUBLE_DOT) {
			throw TypeDefinitionException(scanner.fname, _line);
		}
		Symbol* upper_bound = ParseConstantExpression();
		CheckSubrangeBoundType(upper_bound, line);
		Symbol* symbol = new SymTypeSubrange(
										dynamic_cast<SymConstInteger*>(lower_bound)->getValue(),
										dynamic_cast<SymConstInteger*>(upper_bound)->getValue()
									);
		delete lower_bound;
		delete upper_bound;
		return symbol;
	} catch (IllegalExprException) {
		throw TypeDefinitionException(scanner.fname, line);
	}
}

Symbol* Parser::ParseType(bool isOpenArray)
{
	Symbol* symbol(nullptr);
	TokenPtr token = GetToken();
	if (*token == Tag::IDENTIFICATOR) {
		if ((symbol = FindSymbolByName(token->text)) == nullptr || !symbol->IsType()) {
			PutToken(token);
			symbol = ParseSubrangeType();
		}
	} else if (*token == Tag::ARRAY) {
		symbol = ParseArrayDeclaration(isOpenArray);
	} else if (*token == Tag::RECORD) {
		symbol = ParseRecordDeclaration();
	} else {
		PutToken(token);
		symbol = ParseSubrangeType();
	}
	return symbol;
}

SymTable* Parser::ParseFormalParameterList(SymSubroutine* subroutine, unsigned depth)
{
	CheckExpectedToken(Tag::LPARENTHESIS);
	SymTable* symArgs = new SymTable();
	while (CheckNextTokenTag(Tag::IDENTIFICATOR) || CheckNextTokenTag(Tag::VAR)) {
		bool isVar = false;
		TokenPtr token = GetToken();
		if (*token == Tag::VAR) {
			isVar = true;
		} else {
			PutToken(token);
		}
		IdentifierList list = ParseIdentifierList();
		CheckExpectedToken(Tag::COLON);
		SymbolPtr type = SymbolPtr(ParseType(true));
		if (*type == stTypeRecord) {
			throw SimpleException(scanner.fname, token->line, "Type identifier expected");
		}
		for (auto &id: list) {
			if (isVar) {
				symArgs->Add(new SymVarParam(type, symArgs->GetSize(), subroutine, depth), id.name);
			} else {
            symArgs->Add(new SymParam(type, symArgs->GetSize(), subroutine, depth), id.name);
			}
		}
		if (CheckNextTokenTag(Tag::SEMICOLON)) {
			GetToken();
			bool isVar = CheckNextTokenTag(Tag::VAR);
			if (isVar) {
				token = GetToken();
			}
			CheckExpectedToken(Tag::IDENTIFICATOR, false);
			if (isVar) {
				PutToken(token);
			}
		}
	}
	CheckExpectedToken(Tag::RPARENTHESIS);
	return symArgs;
}

SymTable* Parser::ParseProcFuncBlock(SymTable* params, string& name, unsigned depth)
{
	symTable = new SymTable();
	tableStack.Add(symTable);
	for (auto &symbol: params->symbols) {
		symTable->Add(symbol);
	}
	ParseBlock(name, depth);
	if (!isDeclarationParse) {
		CheckExpectedToken(Tag::SEMICOLON);
	}
	SymTable* result = tableStack.Top();
	tableStack.Pop();
	symTable = tableStack.Top();
	for (auto &symbol: params->symbols) {
		result->DeleteParam(symbol->name);
	}
	return result;
}

NodeExpr* Parser::ParseExpression(int priority, unsigned depth)
{
	if (priority == PRIORITIES_NUMBER - 1) return ParseFactor(depth);
	NodeExpr* result = ParseExpression(priority + 1, depth);
	TokenPtr token = GetToken();
	while (CheckPriorityByTag(priority, token->tag)) {
		result = new NodeBinaryOp(token, result, ParseExpression(priority + 1, depth), depth);
		token = GetToken();
	}
	if (!token->isEndOfFile()) {
		PutToken(token);
	}
	return result;
}
	
NodeExpr* Parser::ParseFactor(unsigned depth)
{
	NodeExpr* result = nullptr;
	TokenPtr token = GetToken();
	if (CheckPriorityByTag(ptHighest, token->tag)) {
		TokenPtr tmp_token = token;
		token = GetToken();
		if (*token == ttOperator && !CheckPriorityByTag(ptHighest, token->tag)) {
			throw CompilerException(scanner.fname, token->line, errorSyntax);
		}
		PutToken(token);
		result = new NodeUnaryOp(tmp_token, ParseFactor(depth), depth);
	} else if (*token == ttIntegerNumber) {
		result = new NodeIntegerNumber(token);
   } else if (*token == ttRealNumber) {
      result = new NodeRealNumber(token);
      if (!_isConstantParsing) {
         dynamic_cast<NodeRealNumber*>(result)->GenerateData(asmCode);
      }
   }  else if (*token == ttCharacterString) {
		result = new NodeCharacterString(token, depth);
   } else if (*token == Tag::IDENTIFICATOR && token->text == "integer") {
      CheckExpectedToken(Tag::LPARENTHESIS);
      result = new NodeIntegerTypecast(ParseExpression(0, depth));
      Symbol* exprType = dynamic_cast<NodeIntegerTypecast*>(result)->arg->GetType();
      if (*exprType != stTypeChar && *exprType != stTypeFloat && *exprType != stTypeInteger) {
         throw IllegalTypeConversionException(scanner.fname, _line);
      }
      CheckExpectedToken(Tag::RPARENTHESIS);
   } else if (*token == Tag::LPARENTHESIS) {
		result = ParseExpression(0, depth);
		CheckExpectedToken(Tag::RPARENTHESIS);
	} else if (*token == ttIdentificator) {
		result = ParseIdentifier(token, depth);
	} else if (*token == ttKeyWord && (*token == Tag::ORD || *token == Tag::CHR)) {
		CheckExpectedToken(Tag::LPARENTHESIS);
		NodeExpr* arg = ParseExpression(0, depth);
		CheckExpectedToken(Tag::RPARENTHESIS);
		if (*token == Tag::ORD) {
			CheckExpectedExpressionType(arg->GetType(), stTypeChar);
			result = new NodeOrd(token, arg, depth);
		} else if (*token == Tag::CHR) {
			CheckExpectedExpressionType(arg->GetType(), stTypeInteger);
			result = new NodeChr(token, arg, depth);
		}
	} else {
		throw IllegalExprException(scanner.fname, _line);
	}
	return result;
}

NodeExpr* Parser::ParseIdentifier(TokenPtr token, unsigned depth, bool isLookAhead, bool findInCurTable)
{
	token = token == nullptr ? GetToken() : token;
	Symbol* symbol = FindSymbolByName(token->text, findInCurTable);
	if (symbol == nullptr) {
		throw IdentifierNotFoundException(scanner.fname, token->text, _line);
	}
	if (symbol->IsType()) {
		throw SimpleException(scanner.fname, _line, "Variable identifier expected");
	}
	NodeExpr* result = new NodeVar(token, symbol, depth);
	while (isLookAhead) {
		token = GetToken();
		if (*token == Tag::LPARENTHESIS) {
			CheckExpectedSubroutineType(result->GetType());
			result = CreateCallNode(result, ParseFuncArgs(depth), depth);
			CheckExpectedToken(Tag::RPARENTHESIS);
		} else if (*token == Tag::LBRACKET) {
         Symbol* type = result->GetType();
         if (*type != stTypeArray && *type != stTypeOpenArray) {
            CheckExpectedVarType(result->GetType(), stTypeArray);
         }
			result = CreateArrIdxNode(result, depth);
			CheckExpectedToken(Tag::RBRACKET);
		} else if (*token == Tag::DOT) {
			CheckExpectedVarType(result->GetType(), stTypeRecord);
			CheckExpectedToken(Tag::IDENTIFICATOR, false);
			SymTable* tmpTable = symTable;
			symTable = dynamic_cast<SymTypeRecord*>(result->GetType())->GetFields();
			result =	new NodeRecordAccess(token, result, ParseIdentifier(nullptr, depth, false, true), depth);
			symTable = tmpTable;
		} else {
			PutToken(token);
			isLookAhead = false;
		}
	}
	return result;
}

SyntaxNode* Parser::ParseStatement(unsigned depth)
{
	TokenPtr token = GetToken();
	SyntaxNode* statement(nullptr);
	if (*token == Tag::BEGIN) {
		PutToken(token);
		statement = ParseCompoundStatement("inner block", depth);
   } else if (*token == Tag::WRITE || *token == Tag::WRITELN) {
      statement = CreateWriteNode(token, depth);
	} else if (*token == Tag::IF) {
		statement = ParseIfStatement(depth);
	} else if (*token == Tag::WHILE) {
		statement = ParseWhileStatement(depth);
	} else if (*token == Tag::FOR) {
		statement = ParseForStatement(depth);
	} else if (*token == Tag::REPEAT) {
		statement = ParseRepeatStatement(depth);
	} else if (*token == Tag::EXIT) {
		statement = new NodeExitStmt(symTable->block);
	} else if (*token == Tag::BREAK || *token == Tag::CONTINUE) {
		statement = ParseJumpStatement(token);
	} else if (*token != ttKeyWord && *token != ttEndOfFile) {
		PutToken(token);
		NodeExpr* stmt = ParseExpression(0, depth);
		if (CheckNextTokenTag(Tag::ASSIGNMENT)) {
			if (!stmt->IsLValue()) {
				throw SimpleException(scanner.fname, _line, "Argument can't be assigned to");
			}
			token = GetToken();
			statement = CreateAssignmentStatement(token, stmt, ParseExpression(0, depth));
		} else {
			if (!stmt->IsSubroutineCall()) {
				throw IllegalExprException(scanner.fname, _line);
			}
			statement = stmt;
		}
	} else {
		PutToken(token);
	}
	return statement;
}

NodeBlock* Parser::ParseCompoundStatement(string name, unsigned depth)
{
	NodeBlock* result = new NodeBlock(name);
	CheckExpectedToken(Tag::BEGIN);
	ParseStatementSequence(result, depth);
	CheckExpectedToken(Tag::END);
	return result;
}

SyntaxNode* Parser::ParseIfStatement(unsigned depth)
{
	NodeExpr* expr = ParseExpression(0, depth);
	CheckExpectedToken(Tag::THEN);
	SyntaxNode* thenStmt = ParseStatement(depth);
	SyntaxNode* elseStmt(nullptr);
	if (CheckNextTokenTag(Tag::ELSE)) {
		GetToken();
		elseStmt = ParseStatement(depth);
	}
	return new NodeIfStmt(expr, thenStmt, elseStmt, depth);
}

SyntaxNode* Parser::ParseWhileStatement(unsigned depth)
{
	NodeWhileStmt* whileStmt = new NodeWhileStmt(ParseExpression(0, depth), depth);
	loopStack.push_back(whileStmt);
	CheckExpectedToken(Tag::DO);
	whileStmt->SetStatement(ParseStatement(depth));
	loopStack.pop_back();
	return whileStmt;
}

SyntaxNode* Parser::ParseForStatement(unsigned depth)
{
	CheckExpectedToken(Tag::IDENTIFICATOR, false);
	TokenPtr token = GetToken();
	Symbol* var = FindSymbolByName(token->text);
	if (var == nullptr) {
		throw IdentifierNotFoundException(scanner.fname, token->text, _line);
	}
	if ((*var != stVarGlobal && *var != stVarLocal) || *(var->GetType()) != stTypeInteger) {
		throw SimpleException(scanner.fname, _line, "Integer variable identifier expected");
	}
	CheckVariableForLoopUsage(var);
	CheckExpectedToken(Tag::ASSIGNMENT);
	NodeExpr* initialExpr = ParseExpression(0, depth);
	if (*(token = GetToken()) != Tag::TO && *token != Tag::DOWNTO) {
		throw SyntaxException(scanner.fname, token->text, _line, token->tag);	
	}
	LoopForType type = *token == Tag::TO ? loopTo : loopDownto;
	NodeExpr* finalExpr = ParseExpression(0, depth);
	CheckExpectedExpressionType(initialExpr->GetType(), stTypeInteger);
	CheckExpectedExpressionType(finalExpr->GetType(), stTypeInteger);
	CheckExpectedToken(Tag::DO);
	NodeForStmt* forStmt = new NodeForStmt(var, initialExpr, finalExpr, type, depth);
	loopStack.push_back(forStmt);
	forStmt->SetStatement(ParseStatement(depth));
	loopStack.pop_back();
	return forStmt;
}

SyntaxNode* Parser::ParseRepeatStatement(unsigned depth)
{
	NodeRepeateStmt* repeateStmt = new NodeRepeateStmt(depth);
	loopStack.push_back(repeateStmt);
	NodeBlock* stmtSeq = new NodeBlock("repeate");
	ParseStatementSequence(stmtSeq, depth);
	CheckExpectedToken(Tag::UNTIL);
	repeateStmt->SetLoopInfo(stmtSeq, ParseExpression(0, depth));
	loopStack.pop_back();
	return repeateStmt;
}

SyntaxNode* Parser::ParseJumpStatement(TokenPtr token)
{
	if (loopStack.size() == 0 ) {
		throw JumpNotAllowedException(scanner.fname, token->line, token->tag);
	}
	return
		*token == Tag::BREAK
		? (SyntaxNode*) new NodeBreakStmt(loopStack.back())
		: (SyntaxNode*) new NodeContinueStmt(loopStack.back());
}

NodeCall* Parser::CreateCallNode(NodeExpr* name, Args args, unsigned depth)
{
	SymSubroutine* symbol = dynamic_cast<SymSubroutine*>(FindSymbolByName(name->token->text));
	SymTable* params = symbol->GetParams();
	if (args.size() != params->Size() - (*symbol == stFunction)) {
		throw WrongParametersException(scanner.fname, _line, name->token->text);
	}
	for (size_t i = 0; i < args.size(); i++) {
		Symbol* paramType = params->symbols[i]->GetType();
		if (*(params->symbols[i]) == stVarParam) {
			Symbol* argType   = args[i]->GetType();
			if (*paramType == stTypeOpenArray) {
				if (!paramType->IsEqualType(argType)) {
					throw IncompatibleTypeArgException(scanner.fname, _line, i + 1, paramType->symType, true);
				}
			} else if (*paramType != *argType) {
				throw IncompatibleTypeArgException(scanner.fname, _line, i + 1, paramType->symType, true);
			}
			if (!args[i]->IsLValue()) {
				throw SimpleException(scanner.fname, _line, "Variable identifier expected");
			}
      } else if (*(params->symbols[i]) == stParam) {
			DoRight2LeftSimpleTypecast(paramType, &args[i]);
			Symbol* argType = args[i]->GetType();
			if (!paramType->IsEqualType(argType)) {
				throw IncompatibleTypeArgException(scanner.fname, _line, i + 1, paramType->symType);
			}
		}
	}
	return new NodeCall(name, args, depth);
}

NodeArrIdx* Parser::CreateArrIdxNode(NodeExpr* name, unsigned depth)
{
   Args args = ParseCommaSeparated(depth);
	for (auto &arg: args) {
		Symbol* type = arg->GetType();
		if (*type != stTypeInteger) {
			throw IncompatibleTypesException(scanner.fname, _line, stTypeInteger);
		}
	}
	return new NodeArrIdx(name, args, depth);
}

NodeWriteBase* Parser::CreateWriteNode(TokenPtr token, unsigned depth)
{
   Args args;
   CheckExpectedToken(Tag::LPARENTHESIS);
   if (!CheckNextTokenTag(Tag::RPARENTHESIS)) {
      args = ParseCommaSeparated(depth);
   }
   for (auto &arg : args) {
      bool isPossibleType = false;
      for (auto type : {stTypeChar, stConstCharacterString, stTypeInteger, stTypeFloat}) {
         isPossibleType = isPossibleType || *(GetReferenceType(arg->GetType())) == type;
      }
      if (!isPossibleType) {
         throw SimpleException(scanner.fname, _line, "Can't write variables of this type");
      }
   }
   CheckExpectedToken(Tag::RPARENTHESIS);
   return
      *token == Tag::WRITE
      ? (NodeWriteBase*) new NodeWrite(args, depth)
      : (NodeWriteBase*) new NodeWriteln(args, depth);
}

NodeAssignOp* Parser::CreateAssignmentStatement(TokenPtr token, NodeExpr* stmt, NodeExpr* expr)
{
	NodeAssignOp* result(nullptr);
	if (*stmt == ntVar) {
		CheckVariableForLoopUsage(stmt->GetSymbol());
	}
	Symbol* ltype = stmt->GetType();
	DoRight2LeftSimpleTypecast(ltype, &expr);
	Symbol* rtype = expr->GetType();
	if (ltype->IsEqualType(rtype)) {
		result = new NodeAssignOp(token, stmt, expr);
	} else {
		throw IncompatibleTypesException(scanner.fname, _line, ltype->symType);
	}
	return result;
}