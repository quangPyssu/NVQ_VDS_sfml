#include "Animation_Two.h"

Animation_Two::Animation_Two(Event* event, LinkedList* l, RenderWindow* window)
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
	FakeCode.setCharacterSize(FakeCodeSize.y/5*2);
	FakeCode.setFont(Fonte);

	// fake Code for Delete
	{
		Code[0][0] = "if (head==null) return";
		Code[0][1] = "Node* temp = head";
		Code[0][2] = "head = head->next,     delete temp";
		Code[0][3] = "if (head != null) head.prev = null";

		Code[1][0] = "if (head==null) return";
		Code[1][1] = "Node* del = head";
		Code[1][2] = "for (k = 0; k < i ; k++)";
		Code[1][3] = "	     del = del->next";
		Code[1][4] = "aft = del->next, pre = del->prev, delete del";
		Code[1][5] = "aft->prev = pre, pre->next=aft";

		Code[2][0] = "if (head==null) return";
		Code[2][1] = "Node* temp = tail";
		Code[2][2] = "tail = tail.prev, tail->next = null, delete temp";
	}

	// fake Code for Add
	{
		Code[3][0] = "Node* vtx = new Node(v)";
		Code[3][1] = "vtx->next = head,  if (head != null) head.prev = vtx;";
		Code[3][2] = "head = vtx";
		
		Code[4][0] = "Node* pre = head";
		Code[4][1] = "for (k = 0; k < i - 1; k++)";
		Code[4][2] = "	   pre = pre->next";
		Code[4][3] = "Node* aft = pre->next";
		Code[4][4] = "Node* vtx = new Node(v)";
		Code[4][5] = "vtx->next = aft, pre->next = vtx, pre.next = vtx, vtx.prev = pre";

		Code[5][0] = "Node* vtx = new Node(v)";
		Code[5][1] = "tail->next = vtx, vtx->prev = tail";
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

Animation_Two::~Animation_Two()
{
}

void Animation_Two::clearAll()
{
	step = curStep = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i] = {}, AdditionalNode[i].NextPos = nullptr;

	for (int i = 0; i < 30; i++) AdditionPos[i] = -1, DisplayRecordStringId[i]=-1, AdditionalNode[i].PrevPos = nullptr;
}

void Animation_Two::Link(int cur)	// point one to another
{
	for (int j = 0; j < DisplayRecordSize[cur] - 1; j++)
	{
		DisplayRecord[cur][j].NextPos = &DisplayRecord[cur][j + 1];
		DisplayRecord[cur][j].nextId = j + 1;
	}

	for (int j = 1; j < DisplayRecordSize[cur]; j++)
	{
		DisplayRecord[cur][j].PrevPos = &DisplayRecord[cur][j - 1];
		DisplayRecord[cur][j].prevId = j - 1;
	}

}

void Animation_Two::cloneList()   //copy linked list
{
	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode_Two DisplayCur;

		DisplayCur.NodeCovert(&l->Two_Node[j]);

		if (j != 0 && j != l->Size - 1) DisplayCur.PosText.setString("");

		DisplayRecord[step].push_back(DisplayCur);
	}

	DisplayRecordSize[step] = l->Size;

	Link(step);

	step++;
}

void Animation_Two::cloneState() //copy display linked list
{
	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecordSize[step] = DisplayRecordSize[step - 1];
	AdditionalNode[step] = AdditionalNode[step - 1];
	Link(step);
}

