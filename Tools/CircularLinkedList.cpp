#include "CircularLinkedList.h"

Node* NewCircular(int data)
{
    //dataing
    Node* node = new Node;
    node->data = data;
    node->Next = nullptr;

    return node;
}

//Round Node

void Display_Node_Circular::NewCircular(int data)
{
    this->data = data;

    nextPos = Vector2f(0, 0);

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

    // Font font;
    font->loadFromFile("asset/fonts/ArialTh.ttf");

    text = Text("", *font);
    text.setFillColor(Color::Black);
    text.setCharacterSize((int) body.getRadius());
    PosText = text;

    string s = to_string(data);
    text.setString(s);
}

void Display_Node_Circular::renderNode(RenderTarget* window)
{
    string s = to_string(data);
    text.setString(s);
    text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);

    line.setPosition(body.getPosition());

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

        line.setScale(Vector2f(distance, 1));
        arrow_head.setScale(Vector2f(1, 1));

        line.setPosition(body.getPosition());
        arrow_head.setPosition(Vector2f(nextPos.x - (body.getRadius()+arrow_head.getRadius()), body.getPosition().y + dy / 2));

        if (dx) angle = (float)atan(dy / dx) * 180 / PI; else
        {
            if (dy < 0)
            {
                angle = 270;
                arrow_head.setPosition(Vector2f(nextPos.x , body.getPosition().y + dy / 2 - (body.getRadius() + arrow_head.getRadius())/2));
            }
            else
            {
                angle = 90;
                arrow_head.setPosition(Vector2f(nextPos.x, body.getPosition().y + dy / 2 - (body.getRadius() + arrow_head.getRadius())/2));
            }
        }

        if (dy == 0)
        {
            if (dx < 0)
            {
                angle = 180;
                arrow_head.setPosition(Vector2f(nextPos.x-dx/2, body.getPosition().y + dy / 2));
            }
            else angle = 0;
        }



        line.setRotation(angle);
        arrow_head.setRotation(angle + 90);
    }

    window->draw(line);
    window->draw(body);
    window->draw(arrow_head);
    window->draw(text);

    if (isPos != isMiddle)
    {
        PosText.setPosition(Vector2f(text.getPosition().x - body.getRadius(), text.getPosition().y + body.getRadius() + 5));
        if (isPos == isHead) PosText.setString("Head"); else PosText.setString("Tail");
        window->draw(PosText);
    }
}

void Display_Node_Circular::change(int sizeId, bool theme)
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

    line.setSize(Vector2f(1, size/8));
    line.setOrigin(Vector2f(0, size / 16));

    arrow_head.setRadius(size / 3);
    arrow_head.setOrigin(arrow_head.getRadius(), arrow_head.getRadius());

    text.setCharacterSize(size);
    PosText.setCharacterSize(size);

    body.setOutlineThickness(size/8);


    if (!theme)
    {
        body.setOutlineColor(OutlineColor);
        body.setFillColor(BodyColor);
        line.setFillColor(LineColor);
        arrow_head.setFillColor(LineColor);

        text.setFillColor(OutlineColor);  
        PosText.setFillColor(OutlineColor);
    }
    else
    {
        body.setOutlineColor(OutlineColor_D);
        body.setFillColor(BodyColor_D);
        line.setFillColor(LineColor_D);
        arrow_head.setFillColor(LineColor_D);

        text.setFillColor(OutlineColor_D);
        PosText.setFillColor(OutlineColor_D);
    }
}


// Linked List Funtion

void CircularLinkedList::AddDisplay(int v, int data)
{
    switch (type)
    {
        case isCircle:
        {
            Display_Node_Circular newRound;
            newRound.NewCircular(data);

            if (v >= Round_Node.size())
            {
                Round_Node.push_back(newRound);
                return;
            }

            Round_Node.push_back(newRound);

            for (int i = v; i < Round_Node.size() - 1; i++) Round_Node[i + 1] = Round_Node[i];

            Round_Node[v] = newRound;

            break;
        }
    }
}

void CircularLinkedList::addTail(Node* node)
{
    AddDisplay(15, node->data);

    Size++;
    if (Tail == nullptr)
    {
        Head = node;
        Tail = node;
        Tail->Next = Head;
        return;
    }

    Tail->Next = node;
    Tail = node;
    Tail->Next = Head;
}

void CircularLinkedList::addHead(Node* node)
{
    AddDisplay(0, node->data);
    add(Head, Tail, node);
}

void CircularLinkedList::addKth(Node* node, int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ >= k-1)
        {
            AddDisplay(k, node->data);
            add(tmp->Next,tmp, node);
            return;
        }
        tmp = tmp->Next;
    }

    addTail(node);
}

void CircularLinkedList::add(Node* cur,Node* pre, Node* node)
{
    Size++;
    if (cur == nullptr)
    {
        Head = node;
        Tail = node;
        Tail->Next = Head;
        return;
    }

    node->Next = cur;

    if (pre != nullptr) pre->Next = node; else Head = node;
}

void CircularLinkedList::DelDisplay(int v)
{
    switch (type)
    {
    case isCircle:

        if (v >= Round_Node.size())
        {
            Round_Node.pop_back();
            return;
        }

        for (int i = v; i < Round_Node.size() - 1; i++) Round_Node[i] = Round_Node[i + 1];

        Round_Node.pop_back();

        break;
    }
}

