#include <iostream>
#include "symbol_table.h"

using namespace std;

static void printPart(string str, int len)
{
   cout << " " << str;
   int cnt = len - str.length() - 1;
   string tmp(cnt >= 0 ? cnt : 0, ' ');
   cout << tmp;
   int c = tmp.length() + str.length() + 1;
}

SymTable::SymTable():
   block(nullptr),
   symbols(Symbols()),
   symNames(SymbolNames()),
   _tableSize(0)
{}

void SymTable::Add(Symbol* symbol)
{
   _tableSize = symbol->IsVar() ? _tableSize + symbol->GetSize() : _tableSize;
	symbols.push_back(symbol);
	symNames.insert(make_pair(symbol->name, symbols.size() - 1));
}

void SymTable::Add(Symbol* symbol, string name)
{
	symbol->name = name;
	Add(symbol);
}

void SymTable::DeleteParam(string& name)
{
	symNames.erase(symNames.find(name));
	for (auto it = symbols.begin(); it != symbols.end(); it++) {
		if ((*it)->name == name) {
         _tableSize = (*it)->IsVar() ? _tableSize - (*it)->GetSize() : _tableSize;
         for (auto i = it + 1; i != symbols.end(); i++) {
            if (**i == stVarLocal) {
               (*i)->SetOffset((*i)->GetOffset() - (*it)->GetSize());
            }
         }
			symbols.erase(it);
			break;
		}
	}
}

void SymTable::SetBlock(NodeBlock* ABlock, string AName)
{
	block = ABlock;
	dynamic_cast<NodeBlock*>(block)->name = AName;
}

void SymTable::GenerateDeclarations(AsmCode& asmCode) const
{
   for (auto &symbol : symbols) {
      if (*symbol == stVarGlobal) {
         dynamic_cast<SymVarGlobal*>(symbol)->GenerateDeclaration(asmCode);
      } else if (*symbol == stConstFloat) {
         dynamic_cast<SymConstFloat*>(symbol)->GenerateDeclaration(asmCode);
      }
   }
   for (auto &symbol : symbols) {
      if (*symbol == stProcedure || *symbol == stFunction) {
         dynamic_cast<SymSubroutine*>(symbol)->GenerateDeclaration(asmCode);
      }
   }
}

void SymTable::Print(int d)
{
	for (size_t i = 0; i < symbols.size(); i++) {
		symbols[i]->PrintSymbol(d);
		cout << endl;
	}
}

void SymTable::PrintBlock(int d)
{
	for (auto i = symbols.begin(); i != symbols.end(); i++) {
		if ((*i)->symType == stProcedure || (*i)->symType == stFunction) {
			dynamic_cast<SymSubroutine*>(*i)->getLocalVars()->PrintBlock(d + 1);
		}
	}
	block->PrintNode(d);
	cout << endl << endl;
}

bool SymTable::FindSymbol(string& name)
{
	return symNames.find(name) != symNames.end();
}

Symbol* SymTable::GetSymbol(string& name)
{
	auto it = symNames.find(name);
	return symbols[it->second];
}

size_t SymTable::Size() const
{
	return symbols.size();
}

size_t SymTable::GetSize() const
{
   return _tableSize;
}

void SymTableStack::Add(SymTable* table)
{
	tables.push(table);
}

void SymTableStack::Pop()
{
	tables.pop();
}

SymTable* SymTableStack::Top()
{
	return tables.top();
}

SymTable* SymTableStack::GetTop()
{
	SymTable* table = tables.top();
	tables.pop();
	return table;
}

bool SymTableStack::FindSymbol(string& name)
{
	return FindSymbolTable(name) != nullptr;
}


Symbol* SymTableStack::GetSymbol(string& name)
{
	return FindSymbolTable(name)->GetSymbol(name);
}

SymTable* SymTableStack::FindSymbolTable(string& name)
{
	TableStack tmp;
	SymTable* table;
	bool isExist = false;
	do {
		table = tables.top();
		tables.pop();
		tmp.push(table);
		isExist = table->FindSymbol(name); 
	} while(tables.size() != 0 && !isExist);
	SymTable* result = isExist ? table : nullptr;
	while (tmp.size() != 0) {
		tables.push(tmp.top());
		tmp.pop();
	}
	return result;
}

SymTypeRecord::SymTypeRecord(SymTable* AFields): SymType(stTypeRecord), fields(AFields)
{
	name = "record";
}

void SymTypeRecord::PrintType(int d)
{
	cout << endl;
	cout << " record fields:" << endl;
	fields->Print(d + 1);
}

