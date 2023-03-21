#include "LinkedList.h"

Node* New(int data)
{
    //dataing
    Node* node = new Node;
    node->data = data;
    node->Next = node->Prev = nullptr;

    //display part

    node->body.setRadius(15);
    node->body.setOrigin(node->body.getRadius(), node->body.getRadius());

    node->line.setSize(Vector2f(1,2));
    node->line.setOrigin(Vector2f(0,1));
    
    node->arrow_head=CircleShape(8,3);
    node->arrow_head.setOrigin(node->arrow_head.getRadius(), node->arrow_head.getRadius());

    node->body.setFillColor(Color::White);
    node->body.setOutlineThickness(2);
    node->body.setOutlineColor(Color::Black);
    node->line.setFillColor(Color::Color(211,211,211,255));
    node->arrow_head.setFillColor(Color::Green);

    node->font.loadFromFile("asset/fonts/ArialTh.ttf");
    node->text.setFont(node->font);
    node->text.setFillColor(Color::Black);
    node->text.setCharacterSize(15);

    node->ChosenColor = Color::Green;
    node->IdleColor = Color::Black;

    return node;
}

void Node::renderNode(RenderTarget* window)
{
    text.setPosition(body.getPosition().x - text.getGlobalBounds().width / 2.f,body.getPosition().y - text.getGlobalBounds().height / 2.f);

    string s = to_string(data); 
    text.setString(s);

    line.setPosition(body.getPosition());
    if (Next == nullptr)
    {   
        line.setScale(Vector2f(0, 0));
        arrow_head.setScale(Vector2f(0, 0));
    }
    else
    {
        Node* next = Next;

        float dx = -body.getPosition().x + next->body.getPosition().x;
        float dy = -body.getPosition().y + next->body.getPosition().y;

        float distance = sqrt(dx*dx+dy*dy);

        line.setScale(Vector2f(distance,1));
        arrow_head.setScale(Vector2f(1, 1));

        line.setPosition(body.getPosition());
        arrow_head.setPosition(Vector2f(body.getPosition().x+dx/2, body.getPosition().y+dy/2));

        if (dx) angle = (float) atan(dy / dx) * 180 / PI; else angle = 0;

        line.setRotation(angle);
        arrow_head.setRotation(angle+90);
    }

    window->draw(line);
    window->draw(body);
    window->draw(arrow_head);
    window->draw(text);

    if (isPos != isMiddle)
    {
        text.setPosition(Vector2f(text.getPosition().x, text.getPosition().y+body.getRadius() + 5));
        if (isPos == isHead) text.setString("Head"); else text.setString("Tail");
        window->draw(text);
    }
}

void LinkedList::addTail(Node* node)
{
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
    add(Head, node);
}

void LinkedList::addKth(Node* node,int k)
{
    int i = 0;
    Node* tmp = Head;

    while (tmp != nullptr)
    {
        if (i++ >= k)
        {
            add(tmp,node);
            return;
        }
        tmp = tmp->Next;
    }

    addTail(node);
}

void LinkedList::add(Node* cur,Node* node)
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

    if (cur->Prev!= nullptr) cur->Prev->Next = node; else Head = node;
    cur->Prev = node;
}

void LinkedList::delTail()
{
    if (Tail == nullptr) return;

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
    while (Head!=nullptr)
    {
        Node* tmp = Head;
        Head = Head->Next;
        delete tmp;
    }

    Size = 0;
    Head = Tail = nullptr;
}

void LinkedList::UpdateKth(int k,int data)
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
        
        i++;tmp = tmp->Next;
    }

    if (tmp == nullptr) return -1;

    return 0;
}

void LinkedList::render(RenderWindow* window)
{
    if (Head == nullptr) return;
    Node* cur = Head;
    //repostion
    
    float between = (float) 800/Size;
    float original = 500-400;

    int cnt = 0;
    while (cur != nullptr)
    {
        cur->body.setPosition(Vector2f(original+between*cnt,500));

        cnt++; cur = cur->Next;
    }
    
    //draw
    cur = Head;
    while (cur != nullptr)
    {
        if (cur == Head) cur->isPos = isHead; else
            if (cur == Tail) cur->isPos = isTail; else
                cur->isPos = isMiddle;


        cur->renderNode(window);
        cur = cur->Next;
    }

    //window->display();
}

void LinkedList::choose(int n)
{
    Node* node = Head;
    for (int i = 0; i < n - 1; i++)
        node = node->Next;

    node->body.setOutlineColor(node->ChosenColor);
}