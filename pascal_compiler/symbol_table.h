#pragma once

#include "symbols.h"
#include "syntax_node.h"

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
	void DeleteParam(string&);
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
protected:
	SymTable* params;
	SymTable* localVariables;
   AsmStrImmediate* _label;
   size_t GetParamsSize();
public:
	SymSubroutine(string&, SymbolType);
	void SetParams(SymTable*);
	void SetVars(SymTable*);
	void PrintSymbol(int) override;
   void GenerateLabel(AsmCode&);
   virtual void GenerateDeclaration(AsmCode&);
	SymTable* getLocalVars() const;
	SymTable* GetParams() const;
	Symbol* GetType() override;
   SymVar* GetArg(unsigned) const;
   AsmStrImmediate* GetLabel() const;
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

class SymSubroutineVar: public SymVar {
protected:
   unsigned _depth;
   void ComputeSubroutineEBPToEBX(AsmCode&, unsigned) const;
public:
   SymSubroutineVar(SymbolPtr, size_t, unsigned, SymbolType);
};

struct SymVarLocal: public SymSubroutineVar {
   SymVarLocal(SymbolPtr, size_t, unsigned);
   void PrintSymbol(int) override;
   void Generate(AsmCode&, unsigned) const override;
   void GenerateLValue(AsmCode&, unsigned) const override;
};

class SymParamBase: public SymSubroutineVar {
protected:
   SymSubroutine* subroutine;
   void GetParamSize(AsmCode&) const;
   void GenerateOffsetInStack(AsmCode&, unsigned) const;
public:
   SymParamBase(SymbolPtr, size_t, SymSubroutine*, unsigned, SymbolType);
};

struct SymParam: public SymParamBase {
   SymParam(SymbolPtr, size_t, SymSubroutine*, unsigned);
   SymParam(SymbolPtr, size_t, SymSubroutine*, unsigned, SymbolType);
   void Generate(AsmCode&, unsigned) const override;
   void GenerateLValue(AsmCode&, unsigned) const override;
   void PrintSymbol(int) override;
};

struct SymParamResult: public SymParam {
   SymParamResult(SymbolPtr, size_t, SymSubroutine*, unsigned);
   void PrintSymbol(int) override;
};

struct SymVarParam: public SymParamBase {
   SymVarParam(SymbolPtr, size_t, SymSubroutine*, unsigned);
   void Generate(AsmCode&, unsigned) const override;
   void GenerateLValue(AsmCode&, unsigned) const override;
   void PrintSymbol(int) override;
   bool IsByRef() const override;
   size_t GetSize() override;
};
