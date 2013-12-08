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
      _isGlobalNamespace(true)
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
   //asmCode.AddCmd(MOV, ESP, EBP);
   symTable->block->Generate(asmCode);
   //asmCode.AddCmd(MOV, EBP, ESP);
   //asmCode.AddCmd(MOV, EAX, 0);
   asmCode.AddCmd(RET);
   asmCode.AddCmd("end main");
   asmCode.Print();
}

void Parser::ParseProgram()
{
	if (isDeclarationParse) {
		ParseBlock("");
	} else {
		string program_name = "main";
		TokenPtr token = GetToken();
		if (*token == Tag::PROGRAM) {
			CheckExpectedToken(Tag::IDENTIFICATOR, false);
			program_name = GetToken()->text;
			CheckExpectedToken(Tag::SEMICOLON);
		} else {
			PutToken(token);
		}
		ParseBlock("program " + program_name);
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
		*rPtr = new NodeInt2Float(*rPtr);
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
	//Symbol* varType = symbol->GetVarType();
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

void Parser::ParseBlock(string name)
{
	ParseDeclarationPart();
	if (!isDeclarationParse) {
		NodeSubroutineBlock* block = new NodeSubroutineBlock;
		symTable->block = block;
		block->AddBody(ParseCompoundStatement(name));
	}
}

void Parser::ParseDeclarationPart()
{
	DeclarationParseList::iterator it;
	TokenPtr token = GetToken();
	while ((it = declParseList.find(token->tag)) != declParseList.end()) {
		(this->*(it->second))();
		token = GetToken();
	}
	PutToken(token);
}


void Parser::ParseConstantDefinition()
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

void Parser::ParseTypeDefinition()
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

void Parser::ParseProcedureDefinition()
{
	string name = GetSubroutineName();
	CheckNameForUnique(name);
	SymProcedure* proc = new SymProcedure(name);
	symTable->Add(proc);
	SymTable* params = ParseFormalParameterList();
	CheckExpectedToken(Tag::SEMICOLON);
	proc->SetParams(params);
	proc->SetVars(ParseProcFuncBlock(params, name));
}

void Parser::ParseFunctionDefinition()
{
	string name = GetSubroutineName();
	CheckNameForUnique(name);
	SymFunction* func = new SymFunction(name);
	symTable->Add(func);
	SymTable* params = ParseFormalParameterList();
	CheckExpectedToken(Tag::COLON);
	Symbol* resultType = ParseType();
	CheckExpectedToken(Tag::SEMICOLON);
	func->SetParams(params, resultType);
	func->SetVars(ParseProcFuncBlock(params, name, resultType));
}

void Parser::ParseVariableDeclaration()
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
            symTable->Add(new SymVarLocal(type, symTable->GetSize()), id.name);
         }
		}
	}
}

void Parser::ParseStatementSequence(NodeBlock* block)
{
	TokenPtr token(nullptr);
	do {
		block->AddStatement(ParseStatement());
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
					ComputeConstantExpression(dynamic_cast<NodeBinaryOp*>(node)->left, line),
					ComputeConstantExpression(dynamic_cast<NodeBinaryOp*>(node)->right, line));
	} else if (*node == ntNumber) {
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

Args Parser::ParseFuncArgs()
{
	Args result;
	TokenPtr token = GetToken();
	int tag = token->tag;
	PutToken(token);
	if (tag != Tag::RPARENTHESIS) {
		result = ParseCommaSeparated();
	}
	return result;
}

Args Parser::ParseCommaSeparated()
{
	Args result;
	TokenPtr token;
	 do {
		result.push_back(ParseExpression(0));
		token = GetToken();
	} while (*token == Tag::COMMA);
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

Symbol* Parser::CreateConstExprSymbol(NodeExpr* node, int line)
{
	double value = ComputeConstantExpression(node, line);
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
	return CreateConstExprSymbol(ParseExpression(), _line);
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
		arry->SetElementType(ParseType());
	} else {
		result->SetElementType(ParseType());
	}
	return result;
}

Symbol* Parser::ParseRecordDeclaration()
{
	symTable = new SymTable();
	tableStack.Add(symTable);
	ParseVariableDeclaration();
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

SymTable* Parser::ParseFormalParameterList()
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
				symArgs->Add(new SymVarParam(type), id.name);
			} else {
				symArgs->Add(new SymParam(type), id.name);
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

SymTable* Parser::ParseProcFuncBlock(SymTable* params, string& name, Symbol* resultType)
{
	symTable = new SymTable();
	tableStack.Add(symTable);
	for (auto &symbol: params->symbols) {
		symTable->Add(symbol);
	}
	if (resultType != nullptr) {
      symTable->Add(new SymVarLocal(SymbolPtr(resultType), symTable->GetSize()), "result");
	}
   _isGlobalNamespace = false;
	ParseBlock(name);
   _isGlobalNamespace = true;
	if (!isDeclarationParse) {
		CheckExpectedToken(Tag::SEMICOLON);
	}
	SymTable* result = tableStack.Top();
	tableStack.Pop();
	symTable = tableStack.Top();
	for (auto &symbol: params->symbols) {
		result->Delete(symbol->name);
	}
	return result;
}

NodeExpr* Parser::ParseExpression(int priority)
{
	if (priority == PRIORITIES_NUMBER - 1) return ParseFactor();
	NodeExpr* result = ParseExpression(priority + 1);
	TokenPtr token = GetToken();
	while (CheckPriorityByTag(priority, token->tag)) {
		result = new NodeBinaryOp(token, result, ParseExpression(priority + 1));
		token = GetToken();
	}
	if (!token->isEndOfFile()) {
		PutToken(token);
	}
	return result;
}
	
NodeExpr* Parser::ParseFactor()
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
		result = new NodeUnaryOp(tmp_token, ParseFactor());
	} else if (*token == ttIntegerNumber || *token == ttRealNumber) {
		result = new NodeNumber(token);
	} else if (*token == ttCharacterString) {
		result = new NodeCharacterString(token);
	} else if (*token == Tag::LPARENTHESIS) {
		result = ParseExpression(0);
		CheckExpectedToken(Tag::RPARENTHESIS);
	} else if (*token == ttIdentificator) {
		result = ParseIdentifier(token);
	} else if (*token == ttKeyWord && (*token == Tag::ORD || *token == Tag::CHR)) {
		CheckExpectedToken(Tag::LPARENTHESIS);
		NodeExpr* arg = ParseExpression();
		CheckExpectedToken(Tag::RPARENTHESIS);
		if (*token == Tag::ORD) {
			CheckExpectedExpressionType(arg->GetType(), stTypeChar);
			result = new NodeOrd(token, arg);
		} else if (*token == Tag::CHR) {
			CheckExpectedExpressionType(arg->GetType(), stTypeInteger);
			result = new NodeChr(token, arg);
		}
	} else {
		throw IllegalExprException(scanner.fname, _line);
	}
	return result;
}

