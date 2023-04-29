#include "Queue.h"

Node* NewQueue(int data)
{
    //dataing
    Node* node = new Node;
    node->data = data;
    node->Next = nullptr;

    return node;
}

//Round Node

void Display_Node_Queue::NewQueue(int data)
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

void Display_Node_Queue::renderNode(RenderTarget* window)
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

void Display_Node_Queue::change(int sizeId, bool theme)
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

//  Funtion

void Queue::AddDisplay(int v, int data)
{
    switch (type)
    {
        case isRound:
        {
            Display_Node_Queue newRound;
            newRound.NewQueue(data);

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

void Queue::addTail(Node* node)
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
    Tail = node;
}

void Queue::DelDisplay(int v)
{
    switch (type)
    {
    case isRound:

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

void Queue::delHead()
{
    if (Head == nullptr) return;

    Size--;

    Node* Temp = Head;

    Head = Head->Next;

    delete Temp;
}

void Queue::delAll()
{
    switch (type)
    {
    case isRound:

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

void Queue::UpdateKth(int k, int data)
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

short Queue::find(int data)
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

void Queue::render(RenderWindow* window)
{
    if (Head == nullptr) return;
    
    //repostion

    float between = (float) Distance;
    float original = window->getSize().x / 2 - between * 10 / 2;

    float cnt = 0.5;
    Node* Cur = Head;

    switch (type)
    {
        case isRound:
        {

            for (int i = 0; i < Round_Node.size(); i++) Round_Node[i].body.setPosition(Vector2f(original + between * i, 600));

            for (int i = 0; i < Round_Node.size(); i++)
            {
                Round_Node[i].data = Cur->data;

                if (Cur == Head) Round_Node[i].isPos = isHead; else if (Cur == Tail) Round_Node[i].isPos = isTail; else Round_Node[i].isPos = isMiddle;

                if (i < Round_Node.size() - 1) Round_Node[i].nextPos = Round_Node[i + 1].body.getPosition(); else Round_Node[i].nextPos = Round_Node[i].body.getPosition();

                Round_Node[i].renderNode(window);

                Cur = Cur->Next;
            }
            break;
        }   
    }
}

void Queue::change(int sizeId, bool theme)
{
    switch (type)
    {
    case isRound:
        for (int i = 0; i < Round_Node.size(); i++)
            Round_Node[i].change(sizeId, theme);
        break;
    }
}