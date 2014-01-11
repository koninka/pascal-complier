#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>

using namespace std;

enum SizeType {
   szNONE,
   szBYTE,
   szDWORD,
   szQWORD
};

enum Register {
   EAX,
   EBX,
   ECX,
   EDX,
   ESP,
   EBP,
   AX,
   AL,
   ST1,
   ST
};

enum OpCode {
   LABEL,
   SUBROUTINE,
   RAW_STR,
   JMP,
   JNE,
   JGE,
   JE,
   JG,
   JL,
   TEST,
	CALL,
	PUSH,
	POP,
	RET,
	MUL,
	DIV,
	NOT,
   NEG,
   SAR,
   SAL,
   SAHF,
   SETA,
   SETAE,
   SETB,
   SETBE,
   SETG,
   SETGE,
   SETL,
   SETLE,
   SETE,
   SETNE,
	MOV,
   MOVZX,
   MOVZB,
   INC,
   DEC,
	ADD,
	SUB,
	CMP,
	XOR,
	AND,
	OR,
	RCL,
	RCR,
	LEA,
   IMUL,
   IDIV,
   FLD,
   FILD,
   FCHS,
   FADDP,
   FSUBP,
   FMULP,
   FDIVP,
   FDIVRP,
   FSTP,
   FXCH,
   FCOMPP,
   FNSTSW
};

struct AsmOperand;
class AsmStrImmediate;

class Asm {
protected:
   OpCode opCode;
public:
   AsmOperand *arg1, *arg2;
   Asm(OpCode, AsmOperand* = nullptr, AsmOperand* = nullptr);
   bool operator==(OpCode);
   bool operator!=(OpCode);
   OpCode GetOpCode() const;
   virtual void Print() const;
};

struct AsmCmd0: public Asm {
   AsmCmd0(OpCode);
   void Print() const override;
};

struct AsmCmd1: public Asm {
   AsmCmd1(OpCode, AsmOperand*);
   void Print() const override;
};

struct AsmCmd2: public Asm {
   AsmCmd2(OpCode, AsmOperand*, AsmOperand*);
   void Print() const override;
};

class AsmLabel: public Asm {
   unsigned refAmount;
public:
   AsmLabel(AsmStrImmediate*);
   AsmLabel(AsmStrImmediate);
   AsmLabel(string);
   void IncRefAmount();
   void DecRefAmount();
   unsigned GetRefAmount() const;
   void Print() const override;
};

class AsmSubroutineBase: public Asm {
protected:
   AsmStrImmediate* _label;
public:
   AsmSubroutineBase(AsmStrImmediate*);
};

struct AsmSubroutineBegin: public AsmSubroutineBase {
   AsmSubroutineBegin(AsmStrImmediate*);
   void Print() const override;
};

struct AsmSubroutineEnd: public AsmSubroutineBase {
   AsmSubroutineEnd(AsmStrImmediate*);
   void Print() const override;
};

class AsmRawCmd: public Asm {
   string _str;
public:
   AsmRawCmd(string);
   virtual void Print() const;
};

class AsmDataBase {
protected:
   string _name;
public:
   AsmDataBase(string);
   virtual void Print() const;
};

class AsmData: public AsmDataBase {
   size_t _size;
public:
   AsmData(string, size_t);
   void Print() const override;
};

class AsmDataReal: public AsmDataBase {
   double _value;
public:
   AsmDataReal(string, double);
   void Print() const override;
};

class AsmDataStr: public AsmDataBase {
   string _value;
public:
   AsmDataStr(string, string);
   void Print() const override;
};

struct AsmDataNewLine: public AsmDataBase {
public:
   AsmDataNewLine(string);
   void Print() const override;
};

struct AsmOperand {
   virtual void Print() const;
   virtual void PrintBase() const;
   virtual void SetSizeType(SizeType);
   virtual bool operator==(AsmOperand*);
};

class AsmRegister: public AsmOperand {
   Register _register;
public:
   AsmRegister(Register);
   bool operator==(AsmOperand*) override;
   bool operator!=(AsmOperand*);
   bool operator==(AsmRegister);
   bool operator!=(AsmRegister);
   void Print() const override;
   void PrintBase() const override;
};

struct AsmImmediate: public AsmOperand {
   virtual string GetStrValue() const;
   virtual int GetIntValue() const;
   void Print() const override;
};

class AsmIntImmediate: public AsmImmediate {
   int _value;
   SizeType _sizeType;
public:
   AsmIntImmediate(int, SizeType = szDWORD);
   bool operator==(AsmOperand*) override;
   void SetSizeType(SizeType) override;
   int GetIntValue() const override;
   void PrintBase() const override;
};

class AsmVarBase: public AsmImmediate {
public:
   AsmOperand* arg;
   AsmVarBase(AsmOperand*);
};

class AsmVarAddr: public AsmVarBase {
   int _offset;
   SizeType _sizeType;
public:
   AsmVarAddr(AsmOperand*, int = 0, SizeType = szNONE);
   bool operator==(AsmOperand*) override;
   int GetOffset() const;
   void PrintBase() const override;
};


