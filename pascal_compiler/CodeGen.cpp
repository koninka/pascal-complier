#include "CodeGen.h"

#include <sstream>


string GetSizeTypeText(SizeType type)
{
   switch (type) {
      case szNONE:   return "";
      case szBYTE:   return "byte ptr ";
      case szDWORD:  return "dword ptr ";
      case szQWORD:  return "qword ptr ";
      default:       return "";
   }
}

string GetReg(Register reg)
{
   switch (reg) {
      case EAX:   return "eax";
      case EBX:   return "ebx";
      case ECX:   return "ecx";
      case EDX:   return "edx";
      case ESP:   return "esp";
      case EBP:   return "ebp";
      case AX:    return "ax";
      case AL:    return "al";
      case ST1:   return "st(1)";
      case ST:    return "st";
      default:    return "";
   }
}

bool CmpOperands(AsmOperand* oper1, AsmOperand* oper2)
{
   bool result = false;
   if (TryToCastOperand<AsmRegister>(oper1)) {
      result = *CastOperand<AsmRegister>(oper1) == oper2;
   } else if (TryToCastOperand<AsmIntImmediate>(oper1)) {
      result = *CastOperand<AsmIntImmediate>(oper1) == oper2;
   } else if (TryToCastOperand<AsmStrImmediate>(oper1)) {
      result = *CastOperand<AsmStrImmediate>(oper1) == oper2;
   } else if (TryToCastOperand<AsmVarAddr>(oper1)) {
      result = *CastOperand<AsmVarAddr>(oper1) == oper2;
   } else if (TryToCastOperand<AsmMemory>(oper1)) {
      result = *CastOperand<AsmMemory>(oper1) == oper2;
   }
   return result;
}

string GetCmd(OpCode opCode)
{
   switch (opCode) {
      case JNE:         return "jne";
      case JMP:         return "jmp";
      case JGE:         return "jge";
      case JE:          return "je";
      case JG:          return "jg";
      case JL:          return "jl";
      case FLD:         return "fld";
      case FILD:        return "fild";
      case FCHS:        return "fchs";
      case FSTP:        return "fstp";
      case FXCH:        return "fxch";
      case FADDP:       return "faddp";
      case FMULP:       return "fmulp";
      case FSUBP:       return "fsubp";
      case FDIVP:       return "fdivp";
      case FDIVRP:      return "fdivrp";
      case FCOMPP:      return "fcompp";
      case FNSTSW:      return "fnstsw";
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
      case MOVZB:       return "movzb";
      case INC:         return "inc";
      case DEC:         return "dec";
      case ADD:         return "add";
      case SUB:         return "sub";
      case SAHF:        return "sahf";
      case SETA:        return "seta";
      case SETAE:       return "setae";
      case SETB:        return "setb";
      case SETBE:       return "setbe";
      case SETG:        return "setg";
      case SETGE:       return "setge";
      case SETL:        return "setl";
      case SETLE:       return "setle";
      case SETE:        return "sete";
      case SETNE:       return "setne";
      default:          return "";
   }
}


Asm::Asm(OpCode AOpCode, AsmOperand* AArg1, AsmOperand* AArg2):
   opCode(AOpCode),
   arg1(AArg1),
   arg2(AArg2)
{}

bool Asm::operator==(OpCode AOpCode)
{
   return opCode == AOpCode;
}

bool Asm::operator!=(OpCode AOpCode)
{
   return opCode != AOpCode;
}

OpCode Asm::GetOpCode() const
{
   return opCode;
}

void Asm::Print() const
{}

AsmCmd0::AsmCmd0(OpCode AOpCode):
   Asm(AOpCode)
{}

void AsmCmd0::Print() const
{
   cout << '\t' << GetCmd(opCode);
}

AsmCmd1::AsmCmd1(OpCode AOpCode, AsmOperand* AOper):
   Asm(AOpCode, AOper)
{}

void AsmCmd1::Print() const
{
   cout << '\t' << GetCmd(opCode) << '\t';
   arg1->PrintBase();
}

