#include "DoublyLinkedList.h"

Node* NewDoubly(int data)
{
    //dataing
    Node* node = new Node;
    node->data = data;
    node->Next = node->Prev = nullptr;

    return node;
}

//Round Node Two

void Display_Node_Doubly::NewDoubly(int data)
{
    this->data = data;

    nextPos = prevPos = Vector2f(0, 0);

    body.setRadius(40);
    body.setOrigin(body.getRadius(), body.getRadius());

    line.setSize(Vector2f(1, 5));
    line.setOrigin(Vector2f(0, 2.5));

    arrow_head = CircleShape(12, 3);
    arrow_head.setOrigin(arrow_head.getRadius(), arrow_head.getRadius());

    body.setFillColor(Color::White);
    body.setOutlineThickness(5);
    body.setOutlineColor(Color::Black);
    line.setFillColor(Color::Color(91, 91, 91, 255));
    arrow_head.setFillColor(Color::Color(91, 91, 91, 255));

    back = line;
    arrow_back = arrow_head;

    // Font font;
    font->loadFromFile("asset/fonts/ArialTh.ttf");

    text = Text("", *font);
    text.setFillColor(Color::Black);
    text.setCharacterSize((int)body.getRadius());
    PosText = text;

    string s = to_string(data);
    text.setString(s);
}

void Display_Node_Doubly::renderNode(RenderTarget* window)
{
    string s = to_string(data);
    text.setString(s);
    text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);

    line.setPosition(body.getPosition());
    back.setPosition(body.getPosition());

    if (nextPos == body.getPosition())
    {
        line.setScale(Vector2f(0, 0));
        arrow_head.setScale(Vector2f(0, 0));
    }
    else
    {
        float dx = -body.getPosition().x + nextPos.x;
        float dy = -body.getPosition().y + nextPos.y;

        float distance = sqrt(dx * dx + dy * dy);

        line.setScale(Vector2f(distance - body.getRadius() - body.getOutlineThickness(), 1));
        arrow_head.setScale(Vector2f(1, 1));

        line.setPosition(body.getPosition() - Vector2f(0, 10));
        arrow_head.setPosition(Vector2f(nextPos.x - body.getRadius() - arrow_head.getRadius(), body.getPosition().y + dy / 2 - 10));

        if (dx) angle = (float)atan(dy / dx) * 180 / PI; else angle = 0;

        line.setRotation(angle);
        arrow_head.setRotation(angle + 90);
    }

    if (prevPos == body.getPosition())
    {
        back.setScale(Vector2f(0, 0));
        arrow_back.setScale(Vector2f(0, 0));
    }
    else
    {
        float dx = -body.getPosition().x + prevPos.x;
        float dy = -body.getPosition().y + prevPos.y;

        float distance = sqrt(dx * dx + dy * dy);
        
        back.setScale(Vector2f(distance - body.getRadius()- body.getOutlineThickness(), 1));
        arrow_back.setScale(Vector2f(1, 1));      

        back.setPosition(body.getPosition() + Vector2f(0, 10));
        arrow_back.setPosition(Vector2f(prevPos.x + body.getRadius() + arrow_head.getRadius(), prevPos.y + dy / 2 + 10));
            
        if (dx) angle = (float)atan(dy / dx) * 180 / PI; else angle = 0;

        back.setRotation(angle+180);
        arrow_back.setRotation(angle - 90);
    }

    window->draw(line);
    window->draw(back);
    window->draw(arrow_head);
    window->draw(arrow_back);
    window->draw(body);
    window->draw(text);

    if (isPos != isMiddle)
    {
        PosText.setPosition(Vector2f(text.getPosition().x - body.getRadius(), text.getPosition().y + body.getRadius() + 5));
        if (isPos == isHead) PosText.setString("Head"); else PosText.setString("Tail");
        window->draw(PosText);
    }
}

void Display_Node_Doubly::change(int sizeId, bool theme)
{
    //display part
    switch (sizeId)
    {
    case 0: size = 40;  break;
    case 1: size = 49;  break;
    case 2: size = 30;  break;
    default: size = 40; break;
    }

    body.setRadius(size);
    body.setOrigin(size, size);

    line.setSize(Vector2f(1, size / 8));
    line.setOrigin(Vector2f(0, size / 16));

    back.setSize(Vector2f(1, size / 8));
    back.setOrigin(Vector2f(0, size / 16));

    arrow_head.setRadius(size / 3);
    arrow_head.setOrigin(arrow_head.getRadius(), arrow_head.getRadius());
    arrow_back.setRadius(size / 3);
    arrow_back.setOrigin(arrow_head.getRadius(), arrow_head.getRadius());

    text.setCharacterSize(size);
    PosText.setCharacterSize(size);

    body.setOutlineThickness(size / 8);


    if (!theme)
    {
        body.setOutlineColor(OutlineColor);
        body.setFillColor(BodyColor);
        line.setFillColor(LineColor);
        back.setFillColor(LineColor);
        arrow_head.setFillColor(LineColor);
        arrow_back.setFillColor(LineColor);

        text.setFillColor(OutlineColor);
        PosText.setFillColor(OutlineColor);
    }
    else
    {
        body.setOutlineColor(OutlineColor_D);
        body.setFillColor(BodyColor_D);
        line.setFillColor(LineColor_D);
        back.setFillColor(LineColor_D);
        arrow_head.setFillColor(LineColor_D);
        arrow_back.setFillColor(LineColor_D);

        text.setFillColor(OutlineColor_D);
        PosText.setFillColor(OutlineColor_D);
    }
}

