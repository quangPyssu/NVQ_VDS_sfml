#include "Animation_Circle.h"

Animation_Circle::Animation_Circle(Event* event, LinkedList* l, RenderWindow* window)
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
	FakeCodePos = Vector2f(window->getSize().x - FakeCodeSize.x, 80);
	CodeBox.setPosition(FakeCodePos);
	FakeCode.setFillColor(Color::White);
	FakeCode.setCharacterSize(FakeCodeSize.y / 2+1);
	//FakeCode.setOutlineThickness(1);
	//FakeCode.setOutlineColor(Color::Black);
	FakeCode.setFont(Fonte);

	// fake Code for Delete
	{
		Code[0][0] = "if (head == null) return";
		Code[0][1] = "if (head==head->next) delete head,head=nullptr;";
		Code[0][2] = "else ";
		Code[0][3] = "{";
		Code[0][4] = "	Node* last = head, Node* tmp=head";
		Code[0][5] = "	while (last->next != head)";
		Code[0][6] = "		last = last->next";
		Code[0][7] = "	delete tmp";
		Code[0][8] = "	head=head->next, last->next = head";
		Code[0][9] = "}";

		Code[1][0] = "if (head==null) return";
		Code[1][1] = "if (head==head->next) delete head,head=nullptr;";
		Code[1][2] = "else";
		Code[1][3] = "{";
		Code[1][4] = "	Node* pre = head";
		Code[1][5] = "	for (k = 0; k < i - 1; k++)";
		Code[1][6] = "	     pre = pre->next";
		Code[1][7] = "	Node* del = pre->next ";
		Code[1][8] = "	aft = del->next, pre->next = aft, delete del";
		Code[1][9] = "}";
	}

	// fake Code for Add
	{
		Code[2][0] = "Node* vtx = new Node(v)";
		Code[2][1] = "if (head == null)";
		Code[2][2] = "	vtx->next = vtx, head = vtx";
		Code[2][3] = "else ";
		Code[2][4] = "{";
		Code[2][5] = "	Node* last = head";
		Code[2][6] = "	while (last->next != head)";
		Code[2][7] = "		last = last->next";
		Code[2][8] = "	last->next = vtx, vtx->next = head, head = vtx";
		Code[2][9] = "}";

		Code[3][0] = "if (head == null)";
		Code[3][1] = "Node* vtx = new Node(v), vtx->next = vtx, head = vtx";
		Code[3][2] = "else ";
		Code[3][3] = "{";
		Code[3][4] = "	Node* pre = head";
		Code[3][5] = "	for (k = 0; k < i - 1; k++)";
		Code[3][6] = "	   pre = pre->next";
		Code[3][7] = "	Node* aft = pre->next, Node* vtx = new Node(v)";
		Code[3][8] = "	vtx->next = aft,  pre->next = vtx";
		Code[3][9] = "}";
	}

	// fake Code for Update
	{
		Code[4][0] = "if (head == null) return";
		Code[4][1] = "Node* temp = head";
		Code[4][2] = "for (k = 0; k < i ; k++)";
		Code[4][3] = "	   temp = temp->next";
		Code[4][4] = "temp->data=new data";
	}

	// fake Code for Search
	{
		Code[5][0] = "if empty, return NOT_FOUND";
		Code[5][1] = "index = 0, Node* temp = head";
		Code[5][2] = "while (temp.item != v)";
		Code[5][3] = "index++, temp = temp->next";
		Code[5][4] = "if (temp == head) return NOT_FOUND";
		Code[5][5] = "return index";
	}
}

Animation_Circle::~Animation_Circle()
{
}

void Animation_Circle::clearAll()
{
	step = curStep = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i] = {}, AdditionalNode[i].NextPos = nullptr;

	for (int i = 0; i < 30; i++) AdditionPos[i] = -1, DisplayRecordStringId[i] = -1;
}

void Animation_Circle::Link(int cur)	// point one to another
{
	for (int j = 0; j < DisplayRecordSize[cur] - 1; j++)
		DisplayRecord[cur][j].NextPos = &DisplayRecord[cur][j + 1];
}

void Animation_Circle::cloneList()   //copy linked list
{
	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode_Circle DisplayCur;

		DisplayCur.NodeCovert(&l->Round_Node[j]);

		if (j != 0) DisplayCur.PosText.setString("");

		DisplayRecord[step].push_back(DisplayCur);
	}

	DisplayRecordSize[step] = l->Size;

	HeadPos[step] = 0;
	TailPos[step] = l->Size-1;

	Link(step);

	step++;
}

