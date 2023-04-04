#include "Animation_Stack.h"

Animation_Stack::Animation_Stack(Event* event, LinkedList* l, RenderWindow* window)
{
	this->l = l;
	this->event = event;
	this->window = window;

	tet.loadFromFile("asset/texture/cream.jpg");
	Fonte.loadFromFile("asset/fonts/cour.ttf");
	sprite.setTexture(tet);
	sprite.setScale(Vector2f(1920.f / tet.getSize().x, 1080.f / tet.getSize().y));

	CodeBox.setFillColor(CodeBoxColor);
	CodeBox.setSize(FakeCodeSize);
	FakeCodePos = Vector2f(window->getSize().x - FakeCodeSize.x, 150);
	CodeBox.setPosition(FakeCodePos);
	FakeCode.setFillColor(Color::White);
	FakeCode.setCharacterSize(FakeCodeSize.y / 2);
	FakeCode.setFont(Fonte);

	
	{
		// fake Code for Delete
		Code[0][0] = "if (head==null) return";
		Code[0][1] = "Node* temp = head";
		Code[0][2] = "head = head->next,     delete temp";

		// fake Code for Add

		Code[1][0] = "Node* vtx = new Node(v)";
		Code[1][1] = "vtx->next = head";
		Code[1][2] = "head = vtxt";

		// fake Code for Peek

		Code[2][0] = "if (head==null) return NOT_FOUND";
		Code[2][1] = "return head.item";
	}
}

Animation_Stack::~Animation_Stack()
{
}

void Animation_Stack::clearAll()
{
	step = curStep = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i] = {}, AdditionalNode[i].NextPos = nullptr;

	for (int i = 0; i < 30; i++) AdditionPos[i] = -1, DisplayRecordStringId[i] = -1;
}

void Animation_Stack::Link(int cur)	// point one to another
{
	for (int j = 0; j < DisplayRecordSize[cur] - 1; j++)
		DisplayRecord[cur][j].NextPos = &DisplayRecord[cur][j + 1];
}

void Animation_Stack::cloneList()   //copy linked list
{
	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode_Stack DisplayCur;

		DisplayCur.NodeCovert(&l->Round_Node[j]);

		if (j != 0 && j != l->Size - 1) DisplayCur.PosText.setString("");

		DisplayRecord[step].push_back(DisplayCur);
	}

	DisplayRecordSize[step] = l->Size;

	Link(step);

	step++;
}

void Animation_Stack::cloneState() //copy display linked list
{
	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecordSize[step] = DisplayRecordSize[step - 1];
	AdditionalNode[step] = AdditionalNode[step - 1];
	Link(step);
}

void DisplayNode_Stack::CalculateLine(DisplayNode_Stack* next)
{
	text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);
	PosText.setPosition(Vector2f(text.getPosition().x - body.getRadius(), text.getPosition().y + body.getRadius() + 5));

	if (next == nullptr)
	{
		line.setScale(Vector2f(0, 1));
		arrow_head.setScale(Vector2f(0, 1));
		return;
	}

	Vector2f NextPos = next->body.getPosition();

	Vector2f d = -body.getPosition() + NextPos;

	float distance = sqrt(d.x * d.x + d.y * d.y);

	line.setScale(Vector2f(distance - body.getRadius(), 1));
	arrow_head.setScale(Vector2f(1, 1));

	line.setPosition(body.getPosition());


	if (d.x) rad = (float)atan(d.y / d.x); else rad = 3 * PI / 2;
	angle = rad * 180 / PI;

	line.setRotation(angle);
	arrow_head.setRotation(angle + 90);

	arrow_head.setPosition(body.getPosition() + d + Vector2f((body.getRadius() + arrow_head.getRadius()) * cos(rad + PI), (body.getRadius() + arrow_head.getRadius()) * sin(rad + PI)));
}

void Animation_Stack::CalculatePos(int pos)
{
	for (int i = 0; i < DisplayRecordSize[pos]; i++)
	{
		DisplayNode_Stack* cur = &DisplayRecord[pos][i];
		cur->CalculateLine(cur->NextPos);
	}

	AdditionalNode[pos].CalculateLine(AdditionalNode[pos].NextPos);
	if (AdditionPos[pos] == -1)
	{
		AdditionalNode[pos].arrow_head.setScale(Vector2f(0, 1));
		AdditionalNode[pos].line.setScale(Vector2f(0, 1));
	}
}

