#include "Animation.h"

Animation::Animation(Event* event, LinkedList* l, RenderWindow* window)
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
	FakeCodePos = Vector2f(window->getSize().x- FakeCodeSize.x, 150);
	CodeBox.setPosition(FakeCodePos);
	FakeCode.setFillColor(Color::White);
	FakeCode.setCharacterSize(FakeCodeSize.y/2);
	FakeCode.setFont(Fonte);

	// fake Code for Delete
	{
		Code[0][0] = "if (head==null) return";
		Code[0][1] = "Node* temp = head";
		Code[0][2] = "head = head->next,delete temp";

		Code[1][0] = "if (head==null) return";
		Code[1][1] = "Node* pre = head";
		Code[1][2] = "for (k = 0; k < i - 1; k++)";
		Code[1][3] = "	  pre = pre->next";
		Code[1][4] = "Node* del = pre->next ";
		Code[1][5] = "aft = del->next,pre->next = aft,delete del";

		Code[2][0] = "if (head==null) return";
		Code[2][1] = "Node* pre = head, temp = head->next";
		Code[2][2] = "while (temp->next != null)";
		Code[2][3] = "	   pre = pre->next, temp=temp->next";
		Code[2][4] = "pre->next = null,delete temp,tail = pre";

	}

	// fake Code for Add
	{
		Code[3][0] = "Node* vtx = new Node(v)";
		Code[3][1] = "vtx->next = head";
		Code[3][2] = "head = vtx";

		Code[4][0] = "Node* pre = head";
		Code[4][1] = "for (k = 0; k < i - 1; k++)";
		Code[4][2] = "	   pre = pre->next";
		Code[4][3] = "Node* aft = pre->next";
		Code[4][4] = "Node* vtx = new Node(v)";
		Code[4][5] = "vtx->next = aft,pre->next = vtx";

		Code[5][0] = "Node* vtx = new Node(v)";
		Code[5][1] = "tail->next = vtx";
		Code[5][2] = "tail = vtx";
	}

	// fake Code for Update
	{
		Code[6][0] = "if (head == null) return";
		Code[6][1] = "Node* temp = head";
		Code[6][2] = "for (k = 0; k < i ; k++)";
		Code[6][3] = "	   temp = temp->next";
		Code[6][4] = "temp->data=new data";
	}

	// fake Code for Search
	{
		Code[7][0] = "if (head == null) return NOT_FOUND";
		Code[7][1] = "index = 0, Node* temp = head";
		Code[7][2] = "while (temp.item != v)";
		Code[7][3] = "   index++, temp = temp->next";
		Code[7][4] = "if (temp == null) return NOT_FOUND";
		Code[7][5] = "return index";
	}
}

Animation::~Animation()
{
}

void Animation::clearAll()
{
	step = curStep = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i] = {}, AdditionalNode[i].NextPos = nullptr;

	for (int i = 0; i < 30; i++) AdditionPos[i] = -1, DisplayRecordStringId[i]=-1;
}

void Animation::Link(int cur)	// point one to another
{
	for (int j = 0; j < DisplayRecordSize[cur] - 1; j++)
		DisplayRecord[cur][j].NextPos = &DisplayRecord[cur][j + 1];
}

