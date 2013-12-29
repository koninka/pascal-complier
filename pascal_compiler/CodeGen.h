#pragma once

#include <iostream>
#include <vector>
#include <string>

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
   FSUBRP,
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

struct Asm {
   virtual void Print() const;
};

class AsmCmd: public Asm {
protected:
   OpCode opCode;
public:
   AsmCmd(OpCode);
};

struct AsmCmd0: public AsmCmd {
   AsmCmd0(OpCode);
   void Print() const override;
};

class AsmCmd1: public AsmCmd {
   AsmOperand* _oper;
public:
   AsmCmd1(OpCode, AsmOperand*);
   void Print() const override;
};

class AsmCmd2: public AsmCmd {
   AsmOperand* _src;
   AsmOperand* _dest;
public:
   AsmCmd2(OpCode, AsmOperand*, AsmOperand*);
   void Print() const override;
};

class AsmLabel: public Asm {
   AsmStrImmediate* _label;
public:
   AsmLabel(AsmStrImmediate*);
   AsmLabel(AsmStrImmediate);
   AsmLabel(string);
   void Print() const override;
};

class AsmRawCmd: public Asm {
   string _str;
public:
   AsmRawCmd(string);
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
};

class AsmRegister: public AsmOperand {
   Register _register;
public:
   AsmRegister(Register);
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
   int GetIntValue() const override;
   void PrintBase() const override;
};

class AsmVarBase: public AsmImmediate {
protected:
   AsmOperand* oper;
public:
   AsmVarBase(AsmOperand*);
};

struct AsmVarAddr: public AsmVarBase {
   AsmVarAddr(AsmOperand*);
   void PrintBase() const override;
};

struct AsmVarDword: public AsmVarBase {
   AsmVarDword(AsmOperand*);
   void PrintBase() const override;
};

class AsmStrImmediate: public AsmImmediate {
   string _value;
public:
   AsmStrImmediate(string);
   string GetStrValue() const override;
   void PrintBase() const override;
};

class AsmMemory: public AsmOperand {
   int _offset;
   SizeType _size;
   AsmOperand* _oper;
public:
   AsmMemory(AsmOperand*, int = 0, SizeType = szNONE);
   AsmMemory(Register, int = 0, SizeType = szNONE);
   void Print() const override;
};

typedef vector<Asm*> Commands;
typedef vector<AsmDataBase*> Data;

class AsmCode {
   size_t labelCounter;
   AsmStrImmediate* formatStrReal;
   AsmStrImmediate* formatStrInt;
   AsmStrImmediate* formatStrNewLine;

   AsmStrImmediate functWrite;

   Data data;
   Commands commands;
public:
   AsmCode();
   void AddCmd(string);
   void AddCmd(OpCode);
   void AddCmd(OpCode, AsmVarAddr);
   void AddCmd(OpCode, AsmVarDword);
   void AddCmd(OpCode, Register);
   void AddCmd(OpCode, AsmMemory);
   void AddCmd(OpCode, AsmStrImmediate*);
   void AddCmd(OpCode, AsmStrImmediate);
   void AddCmd(OpCode, AsmIntImmediate);
   void AddCmd(OpCode, int, SizeType = szNONE);
   void AddCmd(OpCode, AsmOperand*, AsmOperand*);
   void AddCmd(OpCode, Register, Register);
   void AddCmd(OpCode, Register, int, SizeType = szNONE);
   void AddCmd(OpCode, AsmMemory, AsmIntImmediate);
   void AddCmd(OpCode, AsmMemory, Register);
   void AddCmd(OpCode, Register, AsmMemory);
   AsmStrImmediate* AddData(string);
   AsmStrImmediate* AddData(string, double);
   AsmStrImmediate* AddData(string, size_t);
   AsmStrImmediate* AddData(string, string);
   void AddLabel(AsmStrImmediate*);
   void AddLabel(AsmStrImmediate);
   void AddLabel(string);
   void AddSubroutineBegin(AsmStrImmediate*);
   void AddSubroutineEnd(AsmStrImmediate*);
   AsmStrImmediate* GenLabel(string);
   string GenStrLabel(string);
   void Print() const;
   void PushMemory(unsigned);
   void GenCallWriteForInt();
   void GenCallWriteForReal();
   void GenCallWriteForStr();
   void GenWriteNewLine();
};