AsmCmd2::AsmCmd2(OpCode AOpCode, AsmOperand* ADest, AsmOperand* ASrc):
   Asm(AOpCode, ADest, ASrc)
{}

void AsmCmd2::Print() const
{
   cout << '\t' << GetCmd(opCode) << '\t';
   arg1->Print();
   cout << ", ";
   arg2->Print();
}

AsmLabel::AsmLabel(AsmStrImmediate* ALabel):
   Asm(LABEL),
   _label(ALabel)
{}

AsmLabel::AsmLabel(AsmStrImmediate ALabel):
   Asm(LABEL),
   _label(new AsmStrImmediate(ALabel))
 {}

AsmLabel::AsmLabel(string ALabel):
   Asm(LABEL),
   _label(new AsmStrImmediate(ALabel))
 {}

void AsmLabel::Print() const
{
   _label->PrintBase();
   cout << ':';
}

AsmSubroutineBase::AsmSubroutineBase(AsmStrImmediate* ALabel):
   Asm(SUBROUTINE),
   _label(ALabel)
{}

AsmSubroutineBegin::AsmSubroutineBegin(AsmStrImmediate* ALabel) :
   AsmSubroutineBase(ALabel)
{}

void AsmSubroutineBegin::Print() const
{
   _label->PrintBase();
   cout << " proc";
}

AsmSubroutineEnd::AsmSubroutineEnd(AsmStrImmediate* ALabel):
   AsmSubroutineBase(ALabel)
{}

void AsmSubroutineEnd::Print() const
{
   _label->PrintBase();
   cout << " endp";
}

AsmRawCmd::AsmRawCmd(string cmd):
   Asm(RAW_STR),
   _str(cmd)
{}

