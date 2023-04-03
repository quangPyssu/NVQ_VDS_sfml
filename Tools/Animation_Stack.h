#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <math.h>

#include "LinkedList.h"

using namespace std;
using namespace sf;

//event type

struct DisplayNode_Stack {

	RectangleShape line;
	CircleShape arrow_head;
	CircleShape body;

	shared_ptr<Font> font = make_shared<Font>();;

	Text text;
	Text PosText;

	//attributes

	float angle = 0;
	float rad = 0;
	Color BodyColor;
	Color ChosenColor = Color::Green;
	Color IdleColor = Color::Black;
	Color DeleteColor = Color::Red;

	//redraw past node
	void renderNode(RenderTarget* window);

	// copy stat;
	void NodeCovert(Node* node);

	void Dissolve();

	// Interpolate
	DisplayNode_Stack interpolate(DisplayNode_Stack* a, DisplayNode_Stack* b, float t);

	//next Point
	DisplayNode_Stack* NextPos = nullptr;
	void CalculateLine(DisplayNode_Stack* next);
};


class Animation_Stack
{
public:
	Animation_Stack(Event* event, LinkedList* l, RenderWindow* window);

	enum FakeCodeStatus { Appear = 1, Disappear=-1,Display=0 };

	virtual ~Animation_Stack();

	int step = 0;
	int curStep = 0;
	vector <DisplayNode_Stack> DisplayRecord[30];
	DisplayNode_Stack AdditionalNode[30];

	int AdditionPos[30]{ 0 };

	int DisplayRecordSize[30]{ 0 };
	int DisplayRecordStringId[30]{ 0 };

	//tool
	void clearAll();
	void MakeChoosenUpTo(int u, int v);
	void MakeFillIndex(int n, Color color);

	void CalculatePos(int pos);


	// uses

	void Del_pos(int v);
	void Add_pos(int v, int data);
	void Ser_pos(int v);

	// render

	Texture tet;
	Sprite sprite;

	void render();
	void drawOneStep(int i);

	void drawFakeCode(int cur,float posX);

	void drawSmoothTransition(int start, int end, float progress,short CodeStatus);


	//fake Code
	int eventType = 0;

	RectangleShape CodeBox;
	Text FakeCode;
	Font Fonte;

	Color CodeBoxColor = Color(252, 142, 172);

	Vector2f FakeCodeSize = Vector2f(500, 50);
	Vector2f FakeCodePos = Vector2f(700, 150);

private:

	enum evType { E_DelHead = 0, E_AddHead = 1, E_Search = 2 };

	Event* event;
	LinkedList* l;
	RenderWindow* window;

	//Stat for render

	void cloneList();
	void cloneState();

	CircleShape arrow_head2;

	//fake codes

	int fakeId[3] = {3,3,2};

	string Code[3][3];

	// transition
	void Link(int cur);

};