void Animation_Circle::cloneState() //copy display linked list
{
	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecordSize[step] = DisplayRecordSize[step - 1];
	AdditionalNode[step] = AdditionalNode[step - 1];

	HeadPos[step] = HeadPos[step - 1];
	TailPos[step] = TailPos[step - 1];

	Link(step);
}

void DisplayNode_Circle::CalculateLine(DisplayNode_Circle* next)
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

void Animation_Circle::CalculatePos(int pos)
{
	for (int i = 0; i < DisplayRecordSize[pos]; i++)
	{
		DisplayNode_Circle* cur = &DisplayRecord[pos][i];
		cur->CalculateLine(cur->NextPos);
	}

	AdditionalNode[pos].CalculateLine(AdditionalNode[pos].NextPos);
	if (AdditionPos[pos] == -1)
	{
		AdditionalNode[pos].arrow_head.setScale(Vector2f(0, 1));
		AdditionalNode[pos].line.setScale(Vector2f(0, 1));
	}
}

void Animation_Circle::MakeFillIndex(int n, Color color)   // n<l.Size
{
	if (n < 0) return;
	cloneState();

	DisplayRecord[step][n].body.setFillColor(color);

	step++;
}

void Animation_Circle::MakeChoosenUpTo(int u, int v)  //	u<=v<l.Size
{
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

void Animation_Circle::Del_pos(int v)
{
	v = min(v, l->Size - 1);

	cloneList();

	if (!v) // Head
	{
		eventType = E_DelHead;

		MakeChoosenUpTo(0, l->Size - 1);

		DisplayRecordStringId[0] = -1;

		MakeFillIndex(v, Color::Red);
		if (l->Size == 1) DisplayRecordStringId[1] = 1;
		else
		{
			DisplayRecordStringId[1] = 4;
			for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 6; else DisplayRecordStringId[i] = 5;
		}
		
		if (l->Size == 1) DisplayRecordStringId[step-1] = 1;
		else DisplayRecordStringId[step - 1] = 7;

		cloneState();  // dissolve
		DisplayRecord[step][v].Dissolve();
		if (v + 1 < l->Size) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());
		if (l->Size > 1)
		{
			DisplayRecord[step][1].PosText.setString("Head");
			HeadPos[step] = 1;	TailPos[step] = l->Size - 1;
		} else HeadPos[step] = TailPos[step] = - 1;

		CalculatePos(step);
		step++; 

		if (l->Size == 1) DisplayRecordStringId[step-1] = 1;
		else DisplayRecordStringId[step-1] = 7;

		cloneState();

		for (int i = v + 1; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));

		DisplayRecord[step][v].Dissolve();
		if (l->Size > 1)
		{
			DisplayRecord[step][1].PosText.setString("Head");
			HeadPos[step] = 1;	TailPos[step] = l->Size - 1;
		} else HeadPos[step] = TailPos[step] = -1;

		CalculatePos(step);

		step++;
		
		if (l->Size == 1) DisplayRecordStringId[step - 1] = 1;
		else DisplayRecordStringId[step - 1] = 8;
	}
	else
		if (v < l->Size - 1)  //Middle
		{
			eventType = E_DelMiddle;

			MakeChoosenUpTo(0, v - 1);

			DisplayRecordStringId[0] = -1;

			if (l->Size == 1) DisplayRecordStringId[1] = 1;
			else
			{
				DisplayRecordStringId[1] = 4;
				for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 6; else DisplayRecordStringId[i] = 5;
			}

			MakeFillIndex(v, Color::Red);
			DisplayRecordStringId[step - 1] = 7;

			cloneState();  // dissolve
			DisplayRecord[step][v].Dissolve();
			if (v + 1 < l->Size) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());

			CalculatePos(step);
			step++; DisplayRecordStringId[step - 1] = 8;


			cloneState();

			for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));

			DisplayRecord[step][v].Dissolve();

			CalculatePos(step);

			step++; DisplayRecordStringId[step - 1] = 8;
		}
}

