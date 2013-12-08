#include "CodeGen.h"

#include <sstream>

string GetReg(Register reg)
{
   switch (reg) {
      case EAX:   return "eax";
      case EBX:   return "ebx";
      case ECX:   return "ecx";
      case EDX:   return "edx";
      case ESP:   return "esp";
      case EBP:   return "ebp";
      case AL:    return "al";
      default:    return "";
   }
}

string GetCmd(OpCode opCode)
{
   switch (opCode) {
      case SAR:         return "sar";
      case SAL:         return "sal";
      case LEA:         return "lea";
      case RCL:         return "rcl";
      case RCR:         return "rcr";
      case NOT:         return "not";
      case CMP:         return "cmp";
      case XOR:         return "xor";
      case AND:         return "and";
      case OR:          return "or";
      case NEG:         return "neg";
      case TEST:        return "test";
      case CALL:        return "call";
      case PUSH:        return "push";
      case POP:         return "pop";
      case RET:         return "ret";
      case IMUL:        return "imul";
      case MUL:         return "mul";
      case DIV:         return "div";
      case IDIV:        return "idiv";
      case MOV:         return "mov";
      case MOVZX:       return "movzx";
      case ADD:         return "add";
      case SUB:         return "sub";
      case SETG:        return "setg";
      case SETGE:       return "setge";
      case SETL:        return "setl";
      case SETLE:       return "setle";
      case SETE:        return "sete";
      case SETNE:       return "setne";
      default:          return "";
   }
}


void Asm::Print() const
{}

AsmCmd::AsmCmd(OpCode AOpCode):
   opCode(AOpCode)
{}

AsmCmd0::AsmCmd0(OpCode AOpCode):
   AsmCmd(AOpCode)
{}

void AsmCmd0::Print() const
{
   cout << '\t' << GetCmd(opCode);
}

AsmCmd1::AsmCmd1(OpCode AOpCode, AsmOperand* AOper):
   AsmCmd(AOpCode),
   _oper(AOper)
{}

void AsmCmd1::Print() const
{
   cout << '\t' << GetCmd(opCode) << '\t';
   _oper->PrintBase();
}

AsmCmd2::AsmCmd2(OpCode AOpCode, AsmOperand* ADest, AsmOperand* ASrc):
   AsmCmd(AOpCode),
   _dest(ADest),
   _src(ASrc)
{}

void AsmCmd2::Print() const
{
   cout << '\t' << GetCmd(opCode) << '\t';
   _dest->Print();
   cout << ", ";
   _src->Print();
}

AsmDataBase::AsmDataBase(string AName):
   _name(AName)
{}

void AsmDataBase::Print() const
{}

AsmData::AsmData(string AName, size_t ASize):
   AsmDataBase(AName),
   _size(ASize)
{}

void AsmData::Print() const
{
   cout << "\t" << _name << " db " << _size << " dup(0)";
}

AsmDataStr::AsmDataStr(string AName, string AValue):
   AsmDataBase(AName),
   _value(AValue)
{}

void AsmDataStr::Print() const
{
   cout << "\t" << _name << " db \"" << _value << "\", 0";
}

AsmRawCmd::AsmRawCmd(string cmd):
   _str(cmd)
{}

void AsmRawCmd::Print() const
{
   cout << _str;
}

void AsmOperand::Print() const
{}

void AsmOperand::PrintBase() const
{
   Print();
}

AsmRegister::AsmRegister(Register AReg):
   _register(AReg)
{}

void AsmRegister::Print() const
{
   cout << GetReg(_register);
}

void AsmRegister::PrintBase() const
{
   Print();
}

string AsmImmediate::GetStrValue() const
{
   return "";
}

int AsmImmediate::GetIntValue() const
{
   return 0;
}

void AsmImmediate::Print() const
{
   PrintBase();
}

AsmIntImmediate::AsmIntImmediate(int AValue):
   _value(AValue)
{}

int AsmIntImmediate::GetIntValue() const
{
   return _value;
}

void AsmIntImmediate::PrintBase() const
{
   cout << "dword ptr " <<_value;
}

AsmVarBase::AsmVarBase(AsmOperand* AOper):
   oper(AOper)
{}

AsmVarAddr::AsmVarAddr(AsmOperand* AOper) :
   AsmVarBase(AOper)
{}

void AsmVarAddr::PrintBase() const
{
   cout << "offset ";
   oper->PrintBase();
}

AsmVarDword::AsmVarDword(AsmOperand* AOper):
   AsmVarBase(AOper)
{}

void AsmVarDword::PrintBase() const
{
   cout << "dword ptr ";
   oper->PrintBase();
}

AsmStrImmediate::AsmStrImmediate(const string& AValue):
   _value(AValue)
{}

void AsmStrImmediate::PrintBase() const
{
   cout << _value;
}

string AsmStrImmediate::GetStrValue() const
{
   return _value;
}

AsmMemory::AsmMemory(AsmOperand* AOper, int AOffset):
   _oper(AOper),
   _offset(AOffset)
{}

