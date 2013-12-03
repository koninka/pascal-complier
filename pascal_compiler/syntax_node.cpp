#include <iostream>
#include "syntax_node.h"

using namespace std;

SyntaxNode::SyntaxNode(NodeType AType): type(AType) {}

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