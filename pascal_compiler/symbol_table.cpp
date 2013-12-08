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

void SymTable::Delete(string& name)
{
	symNames.erase(symNames.find(name));
	for (auto it = symbols.begin(); it != symbols.end(); it++) {
		if ((*it)->name == name) {
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

SymSubroutine::SymSubroutine(string& AName, SymbolType AType): Symbol(AType)
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
   //asmCode.AddLabel(label);
   //asmCode.AddCmd(ASM_PUSH, REG_EBP);
   //asmCode.AddCmd(ASM_MOV, REG_ESP, REG_EBP);
   //if (sym_table->GetLocalsSize()) asm_code.AddCmd(ASM_SUB, sym_table->GetLocalsSize(), REG_ESP);
   //body->Generate(asm_code);
   //asmCode.AddLabel(exit_label);
   //asmCode.AddCmd(ASM_MOV, REG_EBP, REG_ESP);
   //asmCode.AddCmd(ASM_POP, REG_EBP);
   //asmCode.AddCmd(ASM_RET, sym_table->GetParamsSize() - GetResultType()->GetSize());
}

void SymSubroutine::PrintSymbol(int d)
{
	string fname = " " + name;
	cout << fname << " params:" << endl;
	params->Print(d + 1);
	cout << fname << " locals:" << endl;
	localVariables->Print(d + 1);
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

SymProcedure::SymProcedure(string& AName): SymSubroutine(AName, stProcedure) {}

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

SymFunction::SymFunction(string& AName): SymSubroutine(AName, stFunction) {}

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