void AsmRawCmd::Print() const
{
   cout << _str;
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

AsmDataReal::AsmDataReal(string AName, double AValue):
   AsmDataBase(AName),
   _value(AValue)
{}

void AsmDataReal::Print() const
{
   cout << "\t" << _name << " real4 " << fixed << _value;
}

AsmDataStr::AsmDataStr(string AName, string AValue):
   AsmDataBase(AName),
   _value(AValue)
{}

void AsmDataStr::Print() const
{
   cout << "\t" << _name << " db \"" << _value << "\", 0";
}

AsmDataNewLine::AsmDataNewLine(string AName):
   AsmDataBase(AName)
{}

void AsmDataNewLine::Print() const
{
   cout << '\t' << _name << " db 10, 0";
}

void AsmOperand::Print() const
{}

void AsmOperand::PrintBase() const
{
   Print();
}

void AsmOperand::SetSizeType(SizeType)
{}

bool AsmOperand::operator==(AsmOperand* oper)
{
   return false;
}

AsmRegister::AsmRegister(Register AReg):
   _register(AReg)
{}

bool AsmRegister::operator==(AsmOperand* oper)
{
   bool result = false;
   if (TryToCastOperand<AsmRegister>(oper)) {
      result = _register == CastOperand<AsmRegister>(oper)->_register;
   }
   return result;
}

bool AsmRegister::operator!=(AsmOperand* oper)
{
   return !(*this == oper);
}

bool AsmRegister::operator==(AsmRegister reg)
{
   return _register == reg._register;
}

bool AsmRegister::operator!=(AsmRegister reg)
{
   return _register != reg._register;
}

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

AsmIntImmediate::AsmIntImmediate(int AValue, SizeType AType):
   _value(AValue),
   _sizeType(AType)
{}

bool AsmIntImmediate::operator==(AsmOperand* oper)
{
   bool result = false;
   if (TryToCastOperand<AsmIntImmediate>(oper)) {
      result = _value == CastOperand<AsmIntImmediate>(oper)->_value;// && CastOperand<AsmIntImmediate>(oper)->_sizeType;
   }
   return result;;
}

void AsmIntImmediate::SetSizeType(SizeType AType)
{
   _sizeType = AType;
}

int AsmIntImmediate::GetIntValue() const
{
   return _value;
}

void AsmIntImmediate::PrintBase() const
{
   cout << GetSizeTypeText(_sizeType) << _value;
}

AsmVarBase::AsmVarBase(AsmOperand* AOper):
   arg(AOper)
{}

AsmVarAddr::AsmVarAddr(AsmOperand* AOper, int AOffset, SizeType AType):
   AsmVarBase(AOper),
   _offset(AOffset),
   _sizeType(AType)
{}

bool AsmVarAddr::operator==(AsmOperand* oper_)
{
   bool result = false;
   if (TryToCastOperand<AsmVarAddr>(oper_)) {
      result =
            _offset == CastOperand<AsmVarAddr>(oper_)->_offset
         && _sizeType == CastOperand<AsmVarAddr>(oper_)->_sizeType
         && CmpOperands(arg, CastOperand<AsmVarAddr>(oper_)->arg);
   }
   return result;
}

int AsmVarAddr::GetOffset() const
{
   return _offset;
}

void AsmVarAddr::PrintBase() const
{
   cout << GetSizeTypeText(_sizeType) << "offset ";
   arg->PrintBase();
   if (_offset) {
      cout << (_offset > 0 ? " + " : " - ") << abs(_offset);
   }
}

AsmStrImmediate::AsmStrImmediate(string AValue):
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

bool AsmStrImmediate::operator==(AsmOperand* oper)
{
   bool result = false;
   if (TryToCastOperand<AsmStrImmediate>(oper)) {
      result = _value == CastOperand<AsmStrImmediate>(oper)->_value;
   }
   return result;
}

AsmMemory::AsmMemory(AsmOperand* AOper, int AOffset, SizeType AType):
   arg(AOper),
   _offset(AOffset),
   _size(AType)
{}

AsmMemory::AsmMemory(Register AReg, int AOffset, SizeType AType):
   arg(new AsmRegister(AReg)),
   _offset(AOffset),
   _size(AType)
{}

AsmMemory::AsmMemory(AsmRegister AReg, int AOffset, SizeType AType):
   arg(new AsmRegister(AReg)),
   _offset(AOffset),
   _size(AType)
{}

bool AsmMemory::operator==(AsmOperand* oper)
{
   bool result = false;
   if (TryToCastOperand<AsmMemory>(oper)) {
      result =
            _offset == CastOperand<AsmMemory>(oper)->_offset
         //&& _size == CastOperand<AsmMemory>(oper)->_size
         && CmpOperands(arg, CastOperand<AsmMemory>(oper)->arg);
   }
   return result;
}

int AsmMemory::GetOffset() const
{
   return _offset;
}

void AsmMemory::SetOffset(int newOffset)
{
   _offset = newOffset;
}

SizeType AsmMemory::GetSizeType() const
{
   return _size;
}

void AsmMemory::SetSizeType(SizeType AType)
{
   _size = AType;
}

void AsmMemory::Print() const
{
   cout << GetSizeTypeText(_size);
   cout << '[';
   arg->PrintBase();
   if (_offset) {
      cout << (_offset > 0 ? " + " : " - ") << abs(_offset);
   }
   cout << ']';
}

void AsmCodeBase::AddCmd(string rawCmd)
{
   commands.push_back(new AsmRawCmd(rawCmd));
}

void AsmCodeBase::AddCmd(OpCode cmd)
{
   commands.push_back(new AsmCmd0(cmd));
}

void AsmCodeBase::AddCmd(Command cmd)
{
   commands.push_back(cmd);
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmMemory mem)
{
   commands.push_back(new AsmCmd1(cmd, new AsmMemory(mem)));
}

void AsmCodeBase::AddCmd(OpCode cmd, Register dest, Register src)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(dest), new AsmRegister(src)));
}

void AsmCodeBase::AddCmd(OpCode cmd, Register dest, AsmStrImmediate* src)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(dest), src));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmRegister dest, AsmRegister src)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(dest), new AsmRegister(src)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmRegister dest, AsmOperand* src)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(dest), src));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmVarAddr oper)
{
   commands.push_back(new AsmCmd1(cmd, new AsmVarAddr(oper)));
}