void DisplayNode_Two::CalculateLine(DisplayNode_Two* next, DisplayNode_Two* prev)
{
	if (body.getFillColor() == Color::Transparent)
	{
		body.setOutlineColor(Color::Transparent);
		body.setFillColor(Color::Transparent);

		line.setFillColor(Color::Transparent);
		back.setFillColor(Color::Transparent);
		arrow_head.setFillColor(Color::Transparent);
		arrow_back.setFillColor(Color::Transparent);

		text.setFillColor(Color::Transparent);
		NextPos = nullptr;
		PrevPos = nullptr;
		return;
	}

	text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);
	PosText.setPosition(Vector2f(text.getPosition().x - body.getRadius(), text.getPosition().y + body.getRadius() + 5));

	if (next == nullptr || next->body.getPosition() == body.getPosition())
	{
		line.setScale(Vector2f(0, 0));
		arrow_head.setScale(Vector2f(0, 0));
	}
	else
	{

		Vector2f NextPos = next->body.getPosition();

		Vector2f d = -body.getPosition() + NextPos;

		float distance = sqrt(d.x * d.x + d.y * d.y);

		line.setScale(Vector2f(distance - body.getRadius(), 1));
		arrow_head.setScale(Vector2f(1, 1));


		line.setPosition(body.getPosition() - Vector2f(0, 10));


		if (d.x) rad = (float)atan(d.y / d.x); else rad = 3 * PI / 2;
		angle = rad * 180 / PI;

		line.setRotation(angle);
		arrow_head.setRotation(angle + 90);

		arrow_head.setPosition(body.getPosition() + d + Vector2f((body.getRadius() + arrow_head.getRadius()) * cos(rad + PI), (body.getRadius() + arrow_head.getRadius()) * sin(rad + PI)-10));
	}

	if (prev == nullptr || prev->body.getPosition() == body.getPosition())
	{
		back.setScale(Vector2f(0, 0));
		arrow_back.setScale(Vector2f(0, 0));
	}
	else
	{
		Vector2f PrevPos = prev->body.getPosition();

		Vector2f d = body.getPosition() - PrevPos;

		float distance = sqrt(d.x * d.x + d.y * d.y);

		back.setScale(Vector2f(distance - body.getRadius(), 1));
		arrow_back.setScale(Vector2f(1, 1));


		back.setPosition(body.getPosition() + Vector2f(0, 10));

		if (d.x) rad_back = (float)atan(d.y / d.x); else rad_back = 3 * PI / 2;
		angle_back = rad_back * 180 / PI;

		back.setRotation(angle_back+180);
		arrow_back.setRotation(angle_back - 90);

		arrow_back.setPosition(body.getPosition() - d - Vector2f(((body.getRadius() + arrow_head.getRadius()) * cos(rad_back + PI)), (body.getRadius() + arrow_head.getRadius()) * sin(rad_back + PI)-10));
	}	
}

void Animation_Two::CalculatePos(int pos)
{
	for (int i = 0; i < DisplayRecordSize[pos]; i++)
	{
		DisplayNode_Two* cur = &DisplayRecord[pos][i];
		cur->CalculateLine(cur->NextPos,cur->PrevPos);
	}

	AdditionalNode[pos].CalculateLine(AdditionalNode[pos].NextPos, AdditionalNode[pos].PrevPos);

	if (AdditionPos[pos] == -1)
	{
		AdditionalNode[pos].arrow_head.setScale(Vector2f(0, 1));
		AdditionalNode[pos].arrow_back.setScale(Vector2f(0, 1));
		AdditionalNode[pos].line.setScale(Vector2f(0, 1));
		AdditionalNode[pos].line.setScale(Vector2f(0, 1));
	}
}

void Animation_Two::MakeFillIndex(int n, Color color)   // n<l.Size
{
	if (n < 0) return;
	cloneState();

	DisplayRecord[step][n].body.setFillColor(color);

	step++;
}

void Animation_Two::MakeChoosenUpTo(int u, int v)  //	u<=v<l.Size
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