NodeExpr* Parser::ParseIdentifier(TokenPtr token, bool isLookAhead, bool findInCurTable)
{
	token = token == nullptr ? GetToken() : token;
	Symbol* symbol = FindSymbolByName(token->text, findInCurTable);
	if (symbol == nullptr) {
		throw IdentifierNotFoundException(scanner.fname, token->text, _line);
	}
	if (symbol->IsType()) {
		throw SimpleException(scanner.fname, _line, "Variable identifier expected");
	}
	NodeExpr* result = new NodeVar(token, symbol);
	while (isLookAhead) {
		token = GetToken();
		if (*token == Tag::LPARENTHESIS) {
			CheckExpectedSubroutineType(result->GetType());
			result = CreateCallNode(result, ParseFuncArgs());
			CheckExpectedToken(Tag::RPARENTHESIS);
		} else if (*token == Tag::LBRACKET) {
			CheckExpectedVarType(result->GetType(), stTypeArray);
			result = CreateArrIdxNode(result, ParseCommaSeparated());
			CheckExpectedToken(Tag::RBRACKET);
		} else if (*token == Tag::DOT) {
			CheckExpectedVarType(result->GetType(), stTypeRecord);
			CheckExpectedToken(Tag::IDENTIFICATOR, false);
			SymTable* tmpTable = symTable;
			symTable = dynamic_cast<SymTypeRecord*>(result->GetType())->GetFields();
			result =	new NodeRecordAccess(token, result, ParseIdentifier(nullptr, false, true));
			symTable = tmpTable;
		} else {
			PutToken(token);
			isLookAhead = false;
		}
	}
	return result;
}

