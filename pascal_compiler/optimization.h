#pragma once

#include <vector>
#include <functional>
#include "CodeGen.h"

class Optimizator {
   typedef bool (Optimizator::*optimizationFunc)();
   typedef function<bool()> OptimizationCheckFunc;
   typedef function<void()> OptimizationExecFunc;
   typedef pair<OptimizationCheckFunc, OptimizationExecFunc> OptimizationFunc;

   vector<OptimizationFunc> oneCmdOptimizations;
   vector<OptimizationFunc> twoCmdOptimizations;
   vector<OptimizationFunc> threeCmdOptimizations;
   vector<optimizationFunc> optimizations;
   Commands commandsToBeOptimized;
   AsmCodeBase cmdsContainer;

   void CleanContainer();
   void Add1(OptimizationCheckFunc, OptimizationExecFunc);
   void Add2(OptimizationCheckFunc, OptimizationExecFunc);
   void Add3(OptimizationCheckFunc, OptimizationExecFunc);
   Command Cmd(size_t) const;
   Commands GetNewCommands() const;
   bool OptimizationForCmds(vector<OptimizationFunc>&);
   bool OptimizationFor1Cmd();
   bool OptimizationFor2Cmd();
   bool OptimizationFor3Cmd();
   bool OptimizationFor4Cmd();
   bool OptimizationFor5Cmd();
   //bool PopUp(Command, Command);
   //bool PushDown(Command, Command);
   bool TryToMovePushPop(Command, Command);
   bool CheckConstraintsForPushPopInstructions(Command, Command);
   bool CheckForIllegalCommands(Command);
   bool CheckCmds(Command, Command, OpCode, OpCode);
   bool CheckCmds(Command, Command, Command, OpCode, OpCode, OpCode);
   bool CheckCmds(Command, Command, Command, Command, OpCode, OpCode, OpCode, OpCode);
   bool CheckCmds(Command, Command, Command, Command, Command, OpCode, OpCode, OpCode, OpCode, OpCode);
public:
   Optimizator();
   void Optimize(AsmCode&);
};