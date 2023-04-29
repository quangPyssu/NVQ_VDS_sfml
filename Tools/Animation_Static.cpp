#include "Animation_Static.h"

Animation_Static::Animation_Static(Event* event, LinkedList* l, RenderWindow* window)
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

	// fake Code for Update
	{
		Code[0][0] = "if (pos>size) return";
		Code[0][1] = "  a[pos]=val;";
	}

	// fake Code for Search
	{
		Code[1][0] = "if (empty) return NOT_FOUND";
		Code[1][1] = "index = 0";
		Code[1][2] = "while (a[index] != v && index!=size)";
		Code[1][3] = "        index++";
		Code[1][4] = "if (index == size) return NOT_FOUND";
		Code[1][5] = "return index";
	}
}

Animation_Static::~Animation_Static()
{
}

void Animation_Static::clearAll()
{
	step = curStep = 0;
	for (int i = 0; i < 30; i++) DisplayRecord[i].clear(), DisplayRecordSize[i] = 0, AdditionalNode[i] = {}, AdditionalNode[i].NextPos = nullptr;

	for (int i = 0; i < 30; i++) AdditionPos[i] = -1, DisplayRecordStringId[i]=-1;
}

void Animation_Static::Link(int cur)	// point one to another
{
	for (int j = 0; j < DisplayRecordSize[cur] - 1; j++)
		DisplayRecord[cur][j].NextPos = &DisplayRecord[cur][j + 1];
}

void Animation_Static::cloneList()   //copy linked list
{
	for (int j = 0; j < l->Size; j++)
	{
		DisplayNode_Static DisplayCur;

		DisplayCur.NodeCovert(&l->Square_Node[j]);

		if (j != 0 && j != l->Size - 1) DisplayCur.PosText.setString("");

		DisplayRecord[step].push_back(DisplayCur);
	}

	DisplayRecordSize[step] = l->Size;

	Link(step);

	step++;
}

void Animation_Static::cloneState() //copy display linked list
{
	DisplayRecord[step] = DisplayRecord[step - 1];
	DisplayRecordSize[step] = DisplayRecordSize[step - 1];
	AdditionalNode[step] = AdditionalNode[step - 1];
	Link(step);
}

void DisplayNode_Static::CalculateLine(DisplayNode_Static* next)
{
	text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);
}

void Animation_Static::CalculatePos(int pos)
{
	for (int i = 0; i < DisplayRecordSize[pos]; i++)
	{
		DisplayNode_Static* cur = &DisplayRecord[pos][i];
		cur->CalculateLine(cur->NextPos);
	}

	AdditionalNode[pos].CalculateLine(AdditionalNode[pos].NextPos);
}

void Animation_Static::MakeFillIndex(int n, Color color)   // n<l.Size
{
	if (n < 0) return;
	cloneState();

	DisplayRecord[step][n].body.setFillColor(color);

	step++;
}

void Animation_Static::MakeChoosenUpTo(int u, int v)  //	u<=v<l.Size
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
			step++;
		}
		
	}
}

void Animation_Static::MakeCopyNext(int n)  //	n<=l.Size
{
	for (int i = n; i < l->Size; i++)
	{
		cloneState();

		DisplayRecord[step][i].body.setOutlineColor(DisplayRecord[step][i].ChosenColor);
		CalculatePos(step);

		step++;

		cloneState();
		if (i < l->Size - 1) DisplayRecord[step][i].text.setString(DisplayRecord[step][i + 1].text.getString());
		CalculatePos(step);

		step++;
	}
}

void Animation_Static::MakeCopyPrev(int n)  //	n<=l.Size
{
	for (int i = l->Size - 1; i > n; i--)
	{
		cloneState();

		DisplayRecord[step][i].body.setOutlineColor(DisplayRecord[step][i].ChosenColor);
		CalculatePos(step);

		step++;

		cloneState();
		DisplayRecord[step][i].text.setString(DisplayRecord[step][i - 1].text.getString());
		CalculatePos(step);

		step++;
	}
}

void Animation_Static::Del_pos(int v)
{
	v = min(v, l->Size - 1);

	if (!v) // Head
	{
		eventType = E_Nul;

		MakeChoosenUpTo(-1, l->Size - 1);

		cloneState();

		MakeCopyNext(0);

		cloneState();

		DisplayRecord[step][l->Size - 1].text.setString("0");

		CalculatePos(step);
		step++;
	}
	else
		if (v < l->Size - 1)  //Middle
		{
			eventType = E_Nul;

			MakeChoosenUpTo(-1, l->Size - 1);

			cloneState();

			MakeCopyNext(v);

			cloneState();

			DisplayRecord[step][l->Size - 1].text.setString("0");

			CalculatePos(step);
			step++;
		}
		else  //Tail
		{
			eventType = E_Nul;
			MakeChoosenUpTo(v + 1, l->Size - 1);

			MakeFillIndex(v, Color::Red);

			cloneState();

			DisplayRecord[step][v].text.setString("0");

			CalculatePos(step);
			step++;
		}
}

