#pragma once

#include "symbols.h"
#include "syntax_nodes.h"

typedef unordered_map<string, int> SymbolNames;
typedef vector<Symbol*> Symbols;
typedef void* Handle;

class SymInterface {
public:
	virtual bool FindSymbol(string&) abstract;
	virtual Symbol* GetSymbol(string&) abstract;
};

class SymTable: public SymInterface {
   size_t _tableSize;
	SymbolNames symNames;
public:
	SyntaxNode* block;
	Symbols symbols;
	SymTable();
	void Add(Symbol*);
	void Add(Symbol*, string);
	void Delete(string&);
	void SetBlock(NodeBlock*, string);
   void GenerateDeclarations(AsmCode&) const;
	void Print(int);
	void PrintBlock(int d);
	bool FindSymbol(string&) override;
	Symbol* GetSymbol(string&) override;
	size_t Size() const;
   size_t GetSize() const;
};

typedef stack<SymTable*> TableStack;

class SymTableStack: public SymInterface {
	TableStack tables;
	SymTable* FindSymbolTable(string&);
public:
	void Add(SymTable*);
	void Pop();
	SymTable* Top();
	SymTable* GetTop();
	bool FindSymbol(string&) override;
	Symbol* GetSymbol(string&) override;
};

class SymTypeRecord: public SymType {
	SymTable* fields;
public:
	SymTypeRecord(SymTable*);
	void PrintType(int) override;
	void PrintSymbol(int) override;
	SymTable* GetFields() const;
	bool IsEqualType(Symbol*) override;
   size_t GetSize() override;
};

class SymSubroutine: public Symbol {
	SymTable* params;
	SymTable* localVariables;
public:
	SymSubroutine(string&, SymbolType);
	void SetParams(SymTable*);
	void SetVars(SymTable*);
   void GenerateDeclaration(AsmCode&);
	void PrintSymbol(int) override;
	SymTable* getLocalVars() const;
	SymTable* GetParams() const;
	Symbol* GetType() override;
};

struct SymProcedure: public SymSubroutine {
	SymProcedure(string&);
	void PrintSymbol(int) override;
};

class SymFunction: public SymSubroutine {
	Symbol* resultType;
public:
	SymFunction(string&);
	void SetParams(SymTable*, Symbol*);
	void PrintSymbol(int) override;
	Symbol* GetResultType() const;
};