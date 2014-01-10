#include "optimization.h"

static bool IsCmd1(Command cmd)
{
   return TryToCast<AsmCmd1>(cmd);
}

static bool IsCmd2(Command cmd)
{
   return TryToCast<AsmCmd2>(cmd);
}

static bool IsReg(AsmOperand* oper)
{
   return TryToCast<AsmRegister>(oper);
}

static AsmRegister GetRegister(AsmOperand* oper)
{
   return *CastOperand<AsmRegister>(oper);
}

static bool IsMem(AsmOperand* oper)
{
   return TryToCast<AsmMemory>(oper);
}

static AsmMemory GetMem(AsmOperand* oper)
{
   return *CastOperand<AsmMemory>(oper);
}

static bool IsAddr(AsmOperand* oper)
{
   return TryToCast<AsmVarAddr>(oper);
}

static AsmVarAddr GetAddr(AsmOperand* oper)
{
   return *CastOperand<AsmVarAddr>(oper);
}

static bool IsIntImm(AsmOperand* oper)
{
   return TryToCast<AsmIntImmediate>(oper);
}

static int GetIntImmVal(AsmOperand* oper)
{
   return CastOperand<AsmIntImmediate>(oper)->GetIntValue();
}

static bool IsStrImm(AsmOperand* oper)
{
   return TryToCast<AsmStrImmediate>(oper);
}

static bool operator==(AsmOperand* oper, Register reg)
{
   return AsmRegister(reg) == oper;
}

static bool operator!=(AsmOperand* oper, Register reg)
{
   return AsmRegister(reg) != oper;
}

static bool IsEqOperands(AsmOperand* oper1, AsmOperand* oper2)
{
   bool result = false;
   if (IsReg(oper1) && IsReg(oper2)) {
      result = GetRegister(oper1) == GetRegister(oper2);
   } else if (IsStrImm(oper1) && IsStrImm(oper2)) {
      result = CastOperand<AsmStrImmediate>(oper1)->GetStrValue() == CastOperand<AsmStrImmediate>(oper2)->GetStrValue();
   } else if (IsAddr(oper1) && IsAddr(oper2)) {
      result = CastOperand<AsmVarAddr>(oper1) == oper2; /// ��������
   }
   return result;
}