class AsmStrImmediate: public AsmImmediate {
   string _value;
public:
   AsmStrImmediate(string);
   bool operator==(AsmOperand*) override;
   string GetStrValue() const override;
   void PrintBase() const override;
};

class AsmMemory: public AsmOperand {
   int _offset;
   SizeType _size;
public:
   AsmOperand* arg;
   AsmMemory(AsmOperand*, int = 0, SizeType = szNONE);
   AsmMemory(Register, int = 0, SizeType = szNONE);
   AsmMemory(AsmRegister, int = 0, SizeType = szNONE);
   bool operator==(AsmOperand*) override;
   int GetOffset() const;
   void SetOffset(int);
   SizeType GetSizeType() const;
   void SetSizeType(SizeType) override;
   void Print() const override;
};

typedef Asm* Command;

typedef vector<Command> Commands;
typedef vector<AsmDataBase*> Data;

struct AsmCodeBase {
   Commands commands;
   
   void AddCmd(string);
   void AddCmd(OpCode);
   void AddCmd(Command);
   void AddCmd(OpCode, AsmLabel*);
   void AddCmd(OpCode, AsmVarAddr);
   void AddCmd(OpCode, Register);
   void AddCmd(OpCode, AsmOperand*);
   //void AddCmd(OpCode, AsmOperand*, SizeType = szNONE);
   void AddCmd(OpCode, AsmMemory);
   void AddCmd(OpCode, AsmStrImmediate*);
   void AddCmd(OpCode, AsmStrImmediate);
   void AddCmd(OpCode, AsmIntImmediate);
   void AddCmd(OpCode, int, SizeType = szNONE);
   void AddCmd(OpCode, AsmOperand*, AsmOperand*);
   void AddCmd(OpCode, AsmOperand*, AsmOperand*, SizeType);
   void AddCmd(OpCode, Register, Register);
   void AddCmd(OpCode, Register, AsmStrImmediate*);
   void AddCmd(OpCode, AsmRegister, AsmRegister);
   void AddCmd(OpCode, AsmRegister, AsmOperand*);
   void AddCmd(OpCode, Register, int, SizeType = szNONE);
   //void AddCmd(OpCode, AsmMemory, int, SizeType = szNONE);
   void AddCmd(OpCode, Register, AsmIntImmediate);
   void AddCmd(OpCode, AsmRegister, AsmIntImmediate);
   void AddCmd(OpCode, AsmMemory, AsmIntImmediate);
   void AddCmd(OpCode, AsmOperand*, AsmIntImmediate);
   void AddCmd(OpCode, AsmOperand*, AsmVarAddr);
   void AddCmd(OpCode, AsmVarAddr, AsmOperand*);
   void AddCmd(OpCode, AsmMemory, Register);
   void AddCmd(OpCode, AsmMemory, AsmRegister);
   void AddCmd(OpCode, AsmMemory, AsmOperand*);
   void AddCmd(OpCode, AsmOperand*, AsmMemory);
   void AddCmd(OpCode, Register, AsmMemory);
   void CleanCommands();
   Commands GetCommands() const;
};

typedef unordered_map<string, size_t> LabelInfo;

class AsmCode: public AsmCodeBase {
   size_t labelCounter;
   AsmStrImmediate* formatStrReal;
   AsmStrImmediate* formatStrInt;
   AsmStrImmediate* formatStrNewLine;

   AsmStrImmediate functWrite;

   Data data;
   unordered_map<size_t, AsmLabel*> labels;
   LabelInfo labelsInfo;
public:
   AsmCode();
   AsmStrImmediate* AddData(string);
   AsmStrImmediate* AddData(string, double);
   AsmStrImmediate* AddData(string, size_t);
   AsmStrImmediate* AddData(string, string);
   void AddLabel(AsmLabel*);
   void AddSubroutineBegin(AsmStrImmediate*);
   void AddSubroutineEnd(AsmStrImmediate*);
   AsmLabel* GenLabel(string);
   string GenStrLabel(string);
   void Print() const;
   void PushMemory(unsigned);
   void GenCallWriteForInt();
   void GenCallWriteForReal();
   void GenCallWriteForStr();
   void GenWriteNewLine();
   void ReplaceCommands(Commands, size_t, size_t = 1);
   bool TryToChangeLabelOfTheJump(Command);
   Command GetCommand(size_t) const;
   Commands GetCommands(size_t, size_t);
   size_t GetCmdAmount() const;
};

template<class T1, class T2>
bool TryToCast(T2 t)
{
   return dynamic_cast<T1*>(t) != nullptr;
}

template<class T1, class T2>
T1* Cast(T2 t)
{
   return dynamic_cast<T1*>(t);
}

template<class T>
bool TryToCastOperand(AsmOperand* oper)
{
   return TryToCast<T>(oper);
}


template<class T>
T* CastOperand(AsmOperand* oper)
{
   return Cast<T>(oper);
}

extern bool CmpOperands(AsmOperand*, AsmOperand*);