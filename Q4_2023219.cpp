// Head Mover v1.0
#include <iostream>
#include <exception> // to add special exceptions

// ------ PRE-PROC CONSTS ------ 
#define NO_ERRORS 0

using namespace std; // so we don't have to repeatedly say std::cout, std::cin


// ------ CLASS DEFS ------
struct Node
{
    Node* next;
    Node* prev;
    int data;
    Node(const int& data, Node* next, Node* prev) : data(data), next(next), prev(prev) {};
};

class DLList
{
private:
    Node* head;
public:
    DLList() : head(nullptr) {};
    void PushBack(const int&);
    void Show() const;
    void MoveHead(const int&);
};


// ------ ENTRY POINT ------
int main()
{
    DLList A;
    A.PushBack(11);
    A.PushBack(3);
    A.PushBack(8);
    A.PushBack(2);
    A.PushBack(1);

    cout << "Before:\t"; A.Show();

    try { A.MoveHead(3); }
    catch(...) { cout << "The head could not be moved to the specified position."; }
    
    cout << endl << "After:\t"; A.Show();

    return NO_ERRORS;
}

// ------ DOUBLY LINKED LIST FUNCTION DEFINITIONS ------
void DLList::Show() const
{
    Node* Position = head;

    cout << "[ ";
    while (Position)
    {
        cout << Position->data << " -> ";
        Position = Position->next;
    }

    cout << "NULL (pointer) ]";
}

void DLList::PushBack(const int& data)
{
    // CASE A: There are no elements in the list
    if (!head)
    {
        head = new Node(data, nullptr, nullptr);
        return;
    }

    // CASE B: There are some elements in the list
    Node* Position = head;
    Node* Insertion = new Node(data, nullptr, nullptr);
    while (Position->next)
    {
        Position = Position->next;
    }
    
    Position->next = Insertion;
    Insertion->prev = Position;
}

// Note that indexing starts at ONE not zero. ie. current head is one
void DLList::MoveHead(const int& TargetPos)
{
    if (TargetPos <= 1)
    {
        return; // moving head to itself will result in no change
    }

    Node* Position = head;
    Node* BufferA = nullptr;
    Node* Target = nullptr;
    int idx = 1;

    while (Position)
    {
        if (idx == TargetPos)
        {
            Target = Position;
            break;
        }

        Position = Position->next;
        idx++;
    }

    if (!Target)
    {
        throw domain_error("");
    }

    head = Target;
    Position = Target;

    // "Detach" elements before target
    Target->prev->next = nullptr;
    
    // "Pick up" the leftmost element
    while(Position->prev)
    {
        Position = Position->prev;
    }

    BufferA = Position;
    Position = Target;

    // "Place it" at the end, moving every element until target to the right
    while(Position->next)
    {
        Position = Position->next;
    }

    Position->next = BufferA;
    BufferA->prev = Position;
}