Optimizator::Optimizator()
{
   optimizations.push_back(&Optimizator::OptimizationFor1Cmd);
   optimizations.push_back(&Optimizator::OptimizationFor2Cmd);
   optimizations.push_back(&Optimizator::OptimizationFor3Cmd);
   optimizations.push_back(&Optimizator::OptimizationFor4Cmd);

   //-------------------------------------------------------------------------
   //-------------------------ONE COMMAND OPTIMIZATIONS-----------------------
   Add1(
      [this]() -> bool {
         return (*Cmd(1) == ADD || *Cmd(1) == SUB) && IsIntImm(Cmd(1)->arg2) && abs(GetIntImmVal(Cmd(1)->arg2)) <= 1;
      },
      [this]() {
         int val = GetIntImmVal(Cmd(1)->arg2);
         if (val == 1) {
            cmdsContainer.AddCmd(*Cmd(1) == ADD ? INC : DEC, Cmd(1)->arg1);
         } else if (val == -1) {
            cmdsContainer.AddCmd(*Cmd(1) == ADD ? DEC : INC, Cmd(1)->arg1);
         }
      }
   );
   Add1(
      [this]() -> bool {
         return *Cmd(1) == MOV && IsReg(Cmd(1)->arg1) && IsAddr(Cmd(1)->arg2) && GetAddr(Cmd(1)->arg2).GetOffset() == 0; // mov R, offset strImm -> lea R, strImm
      },
      [this]() {
         cmdsContainer.AddCmd(LEA, Cmd(1)->arg1, GetAddr(Cmd(1)->arg2).arg);
      }
   );
   Add1(
      [this]() -> bool {
         return *Cmd(1) == MOV && IsReg(Cmd(1)->arg1) && IsIntImm(Cmd(1)->arg2) && GetIntImmVal(Cmd(1)->arg2) == 0;      // mov R, 0 -> xor R, R
      },
      [this]() {
         cmdsContainer.AddCmd(XOR, Cmd(1)->arg1, Cmd(1)->arg1);
      }
   );
   Add1(
      [this]() -> bool {
         return *Cmd(1) == MOV && CmpOperands(Cmd(1)->arg1, Cmd(1)->arg2);     // mov operand, operand  -> null
      },
      []() {}
   );

   //-------------------------------------------------------------------------
   //-------------------------TWO COMMANDS OPTIMIZATIONS----------------------
   Add2(
      [this]() -> bool {
         return CheckCmds(Cmd(1), Cmd(2), PUSH, POP) && IsReg(Cmd(1)->arg1) && IsReg(Cmd(2)->arg1);
      },
      [this]() {
         if (GetRegister(Cmd(1)->arg1) != Cmd(2)->arg1) {
            cmdsContainer.AddCmd(MOV, Cmd(2)->arg1, Cmd(1)->arg1);
         }
      }
   );
   Add2(
      [this]() -> bool {
         return CheckCmds(Cmd(1), Cmd(2), PUSH, POP) && IsReg(Cmd(2)->arg1) && IsAddr(Cmd(1)->arg1);
      },
      [this]() {
         cmdsContainer.AddCmd(LEA, Cmd(2)->arg1, GetAddr(Cmd(1)->arg1).arg);
      }
   );
   Add2(
      [this]() -> bool {
         return CheckCmds(Cmd(1), Cmd(2), PUSH, POP) && IsReg(Cmd(2)->arg1) && IsIntImm(Cmd(1)->arg1);
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(2)->arg1, Cmd(1)->arg1);
      }
   );
   Add2(
      [this]() -> bool {
         return CheckCmds(Cmd(1), Cmd(2), PUSH, POP) && IsReg(Cmd(2)->arg1) && IsMem(Cmd(1)->arg1);
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(2)->arg1, Cmd(1)->arg1, szDWORD);
      }
   );
   Add2(
      [this]() -> bool {
         return *Cmd(1) == MOV && (*Cmd(2) == ADD || *Cmd(2) == SUB) && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2)->GetOpCode(), Cmd(2)->arg1, Cmd(1)->arg2);
      }
   );
   Add2(
      [this]() -> bool {
         return
               *Cmd(1) == MOV && (*Cmd(2) == ADD || *Cmd(2) == SUB)
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)
            && IsIntImm(Cmd(1)->arg2)
            && IsIntImm(Cmd(2)->arg2);
      },
      [this]() {
         int val1 = GetIntImmVal(Cmd(1)->arg2);
         int val2 = GetIntImmVal(Cmd(2)->arg2);
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, *Cmd(2) == ADD ? val1 + val2 : val1 - val2);
      }
   );
   Add2(
      [this]() -> bool {
         return
               *Cmd(1) == MOV && (*Cmd(2) == ADD || *Cmd(2) == SUB)        //mov   eax, 32
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)                    //add   eax, offset v_a
            && IsIntImm(Cmd(1)->arg2)
            && IsAddr(Cmd(2)->arg2);
      },
      [this]() {
         AsmVarAddr addr = GetAddr(Cmd(2)->arg2);
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, AsmVarAddr(addr.arg, GetIntImmVal(Cmd(1)->arg2) + addr.GetOffset()));
      }
   );
   Add2(
      [this]() -> bool {
         return
               *Cmd(1) == MOV && (*Cmd(2) == ADD || *Cmd(2) == SUB)        //mov   eax, offset v_a + 4
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)                    //add   eax, 4
            && IsIntImm(Cmd(2)->arg2)
            && IsAddr(Cmd(1)->arg2);
      },
      [this]() {
         AsmVarAddr addr = GetAddr(Cmd(1)->arg2);
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, AsmVarAddr(addr.arg, GetIntImmVal(Cmd(2)->arg2) + addr.GetOffset()));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, MOV)
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2)
            && !(IsMem(Cmd(1)->arg2) && IsMem(Cmd(2)->arg1));
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(2)->arg1, Cmd(1)->arg2, IsReg(Cmd(1)->arg2) ? szNONE : szDWORD);
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, MOV)                                  // mov ebx, 4                 mov ebx, ebp
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)                             // mov ebx, dword ptr [eax]   mov ebx, [ebx+8]
            && !(IsMem(Cmd(2)->arg2) && IsEqOperands(Cmd(1)->arg1, GetMem(Cmd(2)->arg2).arg));
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, CMP)
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)
            && IsReg(Cmd(2)->arg2)
            && !IsIntImm(Cmd(1)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(CMP, Cmd(1)->arg2, Cmd(2)->arg2);
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, CMP)
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2)
            && IsReg(Cmd(2)->arg1);
      },
      [this]() {
         cmdsContainer.AddCmd(CMP, Cmd(2)->arg1, Cmd(1)->arg2);
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, NEG)        // mov eax, 25
            && IsIntImm(Cmd(1)->arg2)                     // neg eax
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1);
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, -GetIntImmVal(Cmd(1)->arg2));
      }
   );
   Add2(
      [this]() -> bool {
         return
              CheckCmds(Cmd(1), Cmd(2), MOV, IMUL)             //mov   eax, 3
           && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)         //imul  eax, 4
           && IsIntImm(Cmd(1)->arg2)
           && IsIntImm(Cmd(2)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, GetIntImmVal(Cmd(1)->arg2) * GetIntImmVal(Cmd(2)->arg2));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, IMUL)             //mov   eax, 1
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)         //imul  eax, ebx
            && IsIntImm(Cmd(1)->arg2)
            && GetIntImmVal(Cmd(1)->arg2) == 1;
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, Cmd(2)->arg2);
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), ADD, ADD)
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)
            && IsIntImm(Cmd(1)->arg2)
            && IsIntImm(Cmd(2)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(ADD, Cmd(1)->arg1, GetIntImmVal(Cmd(1)->arg2) + GetIntImmVal(Cmd(2)->arg2));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), ADD, ADD)
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)               //add   eax, offset v_a
            && (IsIntImm(Cmd(1)->arg2) || IsIntImm(Cmd(2)->arg2))     //add   eax, 4
            && (IsAddr(Cmd(1)->arg2)   || IsAddr(Cmd(2)->arg2));
      },
      [this]() {
         cmdsContainer.AddCmd(
           ADD,
           Cmd(1)->arg1,
           IsIntImm(Cmd(1)->arg2)
           ? AsmVarAddr(GetAddr(Cmd(2)->arg2).arg, GetAddr(Cmd(2)->arg2).GetOffset() + GetIntImmVal(Cmd(1)->arg2))
           : AsmVarAddr(GetAddr(Cmd(1)->arg2).arg, GetAddr(Cmd(1)->arg2).GetOffset() + GetIntImmVal(Cmd(2)->arg2))
         );
      }
   );
   Add2(
      [this]() -> bool {
         return
               *Cmd(1) == ADD
            && IsIntImm(Cmd(1)->arg2)           //add   eax, 4
            && IsIntImm(Cmd(2)->arg2)           //mov[eax], dword ptr 5
            && IsMem(Cmd(2)->arg1)
            && IsEqOperands(Cmd(1)->arg1, GetMem(Cmd(2)->arg1).arg);
      },
      [this]() {
         AsmMemory mem = GetMem(Cmd(2)->arg1);
         mem.SetOffset(mem.GetOffset() + GetIntImmVal(Cmd(1)->arg2));
         if (IsCmd2(Cmd(2))) {
            cmdsContainer.AddCmd(Cmd(2)->GetOpCode(), mem, Cmd(2)->arg2);
         } else {
           cmdsContainer.AddCmd(Cmd(2)->GetOpCode(), mem);
         }
      }
   );
   Add2(
      [this]() -> bool {
         return
               *Cmd(1) == LEA                         //lea   eax, v_a
            && (*Cmd(2) == ADD || *Cmd(2) == SUB)     //add   eax, 4
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)
            && IsIntImm(Cmd(2)->arg2)
            && IsStrImm(Cmd(1)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, AsmVarAddr(Cmd(1)->arg2, (*Cmd(2) == ADD ? 1 : -1) * GetIntImmVal(Cmd(2)->arg2)));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), LEA, ADD)        //lea   ebx, v_a
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2)   //add   eax, ebx
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1); // �������� �� �����
      },
      [this]() {
         cmdsContainer.AddCmd(ADD, Cmd(2)->arg1, AsmVarAddr(Cmd(1)->arg2));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), XOR, IMUL)     //xor   eax, eax
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1) //imul  eax, ebx
            && IsEqOperands(Cmd(1)->arg1, Cmd(1)->arg2); // �������� �� ���������
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(1));
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), XOR, ADD)        //xor   eax, eax
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)   //add   eax, offset v_a + 4
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2); //�������� �� ���������
      },
      [this]() {
         cmdsContainer.AddCmd(MOV, Cmd(1)->arg1, Cmd(2)->arg2);
      }
   );
   Add2(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), POP, MOV)        //pop   ebx
            && IsMem(Cmd(2)->arg1)                          //mov[eax], ebx
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(POP, Cmd(2)->arg1);
      }
   );

   //-------------------------------------------------------------------------
   //-------------------------THREE COMMANDS OPTIMIZATIONS--------------------
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(3), MOV, MOV)       //mov   ebx, ebp
            && (*Cmd(2) == ADD || *Cmd(2) == SUB)        //add   ebx, -4
            && IsIntImm(Cmd(2)->arg2)                    //mov   eax, ebx
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2);
      },
      [this]() {
         if (!IsEqOperands(Cmd(1)->arg2, Cmd(3)->arg1)) {
            cmdsContainer.AddCmd(MOV, Cmd(3)->arg1, Cmd(1)->arg2);
         }
         cmdsContainer.AddCmd(Cmd(2)->GetOpCode(), Cmd(3)->arg1, Cmd(2)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, MOV)        // mov eax, 3
            && (*Cmd(3) == ADD || *Cmd(3) == SUB)         // mov ebx, edx
            && IsIntImm(Cmd(1)->arg2)                     // add ebx, eax
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1)
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)  //����� �� �����
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2); //����� �� �����
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(Cmd(3)->GetOpCode(), Cmd(3)->arg1, Cmd(1)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, MOV)        //mov   ebx, eax
            && (*Cmd(3) == ADD || *Cmd(3) == SUB)         //mov   eax, 5
            && IsIntImm(Cmd(2)->arg2)                     //add   eax, ebx
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1)
            && IsEqOperands(Cmd(1)->arg2, Cmd(2)->arg1);
            //&& !IsEqOperands(Cmd(2)->arg1, Cmd(1)->arg2)
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(3)->GetOpCode(), Cmd(2)->arg1, Cmd(2)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, MOV)           //mov   ebx, dword ptr[v_b]
            && (*Cmd(3) == ADD || *Cmd(3) == SUB)            //mov   eax, dword ptr[v_a]
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)      //add   eax, ebx
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2) // ����� �� ����� - ����� �������
            && !IsEqOperands(Cmd(1)->arg2, Cmd(2)->arg1)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1); // ������ �� �����
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(Cmd(3)->GetOpCode(), Cmd(2)->arg1, Cmd(1)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, MOV, IMUL)        //mov   ebx, 20
            && *Cmd(3) == IMUL && IsCmd1(Cmd(3))         //mov   eax, dword ptr[v_i]
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg1)   //imul  ebx
            && !IsEqOperands(Cmd(1)->arg2, Cmd(2)->arg1)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1); // �������� �� ���������
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(IMUL, Cmd(2)->arg1, Cmd(1)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), MOV, MOV)        //mov   eax, -8
            && *Cmd(3) == IMUL && !IsCmd2(Cmd(3))         //mov   ebx, 3
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1)   //imul  ebx
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1);  // �������� �� ���������
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(1));
         cmdsContainer.AddCmd(IMUL, Cmd(1)->arg1, Cmd(2)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, MOV, IMUL)     //mov   ebx, 4
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)              //mov   eax, 3
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1);             //imul  eax, ebx
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(IMUL, Cmd(3)->arg1, Cmd(1)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, MOV, CMP)      //mov   ebx, intImm1      mov eax, intImm2
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)              //mov   eax, intImm2      cmp eax, intImm1
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1)              //cmp   eax, ebx
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2); // �������� �� ���������
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(CMP, Cmd(2)->arg1, Cmd(1)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, MOV, MOV)        //mov   eax, offset v_a + intImm
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg1)                //mov   [eax], dword ptr intImm1
            && IsMem(Cmd(2)->arg1)                                     //mov   eax, offset v_a + intImm
            && IsEqOperands(Cmd(1)->arg1, GetMem(Cmd(2)->arg1).arg)
            && CmpOperands(Cmd(1)->arg2, Cmd(3)->arg2);
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(1));
         cmdsContainer.AddCmd(Cmd(2));
      }
   );
   Add3(
      [this]() -> bool {
         return                                                        //mov   ebx, dword ptr - 5
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, MOV, MOV)        //mov   eax, offset v_c + 4
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)                //mov[eax], ebx
            && IsMem(Cmd(3)->arg1)                                     // �������� �� ���������
            && IsEqOperands(Cmd(2)->arg1, GetMem(Cmd(3)->arg1).arg)    // �������� �� ���������
            && !IsMem(Cmd(1)->arg2)
            && !CmpOperands(Cmd(1)->arg2, Cmd(2)->arg1);
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(MOV, Cmd(3)->arg1, Cmd(1)->arg2, szDWORD);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, LEA, MOV)     // mov   ebx, eax       lea   ebx, v_i
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)             // lea   eax, v_i       mov[ebx], eax
            && IsEqOperands(Cmd(1)->arg2, Cmd(2)->arg1)             // mov[eax], ebx
            && IsMem(Cmd(3)->arg1)
            && IsEqOperands(Cmd(2)->arg1, GetMem(Cmd(3)->arg1).arg);
      },
      [this]() {
         cmdsContainer.AddCmd(LEA, Cmd(1)->arg1, Cmd(2)->arg2);
         cmdsContainer.AddCmd(
            MOV,
            AsmMemory(
               GetRegister(Cmd(1)->arg1),
               GetMem(Cmd(3)->arg1).GetOffset(),
               GetMem(Cmd(3)->arg1).GetSizeType()
            ),
            GetRegister(Cmd(1)->arg2)
         );
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, LEA, MOV)       //mov   ebx, dword ptr - 25
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)               //lea   eax, v_r              lea eax, v_r
            && IsMem(Cmd(3)->arg1)                                    //mov[eax], ebx               mov dword ptr [eax], -25
            && IsEqOperands(Cmd(2)->arg1, GetMem(Cmd(3)->arg1).arg)
            && !IsEqOperands(Cmd(1)->arg2, Cmd(2)->arg2)
            && !(IsMem(Cmd(1)->arg2) && IsMem(Cmd(3)->arg1));
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(MOV, Cmd(3)->arg1, Cmd(1)->arg2, szDWORD);
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, LEA, MOV)    //mov   ebx, 8
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg1)            //lea   eax, v_a
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2);          //mov   ebx, 4
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(Cmd(3));
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), MOV, PUSH, MOV)     //mov ebx, 4
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg2)              //push eax
            && IsEqOperands(Cmd(2)->arg1, Cmd(3)->arg1)              //mov eax, ebx
            && IsIntImm(Cmd(1)->arg2)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1);            // �������� �� ���������
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(MOV, Cmd(3)->arg1, Cmd(1)->arg2);
      }
   );
   Add3(
      [this]() -> bool {
         //return  false;
         return                                                      //lea R1, R2
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), LEA, MOV, LEA)      //mov [R1], 20
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg1)              //lea R1, R2
            && CmpOperands(Cmd(1)->arg2, Cmd(3)->arg2)
            && IsMem(Cmd(2)->arg1)
            && IsEqOperands(Cmd(1)->arg1, GetMem(Cmd(2)->arg1).arg);
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(1));
         cmdsContainer.AddCmd(Cmd(2));
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(3), LEA, MOV)                      //lea   ebx, v_a
            && (*Cmd(2) == ADD || *Cmd(2) == SUB)                       //add   eax, ebx
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg2)                 //mov   ebx, 4
            && IsEqOperands(Cmd(1)->arg1, Cmd(3)->arg1)
            && !IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1) //�������� �� ���������
            && IsStrImm(Cmd(1)->arg2);
      },
      [this]() {
         //cmdsContainer.AddCmd(Cmd(2)->GetOpCode(), Cmd(2)->arg1, AsmVarAddr(Cmd(1)->arg2, 0, szDWORD));
         cmdsContainer.AddCmd(Cmd(2)->GetOpCode(), Cmd(2)->arg1, AsmVarAddr(Cmd(1)->arg2));
         cmdsContainer.AddCmd(Cmd(3));
      }
   );
   Add3(
      [this]() -> bool {
         return
               CheckCmds(Cmd(1), Cmd(2), Cmd(3), ADD, LABEL, MOV)    //add esp, 8
            && Cmd(1)->arg1 == ESP                                   //@exit_0:
            && Cmd(3)->arg1 == ESP                                   //mov esp, ebp
            && Cmd(3)->arg2 == EBP;
      },
      [this]() {
         cmdsContainer.AddCmd(Cmd(2));
         cmdsContainer.AddCmd(Cmd(3));
      }
   );
}