void Animation_Circle::Add_pos(int v, int data)
{
	if (l->Size == 0) return;

	string s = to_string(data);

	cloneList();

	if (v > 0)
	{
		//middle

		eventType = E_AddMiddle;
		v = min(v, l->Size - 1);

		MakeChoosenUpTo(0, v - 1);
		DisplayRecordStringId[0] = -1;

		DisplayRecordStringId[1] = 4;
		for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 5; else DisplayRecordStringId[i] = 6;

		MakeFillIndex(v, Color::Green);		

		DisplayRecordStringId[step - 1] = 7;

		//make node appear

		cloneState();

		DisplayNode_Circle DisplayCur = DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(0, -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString(s);
		DisplayCur.PosText.setString("");

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 7;

		//make node point
		cloneState();
		AdditionPos[step] = v;

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];

		AdditionalNode[step].NextPos = &DisplayRecord[step][v];

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 8;

		//move
		cloneState();
		AdditionPos[step] = v;

		for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionalNode[step].body.setPosition(AdditionalNode[step].body.getPosition() - Vector2f(0, 150));

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];
		AdditionalNode[step].NextPos = &DisplayRecord[step][v];
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 8;
	}
	else
	{
		//head

		v = min(v, l->Size - 1);

		eventType = E_AddHead;
		MakeChoosenUpTo(-1, -1);
		DisplayRecordStringId[step - 1] = -1;

		// make node appear

		cloneState();

		DisplayNode_Circle DisplayCur;

		DisplayCur = DisplayRecord[step - 1][0];
		DisplayCur.text.setString(s);
		DisplayCur.body.setPosition(DisplayRecord[step - 1][0].body.getPosition() - Vector2f(l->Distance, -150));
		DisplayCur.PosText.setString("");
		DisplayCur.body.setFillColor(Color::Magenta);

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 0;

		//make node point to head
		MakeChoosenUpTo(0, l->Size-1);
			
		DisplayRecordStringId[2] = 5;
		for (int i = 3; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 6; else DisplayRecordStringId[i] = 7;

		MakeFillIndex(v, Color::Green); step--;

		AdditionalNode[step].NextPos = &DisplayRecord[step][0]; AdditionPos[step] = 0;

		CalculatePos(step);

		step++; 

		DisplayRecordStringId[step - 1] = 8;

		cloneState();

		AdditionalNode[step].body.setPosition(DisplayRecord[step][0].body.getPosition());
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];
		for (int i = 0; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionPos[step] = 0;
		
		CalculatePos(step);

		step++; 
		
		DisplayRecordStringId[step - 1] = 8;

		cloneState();
		HeadPos[step] = l->Size + 1;	TailPos[step] = l->Size - 1;
		AdditionalNode[step].PosText.setString("Head");
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];

		if (l->Size) DisplayRecord[step][0].PosText.setString("");

		AdditionPos[step] = 0;
		CalculatePos(step);

		step++; 
		
		DisplayRecordStringId[step - 1] = 8;
	}
}

void Animation_Circle::Upd_pos(int v, int data)
{
	eventType = E_Update;

	cloneList();

	MakeChoosenUpTo(0, v); DisplayRecordStringId[0] = -1;
	DisplayRecordStringId[1] = 1;

	for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

	MakeFillIndex(v, Color::Yellow); DisplayRecordStringId[step - 1] = 3;

	cloneState();
	string s = to_string(data);
	DisplayRecord[step][v].text.setString(s);

	step++; DisplayRecordStringId[step - 1] = 4;
}

void Animation_Circle::Ser_pos(int v)
{
	eventType = E_Search;

	cloneList();

	if (v == -1)
	{
		cout << "Dont exist" << endl;

		MakeChoosenUpTo(0, l->Size - 1);

		DisplayRecordStringId[0] = -1;
		DisplayRecordStringId[1] = 1;

		for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

		cloneState();

		step++; DisplayRecordStringId[step - 1] = 4;

		return;
	}

	MakeChoosenUpTo(0, v);
	DisplayRecordStringId[0] = -1;
	DisplayRecordStringId[1] = 1;

	for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

	MakeFillIndex(v, Color::Cyan);
	DisplayRecordStringId[step - 2] = 5;
}

