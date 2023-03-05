#include "Node.h"

void Node::pushHead(Node*& Head,int k)
{
	Node* tmp = new Node;
	tmp->data = k;

	if (!Head)
	{
		Head = tmp;
		return;
	}

	Head->prev = tmp;
	tmp->next = Head;
	Head = tmp;
}

void Node::delAll(Node*& Head)
{
	while (Head)
	{
		Node* Tmp = Head;
		Head = Head->next;
		delete Tmp;
	}
}