void Animation_Two::Del_pos(int v)
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
		if (l->Size > 1)
		{
			DisplayRecord[step][1].PosText.setString("Head");
			DisplayRecord[step][1].prevId = 1;
			DisplayRecord[step][1].PrevPos = nullptr;
		}
				

		CalculatePos(step);

		step++;DisplayRecordStringId[step-1] = 2;
	}
	else
		if (v < l->Size - 1)  //Middle
		{
			eventType = E_DelMiddle;

			MakeChoosenUpTo(0, v);

			DisplayRecordStringId[0] = -1;
			DisplayRecordStringId[1] = 1;

			for (int i=2;i<step;i++) if (i&1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

			MakeFillIndex(v, Color::Red);
			DisplayRecord[step-1][v + 1].prevId = v;
			DisplayRecordStringId[step-1] = 4;

			DisplayNode_Two DisplayCur = DisplayRecord[step-1][v];
			DisplayCur.body.setFillColor(Color::Transparent);
			DisplayCur.NextPos = DisplayCur.PrevPos = &DisplayCur;
			DisplayCur.PosText.setString("");

			AdditionalNode[step-1] = DisplayCur;

			cloneState();  // dissolve
			DisplayRecord[step][v].Dissolve();
			DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v + 1].body.getPosition());
			
			DisplayRecord[step][v + 1].PrevPos = &DisplayRecord[step][v - 1];
			DisplayRecord[step][v + 1].prevId = l->Size+1;
												/// need addition
			AdditionalNode[step].body.setPosition(DisplayRecord[step][v-1].body.getPosition());

			CalculatePos(step);
			step++; DisplayRecordStringId[step - 1] = 5;


			cloneState();

			AdditionalNode->body.setPosition(DisplayRecord[step][v - 1].body.getPosition());

			for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(l->Distance, 0));
			DisplayRecord[step][v + 1].PrevPos = &DisplayRecord[step][v - 1];
			DisplayRecord[step][v + 1].prevId = v - 1;

			DisplayRecord[step][v].Dissolve();

			CalculatePos(step);

			step++; DisplayRecordStringId[step - 1] = 5;
		}
		else  //Tail
		{
			eventType = E_DelTail;
			MakeChoosenUpTo(0, -1);
			DisplayRecordStringId[0] = -1;

			MakeFillIndex(v, Color::Red);
			DisplayRecordStringId[step - 1] = 1;

			cloneState();
			DisplayRecord[step][v].Dissolve();
			if (v) DisplayRecord[step][v].body.setPosition(DisplayRecord[step][v - 1].body.getPosition());
			if (l->Size > 1) DisplayRecord[step][v - 1].PosText.setString("Tail");

			CalculatePos(step);
			step++; DisplayRecordStringId[step-1] = 2;
		}
}