void Animation_Circle::drawSmoothTransition(int start, int end, float progress, short CodeStatus)
{
	 //Define a function to render a smooth transition between two frames
	 //Interpolate each node between the start and end frames

	vector<DisplayNode_Circle> interpolated_nodes;

	for (int i = 0; i < DisplayRecordSize[start]; i++)
	{
		DisplayNode_Circle a = DisplayRecord[start][i];
		DisplayNode_Circle b = DisplayRecord[end][i];
		DisplayNode_Circle interpolated = interpolated.interpolate(&a, &b, progress);
		interpolated_nodes.push_back(interpolated);
		if (i) interpolated_nodes[i - 1].CalculateLine(&interpolated_nodes[i]);
	}


	DisplayNode_Circle a = AdditionalNode[start];
	DisplayNode_Circle b = AdditionalNode[end];
	DisplayNode_Circle interpolated = interpolated.interpolate(&a, &b, progress);
	interpolated_nodes.push_back(interpolated);

	if (AdditionPos[start] == -1) interpolated_nodes.back().CalculateLine(nullptr);
	else
	{
		if (AdditionPos[start] > 0) interpolated_nodes[AdditionPos[start] - 1].CalculateLine(&interpolated_nodes.back());

		interpolated_nodes.back().CalculateLine(&interpolated_nodes[AdditionPos[start]]);
	}

	int curSize = interpolated_nodes.size();

	//line back
	Vector2f pos1, pos2;
	Vector2f start1, start2;

		if (HeadPos[end] >= curSize) pos1 = interpolated_nodes.back().body.getPosition(); else
			if (HeadPos[end] < 0)  pos1 = Vector2f(-4000, -2000); else
				pos1 = interpolated_nodes[HeadPos[end]].body.getPosition();

		if (TailPos[end] >= curSize) pos2 = interpolated_nodes.back().body.getPosition(); else
			if (TailPos[end] < 0)  pos2 = Vector2f(-4000, -2000); else
				pos2 = interpolated_nodes[TailPos[end]].body.getPosition();
	

		if (HeadPos[start] >= curSize) start1 = interpolated_nodes.back().body.getPosition(); else
			if (HeadPos[start] < 0)  start1 = Vector2f(-4000, -2000); else
				start1 = interpolated_nodes[HeadPos[start]].body.getPosition();

		if (TailPos[start] >= curSize) start2 = interpolated_nodes.back().body.getPosition(); else
			if (TailPos[start] < 0)  start2 = Vector2f(-4000, -2000); else
				start2 = interpolated_nodes[TailPos[start]].body.getPosition();

	float t = progress;

	l->CalBack(Vector2f(pos1.x*t + start1.x*(1-t), pos1.y*t + start1.y*(1-t)), Vector2f(pos2.x*t + start2.x*(1-t), pos2.y*t + start2.y*(1-t)));

	window->draw(l->line1); window->draw(l->line2); window->draw(l->line3); window->draw(l->line4); window->draw(l->arrow);
	window->draw(l->arrow);


	 //Render the interpolated nodes
	for (auto node : interpolated_nodes) node.renderNode(window);

	if (CodeStatus == Disappear) drawFakeCode(start, FakeCodeSize.x * progress); else
		if (CodeStatus == Display) drawFakeCode(start, 0); else
			drawFakeCode(start, FakeCodeSize.x * (1 - progress));

	window->display();
}

void Animation_Circle::drawOneStep(int i)
{
	Vector2f pos1, pos2;

	if (HeadPos[i] >= DisplayRecordSize[i]) pos1 = AdditionalNode[i].body.getPosition(); else
		if (HeadPos[i] < 0)  pos1 = Vector2f(-2000, -1000); else 
		pos1 = DisplayRecord[i][HeadPos[i]].body.getPosition();

	if (TailPos[i] >= DisplayRecordSize[i]) pos2 = AdditionalNode[i].body.getPosition(); else
		if (TailPos[i] < 0)  pos2 = Vector2f(-2000, -1000); else
			pos2 = DisplayRecord[i][TailPos[i]].body.getPosition();

	l->CalBack(pos1, pos2);

	window->draw(l->line1); window->draw(l->line2); window->draw(l->line3); window->draw(l->line4); window->draw(l->arrow);
	window->draw(l->arrow);

	AdditionalNode[i].renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++) DisplayRecord[i][j].renderNode(window);
}

void Animation_Circle::drawFakeCode(int cur, float posX)
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

void Animation_Circle::render()
{
}

void DisplayNode_Circle::renderNode(RenderTarget* window)
{
	window->draw(line);
	window->draw(body);
	window->draw(arrow_head);
	window->draw(text);
	window->draw(PosText);
}

void DisplayNode_Circle::NodeCovert(Round_Display_Node* node)
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

DisplayNode_Circle DisplayNode_Circle::interpolate(DisplayNode_Circle* a, DisplayNode_Circle* b, float t)   //make display between 2 frames
{
	// Create a new DisplayNode_Circle to store the interpolated values
	DisplayNode_Circle result = *a;

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

	// Return the interpolated DisplayNode_Circle
	return result;
}

void DisplayNode_Circle::Dissolve()
{
	body.setOutlineColor(Color::Transparent);
	body.setFillColor(Color::Transparent);
	line.setFillColor(Color::Transparent);
	arrow_head.setFillColor(Color::Transparent);
	text.setFillColor(Color::Transparent);
	PosText.setFillColor(Color::Transparent);
	NextPos = nullptr;
}