SyntaxNode* Parser::ParseStatement()
{
	TokenPtr token = GetToken();
	SyntaxNode* statement(nullptr);
	if (*token == Tag::BEGIN) {
		PutToken(token);
		statement = ParseCompoundStatement("inner block");
   } else if (*token == Tag::WRITE || *token == Tag::WRITELN) {
      statement = CreateWriteNode(token);
	} else if (*token == Tag::IF) {
		statement = ParseIfStatement();
	} else if (*token == Tag::WHILE) {
		statement = ParseWhileStatement();
	} else if (*token == Tag::FOR) {
		statement = ParseForStatement();
	} else if (*token == Tag::REPEAT) {
		statement = ParseRepeatStatement();
	} else if (*token == Tag::EXIT) {
		statement = new NodeExitStmt(symTable->block);
	} else if (*token == Tag::BREAK || *token == Tag::CONTINUE) {
		statement = ParseJumpStatement(token);
	} else if (*token != ttKeyWord && *token != ttEndOfFile) {
		PutToken(token);
		NodeExpr* stmt = ParseExpression(0);
		if (CheckNextTokenTag(Tag::ASSIGNMENT)) {
			if (!stmt->IsLValue()) {
				throw SimpleException(scanner.fname, _line, "Argument can't be assigned to");
			}
			token = GetToken();
			statement = CreateAssignmentStatement(token, stmt, ParseExpression(0));
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

NodeBlock* Parser::ParseCompoundStatement(string name)
{
	NodeBlock* result = new NodeBlock(name);
	CheckExpectedToken(Tag::BEGIN);
	ParseStatementSequence(result);
	CheckExpectedToken(Tag::END);
	return result;
}

SyntaxNode* Parser::ParseIfStatement()
{
	NodeExpr* expr = ParseExpression(0);
	CheckExpectedToken(Tag::THEN);
	SyntaxNode* then_stmt = ParseStatement();
	SyntaxNode* else_stmt(nullptr);
	if (CheckNextTokenTag(Tag::ELSE)) {
		GetToken();
		else_stmt = ParseStatement();
	}
	return new NodeIfStmt(expr, then_stmt, else_stmt);
}

SyntaxNode* Parser::ParseWhileStatement()
{
	NodeWhileStmt* whileStmt = new NodeWhileStmt(ParseExpression(0));
	loopStack.push_back(whileStmt);
	CheckExpectedToken(Tag::DO);
	whileStmt->SetStatement(ParseStatement());
	loopStack.pop_back();
	return whileStmt;
}

SyntaxNode* Parser::ParseForStatement()
{
	CheckExpectedToken(Tag::IDENTIFICATOR, false);
	TokenPtr token = GetToken();
	Symbol* var = FindSymbolByName(token->text);
	if (var == nullptr) {
		throw IdentifierNotFoundException(scanner.fname, token->text, _line);
	}
	if ((*var != stVar && *var != stVarLocal) || *(var->GetType()) != stTypeInteger) {
		throw SimpleException(scanner.fname, _line, "Integer variable identifier expected");
	}
	CheckVariableForLoopUsage(var);
	CheckExpectedToken(Tag::ASSIGNMENT);
	NodeExpr* initialExpr = ParseExpression(0);
	token = GetToken();
	if (*token != Tag::TO && *token != Tag::DOWNTO) {
		throw SyntaxException(scanner.fname, token->text, _line, token->tag);	
	}
	LoopForType type = *token == Tag::TO ? loopTo : loopDownto;
	NodeExpr* finalExpr = ParseExpression(0);
	CheckExpectedExpressionType(initialExpr->GetType(), stTypeInteger);
	CheckExpectedExpressionType(finalExpr->GetType(), stTypeInteger);
	CheckExpectedToken(Tag::DO);
	NodeForStmt* forStmt = new NodeForStmt(var, initialExpr, finalExpr, type);
	loopStack.push_back(forStmt);
	forStmt->SetStatement(ParseStatement());
	loopStack.pop_back();
	return forStmt;
}

SyntaxNode* Parser::ParseRepeatStatement()
{
	NodeRepeateStmt* repeateStmt = new NodeRepeateStmt;
	loopStack.push_back(repeateStmt);
	NodeBlock* stmt_seq = new NodeBlock("repeate");
	ParseStatementSequence(stmt_seq);
	CheckExpectedToken(Tag::UNTIL);
	repeateStmt->SetLoopInfo(stmt_seq, ParseExpression(0));
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

NodeCall* Parser::CreateCallNode(NodeExpr* name, Args args)
{
	SymSubroutine* symbol = dynamic_cast<SymSubroutine*>(FindSymbolByName(name->token->text));
	SymTable* params = symbol->GetParams();
	if (args.size() != params->Size()) {
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
		} else {
			DoRight2LeftSimpleTypecast(paramType, &args[i]);
			Symbol* argType = args[i]->GetType();
			if (!paramType->IsEqualType(argType)) {
				throw IncompatibleTypeArgException(scanner.fname, _line, i + 1, paramType->symType);
			}
		}
	}
	SymFunction* symFunc = dynamic_cast<SymFunction*>(symbol);
	return new NodeCall(name, args, symFunc != nullptr ? symFunc->GetResultType() : nullptr);
}

NodeArrIdx* Parser::CreateArrIdxNode(NodeExpr* name, Args args)
{
	for (auto &arg: args) {
		Symbol* type = arg->GetType();
		if (*type != stTypeInteger) {
			throw IncompatibleTypesException(scanner.fname, _line, stTypeInteger);
		}
	}
	return new NodeArrIdx(name, args);
}

NodeWriteBase* Parser::CreateWriteNode(TokenPtr token)
{
   CheckExpectedToken(Tag::LPARENTHESIS);
   Args args = ParseCommaSeparated();
   for (auto &arg : args) {
      bool isPossibleType = false;
      for (auto type : {stTypeChar, stConstCharacterString, stTypeInteger, stTypeFloat}) {
         isPossibleType = isPossibleType || *(GetReferenceType(arg->GetType())) == type;
      }
      if (!isPossibleType) {
         throw SimpleException(scanner.fname, _line, "Can't read or write variables of this type");
      }
   }
   CheckExpectedToken(Tag::RPARENTHESIS);
   return
      *token == Tag::WRITE
      ? (NodeWriteBase*) new NodeWrite(args)
      : (NodeWriteBase*) new NodeWriteln(args);
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