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
      case LEA:         return "lea";
      case JNE:         return "jne";
      case JMP:         return "jmp";
      case JE:          return "je";
      case JL:          return "jl";
      case JNL:         return "jnl";
      case JLE:         return "jle";
      case JNLE:        return "jnle";
      case JNGE:        return "jnge";
      case JGE:         return "jge";
      case JNG:         return "jng";
      case JG:          return "jg";
      case RCL:         return "rcl";
      case RCR:         return "rcr";
      case NOT:         return "not";
      case CMP:         return "cmp";
      case XCHG:        return "xchg";
      case XOR:         return "xor";
      case AND:         return "and";
      case OR:          return "or";
      case NEG:         return "neg";
      case EXIT:        return "exit";
      case TEST:        return "test";
      case INC:         return "inc";
      case DEC:         return "dec";
      case CALL:        return "call";
      case PUSH:        return "push";
      case POP:         return "pop";
      case RET:         return "ret";
      case IMUL:        return "imul";
      case MUL:         return "mul";
      case DIV:         return "div";
      case MOV:         return "mov";
      case MOVZB:       return "movzb";
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

AsmLabel::AsmLabel(AsmStrImmediate* ALabel):
   _label(ALabel)
{}

AsmLabel::AsmLabel(AsmStrImmediate ALabel):
   _label(new AsmStrImmediate(ALabel))
{}

AsmLabel::AsmLabel(string ALabel):
   _label(new AsmStrImmediate(ALabel))
{}

void AsmLabel::Print() const
{
   cout << "  ";
   _label->PrintBase();
   cout << ':';
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

AsmIntImmediate::AsmIntImmediate(const AsmIntImmediate& ASrc) :
   _value(ASrc._value)
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

AsmStrImmediate::AsmStrImmediate()
{}

AsmStrImmediate::AsmStrImmediate(const string& AValue):
   _value(AValue)
{}

AsmStrImmediate::AsmStrImmediate(const AsmStrImmediate& ASrc):
   _value(ASrc._value)
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

AsmMemory::AsmMemory(AsmStrImmediate AOper, int AOffset):
   _oper(new AsmStrImmediate(AOper)),
   _offset(AOffset)
{}

AsmMemory::AsmMemory(AsmIntImmediate AOper, int AOffset):
   _oper(new AsmIntImmediate(AOper)),
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
   label_counter(0),
   hasIntFormat(false),
   hasRealFormat(false),
   hasStrFormat(false),
   hasNewLineFormat(false)
{}

string AsmCode::GenStrLabel()
{
   stringstream s;
   s << label_counter++;
   return s.str();
}

AsmStrImmediate AsmCode::GenLabel(string prefix)
{
   stringstream s;
   s << prefix << '_' << label_counter++;
   return AsmStrImmediate(s.str());
}

string AsmCode::GenStrLabel(string prefix)
{
   stringstream s;
   s << prefix << '_' << label_counter++;
   return s.str();
}

AsmStrImmediate AsmCode::LabelByStr(string str)
{
   return AsmStrImmediate(str);
}

void AsmCode::AddCmd(AsmCmd* cmd)
{
   commands.push_back(cmd);
}

void AsmCode::AddCmd(AsmLabel label)
{
   commands.push_back(new AsmLabel(label));
}

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

void AsmCode::AddCmd(OpCode cmd, AsmOperand* oper)
{
   commands.push_back(new AsmCmd1(cmd, oper));
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

void AsmCode::AddCmd(OpCode cmd, AsmMemory* mem)
{
   commands.push_back(new AsmCmd1(cmd, mem));
}

void AsmCode::AddCmd(OpCode cmd, AsmImmediate* imm)
{
   commands.push_back(new AsmCmd1(cmd, imm));
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

void AsmCode::AddCmd(OpCode cmd, Register reg, AsmImmediate* src)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), src));
}

void AsmCode::AddCmd(OpCode cmd, Register reg, AsmStrImmediate src)
{
   AsmStrImmediate* imm = new AsmStrImmediate(src);
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), imm));
}

void AsmCode::AddCmd(OpCode cmd, Register reg, AsmIntImmediate src)
{
   AsmIntImmediate* imm = new AsmIntImmediate(src);
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), imm));
}

void AsmCode::AddCmd(OpCode cmd, AsmMemory* mem, Register reg)
{
   commands.push_back(new AsmCmd2(cmd, mem, new AsmRegister(reg)));
}

void AsmCode::AddCmd(OpCode cmd, AsmMemory mem, Register reg)
{
   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), new AsmRegister(reg)));
}

void AsmCode::AddCmd(OpCode cmd, Register reg, AsmMemory* mem)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), mem));
}

void AsmCode::AddCmd(OpCode cmd, Register reg, AsmMemory mem)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), new AsmMemory(mem)));
}

void AsmCode::AddCmd(OpCode cmd, AsmImmediate* src, AsmMemory* mem)
{
   commands.push_back(new AsmCmd2(cmd, src, mem));
}

void AsmCode::AddCmd(OpCode cmd, AsmMemory mem, AsmStrImmediate src)
{
   AddCmd(cmd, new AsmMemory(mem), new AsmStrImmediate(src));
}

void AsmCode::AddCmd(OpCode cmd, AsmMemory mem, AsmIntImmediate intImm)
{
   AddCmd(cmd, new AsmMemory(mem), new AsmIntImmediate(intImm));
}

void AsmCode::AddData(AsmData* newData)
{
   data.push_back(newData);
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

void AsmCode::AddLabel(AsmStrImmediate* label)
{
   commands.push_back(new AsmLabel(label));
}

void AsmCode::AddLabel(AsmStrImmediate label)
{
   commands.push_back(new AsmLabel(label));
}

void AsmCode::AddLabel(string label)
{
   commands.push_back(new AsmLabel(label));
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

void AsmCode::MoveMemory(unsigned size)
{
   AddCmd(POP, EBX);
   AddCmd(POP, EDX);
   AddCmd(SUB, ESP, size);
   for (size_t i = 0; i < size; i += 4) {
      AddCmd(MOV, AsmMemory(EBX, i), EAX);
      AddCmd(MOV, EAX, AsmMemory(EDX, size - i - 4));
   }
}

void AsmCode::AddMainFunctionLabel()
{
   AddCmd("main:\n");
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
   AddCmd(PUSH, formatStrNewLine);
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 4);
}
