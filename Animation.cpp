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
	step = curStep = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i] = {}, AdditionalNode[i].NextPos=nullptr;

	for (int i = 0; i < 30; i++) AdditionPos[i] = -1;
}

void Animation::Link(int cur)	// point one to another
{
	for (int j = 0; j < DisplayRecordSize[cur] - 1; j++)
		DisplayRecord[cur][j].NextPos = &DisplayRecord[cur][j + 1];
}

void Animation::cloneList()   //copy linked list
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
	
	Link(step);

	step++;
}

void Animation::cloneState() //copy display linked list
{
	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecordSize[step] = DisplayRecordSize[step - 1];
	AdditionalNode[step] = AdditionalNode[step - 1];
	Link(step);
}

void DisplayNode::CalculateLine(DisplayNode* next)
{
	text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);
	PosText.setPosition(text.getPosition() - Vector2f(25, -30));

	if (next == nullptr)
	{
		line.setScale(Vector2f(0, 1));
		arrow_head.setScale(Vector2f(0, 1));
		return;
	}

	Vector2f NextPos = next->body.getPosition();

	Vector2f d = -body.getPosition() + NextPos;

	float distance = sqrt(d.x * d.x + d.y * d.y);

	line.setScale(Vector2f(distance-body.getRadius(), 1));
	arrow_head.setScale(Vector2f(1, 1));

	line.setPosition(body.getPosition());
		

	if (d.x) rad = (float)atan(d.y / d.x) ; else rad = 3*PI/2;
	angle = rad * 180 / PI;

	line.setRotation(angle);
	arrow_head.setRotation(angle + 90);

	arrow_head.setPosition(body.getPosition() + d + Vector2f((body.getRadius()+arrow_head.getRadius())*cos(rad+PI),(body.getRadius() + arrow_head.getRadius()) * sin(rad+PI)));
}

void Animation::CalculatePos(int pos)
{
	for (int i=0;i<DisplayRecordSize[pos];i++)
	{
		DisplayNode* cur = &DisplayRecord[pos][i];
		cur->CalculateLine(cur->NextPos);
	}

	AdditionalNode[pos].PosText.setString(""); 
	AdditionalNode[pos].CalculateLine(AdditionalNode[pos].NextPos);
	if (AdditionPos[pos] == -1)
	{
		AdditionalNode[pos].arrow_head.setScale(Vector2f(0, 1));
		AdditionalNode[pos].line.setScale(Vector2f(0, 1));
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

	if (v<l->Size-1)  //not Tail
	{
		cloneState();
		DisplayRecord[step][v].Dissolve();
		DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v+1].body.getPosition());

		CalculatePos(step);
		step++;


		cloneState();

		for (int i=v;i<DisplayRecordSize[step];i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));

		DisplayRecord[step][v].Dissolve();

		CalculatePos(step);

		step++;
	}
	else  //Tail
	{
		cloneState();
		DisplayRecord[step][v].Dissolve();
		if (v) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v-1].body.getPosition());

		CalculatePos(step);
		step++;
	}
}

void Animation::Add_pos(int v,int data)
{
	if (l->Size == 1) return;

	string s = to_string(data);

	MakeFillIndex(min(v,l->Size-2), Color::Green);

	if (v > l->Size-2)
	{	
		v = min(v, l->Size - 2);
		//tail
		//make node appear

		AdditionPos[step] = -1;

		cloneState();

		DisplayNode DisplayCur = DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(-l->Distance, -120));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString(s);

		AdditionalNode[step]=DisplayCur;
		CalculatePos(step);

		step++;

		//make node point
		cloneState();

		DisplayRecord[step][v].NextPos = &AdditionalNode[step];
		DisplayRecord[step][v].line.setFillColor(DisplayRecord[step][v].ChosenColor);
		DisplayRecord[step][v].arrow_head.setFillColor(DisplayRecord[step][v].ChosenColor);
		CalculatePos(step);

		step++;

		cloneState();

		AdditionalNode[step].body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(-l->Distance, 0));

		DisplayRecord[step][v].NextPos = &AdditionalNode[step];

		CalculatePos(step);

		step++;
	} else if (v>0)
	{
		v = min(v, l->Size - 2);

		//middle
		//make node appear

		cloneState();

		DisplayNode DisplayCur=DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(0, -120));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString(s);

		AdditionalNode[step]=DisplayCur;
		CalculatePos(step);

		step++;

		//make node point
		cloneState();
		AdditionPos[step] = v;

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];

		AdditionalNode[step].NextPos = &DisplayRecord[step][v];

		CalculatePos(step);

		step++;

		//move
		cloneState();
		AdditionPos[step] = v;

		for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionalNode[step].body.setPosition(AdditionalNode[step].body.getPosition() - Vector2f(0, +120));

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];
		AdditionalNode[step].NextPos = &DisplayRecord[step][v];
		CalculatePos(step);

		step++;
	}
	else
	{
		v = min(v, l->Size - 2);
		//head
		// make node appear

		cloneState();

		DisplayNode DisplayCur;

		DisplayCur.NodeCovert(l->Head);
		DisplayCur.body.setPosition(DisplayRecord[step - 1][0].body.getPosition() - Vector2f(l->Distance, -120));
		DisplayCur.body.setFillColor(Color::Magenta);

		AdditionalNode[step]=DisplayCur;
		CalculatePos(step);

		step++;

		//make node point to head
		cloneState();

		AdditionalNode[step].NextPos = &DisplayRecord[step][0]; AdditionPos[step] = 0;
		CalculatePos(step);
		step++;

		cloneState(); 

		AdditionalNode[step].body.setPosition(DisplayRecord[step][0].body.getPosition());
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];
		for (int i = 0; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionPos[step] = 0;
		CalculatePos(step);

		step++;		
	}
	
}