void AsmCodeBase::AddCmd(OpCode cmd, Register reg)
{
   commands.push_back(new AsmCmd1(cmd, new AsmRegister(reg)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper)
{
   commands.push_back(new AsmCmd1(cmd, oper));
}

//void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper, SizeType AType)
//{
//   oper->SetSizeType(AType);
//   commands.push_back(new AsmCmd1(cmd, oper));
//}

void AsmCodeBase::AddCmd(OpCode cmd, AsmStrImmediate* strImm)
{
   commands.push_back(new AsmCmd1(cmd, strImm));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmStrImmediate strImm)
{
   AsmStrImmediate* tmp = new AsmStrImmediate(strImm);
   commands.push_back(new AsmCmd1(cmd, tmp));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmIntImmediate intImm)
{
   AsmIntImmediate* tmp = new AsmIntImmediate(intImm);
   commands.push_back(new AsmCmd1(cmd, tmp));
}

void AsmCodeBase::AddCmd(OpCode cmd, int intImm, SizeType type)
{
   AsmIntImmediate* tmp = new AsmIntImmediate(intImm, type);
   commands.push_back(new AsmCmd1(cmd, tmp));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper1, AsmOperand* oper2)
{
   //oper2->SetSizeType(AType);
   commands.push_back(new AsmCmd2(cmd, oper1, oper2));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper1, AsmOperand* oper2, SizeType AType)
{
   oper2->SetSizeType(AType);
   AddCmd(cmd, oper1, oper2);
}

void AsmCodeBase::AddCmd(OpCode cmd, Register reg, int intImm, SizeType type)
{
   AsmIntImmediate* imm = new AsmIntImmediate(intImm, type);
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), imm));
}

//void AsmCodeBase::AddCmd(OpCode cmd, AsmMemory mem, int intImm, SizeType type)
//{
//   AsmIntImmediate* imm = new AsmIntImmediate(intImm, type);
//   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), imm));
//}

void AsmCodeBase::AddCmd(OpCode cmd, Register reg, AsmIntImmediate intImm)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), new AsmIntImmediate(intImm)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmRegister reg, AsmIntImmediate intImm)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), new AsmIntImmediate(intImm)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmMemory mem, AsmIntImmediate intImm)
{
   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), new AsmIntImmediate(intImm)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper, AsmIntImmediate intImm)
{
   AddCmd(cmd, oper, new AsmIntImmediate(intImm));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper, AsmVarAddr addr)
{
   commands.push_back(new AsmCmd2(cmd, oper, new AsmVarAddr(addr)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmVarAddr addr, AsmOperand* oper)
{
   commands.push_back(new AsmCmd2(cmd, new AsmVarAddr(addr), oper));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmMemory mem, Register reg)
{
   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), new AsmRegister(reg)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmMemory mem, AsmRegister reg)
{
   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), new AsmRegister(reg)));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmMemory mem, AsmOperand* oper)
{
   commands.push_back(new AsmCmd2(cmd, new AsmMemory(mem), oper));
}

void AsmCodeBase::AddCmd(OpCode cmd, AsmOperand* oper, AsmMemory mem)
{
   commands.push_back(new AsmCmd2(cmd, oper, new AsmMemory(mem)));
}

void AsmCodeBase::AddCmd(OpCode cmd, Register reg, AsmMemory mem)
{
   commands.push_back(new AsmCmd2(cmd, new AsmRegister(reg), new AsmMemory(mem)));
}

void AsmCodeBase::CleanCommands()
{
   commands.clear();
}

Commands AsmCodeBase::GetCommands() const
{
   return commands;
}

AsmCode::AsmCode():
   labelCounter(0),
   functWrite(AsmStrImmediate("crt_printf")),
   formatStrInt(nullptr),
   formatStrReal(nullptr),
   formatStrNewLine(nullptr)
{}

