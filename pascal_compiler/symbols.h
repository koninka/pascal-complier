#pragma once

#include <stack>
#include <string>
#include <memory>
#include <unordered_map>
#include "CodeGen.h"

using namespace std;

enum SymbolType {
   stSymbol,
   stConst,
   stConstFloat,
   stConstInteger,
   stConstChar,
   stConstCharacterString,
   stType,
   stTypeScalar,
   stTypeFloat,
   stTypeInteger,
   stTypeChar,
   stTypeSubrange,
   stTypeArry,
   stTypeArray,
   stTypeOpenArray,
   stTypeRecord,
   stTypeAlias,
   stVar,
   stVarGlobal,
   stVarLocal,
	stVarParam,
	stParam,
   stParamResult,
	stSubroutine,
	stProcedure,
	stFunction
};

const int COLUMN_LEN = 37;
const int VALUE_LEN = 17;
const int NAME_LEN = 8;
const int TYPE_LEN = 15;
const int TABLE_IDX_LEN = 2;

class Symbol {
protected:
   size_t _size;
public:
	string name;
	SymbolType symType;
	Symbol(SymbolType);
	virtual ~Symbol() {};
   virtual void SetOffset(size_t);
	virtual void PrintType(int) {};
	virtual void PrintSymbol(int);
   virtual void Generate(AsmCode&, unsigned) const;
   virtual void GenerateLValue(AsmCode&, unsigned) const;
	virtual bool IsType();
   virtual bool IsVar();
   virtual bool IsEqualType(Symbol*);
	virtual Symbol* GetType();
   virtual string getTypeValue();
   virtual size_t GetSize();
   virtual size_t GetOffset() const;
	bool operator ==(const Symbol);
	bool operator !=(const Symbol);
	bool operator ==(const SymbolType);
	bool operator !=(const SymbolType);
};

Symbol* GetReferenceType(Symbol*);

struct SymConst: public Symbol {
	SymConst(SymbolType);
	void printScalar(int, string, string);
};

class SymConstInteger: public SymConst {
	int value;
public:
	SymConstInteger(int);
	int getValue() const;
	void PrintSymbol(int) override;
	Symbol* GetType() override;
   size_t GetSize() override;
   void Generate(AsmCode&, unsigned) const override;
};

class SymConstFloat: public SymConst {
	double value;
public:
	SymConstFloat(double);
	double getValue() const;
	void PrintSymbol(int) override;
	Symbol* GetType() override;
   size_t GetSize() override;
   void Generate(AsmCode&, unsigned) const override;
};

class SymConstCharacterString: public SymConst {
	string value;
public:
	SymConstCharacterString(string&);
	void PrintSymbol(int) override;
	Symbol* GetType() override;
   void Generate(AsmCode&, unsigned) const override;
};

typedef shared_ptr<Symbol> SymbolPtr;

struct SymType: public Symbol {
	SymType();
	SymType(SymbolType);
	bool IsType() override;
	string getTypeValue() override;
	void PrintSymbol(int) override;
};

class SymVar: public Symbol {
protected:
   size_t _offset;
public:
	SymbolPtr type;
   SymVar(SymbolPtr, size_t, SymbolType);
   void SetOffset(size_t) override;
   virtual bool IsByRef() const;
	Symbol* GetType() override;
   bool IsVar() override;
   size_t GetSize() override;
   size_t GetOffset() const override;
};

class SymVarGlobal: public SymVar {
   AsmStrImmediate* varLabel;
public:
   SymVarGlobal(SymbolPtr, size_t);
   void GenerateDeclaration(AsmCode&);
   void Generate(AsmCode&, unsigned) const override;
   void GenerateLValue(AsmCode&, unsigned) const override;
   void PrintSymbol(int) override;
};

class SymTypeSubrange: public SymType {
	int lb, ub;
public:
	SymTypeSubrange(int, int);
	void PrintSymbol(int) override;
	string getTypeValue() override;
	string getSubrangeStr();
	bool IsEqualType(Symbol*) override;
   size_t GetSize() override;
   int GetLow() const;
   int GetHigh() const;
};

struct SymTypeArry: public SymType {
	Symbol* elemType;
	SymTypeArry(SymbolType);
	void SetElementType(Symbol*);
   void PrintSymbol(int) override;
   virtual int GetLow() const;
};

struct SymTypeOpenArray: public SymTypeArry {
	SymTypeOpenArray();
	bool IsEqualType(Symbol*) override;
	string getTypeValue() override;
};


struct SymTypeArray: public SymTypeArry {
	Symbol* subrange;
	SymTypeArray(Symbol*);
	bool IsEqualType(Symbol*) override;
	string getTypeValue() override;
   size_t GetSize() override;
   int GetLow() const override;
   int GetHigh() const;
};

struct SymTypeScalar: public SymType {
	SymTypeScalar(SymbolType);
   size_t GetSize() override;
};

struct SymTypeInteger: public SymTypeScalar {
	SymTypeInteger();
};

struct SymTypeFloat: public SymTypeScalar {
	SymTypeFloat();
};

struct SymTypeChar: public SymTypeScalar {
	SymTypeChar();
};

struct SymTypeAlias: public SymType {
	Symbol* refType;
	SymTypeAlias(Symbol*);
	void PrintSymbol(int) override;
   size_t GetSize() override;
};

extern Symbol* typeChar;
extern Symbol* typeFloat;
extern Symbol* typeInteger;
extern Symbol* typeDefault;