void Animation_Two::Add_pos(int v, int data)
{
	if (l->Size == 0) return;

	string s = to_string(data);

	if (v > l->Size - 1)
	{	//tail
		eventType = E_AddTail;

		v = min(v, l->Size - 1);
		MakeChoosenUpTo(-1, -1);
		DisplayRecordStringId[0] = -1;
		
		//make node appear

		AdditionPos[step] = -1;

		cloneState();

		DisplayNode_Two DisplayCur = DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(-l->Distance, -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = DisplayCur.PrevPos = nullptr;
		DisplayCur.text.setString(s);
		DisplayCur.PosText.setString("");

		AdditionalNode[step] = DisplayCur;

		CalculatePos(step);

		step++; DisplayRecordStringId[step-1] = 0;

		//make node point

		MakeFillIndex(v, Color::Green); step--;

		AdditionalNode[step].PrevPos= &DisplayRecord[step][v];
		AdditionalNode[step].prevId = v;
		AdditionPos[step] = v + 1;

		DisplayRecord[step][v].NextPos = &AdditionalNode[step];
		DisplayRecord[step][v].line.setFillColor(DisplayRecord[step][v].ChosenColor);
		DisplayRecord[step][v].arrow_head.setFillColor(DisplayRecord[step][v].ChosenColor);
		AdditionalNode[step].back.setFillColor(DisplayRecord[step][v].ChosenColor);
		AdditionalNode[step].arrow_back.setFillColor(DisplayRecord[step][v].ChosenColor);
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();

		AdditionalNode[step].body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionPos[step] = v + 1;

		AdditionalNode[step].PrevPos = &DisplayRecord[step][v];
		AdditionalNode[step].prevId = v;
		DisplayRecord[step][v].NextPos = &AdditionalNode[step];

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();

		AdditionalNode[step].PrevPos = &DisplayRecord[step][v];
		AdditionalNode[step].prevId = v;
		AdditionPos[step] = v + 1;
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

		DisplayNode_Two DisplayCur = DisplayRecord[step][v];

		DisplayCur.body.setPosition(DisplayRecord[step][v].body.getPosition() - Vector2f(0, -150));
		DisplayCur.body.setFillColor(Color::Magenta);
		DisplayCur.NextPos = DisplayCur.PrevPos = &DisplayCur;
		DisplayCur.text.setString(s);
		DisplayCur.PosText.setString("");

		AdditionalNode[step] = DisplayCur;

		AdditionalNode[step].prevId = v - 1;
		AdditionPos[step] = v;

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 4;

		//make node point
		cloneState();
		AdditionPos[step] = v;

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];
		AdditionalNode[step].PrevPos = &DisplayRecord[step][v - 1];
		AdditionalNode[step].prevId = v-1;

		DisplayRecord[step][v].PrevPos = &AdditionalNode[step];
		DisplayRecord[step][v].prevId = l->Size + 1;
		AdditionalNode[step].NextPos = &DisplayRecord[step][v];

		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 5;

		//move
		cloneState();
		AdditionPos[step] = v;

		for (int i = v; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionalNode[step].body.setPosition(AdditionalNode[step].body.getPosition() - Vector2f(0, 150));

		DisplayRecord[step][v - 1].NextPos = &AdditionalNode[step];
		AdditionalNode[step].PrevPos = &DisplayRecord[step][v - 1];
		AdditionalNode[step].prevId = v-1;

		DisplayRecord[step][v].PrevPos = &AdditionalNode[step];
		DisplayRecord[step][v].prevId = l->Size + 1;
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

		DisplayNode_Two DisplayCur;

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

		AdditionalNode[step].NextPos = &DisplayRecord[step][0]; 
		DisplayRecord[step][0].PrevPos = &AdditionalNode[step];

		
		AdditionPos[step] = 0;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();

		AdditionalNode[step].body.setPosition(DisplayRecord[step][0].body.getPosition());
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];
		DisplayRecord[step][0].PrevPos = &AdditionalNode[step];
		DisplayRecord[step][0].prevId = l->Size + 1;

		for (int i = 0; i < DisplayRecordSize[step]; i++) DisplayRecord[step][i].body.setPosition(DisplayRecord[step][i].body.getPosition() - Vector2f(-l->Distance, 0));
		AdditionPos[step] = 0;
		CalculatePos(step);

		step++; DisplayRecordStringId[step - 1] = 1;

		cloneState();
		AdditionalNode[step].PosText.setString("Head");
		AdditionalNode[step].NextPos = &DisplayRecord[step][0];
		DisplayRecord[step][0].PrevPos = &AdditionalNode[step];
		DisplayRecord[step][0].prevId = l->Size + 1;

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

void Animation_Two::Upd_pos(int v, int data)
{
	eventType = E_Update;

	MakeChoosenUpTo(0, v); DisplayRecordStringId[0] = -1;
	DisplayRecordStringId[1] = 1;

	for (int i = 2; i < step; i++) if (i & 1) DisplayRecordStringId[i] = 3; else DisplayRecordStringId[i] = 2;

	MakeFillIndex(v, Color::Yellow); DisplayRecordStringId[step-1] = 4;

	cloneState();
	string s = to_string(data);
	DisplayRecord[step][v].text.setString(s);

	step++; DisplayRecordStringId[step - 1] = 4;
}

void Animation_Two::Ser_pos(int v)
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
	DisplayRecordStringId[step - 2] = 5;
}

void Animation_Two::drawSmoothTransition(int start, int end, float progress,short CodeStatus)
{
	// Define a function to render a smooth transition between two frames
	// Interpolate each node between the start and end frames

	vector<DisplayNode_Two> interpolated_nodes;


	for (int i = 0; i < DisplayRecordSize[start]; i++)
	{
		DisplayNode_Two a = DisplayRecord[start][i];
		DisplayNode_Two b = DisplayRecord[end][i];
		DisplayNode_Two interpolated = interpolated.interpolate(&a, &b, progress);

		interpolated.prevId= b.prevId; 

		interpolated_nodes.push_back(interpolated);
	}

	DisplayNode_Two a = AdditionalNode[start];
	DisplayNode_Two b = AdditionalNode[end];
	DisplayNode_Two interpolated = interpolated.interpolate(&a, &b, progress);
	interpolated_nodes.push_back(interpolated);
	
	for (int i = 0; i < DisplayRecordSize[start]; i++)
	{
		DisplayNode_Two* next = nullptr;
		DisplayNode_Two* prev = nullptr;

		if (i < DisplayRecordSize[start] - 1) next = &interpolated_nodes[i + 1];
		if (i) prev = &interpolated_nodes[i - 1];

		if (interpolated_nodes[i].prevId != -1)
		{

			if (interpolated_nodes[i].prevId >= l->Size) prev = &interpolated_nodes.back(); else
			prev = &interpolated_nodes[interpolated_nodes[i].prevId];
		}

		interpolated_nodes[i].CalculateLine(next, prev);
	}

	if (AdditionPos[start] == -1) interpolated_nodes.back().CalculateLine(nullptr,nullptr);
	else
	{
		int v = AdditionPos[start];

		if (v > 0)
		{
			
			interpolated_nodes.back().CalculateLine(&interpolated_nodes[v], &interpolated_nodes[v-1]);

			DisplayNode_Two* next = nullptr;
			DisplayNode_Two* prev = nullptr;
			
			if (v>1) prev = &interpolated_nodes[v - 2];

			interpolated_nodes[v-1].CalculateLine(&interpolated_nodes.back(), prev);
		} else interpolated_nodes.back().CalculateLine(&interpolated_nodes[v], &interpolated_nodes.back());

	}

	// Render the interpolated nodes
	for (auto node : interpolated_nodes) node.renderNode(window);

	if (CodeStatus== Disappear) drawFakeCode(start, FakeCodeSize.x * progress); else
	if (CodeStatus == Display) drawFakeCode(start, 0); else
	drawFakeCode(start, FakeCodeSize.x*(1-progress));

	window->display();
}

void Animation_Two::drawOneStep(int i)
{
	AdditionalNode[i].renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++) DisplayRecord[i][j].renderNode(window);
}