void Animation_Stack::MakeFillIndex(int n, Color color)   // n<l.Size
{
	if (n < 0) return;
	cloneState();

	DisplayRecord[step][n].body.setFillColor(color);

	step++;
}

void Animation_Stack::MakeChoosenUpTo(int u, int v)  //	u<=v<l.Size
{
	cloneList();

	if (v < 0 || u < 0) return;

	for (int i = u; i <= v; i++)
	{
		cloneState();

		DisplayRecord[step][i].body.setOutlineColor(DisplayRecord[step][i].ChosenColor);

		step++;

		if (i < v)
		{
			cloneState();
			DisplayRecord[step][i].line.setFillColor(DisplayRecord[step][i].ChosenColor);
			DisplayRecord[step][i].arrow_head.setFillColor(DisplayRecord[step][i].ChosenColor);
			step++;
		}

	}
}

void Animation_Stack::Del_pos(int v)
{
	v = min(v, l->Size - 1);

	 // Head
	{
		eventType = E_DelHead;

		MakeChoosenUpTo(0, v - 1);

		DisplayRecordStringId[step - 1] = -1;

		MakeFillIndex(v, Color::Red);

		DisplayRecordStringId[step - 1] = 1;

		cloneState();  // dissolve
		DisplayRecord[step][v].Dissolve();
		if (v + 1 < l->Size) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());
		if (l->Size > 1) DisplayRecord[step][1].PosText.setString("Head");



		CalculatePos(step);
		step++; DisplayRecordStringId[step - 1] = 2;

		cloneState();

		for (int i = v + 1; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));

		DisplayRecord[step][v].Dissolve();
		if (l->Size > 1) DisplayRecord[step][1].PosText.setString("Head");



		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 2;
	}
}

void Animation_Stack::Add_pos(int v, int data)
{
	if (l->Size == 0) return;

	string s = to_string(data);

	{
		//head

		v = min(v, l->Size - 1);

		eventType = E_AddHead;
		MakeChoosenUpTo(-1, -1);
		DisplayRecordStringId[step - 1] = -1;

		// make node appear

		cloneState();

		DisplayNode_Stack DisplayCur = DisplayRecord[step][v];

		DisplayCur.text.setString(s);
		DisplayCur.body.setPosition(DisplayRecord[step - 1][0].body.getPosition() - Vector2f(l->Distance, -150));
		DisplayCur.PosText.setString("");
		DisplayCur.body.setFillColor(Color::Magenta);

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 0;

		//make node point to head
		MakeFillIndex(v, Color::Green); step--;

		AdditionalNode[step].NextPos = &DisplayRecord[step][0]; AdditionPos[step] = 0;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();

		AdditionalNode[step].body.setPosition(DisplayRecord[step][0].body.getPosition());
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];
		for (int i = 0; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionPos[step] = 0;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();
		AdditionalNode[step].PosText.setString("Head");
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];

		if (l->Size)
		{
			DisplayRecord[step][0].PosText.setString("");
			if (l->Size == 1) DisplayRecord[step][0].PosText.setString("Tail");
		}

		AdditionPos[step] = 0;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 2;
	}
}

void Animation_Stack::Ser_pos(int v)
{
	eventType = E_Search;

	MakeChoosenUpTo(0, -1);
	DisplayRecordStringId[0] = -1;

	MakeFillIndex(v, Color::Cyan);
	DisplayRecordStringId[step - 1] = 1;

	cloneState(); 
	step++; DisplayRecordStringId[step - 1] = 1;
}

void Animation_Stack::drawSmoothTransition(int start, int end, float progress, short CodeStatus)
{
	// Define a function to render a smooth transition between two frames
	// Interpolate each node between the start and end frames

	vector<DisplayNode_Stack> interpolated_nodes;


	for (int i = 0; i < DisplayRecordSize[start]; i++)
	{
		DisplayNode_Stack a = DisplayRecord[start][i];
		DisplayNode_Stack b = DisplayRecord[end][i];
		DisplayNode_Stack interpolated = interpolated.interpolate(&a, &b, progress);
		interpolated_nodes.push_back(interpolated);
		if (i) interpolated_nodes[i - 1].CalculateLine(&interpolated_nodes[i]);
	}


	DisplayNode_Stack a = AdditionalNode[start];
	DisplayNode_Stack b = AdditionalNode[end];
	DisplayNode_Stack interpolated = interpolated.interpolate(&a, &b, progress);
	interpolated_nodes.push_back(interpolated);

	if (AdditionPos[start] == -1) interpolated_nodes.back().CalculateLine(nullptr);
	else
	{
		if (AdditionPos[start] > 0) interpolated_nodes[AdditionPos[start] - 1].CalculateLine(&interpolated_nodes.back());

		interpolated_nodes.back().CalculateLine(&interpolated_nodes[AdditionPos[start]]);
	}

	// Render the interpolated nodes
	for (auto node : interpolated_nodes) node.renderNode(window);

	if (CodeStatus == Disappear) drawFakeCode(start, FakeCodeSize.x * progress); else
		if (CodeStatus == Display) drawFakeCode(start, 0); else
			drawFakeCode(start, FakeCodeSize.x * (1 - progress));

	window->display();
}