void Animation_Static::Add_pos(int v, int data)
{
	if (l->Size == 0) return;

	string s = to_string(data);

	if (v > l->Size - 1)
	{	//tail
		eventType = E_Nul;

		v = min(v, l->Size - 1);
		MakeChoosenUpTo(0, -1);

		//make node appear
		cloneState();

		DisplayNode_Static DisplayCur = DisplayRecord[step - 1][v];

		DisplayCur.body.setPosition(DisplayRecord[step - 1][l->Size - 1].body.getPosition() - Vector2f((float)-14 - DisplayRecord[step - 1][l->Size - 1].body.getSize().x, 0));
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString("0");

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++;

		cloneState();

		AdditionalNode[step].text.setString(s);
		AdditionalNode[step].body.setFillColor(Color::Magenta);

		CalculatePos(step);
		step++;
	}
	else if (v > 0)
	{
		//middle

		eventType = E_Nul;
		v = min(v, l->Size - 1);

		MakeChoosenUpTo(-1, v - 1);

		//make node appear
		cloneState();

		DisplayNode_Static DisplayCur = DisplayRecord[step - 1][v];

		DisplayCur.body.setPosition(DisplayRecord[step - 1][l->Size - 1].body.getPosition() - Vector2f((float)-14 - DisplayRecord[step - 1][l->Size - 1].body.getSize().x, 0));
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString("0");

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++;


		cloneState();

		AdditionalNode[step].text.setString(DisplayRecord[step][l->Size - 1].text.getString());
		AdditionalNode[step].body.setOutlineColor(AdditionalNode[step].ChosenColor);

		CalculatePos(step);
		step++;

		MakeCopyPrev(v);

		cloneState();

		DisplayRecord[step][v].text.setString(s);
		DisplayRecord[step][v].body.setFillColor(Color::Magenta);

		CalculatePos(step);
		step++;
	}
	else
	{
		//head

		eventType = E_Nul;
		v = min(v, l->Size - 1);

		MakeChoosenUpTo(-1, v - 1);

		//make node appear
		cloneState();

		DisplayNode_Static DisplayCur = DisplayRecord[step - 1][v];

		DisplayCur.body.setPosition(DisplayRecord[step - 1][l->Size - 1].body.getPosition() - Vector2f((float)-14 - DisplayRecord[step - 1][l->Size - 1].body.getSize().x, 0));
		DisplayCur.NextPos = &DisplayCur;
		DisplayCur.text.setString("0");

		AdditionalNode[step] = DisplayCur;
		CalculatePos(step);

		step++;


		cloneState();

		AdditionalNode[step].text.setString(DisplayRecord[step][l->Size - 1].text.getString());
		AdditionalNode[step].body.setOutlineColor(AdditionalNode[step].ChosenColor);

		CalculatePos(step);
		step++;

		MakeCopyPrev(v);

		cloneState();

		DisplayRecord[step][v].text.setString(s);
		DisplayRecord[step][v].body.setFillColor(Color::Magenta);

		CalculatePos(step);
		step++;
	}
}

void Animation_Static::Upd_pos(int v, int data)
{
	eventType = E_Update;

	cloneList(); DisplayRecordStringId[0] = -1;

	MakeFillIndex(v, Color::Yellow); DisplayRecordStringId[step-1] = 1;

	cloneState();
	string s = to_string(data);
	DisplayRecord[step][v].text.setString(s);

	step++; DisplayRecordStringId[step - 1] = 1;
}

void Animation_Static::Ser_pos(int v)
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

void Animation_Static::drawSmoothTransition(int start, int end, float progress,short CodeStatus)
{
	// Define a function to render a smooth transition between two frames
	// Interpolate each node between the start and end frames

	vector<DisplayNode_Static> interpolated_nodes;


	for (int i = 0; i < DisplayRecordSize[start]; i++)
	{
		DisplayNode_Static a = DisplayRecord[start][i];
		DisplayNode_Static b = DisplayRecord[end][i];
		DisplayNode_Static interpolated = interpolated.interpolate(&a, &b, progress);
		interpolated_nodes.push_back(interpolated);
		if (i) interpolated_nodes[i - 1].CalculateLine(&interpolated_nodes[i]);
	}


	DisplayNode_Static a = AdditionalNode[start];
	DisplayNode_Static b = AdditionalNode[end];
	DisplayNode_Static interpolated = interpolated.interpolate(&a, &b, progress);
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

void Animation_Static::drawOneStep(int i)
{
	AdditionalNode[i].renderNode(window);

	for (int j = 0; j < DisplayRecordSize[i]; j++) DisplayRecord[i][j].renderNode(window);
}

void Animation_Static::drawFakeCode(int cur,float posX)
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

void Animation_Static::render()
{
}

void DisplayNode_Static::renderNode(RenderTarget* window)
{
	window->draw(body);
	window->draw(text);
	window->draw(PosText);
}

void DisplayNode_Static::NodeCovert(Square_Display_Node* node)
{
	body = node->body;

	this->font = node->font;

	text = node->text;

	this->text.setFont(*this->font);

	PosText = node->PosText;

	this->PosText.setFont(*this->font);
}

DisplayNode_Static DisplayNode_Static::interpolate(DisplayNode_Static* a, DisplayNode_Static* b, float t)   //make display between 2 frames
{
	// Create a new DisplayNode_Static to store the interpolated values
	DisplayNode_Static result = *a;

	// Interpolate the position of the body and arrow head
	result.body.setPosition((1 - t) * a->body.getPosition() + t * b->body.getPosition());

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
		result.text.setFillColor(Color::Transparent);
	}
	else result.body.setFillColor(Color(red, green, blue, alpha));

	// Interpolate the position and color of the text
	result.text.setPosition(result.body.getPosition().x - result.text.getGlobalBounds().width / 2.f, result.body.getPosition().y - result.text.getGlobalBounds().height / 3 * 2);
	result.PosText.setPosition(Vector2f(result.text.getPosition().x - body.getSize().x/2, result.text.getPosition().y + body.getSize().x/2 + 5));

	// Return the interpolated DisplayNode_Static
	return result;
}

void DisplayNode_Static::Dissolve()
{
	body.setOutlineColor(Color::Transparent);
	body.setFillColor(Color::Transparent);
	text.setFillColor(Color::Transparent);
	PosText.setFillColor(Color::Transparent);
	NextPos = nullptr;
}