void Optimizator::Optimize(AsmCode& asmCode)
{
   while (true) {
      bool isOptimize = false;
      size_t idx = 0;
      do {
         for (size_t i = 0; i < AMOUNT_OF_OPTIMIZATION_WINDOWS; i++) {
            if (idx + i >= asmCode.GetCmdAmount())  break;
            commandsToBeOptimized = asmCode.GetCommands(idx, i + 1);
            if ((this->*(optimizations[i]))()) {
               isOptimize = true;
               asmCode.ReplaceCommands(GetNewCommands(), idx, i + 1);
               CleanContainer();
            }
         }
         if (isOptimize) break;
      } while (++idx < asmCode.GetCmdAmount());
      if (!isOptimize) break;
   }
}

bool Optimizator::OptimizationForCmds(vector<OptimizationFunc>& optimizations)
{
   for (auto & optimization : optimizations) {
      if (optimization.first()) {
         optimization.second();
         return true;
      }
   }
   return false;
}

bool Optimizator::OptimizationFor1Cmd()
{
   return OptimizationForCmds(oneCmdOptimizations);
}

bool Optimizator::OptimizationFor2Cmd()
{
   if (CheckForIllegalCommands(Cmd(1))) return false;
   if (TryToMovePushPop(Cmd(1), Cmd(2))) return true;
   return OptimizationForCmds(twoCmdOptimizations);
}

