#include <iostream>
#include "syntax_node.h"

using namespace std;

SyntaxNode::SyntaxNode(NodeType AType, unsigned ADepth):
   type(AType),
   depth(ADepth)
{}

void SyntaxNode::PrintText(int d, string name)
{
	int count = d != 0 ? FACTOR * d : FACTOR;
	string offset(count - 2 - TAIL_LEN, ' ');
	string tail(d != 0 ? TAIL_LEN : 0, '-');
	if (d != 0) {
		tail += ' ';
		offset += ' ';
	}
	cout << offset << tail << name << offset << endl;
}

bool SyntaxNode::operator == (NodeType _type)
{
	return type == _type;
}

bool SyntaxNode::operator != (NodeType _type)
{
	return type != _type;
}

NodeBlock::NodeBlock(string AName):
   SyntaxNode(ntBlock, 0),
   name(AName)
{}

NodeBlock::NodeBlock(NodeType AType):
   SyntaxNode(AType, 0)
{}

NodeBlock::NodeBlock(Statements AStatements, string AName, NodeType AType):
   SyntaxNode(AType, 0),
   name(AName),
   statements(AStatements)
{}

void NodeBlock::AddStatement(SyntaxNode* statement)
{
   if (statement != nullptr) {
      statements.push_back(statement);
   }
}

void NodeBlock::Generate(AsmCode& asmCode)
{
   for (auto &statement : statements) {
      statement->Generate(asmCode);
   }
}

void NodeBlock::PrintNode(int d)
{
   for (size_t i = 0; i < statements.size(); i++) {
      if (i == statements.size() % 2 + 1) {
         SyntaxNode::PrintText(d, name);
      }
      statements[i]->PrintNode(d + 1);
   }
   if (statements.size() == 0) {
      SyntaxNode::PrintText(d + 1, "empty block");
      SyntaxNode::PrintText(d, name);
   } else if (statements.size() == 1) {
      SyntaxNode::PrintText(d, name);
   }
}