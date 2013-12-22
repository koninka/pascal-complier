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


Symbol::Symbol(SymbolType AType):
   symType(AType),
   _size(0)
{}

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

void Symbol::SetOffset(size_t)
{}

void Symbol::PrintSymbol(int d)
{
	printPart(name, NAME_LEN);
}

void Symbol::Generate(AsmCode&, unsigned) const
{}

void Symbol::GenerateLValue(AsmCode&, unsigned) const
{}

bool Symbol::IsType()
{
	return false;
}

bool Symbol::IsVar()
{
   return false;
}

Symbol* Symbol::GetType()
{
	return nullptr;
}

string Symbol::getTypeValue()
{
   return "";
}

size_t Symbol::GetSize()
{
   return 0;
}

size_t Symbol::GetOffset() const
{
   return 0;
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

size_t SymConstInteger::GetSize()
{
   return _size = typeInteger->GetSize();
}

void SymConstInteger::Generate(AsmCode& asmCode, unsigned) const
{
   asmCode.AddCmd(PUSH, value);
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

size_t SymConstFloat::GetSize()
{
   return _size = typeFloat->GetSize();
}

void SymConstFloat::Generate(AsmCode& asmCode, unsigned) const
{

}

void SymConstFloat::PrintSymbol(int d)
{
	SymConst::printScalar(d, "double scalar", to_string(value));
}

void SymConstCharacterString::Generate(AsmCode& asmCode, unsigned stmtDepth) const
{
   asmCode.AddCmd(PUSH, AsmVarAddr(asmCode.AddData(asmCode.GenStrLabel("str"), value)));
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

SymVar::SymVar(SymbolPtr AVarType, size_t AOffset, SymbolType AType):
   Symbol(AType),
   _offset(AOffset),
   type(AVarType)
{}

void SymVar::SetOffset(size_t ANewOffset)
{
   _offset = ANewOffset;
}

bool SymVar::IsByRef() const
{
   return false;
}

Symbol* SymVar::GetType()
{
	return GetReferenceType(type.get());
}

bool SymVar::IsVar()
{
   return true;
}

size_t SymVar::GetSize()
{
   return _size = type.get()->GetSize();
}

size_t SymVar::GetOffset() const
{
   return _offset;
}

SymVarGlobal::SymVarGlobal(SymbolPtr AType, size_t AOffset):
   SymVar(AType, AOffset, stVarGlobal),
   varLabel(nullptr)
{}

void SymVarGlobal::GenerateDeclaration(AsmCode& asmCode)
{
   varLabel = asmCode.AddData(name, type->GetSize());
}

void SymVarGlobal::Generate(AsmCode& asmCode, unsigned) const
{
   if (type->GetSize() > 4) {
      GenerateLValue(asmCode, 0);
      asmCode.PushMemory(type->GetSize());
   } else {
      asmCode.AddCmd(PUSH, AsmVarDword(new AsmMemory(varLabel)));
   }
}

void SymVarGlobal::GenerateLValue(AsmCode& asmCode, unsigned) const
{
   asmCode.AddCmd(PUSH, AsmVarAddr(varLabel));
}

void SymVarGlobal::PrintSymbol(int d)
{
   Symbol::PrintSymbol(d);
   printPart("variable", TYPE_LEN);
   printPart("", VALUE_LEN);
   printPart(type->getTypeValue(), COLUMN_LEN);
   printPart(to_string(d), TABLE_IDX_LEN);
   type->PrintType(d);
}

SymTypeSubrange::SymTypeSubrange(int ALb, int AUb):
   SymType(stTypeSubrange),
   lb(ALb),
   ub(AUb)
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
	return subrange != nullptr && GetLow() == subrange->GetLow() && GetHigh() == subrange->GetHigh();
}

size_t SymTypeSubrange::GetSize()
{
   return _size = ub - lb + 1;
}

int SymTypeSubrange::GetLow() const
{
   return lb;
}

int SymTypeSubrange::GetHigh() const
{
   return ub;
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

int SymTypeArry::GetLow() const
{
   return 0;
}

SymTypeOpenArray::SymTypeOpenArray():
   SymTypeArry(stTypeOpenArray)
{}

bool SymTypeOpenArray::IsEqualType(Symbol* symbol)
{
	SymTypeArry* arry = dynamic_cast<SymTypeArry*>(symbol);
	return arry != nullptr && elemType->IsEqualType(arry->elemType);
}

string SymTypeOpenArray::getTypeValue()
{
	string result = "array of " + elemType->getTypeValue();
	return result;
}

SymTypeArray::SymTypeArray(Symbol* ASubrange):
   SymTypeArry(stTypeArray),
   subrange(ASubrange)
{}

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

size_t SymTypeArray::GetSize()
{
   return _size = elemType->GetSize() * subrange->GetSize();
}

int SymTypeArray::GetLow() const
{
   return dynamic_cast<SymTypeSubrange*>(GetReferenceType(subrange))->GetLow();
}

int SymTypeArray::GetHigh() const
{
   return dynamic_cast<SymTypeSubrange*>(GetReferenceType(subrange))->GetHigh();
}

SymTypeScalar::SymTypeScalar(SymbolType AType): SymType(AType) {}

size_t SymTypeScalar::GetSize()
{
   return _size;
}

SymTypeInteger::SymTypeInteger():
   SymTypeScalar(stTypeInteger)
{
   _size = 4;
	name  = "integer";
}

SymTypeFloat::SymTypeFloat():
   SymTypeScalar(stTypeFloat)
{
   _size = 4;
	name  = "double";
}

SymTypeChar::SymTypeChar(): 
   SymTypeScalar(stTypeChar)
{
   _size = 1;
	name  = "char";
}

SymTypeAlias::SymTypeAlias(Symbol* ARefType):
   SymType(stTypeAlias),
   refType(ARefType)
{}

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

size_t SymTypeAlias::GetSize()
{
   return _size = refType->GetSize();
}