bool Optimizator::OptimizationFor3Cmd()
{
   if (CheckForIllegalCommands(Cmd(1))) return false;
   return OptimizationForCmds(threeCmdOptimizations);
}

bool Optimizator::OptimizationFor4Cmd()
{
   bool result = false;
   if (CheckForIllegalCommands(Cmd(1))) return false;
   if (result =
         CheckCmds(Cmd(1), Cmd(2), Cmd(3), Cmd(4), ADD, PUSH, CALL, ADD)
      && AsmStrImmediate("crt_printf") == Cmd(2)->arg1
      && IsIntImm(Cmd(1)->arg2)
      && IsIntImm(Cmd(4)->arg2)
      && Cmd(1)->arg1 == ESP
      && Cmd(4)->arg1 == ESP
   ) {
      cmdsContainer.AddCmd(Cmd(2));
      cmdsContainer.AddCmd(Cmd(3));
      cmdsContainer.AddCmd(ADD, ESP, GetIntImmVal(Cmd(1)->arg2) + GetIntImmVal(Cmd(4)->arg2));
   } else if (
         result =
            CheckCmds(Cmd(1), Cmd(2), Cmd(3), Cmd(4), PUSH, MOV, POP, ADD)   // DANGER DANGER DANGER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            && IsEqOperands(Cmd(1)->arg1, Cmd(2)->arg1)                  // push eax
            && IsEqOperands(Cmd(1)->arg1, Cmd(4)->arg1)                  // mov  eax, ebx
            && IsEqOperands(Cmd(2)->arg2, Cmd(3)->arg1)                  // pop  ebx
            && IsEqOperands(Cmd(2)->arg2, Cmd(4)->arg2)                  // add  eax, ebx
   ) {
      cmdsContainer.AddCmd(Cmd(4));
   }
   return result;
}

