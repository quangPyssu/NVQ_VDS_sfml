#include "Animation.h"

Animation::Animation(Event* event, LinkedList* l,RenderWindow* window)
{
	this->l = l;
	this->event = event;
	this->window = window;

	tet.loadFromFile("asset/texture/cream.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1000.f / tet.getSize().x, 800.f / tet.getSize().y));
}

Animation::~Animation()
{
}

void Animation::display_Del_Head()
{

}

void Animation::clearAll()
{
	for (int i = 0; i < 15; i++) DisplayRecord[i].clear();
}

void Animation::MakeChoosenUpTo(int u,int v)  // n < l.Size
{
	Node* Cur = l->Head;
	step = 1;

	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode DisplayCur;

		DisplayCur.clone(Cur);

		DisplayRecord[0].push_back(DisplayCur);
		Cur = Cur->Next;
	}

	for (int i = u; i <=v; i++)
	{
		Cur = l->Head;

		for (int j = 0; j < l->Size; j++)
		{
			DisplayNode DisplayCur;

			DisplayCur.clone(Cur);

			DisplayRecord[step].push_back(DisplayCur);
			Cur = Cur->Next;
		}

		for (int j = u; j <= i; j++)
		{
			DisplayRecord[step][j].body.setOutlineColor(DisplayRecord[step][j].ChosenColor);

			if (j > u)
			{
				DisplayRecord[step][j - 1].line.setFillColor(DisplayRecord[step][j - 1].ChosenColor);
				DisplayRecord[step][j - 1].arrow_head.setFillColor(DisplayRecord[step][j - 1].ChosenColor);
			}
		}

		step++;
	}

	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecord[step][v].body.setFillColor(DisplayRecord[step][v].ChosenColor);
	step++;
}

void Animation::drawOneStep(int i)
{
	//cout << "what is s  " << DisplayRecord[i].size() << endl;
	for (int j = 0; j < l->Size; j++)
		DisplayRecord[i][j].renderNode(window);
}

void Animation::render()
{
	
	for (int i = 0; i < step; i++)
	{
		
	}
}

void DisplayNode::renderNode(RenderTarget* window)
{
	window->draw(line);
	window->draw(body);
	window->draw(arrow_head);
	window->draw(text);
}

void DisplayNode::clone(Node* node)
{
    body = node->body;
    line = node->line;
	arrow_head = node->arrow_head;

    body.setOutlineColor(Color::Black);
    node->line.setFillColor(Color::Color(91, 91, 91, 255));
    node->arrow_head.setFillColor(Color::Color(91, 91, 91, 255));

	text = node->text;
	PosText = node->PosText;
}


