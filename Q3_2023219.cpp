// DLL Swapper v1.0
#include <iostream>

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
    void Swap(const int&, const int&);
};

// ------ ENTRY POINT ------ 
int main()
{

}

// ------ DOUBLY LINKED LIST FUNCTION DEFINITIONS ------
void DLList::PushBack(const int& Data)
{
    Node* insertion = new Node(Data, nullptr, nullptr);

    // CASE A: There are no elements in the list
    if (!head)
    {
        head = insertion;
        return;
    }

    // CASE B: Insert at the end
    Node* position = head;
    while (position->next)
    {
        position = position->next;
    }

    position->next = insertion;
    insertion->prev = position;
}

void DLList::Show() const
{
    Node* Position = head;

    cout << endl << "[ ";
    while (Position)
    {
        cout << Position->data << " -> ";
        Position = Position->next;
    }

    cout << "NULL (pointer) ]";
}

void DLList::Swap(const int& A, const int& B)
{
    Node* Position = head;
    Node* NodeA = nullptr;
    Node* NodeB = nullptr;

    while (Position)
    {
        if (Position->data == A)
        {
            NodeA = Position;
        }

        if (Position->data == B)
        {
            NodeB = Position;
        }

        if (NodeA && NodeB)
        {
            break;
        }

        Position = Position->next;
    }

    if (!NodeA || !NodeB)
    {
        cout << "One or more elements not found!";
        return;
    }

    Node* Buffer = nullptr;


    // Swap the next pointers of the nodes before the nodes to be swapped. this comment makes more sense if you draw the nodes tbh
    if (NodeA->prev && NodeA->prev != NodeB) NodeA->prev->next = NodeB;
    if (NodeB->prev && NodeB->prev != NodeA) NodeB->prev->next = NodeA;

    // Swap the previous pointers of the nodes after the nodes to be swapped
    if (NodeA->next && NodeA->next != NodeB) NodeA->next->prev = NodeB;
    if (NodeB->next && NodeB->next != NodeA) NodeB->next->prev = NodeA;

    // Swap the prev pointers
    Buffer = NodeA->prev;
    NodeA->prev = NodeB->prev;
    NodeB->prev = Buffer;

    // Swap the next pointers
    Buffer = NodeB->next;
    NodeB->next = NodeA->next;
    NodeA->next = Buffer;

    // Modify the head if it is one of the nodes
    if (head == NodeA) head = NodeB;
    else if (head == NodeB) head = NodeA;
}