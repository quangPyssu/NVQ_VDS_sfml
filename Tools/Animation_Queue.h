#include <SFML/Graphics.hpp>
#include <windows.h>
#include <iostream>
#include <math.h>

#include "LinkedList.h"

using namespace std;
using namespace sf;

//event type

struct DisplayNode_Queue {

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
	DisplayNode_Queue interpolate(DisplayNode_Queue* a, DisplayNode_Queue* b, float t);

	//next Point
	DisplayNode_Queue* NextPos = nullptr;
	void CalculateLine(DisplayNode_Queue* next);
};


class Animation_Queue
{
public:
	Animation_Queue(Event* event, LinkedList* l, RenderWindow* window);

	enum FakeCodeStatus { Appear = 1, Disappear=-1,Display=0 };

	virtual ~Animation_Queue();

	int step = 0;
	int curStep = 0;
	vector <DisplayNode_Queue> DisplayRecord[30];
	DisplayNode_Queue AdditionalNode[30];

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

	enum evType { E_DelHead = 0, E_AddTail = 1, E_Search_Head = 2, E_Search_Tail= 3	};

	Event* event;
	LinkedList* l;
	RenderWindow* window;

	//Stat for render

	void cloneList();
	void cloneState();

	CircleShape arrow_head2;

	//fake codes

	int fakeId[4] = {3,3,2,2};

	string Code[4][3];

	// transition
	void Link(int cur);

};