void Animation_Two::drawFakeCode(int cur,float posX)
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

void Animation_Two::render()
{
}

void DisplayNode_Two::renderNode(RenderTarget* window)
{
	window->draw(line);
	window->draw(back);
	window->draw(body);
	window->draw(arrow_head);
	window->draw(arrow_back);
	window->draw(text);
	window->draw(PosText);
}

void DisplayNode_Two::NodeCovert(Two_Display_Node* node)
{
	body = node->body;

	line = node->line;
	back = node->back;

	arrow_head = node->arrow_head;
	arrow_back = node->arrow_back;

	this->font = node->font;

	text = node->text;

	this->text.setFont(*this->font);

	PosText = node->PosText;

	this->PosText.setFont(*this->font);
}

DisplayNode_Two DisplayNode_Two::interpolate(DisplayNode_Two* a, DisplayNode_Two* b, float t)   //make display between 2 frames
{
	// Create a new DisplayNode_Two to store the interpolated values
	DisplayNode_Two result = *a;

	// Interpolate the position of the body and arrow head
	result.body.setPosition((1 - t) * a->body.getPosition() + t * b->body.getPosition());
	result.arrow_head.setPosition((1 - t) * a->arrow_head.getPosition() + t * b->arrow_head.getPosition());
	result.arrow_back.setPosition((1 - t) * a->arrow_back.getPosition() + t * b->arrow_back.getPosition());

	result.line.setPosition((1 - t) * a->line.getPosition() + t * b->line.getPosition());
	result.back.setPosition((1 - t) * a->back.getPosition() + t * b->back.getPosition());

	// Interpolate the rotation angle of the body
	float angle_diff = b->angle - a->angle;
	float angle = a->angle + t * angle_diff;
	result.angle = angle;
	result.arrow_head.setRotation(angle + 90);
	result.line.setRotation(angle);

	angle_diff = b->angle_back - a->angle_back;
	angle = a->angle_back + t * angle_diff;
	result.angle_back = angle;
	result.arrow_back.setRotation(angle - 90);
	result.back.setRotation(angle);

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
		result.back.setFillColor(Color::Transparent);
		result.arrow_head.setFillColor(Color::Transparent);
		result.arrow_back.setFillColor(Color::Transparent);
		result.text.setFillColor(Color::Transparent);
	}
	else result.body.setFillColor(Color(red, green, blue, alpha));

	// Interpolate the position and color of the text
	result.text.setPosition(result.body.getPosition().x - result.text.getGlobalBounds().width / 2.f, result.body.getPosition().y - result.text.getGlobalBounds().height / 3 * 2);
	result.PosText.setPosition(Vector2f(result.text.getPosition().x - body.getRadius(), result.text.getPosition().y + body.getRadius() + 5));

	// Return the interpolated DisplayNode_Two
	return result;
}

void DisplayNode_Two::Dissolve()
{
	body.setOutlineColor(Color::Transparent);
	body.setFillColor(Color::Transparent);

	line.setFillColor(Color::Transparent);
	back.setFillColor(Color::Transparent);
	arrow_head.setFillColor(Color::Transparent);
	arrow_back.setFillColor(Color::Transparent);

	text.setFillColor(Color::Transparent);
	PosText.setFillColor(Color::Transparent);
	NextPos = nullptr;
	PrevPos = nullptr;
}


