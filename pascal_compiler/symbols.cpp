#include <iostream>
#include <sstream>
#include "symbols.h"

Symbol* typeChar	  = new SymTypeChar;
Symbol* typeFloat	  = new SymTypeFloat;
Symbol* typeInteger = new SymTypeInteger;
Symbol* typeDefault = new SymType;

static void printPart(string str, int len)
{
   cout << " " << str;
   int cnt = len - str.length() - 1;
   string tmp(cnt >= 0 ? cnt : 0, ' ');
   cout << tmp;
   int c = tmp.length() + str.length() + 1;
}


Symbol::Symbol(SymbolType AType): symType(AType) {}

bool Symbol::operator ==(const SymbolType type)
{
	return symType == type;
}

bool Symbol::operator !=(const SymbolType type)
{
	return symType != type;
}

bool Symbol::operator ==(const Symbol symbol)
{
	return symType == symbol.symType;
}

bool Symbol::operator !=(const Symbol symbol)
{
	return symType != symbol.symType;
}

void Symbol::PrintSymbol(int d)
{
	printPart(name, NAME_LEN);
}

bool Symbol::IsType()
{
	return false;
}

Symbol* Symbol::GetType()
{
	return nullptr;
}

Symbol* GetReferenceType(Symbol* symbol)
{
	return symbol != nullptr && *symbol == stTypeAlias ? dynamic_cast<SymTypeAlias*>(symbol)->refType : symbol;
}

bool Symbol::IsEqualType(Symbol* symbol)
{
	return symbol != nullptr && *this == *symbol;
}

SymConst::SymConst(SymbolType AType): Symbol(AType) {}