void Optimizator::CleanContainer()
{
   cmdsContainer.CleanCommands();
}

void Optimizator::Add1(OptimizationCheckFunc checkFunc, OptimizationExecFunc execFunc)
{
   oneCmdOptimizations.push_back(make_pair(checkFunc, execFunc));
}

void Optimizator::Add2(OptimizationCheckFunc checkFunc, OptimizationExecFunc execFunc)
{
   twoCmdOptimizations.push_back(make_pair(checkFunc, execFunc));
}

void Optimizator::Add3(OptimizationCheckFunc checkFunc, OptimizationExecFunc execFunc)
{
   threeCmdOptimizations.push_back(make_pair(checkFunc, execFunc));
}

Command Optimizator::Cmd(size_t idx) const
{
   return commandsToBeOptimized.at(idx - 1);
}

Commands Optimizator::GetNewCommands() const
{
   return cmdsContainer.GetCommands();
}

bool Optimizator::TryToMovePushPop(Command cmd1, Command cmd2)
{
   bool result = false;
   if (*cmd1 == PUSH) {
      result = CheckConstraintsForPushPopInstructions(cmd2, cmd1);
   } else if (*cmd2 == POP) {
      result = CheckConstraintsForPushPopInstructions(cmd1, cmd2);
      if (result && IsCmd2(cmd1)) {
         result =
               !IsEqOperands(cmd2->arg1, cmd1->arg2)
            && !(IsMem(cmd1->arg2) && IsEqOperands(cmd2->arg1, GetMem(cmd1->arg2).arg));
      }
   }
   if (result) {
      cmdsContainer.AddCmd(cmd2);
      cmdsContainer.AddCmd(cmd1);
   }
   return result;
}