void Animation::drawSmoothTransition(int start, int end, float progress) 
{
	// Define a function to render a smooth transition between two frames
	// Interpolate each node between the start and end frames

	vector<DisplayNode> interpolated_nodes;


	for (int i = 0; i < DisplayRecordSize[start]; i++) 
	{
		DisplayNode a = DisplayRecord[start][i];
		DisplayNode b = DisplayRecord[end][i];
		DisplayNode interpolated = interpolated.interpolate(&a, &b, progress);
		interpolated_nodes.push_back(interpolated);
		if (i) interpolated_nodes[i-1].CalculateLine(&interpolated_nodes[i]);
	}


	DisplayNode a = AdditionalNode[start];
	DisplayNode b = AdditionalNode[end];
	DisplayNode interpolated = interpolated.interpolate(&a, &b, progress);
	interpolated_nodes.push_back(interpolated);

	if (AdditionPos[start] == -1) interpolated_nodes.back().CalculateLine(nullptr);
	else
	{
		if (AdditionPos[start]>0) interpolated_nodes[AdditionPos[start] - 1].CalculateLine(&interpolated_nodes.back());
		
		interpolated_nodes.back().CalculateLine(&interpolated_nodes[AdditionPos[start]]);
	}

	// Render the interpolated nodes
	for (auto node : interpolated_nodes) node.renderNode(window);

	window->display();
}

void Animation::drawOneStep(int i)
{
	AdditionalNode[i].renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++) DisplayRecord[i][j].renderNode(window);
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

	this->font = node->font;

	text = node->text;

	this->text.setFont(*this->font);
	
	PosText = node->PosText;

	this->PosText.setFont(*this->font);
}

DisplayNode DisplayNode::interpolate(DisplayNode* a, DisplayNode* b, float t)   //make display between 2 frames
{
	// Create a new DisplayNode to store the interpolated values
	DisplayNode result=*a;

	// Interpolate the position of the body and arrow head
	result.body.setPosition((1 - t) * a->body.getPosition() + t * b->body.getPosition());
	result.arrow_head.setPosition((1 - t) * a->arrow_head.getPosition() + t * b->arrow_head.getPosition());

	// Interpolate the rotation angle of the body
	float angle_diff = b->angle - a->angle;
	float angle = a->angle + t * angle_diff;
	result.arrow_head.setRotation(angle+90);
	result.line.setRotation(angle);

	// Interpolate the color of the body
	int r_diff = b->body.getFillColor().r - a->body.getFillColor().r;
	int g_diff = b->body.getFillColor().g - a->body.getFillColor().g;
	int b_diff = b->body.getFillColor().b - a->body.getFillColor().b;
	int a_diff = b->body.getFillColor().a - a->body.getFillColor().a;

	int red = a->body.getFillColor().r + t*r_diff;
	int green = a->body.getFillColor().g + t*g_diff;
	int blue = a->body.getFillColor().b + t*b_diff;
	int alpha = a->body.getFillColor().a + t*a_diff;

	if (b->body.getFillColor() == Color::Transparent)
	{
		result.body.setOutlineColor(Color::Transparent);
		result.body.setFillColor(Color::Transparent);
		result.line.setFillColor(Color::Transparent);
		result.arrow_head.setFillColor(Color::Transparent);
		result.text.setFillColor(Color::Transparent);
	}
	else result.body.setFillColor(Color(red,green,blue,alpha));

	// Interpolate the position and color of the text
	result.text.setPosition(result.body.getPosition().x - result.text.getGlobalBounds().width / 2.f, result.body.getPosition().y - result.text.getGlobalBounds().height / 3 * 2);
	result.PosText.setPosition(result.text.getPosition() - Vector2f(25, -30));

	// Return the interpolated DisplayNode
	return result;
}

void DisplayNode::Dissolve()
{
	body.setOutlineColor(Color::Transparent);
	body.setFillColor(Color::Transparent);
	line.setFillColor(Color::Transparent);
	arrow_head.setFillColor(Color::Transparent);
	text.setFillColor(Color::Transparent);
	PosText.setFillColor(Color::Transparent);
	NextPos = nullptr;
}