void Animation::cloneList()   //copy linked list
{
	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode DisplayCur;

		DisplayCur.NodeCovert(&l->Round_Node[j]);

		if (j != 0 && j != l->Size - 1) DisplayCur.PosText.setString("");

		DisplayRecord[step].push_back(DisplayCur);
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

void Animation::CalculatePos(int pos)
{
	for (int i = 0; i < DisplayRecordSize[pos]; i++)
	{
		DisplayNode* cur = &DisplayRecord[pos][i];
		cur->CalculateLine(cur->NextPos);
	}

	AdditionalNode[pos].CalculateLine(AdditionalNode[pos].NextPos);
	if (AdditionPos[pos] == -1)
	{
		AdditionalNode[pos].arrow_head.setScale(Vector2f(0, 1));
		AdditionalNode[pos].line.setScale(Vector2f(0, 1));
	}
}

void Animation::MakeFillIndex(int n, Color color)   // n<l.Size
{
	if (n < 0) return;
	cloneState();

	DisplayRecord[step][n].body.setFillColor(color);

	step++;
}

void Animation::MakeChoosenUpTo(int u, int v)  //	u<=v<l.Size
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

void Animation::Del_pos(int v)
{
	v = min(v, l->Size - 1);

	if (!v) // Head
	{
		eventType = E_DelHead;

		MakeChoosenUpTo(0, v - 1);
		
		DisplayRecordStringId[step - 1] = -1;

		MakeFillIndex(v, Color::Red);

		DisplayRecordStringId[step-1] = 1;

		cloneState();  // dissolve
		DisplayRecord[step][v].Dissolve();
		if (v + 1 < l->Size) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());
		if (l->Size > 1) DisplayRecord[step][1].PosText.setString("Head");

				

		CalculatePos(step);
		step++;DisplayRecordStringId[step-1] = 2;

		cloneState();

		for (int i = v + 1; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));

		DisplayRecord[step][v].Dissolve();
		if (l->Size > 1) DisplayRecord[step][1].PosText.setString("Head");

				

		CalculatePos(step);

		step++;DisplayRecordStringId[step-1] = 2;
	}
	else
		if (v < l->Size - 1)  //Middle
		{
			eventType = E_DelMiddle;

			MakeChoosenUpTo(0, v - 1);

			DisplayRecordStringId[0] = -1;
			DisplayRecordStringId[1] = 1;

			for (int i=2;i<step;i++) if (i&1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

			MakeFillIndex(v, Color::Red);
			DisplayRecordStringId[step-1] = 4;

			cloneState();  // dissolve
			DisplayRecord[step][v].Dissolve();
			if (v + 1 < l->Size) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());

			CalculatePos(step);
			step++; DisplayRecordStringId[step - 1] = 5;


			cloneState();

			for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));

			DisplayRecord[step][v].Dissolve();

			CalculatePos(step);

			step++; DisplayRecordStringId[step - 1] = 5;
		}
		else  //Tail
		{
			eventType = E_DelTail;
			MakeChoosenUpTo(0, v - 1);
			DisplayRecordStringId[0] = -1;
			DisplayRecordStringId[1] = 1;

			for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

			MakeFillIndex(v, Color::Red);

			DisplayRecordStringId[step - 1] = 4;

			cloneState();
			DisplayRecord[step][v].Dissolve();
			if (v) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v - 1].body.getPosition());
			if (l->Size > 1) DisplayRecord[step][v - 1].PosText.setString("Tail");

			CalculatePos(step);
			step++; DisplayRecordStringId[step-1] = 4;
		}
}