void SymConst::printScalar(int d, string scalarName, string value)
{
	Symbol::PrintSymbol(d);
	printPart(scalarName, TYPE_LEN);
	printPart(value, VALUE_LEN);
	printPart("", COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
}

SymConstInteger::SymConstInteger(int AValue): SymConst(stConstInteger), value(AValue) {}

void SymConstInteger::PrintSymbol(int d)
{
	SymConst::printScalar(d, "int scalar", to_string(value));
}

int SymConstInteger::getValue() const
{
	return value;
}

Symbol* SymConstInteger::GetType()
{
	return typeInteger;
}

SymConstFloat::SymConstFloat(double AValue): SymConst(stConstFloat), value(AValue) {}

double SymConstFloat::getValue() const
{
	return value;
}

Symbol* SymConstFloat::GetType()
{
	return typeFloat;
}

void SymConstFloat::PrintSymbol(int d)
{
	SymConst::printScalar(d, "double scalar", to_string(value));
}

SymConstCharacterString::SymConstCharacterString(string& val): SymConst(stConstCharacterString), value(val) {}

Symbol* SymConstCharacterString::GetType()
{
	Symbol* symbol(nullptr);
	if (value.length() == 1) {
		symbol = typeChar;
	} else {
		symbol = new SymType(stConstCharacterString);
	}
	return symbol;
}

void SymConstCharacterString::PrintSymbol(int d)
{
	SymConst::printScalar(d, "string scalar", value);
} 

SymType::SymType(): Symbol(stType) {}

SymType::SymType(SymbolType AType): Symbol(AType) {}

bool SymType::IsType()
{
	return true;
}

string SymType::getTypeValue()
{
	return name;
}

void SymType::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("type", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart("", COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
}

SymVar::SymVar(SymbolPtr AVarType): Symbol(stVar), type(AVarType) {}

SymVar::SymVar(SymbolPtr AVarType, SymbolType AType): Symbol(AType), type(AVarType) {}

void SymVar::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("variable", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart(type->getTypeValue(), COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
	type->PrintType(d);
}

Symbol* SymVar::GetType()
{
	return GetReferenceType(type.get());
}

SymParam::SymParam(SymbolPtr AType): SymVar(AType, stParam) {}

void SymParam::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("func param", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart(type->getTypeValue(), COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
}

SymVarParam::SymVarParam(SymbolPtr AType): SymVar(AType, stVarParam) {}

void SymVarParam::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("func var param", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart(type->getTypeValue(), COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
}

SymTypeSubrange::SymTypeSubrange(int ALb, int AUb): SymType(stTypeSubrange), lb(ALb), ub(AUb)
{
	name = "subrange";
}

string SymTypeSubrange::getSubrangeStr()
{
	stringstream str;
	str << lb << ".." << ub;
	return str.str();
}

string SymTypeSubrange::getTypeValue()
{
	return getSubrangeStr();
}

void SymTypeSubrange::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("subrange", TYPE_LEN);
	printPart("", VALUE_LEN);
	printPart(getTypeValue(), COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
}

bool SymTypeSubrange::IsEqualType(Symbol* symbol)
{
	SymTypeSubrange* subrange = dynamic_cast<SymTypeSubrange*>(symbol);
	return subrange != nullptr && lb == subrange->lb && ub == subrange->ub;
}

SymTypeArry::SymTypeArry(SymbolType AType): SymType(AType)
{
	name = "array";
}

void SymTypeArry::SetElementType(Symbol* AElemType)
{
	elemType = AElemType;
}

void SymTypeArry::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("array", TYPE_LEN);
	//printPart(dynamic_cast<SymTypeSubrange*>(subrange)->getSubrangeStr(), VALUE_LEN);
	printPart("ar", VALUE_LEN);
	printPart(elemType->name, COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
}

SymTypeOpenArray::SymTypeOpenArray(): SymTypeArry(stTypeOpenArray) {}

bool SymTypeOpenArray::IsEqualType(Symbol* symbol)
{
	SymTypeArray* arry = dynamic_cast<SymTypeArray*>(symbol);
	return arry != nullptr && elemType->IsEqualType(arry->elemType);
}

string SymTypeOpenArray::getTypeValue()
{
	string result = "array of " + elemType->getTypeValue();
	return result;
}

SymTypeArray::SymTypeArray(Symbol* ASubrange): SymTypeArry(stTypeArray), subrange(ASubrange) {}

bool SymTypeArray::IsEqualType(Symbol* symbol)
{
	SymTypeArray* arry = dynamic_cast<SymTypeArray*>(symbol);
	return
		arry != nullptr
	&& subrange->IsEqualType(arry->subrange)
	&& GetReferenceType(elemType)->IsEqualType(GetReferenceType(arry->elemType));
}

string SymTypeArray::getTypeValue()
{
	string result = "array";
	result += "["
			  + (*subrange != stTypeAlias ? dynamic_cast<SymTypeSubrange*>(subrange)->getSubrangeStr() : (subrange)->getTypeValue())
			  + "] of " + elemType->getTypeValue();
	return result;
}

SymTypeScalar::SymTypeScalar(SymbolType AType): SymType(AType) {}

SymTypeInteger::SymTypeInteger(): SymTypeScalar(stTypeInteger)
{
	name = "integer";
}

SymTypeFloat::SymTypeFloat(): SymTypeScalar(stTypeFloat)
{
	name = "double";
}

SymTypeChar::SymTypeChar(): SymTypeScalar(stTypeChar)
{
	name = "char";
}

SymTypeAlias::SymTypeAlias(Symbol* ARefType): SymType(stTypeAlias), refType(ARefType) {}

void SymTypeAlias::PrintSymbol(int d)
{
	Symbol::PrintSymbol(d);
	printPart("type alias", TYPE_LEN);
	string name = *refType != stTypeInteger && *refType != stTypeFloat && *refType != stTypeChar && *refType != stTypeRecord ? refType->name : "";
	printPart(name, VALUE_LEN);
	printPart(refType->getTypeValue(), COLUMN_LEN);
	printPart(to_string(d), TABLE_IDX_LEN);
	refType->PrintType(d);
}