// Linked List Funtion

void DoublyLinkedList::AddDisplay(int v, int data)
{
    switch (type)
    {
        
        case isTwo:
        {
            Display_Node_Doubly newTwo;
            newTwo.NewDoubly(data);

            if (v >= Two_Node.size())
            {
                Two_Node.push_back(newTwo);
                return;
            }

            Two_Node.push_back(newTwo);

            for (int i = v; i < Two_Node.size() - 1; i++) Two_Node[i + 1] = Two_Node[i];

            Two_Node[v] = newTwo;

            break;
        }
    }
}

void DoublyLinkedList::addTail(Node* node)
{
    AddDisplay(15, node->data);

    Size++;
    if (Tail == nullptr)
    {
        Head = node;
        Tail = node;
        return;
    }

    Tail->Next = node;
    node->Prev = Tail;
    Tail = node;
}

void DoublyLinkedList::addHead(Node* node)
{
    AddDisplay(0, node->data);
    add(Head, node);
}

void DoublyLinkedList::addKth(Node* node, int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ >= k)
        {
            AddDisplay(k, node->data);
            add(tmp, node);
            return;
        }
        tmp = tmp->Next;
    }

    addTail(node);
}

void DoublyLinkedList::add(Node* cur, Node* node)
{
    Size++;
    if (cur == nullptr)
    {
        Head = node;
        Tail = node;
        return;
    }

    node->Prev = cur->Prev;
    node->Next = cur;

    if (cur->Prev != nullptr) cur->Prev->Next = node; else Head = node;
    cur->Prev = node;
}

void DoublyLinkedList::DelDisplay(int v)
{
    switch (type)
    {
    case isTwo:

        if (v >= Two_Node.size())
        {
            Two_Node.pop_back();
            return;
        }

        for (int i = v; i < Two_Node.size() - 1; i++) Two_Node[i] = Two_Node[i + 1];

        Two_Node.pop_back();

        break;
    }
}

void DoublyLinkedList::delTail()
{
    if (Tail == nullptr) return;
    DelDisplay(15);
    del(Tail);
}

void DoublyLinkedList::delHead()
{
    if (Head == nullptr) return;

    del(Head);
}

void DoublyLinkedList::delKth(int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ == k)
        {
            DelDisplay(k);
            del(tmp);
            return;
        }
        tmp = tmp->Next;
    }

    delTail();
}

void DoublyLinkedList::del(Node* Cur) // Delete specific node on List
{
    Size--;
    if (Cur == nullptr) return;

    if (Cur->Prev != nullptr) Cur->Prev->Next = Cur->Next;
    if (Cur->Next != nullptr) Cur->Next->Prev = Cur->Prev;

    if (Cur == Head) Head = Head->Next;
    if (Cur == Tail) Tail = Tail->Prev;

    delete Cur;
}

void DoublyLinkedList::delAll()
{
    switch (type)
    {

    case isTwo:

        Two_Node.clear();
        break;
    }

    while (Head != nullptr)
    {
        Node* tmp = Head;
        Head = Head->Next;
        delete tmp;
    }

    Size = 0;
    Head = Tail = nullptr;
}

void DoublyLinkedList::UpdateKth(int k, int data)
{
    if (Head == nullptr) return;

    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ == k)
        {
            tmp->data = data;
            return;
        }
        tmp = tmp->Next;
    }

    Tail->data = data;
}

short DoublyLinkedList::find(int data)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (tmp->data == data) return i;

        i++; tmp = tmp->Next;
    }

    if (tmp == nullptr) return -1;

    return 0;
}

void DoublyLinkedList::render(RenderWindow* window)
{
    if (Head == nullptr) return;
    
    //repostion

    float between = (float) Distance;
    float original = window->getSize().x / 2 - between * 10 / 2;

    float cnt = 0.5;
    Node* Cur = Head;

    switch (type)
    {
        case isTwo:
        {
            for (int i = 0; i < Two_Node.size(); i++) Two_Node[i].body.setPosition(Vector2f(original + between * i, 600));

            for (int i = 0; i < Two_Node.size(); i++)
            {
                Two_Node[i].data = Cur->data;

                if (Cur == Head) Two_Node[i].isPos = isHead; else if (Cur == Tail) Two_Node[i].isPos = isTail; else Two_Node[i].isPos = isMiddle;

                if (i < Two_Node.size() - 1) Two_Node[i].nextPos = Two_Node[i + 1].body.getPosition(); else Two_Node[i].nextPos = Two_Node[i].body.getPosition();

                if (i > 0)  Two_Node[i].prevPos = Two_Node[i - 1].body.getPosition(); else Two_Node[i].prevPos = Two_Node[i].body.getPosition();

                Two_Node[i].renderNode(window);

                Cur = Cur->Next;
            }
            break;
        }
    }
}

void DoublyLinkedList::change(int sizeId, bool theme)
{
    switch (type)
    {
    case isTwo:
        for (int i = 0; i < Two_Node.size(); i++)
            Two_Node[i].change(sizeId, theme);
        break;
    }
}