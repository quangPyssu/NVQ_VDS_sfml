#include "Animation.h"

Animation::Animation(Event* event, LinkedList* l,RenderWindow* window)
{
	this->l = l;
	this->event = event;
	this->window = window;

	tet.loadFromFile("asset/texture/cream.jpg");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1350.f / tet.getSize().x, 800.f / tet.getSize().y));
}

Animation::~Animation()
{
}

void Animation::clearAll()
{
	step = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i].clear();
}

void Animation::cloneList()
{
	Node* Cur = l->Head;

	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode DisplayCur;

		DisplayCur.NodeCovert(Cur);

		if (j != 0 && j != l->Size - 1) DisplayCur.PosText.setString("");

		DisplayRecord[step].push_back(DisplayCur);

		Cur = Cur->Next;
	}

	DisplayRecordSize[step] = l->Size;

	step++;
}

void Animation::cloneState()
{
	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecordSize[step] = DisplayRecordSize[step - 1];
	AdditionalNode[step] = AdditionalNode[step - 1];
}

void Animation::CalculateLine(DisplayNode* cur, Vector2f NextPos)
{
	Vector2f d = -cur->body.getPosition() + NextPos;

	float distance = sqrt(d.x * d.x + d.y * d.y);

	if (d.x != 0 || d.y != 0)
	{
		cur->line.setScale(Vector2f(distance-cur->body.getRadius(), 1));
		cur->arrow_head.setScale(Vector2f(1, 1));

		cur->line.setPosition(cur->body.getPosition());
		

		if (d.x) cur->rad = (float)atan(d.y / d.x) ; else cur->rad = 3*PI/2;
		cur->angle = cur->rad * 180 / PI;


		cur->line.setRotation(cur->angle);
		cur->arrow_head.setRotation(cur->angle + 90);

		cur->arrow_head.setPosition(cur->body.getPosition() + d + Vector2f((cur->body.getRadius()+cur->arrow_head.getRadius())*cos(cur->rad+PI), 
			(cur->body.getRadius() + cur->arrow_head.getRadius()) * sin(cur->rad+PI)));
	}
	else
	{
		cur->line.setScale(Vector2f(0, 1));
		cur->arrow_head.setScale(Vector2f(0, 1));
	}

	cur->text.setPosition(cur->body.getPosition().x - cur->text.getGlobalBounds().width / 2.f, cur->body.getPosition().y - cur->text.getGlobalBounds().height / 3 * 2);
}

void Animation::CalculatePos(int pos)
{
	for (int i=0;i<DisplayRecordSize[pos];i++)
	{
		DisplayNode* cur = &DisplayRecord[pos][i];
		CalculateLine(cur, cur->NextPos);
	}

	for (int i = 0; i < AdditionalNode[pos].size(); i++)
	{
		AdditionalNode[pos][i].PosText.setString("");
		CalculateLine(&AdditionalNode[pos][i], AdditionalNode[pos][i].NextPos);
	}
}

void Animation::MakeFillIndex(int n, Color color)   // n<l.Size
{
	cloneState();

	DisplayRecord[step][n].body.setFillColor(color);

	step++;
}

void Animation::MakeChoosenUpTo(int u,int v)  //	u<=v<l.Size
{
	cloneList(); 

	for (int i = u; i <=v; i++)
	{
		cloneState();
		
		DisplayRecord[step][i].body.setOutlineColor(DisplayRecord[step][i].ChosenColor);

		step++;

		cloneState();

		if (i < v)
		{
			DisplayRecord[step][i].line.setFillColor(DisplayRecord[step][i].ChosenColor);
			DisplayRecord[step][i].arrow_head.setFillColor(DisplayRecord[step][i].ChosenColor);
		}
		step++;
	}
}

void Animation::Del_pos(int v)
{
	v = min(v, l->Size - 1);
	MakeFillIndex(v , Color::Red);

	if (v<l->Size-1)
	{
		cloneState();
		DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());		

		if (v>0) DisplayRecord[step][v-1].NextPos=DisplayRecord[step][v + 1].body.getPosition();

		CalculatePos(step);
		step++;
	}	
}

void Animation::Add_pos(int v,int data)
{	
	if (l->Size == 1) return;
	v = min(v, l->Size - 2);

	string s = to_string(data);

	MakeFillIndex(v, Color::Green);

	if (v == l->Size-2)
	{	//tail
		//make node appear
		cloneState();

		DisplayNode DisplayCur = DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(-l->Distance[v], -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = DisplayCur.body.getPosition();
		DisplayCur.text.setString(s);

		AdditionalNode[step].push_back(DisplayCur);
		CalculatePos(step);

		step++;

		//make node point
		cloneState();

		DisplayRecord[step][v].NextPos = AdditionalNode[step].back().body.getPosition();
		CalculatePos(step);

		step++;

	} else if (v>0)
	{	//middle
		//make node appear
		cloneState();

		DisplayNode DisplayCur=DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(0, -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = DisplayCur.body.getPosition();
		DisplayCur.text.setString(s);

		AdditionalNode[step].push_back(DisplayCur);
		CalculatePos(step);

		step++;

		//make node point
		cloneState();

		DisplayRecord[step][v - 1].NextPos = AdditionalNode[step].back().body.getPosition();
		AdditionalNode[step].back().NextPos = DisplayRecord[step][v].body.getPosition();	
		CalculatePos(step);

		step++;
	}
	else
	{	//head
		// make node appear
		cloneState();

		DisplayNode DisplayCur;

		DisplayCur.NodeCovert(l->Head);
		DisplayCur.body.setPosition(DisplayRecord[step - 1][0].body.getPosition() - Vector2f(l->Distance[l->Size - 2], -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = DisplayCur.body.getPosition();

		AdditionalNode[step].push_back(DisplayCur);
		CalculatePos(step);

		step++;

		//make node point to head
		cloneState();

		AdditionalNode[step].back().NextPos = DisplayRecord[step - 1][0].body.getPosition();
		CalculatePos(step);

		step++;
	}
}



void Animation::drawOneStep(int i)
{
	for (auto cur : AdditionalNode[i])
		cur.renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++)
		DisplayRecord[i][j].renderNode(window);
}

void Animation::render()
{
	
	
}

void DisplayNode::renderNode(RenderTarget* window)
{
	window->draw(line);
	window->draw(body);
	window->draw(arrow_head);
	window->draw(text);
	window->draw(PosText);
}

void DisplayNode::NodeCovert(Node* node)
{
    body = node->body;
    line = node->line;
	arrow_head = node->arrow_head;

    body.setOutlineColor(Color::Black);
    node->line.setFillColor(Color::Color(91, 91, 91, 255));
    node->arrow_head.setFillColor(Color::Color(91, 91, 91, 255));

	if (node->Next != nullptr) NextPos = node->Next->body.getPosition(); else NextPos = body.getPosition();

	text = node->text;
	PosText = node->PosText;
}


