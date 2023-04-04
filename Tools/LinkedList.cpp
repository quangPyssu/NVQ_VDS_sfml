#include "LinkedList.h"

Node* New(int data)
{
    //dataing
    Node* node = new Node;
    node->data = data;
    node->Next = node->Prev = nullptr;

    return node;
}

void Round_Display_Node::New(int data)
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

void Round_Display_Node::renderNode(RenderTarget* window)
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
        arrow_head.setPosition(Vector2f(nextPos.x - body.getRadius() - arrow_head.getRadius(), body.getPosition().y + dy / 2));

        if (dx) angle = (float)atan(dy / dx) * 180 / PI; else angle = 0;

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

void Square_Display_Node::New(int data)
{
    this->data = data;

    body.setSize(Vector2f(80,80));
    body.setOrigin(40,40);

    body.setFillColor(Color::White);
    body.setOutlineThickness(5);
    body.setOutlineColor(Color::Black);

    // Font font;
    font->loadFromFile("asset/fonts/ArialTh.ttf");

    text = Text("", *font);
    text.setFillColor(Color::Black);
    text.setCharacterSize((int)body.getSize().x/2);

    string s = to_string(data);
    text.setString(s);
}

void Square_Display_Node::renderNode(RenderTarget* window)
{
    string s = to_string(data);
    text.setString(s);
    text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f, body.getPosition().y - text.getGlobalBounds().height / 3 * 2);


    float dx = -body.getPosition().x + nextPos.x;
    float dy = -body.getPosition().y + nextPos.y;

    float distance = sqrt(dx * dx + dy * dy);

    window->draw(body);
    window->draw(text);
}

void Round_Display_Node::change(int sizeId, bool theme)
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

void LinkedList::AddDisplay(int v, int data)
{
    switch (type)
    {
        case isRound:
        {
            Round_Display_Node newRound;
            newRound.New(data);

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


        case isSquare:
        {
            Square_Display_Node newRound;
            newRound.New(data);

            if (v >= Square_Node.size())
            {
                Square_Node.push_back(newRound);
                return;
            }

            Square_Node.push_back(newRound);

            for (int i = v; i < Square_Node.size() - 1; i++) Square_Node[i + 1] = Square_Node[i];

            Square_Node[v] = newRound;

            break;
        }

    }
}

void LinkedList::addTail(Node* node)
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

void LinkedList::addHead(Node* node)
{
    AddDisplay(0, node->data);
    add(Head, node);
}

void LinkedList::addKth(Node* node, int k)
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

void LinkedList::add(Node* cur, Node* node)
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

void LinkedList::DelDisplay(int v)
{
    switch (type)
    {
    case isRound:

        if (v >= Round_Node.size())
        {
            Round_Node.pop_back();
            return;
        }

        for (int i = v; i < Round_Node.size() - 1; i++) Round_Node[i] = Round_Node[i+1];

        Round_Node.pop_back();

        break;

    case isSquare:

        if (v >= Square_Node.size())
        {
            Square_Node.pop_back();
            return;
        }

        for (int i = v; i < Square_Node.size() - 1; i++) Square_Node[i] = Square_Node[i + 1];

        Square_Node.pop_back();

        break;
    }
}

void LinkedList::delTail()
{
    if (Tail == nullptr) return;
    DelDisplay(15);
    del(Tail);
}

void LinkedList::delHead()
{
    if (Head == nullptr) return;

    del(Head);
}

void LinkedList::delKth(int k)
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

void LinkedList::del(Node* Cur) // Delete specific node on List
{
    Size--;
    if (Cur == nullptr) return;

    if (Cur->Prev != nullptr) Cur->Prev->Next = Cur->Next;
    if (Cur->Next != nullptr) Cur->Next->Prev = Cur->Prev;

    if (Cur == Head) Head = Head->Next;
    if (Cur == Tail) Tail = Tail->Prev;

    delete Cur;
}

void LinkedList::delAll()
{
    switch (type)
    {
    case isRound:

        Round_Node.clear();
        break;

    case isSquare:

        Square_Node.clear();
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

void LinkedList::UpdateKth(int k, int data)
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

short LinkedList::find(int data)
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

void LinkedList::render(RenderWindow* window)
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

        case isSquare:
        {

            for (int i = 0; i < Square_Node.size(); i++) Square_Node[i].body.setPosition(Vector2f(original+200 + Square_Node[i].body.getSize().x*i+i*14, 600));

            for (int i = 0; i < Square_Node.size(); i++)
            {
                Square_Node[i].data = Cur->data;

                if (Cur == Head) Square_Node[i].isPos = isHead; else if (Cur == Tail) Square_Node[i].isPos = isTail; else Square_Node[i].isPos = isMiddle;

                if (i < Square_Node.size() - 1) Square_Node[i].nextPos = Square_Node[i + 1].body.getPosition(); else Square_Node[i].nextPos = Square_Node[i].body.getPosition();

                Square_Node[i].renderNode(window);

                Cur = Cur->Next;
            }
            break;
        }
    }

    window->display();
}

void LinkedList::change(int sizeId, bool theme)
{
    switch (type)
    {
    case isRound:
        for (int i = 0; i < Round_Node.size(); i++)
            Round_Node[i].change(sizeId, theme);
        break;
    }
}