void Animation_Stack::drawOneStep(int i)
{
	AdditionalNode[i].renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++) DisplayRecord[i][j].renderNode(window);
}

void Animation_Stack::drawFakeCode(int cur, float posX)
{
	for (int i = 0; i < fakeId[eventType]; i++)
	{
		CodeBox.setPosition(FakeCodePos + Vector2f(posX, FakeCodeSize.y * i));

		FakeCode.setString(Code[eventType][i]);
		FakeCode.setPosition(CodeBox.getPosition().x + 10, CodeBox.getPosition().y + FakeCodeSize.y / 2.f - FakeCode.getGlobalBounds().height / 2.f);

		if (DisplayRecordStringId[cur] == i) CodeBox.setFillColor(Color::Black); else CodeBox.setFillColor(CodeBoxColor);

		window->draw(CodeBox);
		window->draw(FakeCode);
	}
}

void Animation_Stack::render()
{
}

void DisplayNode_Stack::renderNode(RenderTarget* window)
{
	window->draw(line);
	window->draw(body);
	window->draw(arrow_head);
	window->draw(text);
	window->draw(PosText);
}

void DisplayNode_Stack::NodeCovert(Round_Display_Node* node)
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

DisplayNode_Stack DisplayNode_Stack::interpolate(DisplayNode_Stack* a, DisplayNode_Stack* b, float t)   //make display between 2 frames
{
	// Create a new DisplayNode_Stack to store the interpolated values
	DisplayNode_Stack result = *a;

	// Interpolate the position of the body and arrow head
	result.body.setPosition((1 - t) * a->body.getPosition() + t * b->body.getPosition());
	result.arrow_head.setPosition((1 - t) * a->arrow_head.getPosition() + t * b->arrow_head.getPosition());

	// Interpolate the rotation angle of the body
	float angle_diff = b->angle - a->angle;
	float angle = a->angle + t * angle_diff;
	result.arrow_head.setRotation(angle + 90);
	result.line.setRotation(angle);

	// Interpolate the color of the body
	int r_diff = b->body.getFillColor().r - a->body.getFillColor().r;
	int g_diff = b->body.getFillColor().g - a->body.getFillColor().g;
	int b_diff = b->body.getFillColor().b - a->body.getFillColor().b;
	int a_diff = b->body.getFillColor().a - a->body.getFillColor().a;

	int red = a->body.getFillColor().r + t * r_diff;
	int green = a->body.getFillColor().g + t * g_diff;
	int blue = a->body.getFillColor().b + t * b_diff;
	int alpha = a->body.getFillColor().a + t * a_diff;

	if (b->body.getFillColor() == Color::Transparent)
	{
		result.body.setOutlineColor(Color::Transparent);
		result.body.setFillColor(Color::Transparent);
		result.line.setFillColor(Color::Transparent);
		result.arrow_head.setFillColor(Color::Transparent);
		result.text.setFillColor(Color::Transparent);
	}
	else result.body.setFillColor(Color(red, green, blue, alpha));

	// Interpolate the position and color of the text
	result.text.setPosition(result.body.getPosition().x - result.text.getGlobalBounds().width / 2.f, result.body.getPosition().y - result.text.getGlobalBounds().height / 3 * 2);
	result.PosText.setPosition(Vector2f(result.text.getPosition().x - body.getRadius(), result.text.getPosition().y + body.getRadius() + 5));

	// Return the interpolated DisplayNode_Stack
	return result;
}

void DisplayNode_Stack::Dissolve()
{
	body.setOutlineColor(Color::Transparent);
	body.setFillColor(Color::Transparent);
	line.setFillColor(Color::Transparent);
	arrow_head.setFillColor(Color::Transparent);
	text.setFillColor(Color::Transparent);
	PosText.setFillColor(Color::Transparent);
	NextPos = nullptr;
}