void SymTypeRecord::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("record", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart("", COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
	cout << endl;
	fields->Print(d + 1);
}

SymTable* SymTypeRecord::GetFields() const
{
	return fields;
}

bool SymTypeRecord::IsEqualType(Symbol* symbol)
{
	SymTypeRecord* record = dynamic_cast<SymTypeRecord*>(symbol);
	bool result = record != nullptr && fields->Size() == record->fields->Size();
	if (result) {
		for (size_t i = 0; i < fields->Size() && result; i++) {
			result = result && fields->symbols[i]->GetType()->IsEqualType(record->fields->symbols[i]->GetType());
		}
	}
	return result;
}

size_t SymTypeRecord::GetSize()
{
   return _size = fields->GetSize();
}

SymSubroutine::SymSubroutine(string& AName, SymbolType AType):
   Symbol(AType),
   _label(nullptr)
{
	name = AName;
}

void SymSubroutine::SetParams(SymTable* AParams)
{
	params = AParams;
}

void SymSubroutine::SetVars(SymTable* AVars)
{
	localVariables = AVars;
}

void SymSubroutine::GenerateDeclaration(AsmCode& asmCode)
{
   asmCode.AddSubroutineBegin(_label);
   asmCode.AddCmd(PUSH, EBP);
   asmCode.AddCmd(MOV, EBP, ESP);
   if (localVariables->GetSize() > 0) {
      asmCode.AddCmd(SUB, ESP, localVariables->GetSize());
   }
   localVariables->block->Generate(asmCode);
   asmCode.AddCmd(MOV, ESP, EBP);
   asmCode.AddCmd(POP, EBP);
   asmCode.AddCmd(RET, 4, szBYTE);
   asmCode.AddSubroutineEnd(_label);
   for (auto &symbol : localVariables->symbols) {
      if (*symbol == stProcedure || *symbol == stFunction) {
         dynamic_cast<SymSubroutine*>(symbol)->GenerateDeclaration(asmCode);
      }
   }
}

void SymSubroutine::PrintSymbol(int d)
{
	string fname = " " + name;
	cout << fname << " params:" << endl;
	params->Print(d + 1);
	cout << fname << " locals:" << endl;
	localVariables->Print(d + 1);
}

void SymSubroutine::GenerateLabel(AsmCode& asmCode)
{
   _label = new AsmStrImmediate(asmCode.GenStrLabel(name));
}

SymTable* SymSubroutine::getLocalVars() const
{
	return localVariables;
}

SymTable* SymSubroutine::GetParams() const
{
	return params;
}

Symbol* SymSubroutine::GetType()
{
	return this;
}

SymVar* SymSubroutine::GetArg(unsigned argNum) const
{
   return dynamic_cast<SymVar*>(params->symbols[argNum]);
}

AsmStrImmediate* SymSubroutine::GetLabel() const
{
   return _label;
}

size_t SymSubroutine::GetParamsSize()
{
   size_t result = 0;
   for (auto &symbol : params->symbols) {
      result += *symbol == stParam ? symbol->GetType()->GetSize() : 4;
   }
   return result;
}

SymProcedure::SymProcedure(string& AName):
   SymSubroutine(AName, stProcedure)
{}

void SymProcedure::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("procedure", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart("", COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
	cout << endl;
	SymSubroutine::PrintSymbol(d);
}

SymFunction::SymFunction(string& AName):
   SymSubroutine(AName, stFunction)
{}

void SymFunction::SetParams(SymTable* AParams, Symbol* AResultType)
{
	SymSubroutine::SetParams(AParams);
	resultType = AResultType;
}

void SymFunction::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("function", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart(resultType->getTypeValue(), COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
	cout << endl;
	SymSubroutine::PrintSymbol(d);
}

Symbol* SymFunction::GetResultType() const
{
	return resultType;
}


SymSubroutineVar::SymSubroutineVar(SymbolPtr AType, size_t AOffset, unsigned ADepth, SymbolType ASymbolType):
   SymVar(AType, AOffset, ASymbolType),
   _depth(ADepth)
{}

void SymSubroutineVar::GetLexicalNesting(AsmCode& asmCode, unsigned stmtDepth) const
{
   asmCode.AddCmd(MOV, EBX, EBP);
   for (size_t i = 0; i < stmtDepth - _depth; i++) {
      asmCode.AddCmd(MOV, EBX, AsmMemory(EBX, 8));
   }
}

SymVarLocal::SymVarLocal(SymbolPtr AType, size_t AOffset, unsigned ADepth):
   SymSubroutineVar(AType, AOffset, ADepth, stVarLocal)
{}

void SymVarLocal::PrintSymbol(int d)
{
   Symbol::PrintSymbol(d);
   printPart("local variable", TYPE_LEN);
   printPart("", VALUE_LEN);
   printPart(type->getTypeValue(), COLUMN_LEN);
   printPart(to_string(_depth), TABLE_IDX_LEN);
   type->PrintType(d);
}

void SymVarLocal::Generate(AsmCode& asmCode, unsigned stmtDepth) const
{
   GetLexicalNesting(asmCode, stmtDepth);
   asmCode.AddCmd(PUSH, AsmMemory(EBX, -int(_offset) - 4));
}

void SymVarLocal::GenerateLValue(AsmCode& asmCode, unsigned stmtDepth) const
{
   GetLexicalNesting(asmCode, stmtDepth);
   asmCode.AddCmd(ADD, EBX, -int(_offset) - 4);
   asmCode.AddCmd(PUSH, EBX);
}

SymParamBase::SymParamBase(SymbolPtr AType, size_t AOffset, SymSubroutine* ASubroutine, unsigned ADepth, SymbolType ASymType):
   SymSubroutineVar(AType, AOffset, ADepth, ASymType),
   subroutine(ASubroutine)
{}

void SymParamBase::GetParamSize(AsmCode& asmCode) const
{

}

void SymParamBase::GenerateOffsetInStack(AsmCode& asmCode, unsigned stmtDepth) const
{
   GetLexicalNesting(asmCode, stmtDepth);
   asmCode.AddCmd(ADD, EBX, 12); //EAX point to the first arg
   Symbols params = subroutine->GetParams()->symbols;
   // можно этот цикл сделать на ассемблере
   bool needBreak = false;
   for (auto &param : params) {
      needBreak = name == param->name;
      if (*param == stParam) {
         if (*(param->GetType()) == stTypeOpenArray || *(param->GetType()) == stTypeArray) {
            asmCode.AddCmd(MOV, EAX, AsmMemory(EBX)); //array size of byte
            asmCode.AddCmd(ADD, EBX, 4);
            if (needBreak) break;
            asmCode.AddCmd(ADD, EBX, EAX);
         } else if (!needBreak) {
            asmCode.AddCmd(ADD, EBX, param->GetSize());
         }
      } else if (!needBreak) {
         asmCode.AddCmd(ADD, EBX, 4);
      }
      if (needBreak) break;
   }
}

SymParam::SymParam(SymbolPtr AType, size_t AOffset, SymSubroutine* ASubroutine, unsigned ADepth) :
   SymParamBase(AType, AOffset, ASubroutine, ADepth, stParam)
{}

SymParam::SymParam(SymbolPtr AType, size_t AOffset, SymSubroutine* ASubroutine, unsigned ADepth, SymbolType ASymType) :
   SymParamBase(AType, AOffset, ASubroutine, ADepth, ASymType)
{}

void SymParam::Generate(AsmCode& asmCode, unsigned stmtDepth) const
{
   if (type->GetSize() == 4) {
      GenerateOffsetInStack(asmCode, stmtDepth);
      asmCode.AddCmd(PUSH, AsmMemory(EBX));
   } else {
      GenerateLValue(asmCode, stmtDepth);
      asmCode.PushMemory(type->GetSize());
   }
}

void SymParam::GenerateLValue(AsmCode& asmCode, unsigned stmtDepth) const
{
   GenerateOffsetInStack(asmCode, stmtDepth);
   asmCode.AddCmd(PUSH, EBX);
}

void SymParam::PrintSymbol(int d)
{
   Symbol::PrintSymbol(d);
   printPart("func param", TYPE_LEN);
   printPart("", VALUE_LEN);
   printPart(type->getTypeValue(), COLUMN_LEN);
   printPart(to_string(d), TABLE_IDX_LEN);
}


SymParamResult::SymParamResult(SymbolPtr AType, size_t AOffset, SymSubroutine* ASubroutine, unsigned ADepth):
SymParam(AType, AOffset, ASubroutine, ADepth, stParamResult)
{}

void SymParamResult::PrintSymbol(int d)
{
   Symbol::PrintSymbol(d);
   printPart("func result", TYPE_LEN);
   printPart("", VALUE_LEN);
   printPart(type->getTypeValue(), COLUMN_LEN);
   printPart(to_string(d), TABLE_IDX_LEN);
}

SymVarParam::SymVarParam(SymbolPtr AType, size_t AOffset, SymSubroutine* ASubroutine, unsigned ADepth):
SymParamBase(AType, AOffset, ASubroutine, ADepth, stVarParam)
{}

void SymVarParam::PrintSymbol(int d)
{
   Symbol::PrintSymbol(d);
   printPart("func var param", TYPE_LEN);
   printPart("", VALUE_LEN);
   printPart(type->getTypeValue(), COLUMN_LEN);
   printPart(to_string(d), TABLE_IDX_LEN);
}

void SymVarParam::Generate(AsmCode& asmCode, unsigned stmtDepth) const
{
   GenerateLValue(asmCode, stmtDepth);
   asmCode.PushMemory(type->GetSize());
}

void SymVarParam::GenerateLValue(AsmCode& asmCode, unsigned stmtDepth) const
{
   GenerateOffsetInStack(asmCode, stmtDepth);
   asmCode.AddCmd(PUSH, AsmMemory(EBX));
}

bool SymVarParam::IsByRef() const
{
   return true;
}

size_t SymVarParam::GetSize()
{
   return 4;
}