void Animation::Add_pos(int v, int data)
{
	if (l->Size == 0) return;

	string s = to_string(data);

	if (v > l->Size - 1)
	{	//tail
		eventType = E_AddTail;

		v = min(v, l->Size - 1);
		MakeChoosenUpTo(0, -1);
		DisplayRecordStringId[0] = -1;
		
		//make node appear
		cloneState();

		AdditionPos[step-1] = -1;

		DisplayNode DisplayCur = DisplayRecord[step-1][v];

		DisplayCur.body.setPosition(DisplayRecord[step-1][v].body.getPosition() - Vector2f(-l->Distance, -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString(s);
		DisplayCur.PosText.setString("");

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++; DisplayRecordStringId[step-1] = 0;

		//make node point
		cloneState();

		DisplayRecord[step][v].NextPos = &AdditionalNode[step];
		DisplayRecord[step][v].line.setFillColor(DisplayRecord[step][v].ChosenColor);
		DisplayRecord[step][v].arrow_head.setFillColor(DisplayRecord[step][v].ChosenColor);
		DisplayRecord[step][v].body.setFillColor(DisplayRecord[step][v].ChosenColor);
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();

		AdditionalNode[step].body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(-l->Distance, 0));

		DisplayRecord[step][v].NextPos = &AdditionalNode[step];

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();

		DisplayRecord[step][v].NextPos = &AdditionalNode[step];
		if (l->Size > 1) DisplayRecord[step][v].PosText.setString("");
		AdditionalNode[step].PosText.setString("Tail");

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 2;
	}
	else if (v > 0)
	{
		//middle

		eventType = E_AddMiddle;
		v = min(v, l->Size - 1);

		MakeChoosenUpTo(0, v - 1);
		DisplayRecordStringId[0] = -1;
		DisplayRecordStringId[1] = 0;

		for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 2; else DisplayRecordStringId[i] = 1;

		MakeFillIndex(v, Color::Green);		DisplayRecordStringId[step-1] = 3;

		//make node appear

		cloneState();

		DisplayNode DisplayCur = DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(0, -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString(s);
		DisplayCur.PosText.setString("");

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 4;

		//make node point
		cloneState();
		AdditionPos[step] = v;

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];

		AdditionalNode[step].NextPos = &DisplayRecord[step][v];

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 5;

		//move
		cloneState();
		AdditionPos[step] = v;

		for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionalNode[step].body.setPosition(AdditionalNode[step].body.getPosition() - Vector2f(0, 150));

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];
		AdditionalNode[step].NextPos = &DisplayRecord[step][v];
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 5;
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

		DisplayNode DisplayCur;

		DisplayCur=DisplayRecord[step-1][0];
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

void Animation::Upd_pos(int v, int data)
{
	eventType = E_Update;

	MakeChoosenUpTo(0, v); DisplayRecordStringId[0] = -1;
	DisplayRecordStringId[1] = 1;

	for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

	MakeFillIndex(v, Color::Yellow); DisplayRecordStringId[step-1] = 3;

	cloneState();
	string s = to_string(data);
	DisplayRecord[step][v].text.setString(s);

	step++; DisplayRecordStringId[step - 1] = 4;
}

void Animation::Ser_pos(int v)
{
	eventType = E_Search;

	if (v == -1)
	{
		cout << "Dont exist" << endl;

		MakeChoosenUpTo(0, l->Size-1);

		DisplayRecordStringId[0] = -1;
		DisplayRecordStringId[1] = 1;

		for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

		cloneState();

		step++; DisplayRecordStringId[step-1] = 4;

		return;
	}

	MakeChoosenUpTo(0, v);
	DisplayRecordStringId[0] = -1;
	DisplayRecordStringId[1] = 1;

	for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

	MakeFillIndex(v, Color::Cyan);
	DisplayRecordStringId[step - 1] = 5;
}

void Animation::drawSmoothTransition(int start, int end, float progress,short CodeStatus)
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
		if (i) interpolated_nodes[i - 1].CalculateLine(&interpolated_nodes[i]);
	}


	DisplayNode a = AdditionalNode[start];
	DisplayNode b = AdditionalNode[end];
	DisplayNode interpolated = interpolated.interpolate(&a, &b, progress);
	interpolated_nodes.push_back(interpolated);

	if (AdditionPos[start] == -1) interpolated_nodes.back().CalculateLine(nullptr);
	else
	{
		if (AdditionPos[start] > 0) interpolated_nodes[AdditionPos[start] - 1].CalculateLine(&interpolated_nodes.back());

		interpolated_nodes.back().CalculateLine(&interpolated_nodes[AdditionPos[start]]);
	}

	// Render the interpolated nodes
	for (auto node : interpolated_nodes) node.renderNode(window);

	if (CodeStatus== Disappear) drawFakeCode(start, FakeCodeSize.x * progress); else
	if (CodeStatus == Display) drawFakeCode(start, 0); else
	drawFakeCode(start, FakeCodeSize.x*(1-progress));

	window->display();
}

void Animation::drawOneStep(int i)
{
	AdditionalNode[i].renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++) DisplayRecord[i][j].renderNode(window);
}

void Animation::drawFakeCode(int cur,float posX)
{
	for (int i = 0; i < fakeId[eventType]; i++)
	{
		CodeBox.setPosition(FakeCodePos + Vector2f(posX,FakeCodeSize.y*i));
		
		FakeCode.setString(Code[eventType][i]);
		FakeCode.setPosition(CodeBox.getPosition().x+10,CodeBox.getPosition().y + FakeCodeSize.y/ 2.f - FakeCode.getGlobalBounds().height / 2.f);
		
		if (DisplayRecordStringId[cur] == i) CodeBox.setFillColor(Color::Black); else CodeBox.setFillColor(CodeBoxColor);

		window->draw(CodeBox);
		window->draw(FakeCode);
	}
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

void DisplayNode::NodeCovert(Round_Display_Node* node)
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
	DisplayNode result = *a;

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