void CircularLinkedList::delTail()
{
    if (Tail == nullptr) return;
    DelDisplay(15);
    del(Head,Tail);
}

void CircularLinkedList::delHead()
{
    if (Head == nullptr) return;

    del(Head,Tail);
}

void CircularLinkedList::delKth(int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ == k-1)
        {
            DelDisplay(k);
            del(tmp->Next,tmp);
            return;
        }
        tmp = tmp->Next;
    }
}

void CircularLinkedList::del(Node* Cur,Node* pre) // Delete specific node on List
{
    Size--;
    if (Cur == nullptr) return;

    if (pre != nullptr) pre->Next = Cur->Next;

    if (Cur == Head) Head = Head->Next, Tail->Next = Head;
    if (Cur == Tail) Tail = pre,pre->Next=Head;

    delete Cur;
}

void CircularLinkedList::delAll()
{
    switch (type)
    {
    case isCircle:

        Round_Node.clear();
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

void CircularLinkedList::UpdateKth(int k, int data)
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

short CircularLinkedList::find(int data)
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

void CircularLinkedList::render(RenderWindow* window)
{
    if (Head == nullptr) return;
    
    //repostion

    float between = (float) Distance;
    float original = window->getSize().x / 2 - between * 10 / 2;

    float cnt = 0.5;
    Node* Cur = Head;

    switch (type)
    {
        case isCircle:
        {
            for (int i = 0; i < Round_Node.size(); i++) Round_Node[i].body.setPosition(Vector2f(original + between * i, 600));
            
            CalBack(Round_Node[0].body.getPosition(), Round_Node.back().body.getPosition());

            window->draw(line1);	window->draw(line2);   window->draw(line3);	window->draw(line4); window->draw(arrow);

            for (int i = 0; i < Round_Node.size(); i++)
            {
                Round_Node[i].data = Cur->data;

                if (Cur == Head) Round_Node[i].isPos = isHead; else Round_Node[i].isPos = isMiddle;

                if (i < Round_Node.size() - 1) Round_Node[i].nextPos = Round_Node[i + 1].body.getPosition();
                else Round_Node[i].nextPos = Round_Node[i].body.getPosition();

                Round_Node[i].renderNode(window);

                Cur = Cur->Next;
            }

            break;
        }
    }
}

void CircularLinkedList::change(int sizeId, bool theme)
{
    switch (type)
    {
    case isCircle:
        for (int i = 0; i < Round_Node.size(); i++)
            Round_Node[i].change(sizeId, theme);

        if (Round_Node.size())
        {
            if (theme)
            {
                line1.setFillColor(Round_Node[0].LineColor_D);
                line2.setFillColor(Round_Node[0].LineColor_D);
                line3.setFillColor(Round_Node[0].LineColor_D);
                line4.setFillColor(Round_Node[0].LineColor_D);
                arrow.setFillColor(Round_Node[0].LineColor_D);
            }
            else
            {
                line1.setFillColor(Round_Node[0].LineColor);
                line2.setFillColor(Round_Node[0].LineColor);
                line3.setFillColor(Round_Node[0].LineColor);
                line4.setFillColor(Round_Node[0].LineColor);
                arrow.setFillColor(Round_Node[0].LineColor);
            }
        }

        break;
    }
}

void CircularLinkedList::CalBack(Vector2f PosHead, Vector2f PosTail)
{
    if (PosHead == Vector2f(-1000, -1000) || PosTail == Vector2f(-1000, -1000))
    {
        line1.setPosition(PosHead + Vector2f(2000, 0));
        line2.setPosition(Vector2f(2000, 525));
        line3.setPosition(PosHead + Vector2f(2000, -75));
        line4.setPosition(PosHead + Vector2f(2000,0));

        arrow.setPosition(Vector2f(PosHead.x + 2000, 525));
        return;
    }

    if (PosHead == PosTail)
    {
        line1.setScale(Vector2f(PosHead.y - 525, 1));
        line2.setScale(Vector2f(PosHead.y - 525, 1));
        line3.setScale(Vector2f(Distance, 1));
        line4.setScale(Vector2f(Distance, 1));

        line1.setPosition(PosHead + Vector2f(Distance, 0));
        line2.setPosition(Vector2f(PosHead.x, 525));
        line3.setPosition(PosHead + Vector2f(Distance, -75));
        line4.setPosition(PosHead);

        arrow.setPosition(Vector2f(PosHead.x + 75, 525));
    }
    else
    {
        line1.setScale(Vector2f(PosTail.y - 525, 1));
        line2.setScale(Vector2f(PosHead.y - 525, 1));
        line3.setScale(Vector2f(-PosHead.x + PosTail.x, 1));
        line4.setScale(Vector2f(0, 1));

        line1.setPosition(PosTail);
        line2.setPosition(Vector2f(PosHead.x, 525));
        line3.setPosition(Vector2f(PosTail.x, 525));
        line4.setPosition(PosHead);

        arrow.setPosition(Vector2f(PosHead.x + (PosTail.x - PosHead.x) / 2, 525));
    }
}