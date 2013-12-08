#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Register {
   EAX,
   EBX,
   ECX,
   EDX,
   ESP,
   EBP,
   AL
};

enum OpCode {
	EXIT,
   TEST,
	INC, 
	DEC,
	CALL,
	PUSH,
	POP,
	RET,
	MUL,
	DIV,
	NOT,
   NEG,
	JE,
	JL,
	JNL,
	JLE,
	JNLE,
	JNGE,
	JGE,
	JNG,
	JG,
	JMP,
	JNE,
   SAR,
   SAL,
   SETG,
   SETGE,
   SETL,
   SETLE,
   SETE,
   SETNE,
	MOV,
   MOVZB,
	ADD,
	SUB,
	CMP,
	XCHG,
	XOR,
	AND,
	OR,
	RCL,
	RCR,
	LEA,
   IMUL,
   IDIV,
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

class AsmDataStr: public AsmDataBase {
   string _value;
public:
   AsmDataStr(string, string);
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
public:
   AsmIntImmediate(int);
   AsmIntImmediate(const AsmIntImmediate&);
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
   AsmStrImmediate();
   AsmStrImmediate(const string&);
   AsmStrImmediate(const AsmStrImmediate&);
   string GetStrValue() const override;
   void PrintBase() const override;
};

class AsmMemory: public AsmOperand {
   AsmOperand* _oper;
   int _offset;
public:
   AsmMemory(AsmOperand*, int = 0);
   AsmMemory(AsmStrImmediate, int = 0);
   AsmMemory(AsmIntImmediate, int = 0);
   AsmMemory(Register, int = 0);
   void Print() const override;
};

typedef vector<Asm*> Commands;
typedef vector<AsmDataBase*> Data;

class AsmCode {
   bool hasIntFormat;
   bool hasRealFormat;
   bool hasStrFormat;
   bool hasNewLineFormat;
   AsmStrImmediate* formatStrReal;
   AsmStrImmediate* formatStrInt;
   AsmStrImmediate* formatStrStr;
   AsmStrImmediate* formatStrNewLine;

   AsmStrImmediate functWrite;

   Data data;
   Commands commands;
   unsigned label_counter;
public:
   AsmCode();
   string GenStrLabel();
   AsmStrImmediate GenLabel(string);
   string GenStrLabel(string);
   AsmStrImmediate LabelByStr(string);
   void AddCmd(AsmCmd*);
   void AddCmd(AsmLabel);
   void AddCmd(string);
   void AddCmd(OpCode);
   void AddCmd(OpCode, AsmOperand*);
   void AddCmd(OpCode, AsmVarAddr);
   void AddCmd(OpCode, AsmVarDword);
   void AddCmd(OpCode, Register);
   void AddCmd(OpCode, AsmMemory*);
   void AddCmd(OpCode, AsmMemory);
   void AddCmd(OpCode, AsmImmediate*);
   void AddCmd(OpCode, AsmStrImmediate);
   void AddCmd(OpCode, AsmIntImmediate);
   void AddCmd(OpCode, int);
   void AddCmd(OpCode, AsmOperand*, AsmOperand*);
   void AddCmd(OpCode, Register, Register);
   void AddCmd(OpCode, Register, AsmImmediate*);
   void AddCmd(OpCode, Register, AsmStrImmediate);
   void AddCmd(OpCode, Register, AsmIntImmediate);
   void AddCmd(OpCode, Register, int);
   void AddCmd(OpCode, AsmMemory*, Register);
   void AddCmd(OpCode, AsmMemory, Register);
   void AddCmd(OpCode, Register, AsmMemory*);
   void AddCmd(OpCode, Register, AsmMemory);
   void AddCmd(OpCode, AsmImmediate*, AsmMemory*);
   void AddCmd(OpCode, AsmMemory, AsmStrImmediate);
   void AddCmd(OpCode, AsmMemory, AsmIntImmediate);
   void AddData(AsmData*);
   AsmStrImmediate* AddData(string, size_t);
   AsmStrImmediate* AddData(string, string);
   void AddLabel(AsmStrImmediate*);
   void AddLabel(AsmStrImmediate);
   void AddLabel(string);
   void Print() const;
   void PushMemory(unsigned);
   void MoveMemory(unsigned);
   void AddMainFunctionLabel();
   void GenCallWriteForInt();
   void GenCallWriteForReal();
   void GenCallWriteForStr();
   void GenWriteNewLine();
};