AsmMemory::AsmMemory(Register AReg, int AOffset):
   _oper(new AsmRegister(AReg)),
   _offset(AOffset)
{}

void AsmMemory::Print() const
{
   cout << '[';
   _oper->PrintBase();
   if (_offset) {
      cout << " + " << _offset;
   }
   cout << ']';
}

AsmCode::AsmCode():
   functWrite(AsmStrImmediate("crt_printf")),
   hasIntFormat(false),
   hasRealFormat(false),
   hasStrFormat(false),
   hasNewLineFormat(false)
{}

void AsmCode::AddCmd(string raw_cmd)
{
   commands.push_back(new AsmRawCmd(raw_cmd));
}

void AsmCode::AddCmd(OpCode cmd)
{
   commands.push_back(new AsmCmd0(cmd));
}

void AsmCode::AddCmd(OpCode cmd, AsmMemory mem)
{
   commands.push_back(new AsmCmd1(cmd, new AsmMemory(mem)));
}

void AsmCode::AddCmd(OpCode cmd, Register dest, Register src)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(dest), new AsmRegister(src)));
}

void AsmCode::AddCmd(OpCode cmd, AsmVarAddr oper)
{
   commands.push_back(new AsmCmd1(cmd, new AsmVarAddr(oper)));
}

void AsmCode::AddCmd(OpCode cmd, AsmVarDword oper)
{
   commands.push_back(new AsmCmd1(cmd, new AsmVarDword(oper)));
}

void AsmCode::AddCmd(OpCode cmd, Register reg)
{
   commands.push_back(new AsmCmd1(cmd, new AsmRegister(reg)));
}

void AsmCode::AddCmd(OpCode cmd, AsmStrImmediate str_imm)
{
   AsmStrImmediate* tmp = new AsmStrImmediate(str_imm);
   commands.push_back(new AsmCmd1(cmd, tmp));
}

void AsmCode::AddCmd(OpCode cmd, AsmIntImmediate int_imm)
{
   AsmIntImmediate* tmp = new AsmIntImmediate(int_imm);
   commands.push_back(new AsmCmd1(cmd, tmp));
}

void AsmCode::AddCmd(OpCode cmd, int int_imm)
{
   AsmIntImmediate* tmp = new AsmIntImmediate(int_imm);
   commands.push_back(new AsmCmd1(cmd, tmp));
}

void AsmCode::AddCmd(OpCode cmd, AsmOperand* oper1, AsmOperand* oper2)
{
   commands.push_back(new AsmCmd2(cmd, oper1, oper2));
}

void AsmCode::AddCmd(OpCode cmd, Register reg, int intImm)
{
   AsmIntImmediate* imm = new AsmIntImmediate(intImm);
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), imm));
}

void AsmCode::AddCmd(OpCode cmd, AsmMemory mem, Register reg)
{
   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), new AsmRegister(reg)));
}

void AsmCode::AddCmd(OpCode cmd, Register reg, AsmMemory mem)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), new AsmMemory(mem)));
}

AsmStrImmediate* AsmCode::AddData(string name, size_t size)
{
   name = "v_" + name;
   data.push_back(new AsmData(name, size));
   return new AsmStrImmediate(name);
}

AsmStrImmediate* AsmCode::AddData(string name, string value)
{
   name = "format_str_" + name;
   data.push_back(new AsmDataStr(name, value));
   return new AsmStrImmediate(name);
}

void AsmCode::Print() const
{
   cout << ".686\n"
      ".model flat, stdcall\n"
      "include c:\\masm32\\include\\msvcrt.inc\n"
      "includelib c:\\masm32\\lib\\msvcrt.lib\n"
      ".data\n";
   for (auto &dd : data) {
      dd->Print();
      cout << endl;
   }
   cout << ".code\n";
   for (auto &command : commands) {
      command->Print();
      cout << endl;
   }
}

void AsmCode::PushMemory(unsigned size)
{
   AddCmd(POP, EBX);
   for (size_t i = 0; i < size; i += 4) {
      AddCmd(MOV, EAX, AsmMemory(EBX, size - i - 4));
      AddCmd(PUSH, EAX);
   }
}

void AsmCode::GenCallWriteForInt()
{
   if (!hasIntFormat) {
      formatStrInt = AddData("int", "%d");
      hasIntFormat = true;
   }
   AddCmd(PUSH, AsmVarAddr(formatStrInt));
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 8);
}

void AsmCode::GenCallWriteForReal()
{
   if (!hasRealFormat) {
      formatStrReal = AddData("float", "%f");
      hasRealFormat = true;
   }
}

void AsmCode::GenCallWriteForStr()
{
   if (!hasStrFormat) {
      formatStrStr = AddData("string", "%s");
      hasStrFormat = true;
   }
   AddCmd(PUSH, AsmVarAddr(formatStrStr));
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 8);
}

void AsmCode::GenWriteNewLine()
{
   if (!hasNewLineFormat) {
      formatStrNewLine = AddData("new_line", "\\n");
      hasNewLineFormat = true;
   }
   AddCmd(PUSH, AsmVarAddr(formatStrNewLine));
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 4);
}