AsmStrImmediate* AsmCode::AddData(string name)
{
   name = "fmt_str_" + name;
   data.push_back(new AsmDataNewLine(name));
   return new AsmStrImmediate(name);
}

AsmStrImmediate* AsmCode::AddData(string name, double value)
{
   name = GenStrLabel("f" + name);
   data.push_back(new AsmDataReal(name, value));
   return new AsmStrImmediate(name);
}

AsmStrImmediate* AsmCode::AddData(string name, size_t size)
{
   name = "v_" + name;
   data.push_back(new AsmData(name, size));
   return new AsmStrImmediate(name);
}

AsmStrImmediate* AsmCode::AddData(string name, string value)
{
   name = "fmt_" + name;
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
   commands.push_back(new AsmLabel(new AsmStrImmediate(label)));
}

void AsmCode::AddSubroutineBegin(AsmStrImmediate* strImm)
{
   commands.push_back(new AsmSubroutineBegin(strImm));
}

void AsmCode::AddSubroutineEnd(AsmStrImmediate* strImm)
{
   commands.push_back(new AsmSubroutineEnd(strImm));
}

AsmStrImmediate* AsmCode::GenLabel(string prefix)
{
   prefix = '@' + prefix + '_' + to_string(labelCounter++);
   return new AsmStrImmediate(prefix);
}

string AsmCode::GenStrLabel(string value)
{
   return value + to_string(labelCounter++);
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
   AddCmd(POP, EAX);
   if (size <= 16) {
      for (size_t i = 0; i < size; i += 4) {
         //AddCmd(MOV, EBX, AsmMemory(EAX, size - i - 4));
         AddCmd(PUSH, AsmMemory(EAX, size - i - 4));
      }
   } else {
      AsmStrImmediate* labelBegin = GenLabel("L");
      AsmStrImmediate* labelEnd = GenLabel("L");
      AddCmd(ADD, EAX, size);
      AddCmd(MOV, EBX, 0);
      AddLabel(labelBegin);
      AddCmd(CMP, EBX, size);
      AddCmd(JGE, labelEnd);
      AddCmd(SUB, EAX, 4);
      AddCmd(PUSH, AsmMemory(EAX, 0, szDWORD));
      AddCmd(ADD, EBX, 4);
      AddCmd(JMP, labelBegin);
      AddLabel(labelEnd);
   }
}

void AsmCode::GenCallWriteForInt()
{
   formatStrInt = formatStrInt == nullptr ? AddData("int", "%d") : formatStrInt;
   AddCmd(PUSH, AsmVarAddr(formatStrInt));
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 8);
}

void AsmCode::GenCallWriteForReal()
{
   formatStrReal = formatStrReal == nullptr ? AddData("float", "% 0.14E") : formatStrReal;
   AddCmd(FLD, AsmMemory(ESP, 0, szDWORD));
   AddCmd(SUB, ESP, 8);
   AddCmd(FSTP, AsmMemory(ESP, 0, szQWORD));
   AddCmd(PUSH, AsmVarAddr(formatStrReal));
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 12);
}

void AsmCode::GenCallWriteForStr()
{
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 4);
}

void AsmCode::GenWriteNewLine()
{
   formatStrNewLine = formatStrNewLine == nullptr ? AddData("new_line") : formatStrNewLine;
   AddCmd(PUSH, AsmVarAddr(formatStrNewLine));
   AddCmd(CALL, functWrite);
   AddCmd(ADD, ESP, 4);
}

void AsmCode::ReplaceCommands(Commands newCommands, size_t idx, size_t amount)
{
   commands.erase(commands.begin() + idx, commands.begin() + idx + amount);
   for (auto &command : newCommands) {
      commands.insert(commands.begin() + idx++, command);
   }
}

Commands AsmCode::GetCommands(size_t idx, size_t amount)
{
   return Commands(commands.begin() + idx, commands.begin() + idx + amount);
}

size_t AsmCode::GetCmdAmount() const
{
   return commands.size();
}