bool Optimizator::CheckConstraintsForPushPopInstructions(Command cmd1, Command cmd2)
{
   return
         !(*cmd1 == PUSH || *cmd1 == POP || *cmd1 == CALL || *cmd1 == LABEL)
      && !(*cmd1 == JMP  || *cmd1 == JNE || *cmd1 == JGE  || *cmd1 == JE || *cmd1 == JG || *cmd1 == JL)
      && cmd1->arg1 != ESP
      && !IsEqOperands(cmd2->arg1, cmd1->arg1)
      && !(cmd2->arg1 == EAX && (cmd1->arg1 == AX || cmd1->arg1 == AL))
      && !(IsMem(cmd1->arg1) && GetMem(cmd1->arg1).arg == ESP)
      && !(IsMem(cmd2->arg1) && CmpOperands(GetMem(cmd2->arg1).arg, cmd1->arg1));
}


bool Optimizator::CheckForIllegalCommands(Command cmd)
{
   return *cmd == MOV && cmd->arg1 == EBP && cmd->arg2 == ESP;
}

bool Optimizator::CheckCmds(Command cmd1, Command cmd2, OpCode cd1, OpCode cd2)
{
   return *cmd1 == cd1 && *cmd2 == cd2;
}

bool Optimizator::CheckCmds(Command cmd1, Command cmd2, Command cmd3, OpCode cd1, OpCode cd2, OpCode cd3)
{
   return CheckCmds(cmd1, cmd2, cd1, cd2) && *cmd3 == cd3;
}

bool Optimizator::CheckCmds(Command cmd1, Command cmd2, Command cmd3, Command cmd4, OpCode cd1, OpCode cd2, OpCode cd3, OpCode cd4)
{
   return CheckCmds(cmd1, cmd2, cmd3, cd1, cd2, cd3) && *cmd4 == cd4;
}