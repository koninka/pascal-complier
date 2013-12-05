#pragma once

#include <stack>
#include <string>
#include <memory>
#include <unordered_map>

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
	stVarParam,
	stParam,
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
public:
	string name;
	SymbolType symType;
	Symbol(SymbolType);
	virtual ~Symbol() {};
	virtual void PrintType(int) {};
	virtual void PrintSymbol(int);
	virtual bool IsType();
	virtual Symbol* GetType();
	virtual string getTypeValue() { return ""; }
	virtual bool IsEqualType(Symbol*);
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
};

class SymConstFloat: public SymConst {
	double value;
public:
	SymConstFloat(double);
	double getValue() const;
	void PrintSymbol(int) override;
	Symbol* GetType() override;
};

class SymConstCharacterString: public SymConst {
	string value;
public:
	SymConstCharacterString(string&);
	void PrintSymbol(int) override;
	Symbol* GetType() override;
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
public:
	SymbolPtr type;
	SymVar(SymbolPtr);
	SymVar(SymbolPtr, SymbolType);
	void PrintSymbol(int) override;
	Symbol* GetType() override;
};

class SymParam: public SymVar {
public:
	SymParam(SymbolPtr);
	void PrintSymbol(int) override;
};

class SymVarParam: public SymVar {
public:
	SymVarParam(SymbolPtr);
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
};

struct SymTypeArry: public SymType {
	Symbol* elemType;
	SymTypeArry(SymbolType);
	void SetElementType(Symbol*);
	void PrintSymbol(int) override;
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
};

struct SymTypeScalar: public SymType {
	SymTypeScalar(SymbolType);
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
};

extern Symbol* typeChar;
extern Symbol* typeFloat;
extern Symbol* typeInteger;
extern Symbol* typeDefault;