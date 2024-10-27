// DLL Swapper v1.0
#include <iostream>
#include <exception> // to add special exceptions

// ------ PRE-PROC CONSTS ------ 
#define NO_ERRORS 0
#define SWAP_POS_A 3
#define SWAP_POS_B 4

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
    DLList A;
    A.PushBack(1);
    A.PushBack(3);
    A.PushBack(4);
    A.PushBack(5);
    A.Show();

    try
    {
        A.Swap(SWAP_POS_A, SWAP_POS_B);
    }
    catch(...)
    {
        cout << endl << "The swap operation was interrupted due to one or more nodes not being found.";
    }
    A.Show();

    return NO_ERRORS;
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

    // CASE B: There are some elements in the list
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
        throw domain_error("");
        return;
    }

    // Handle adjacent nodes
    if (NodeA->next == NodeB)
    {
        NodeA->next = NodeB->next;
        if (NodeB->next) NodeB->next->prev = NodeA;
        NodeB->prev = NodeA->prev;
        if (NodeA->prev) NodeA->prev->next = NodeB;
        NodeB->next = NodeA;
        NodeA->prev = NodeB;
    }
    else if (NodeB->next == NodeA)
    {
        NodeB->next = NodeA->next;
        if (NodeA->next) NodeA->next->prev = NodeB;
        NodeA->prev = NodeB->prev;
        if (NodeB->prev) NodeB->prev->next = NodeA;
        NodeA->next = NodeB;
        NodeB->prev = NodeA;
    }
    else
    {
        // Swap the next pointers of the nodes before the nodes to be swapped
        if (NodeA->prev) NodeA->prev->next = NodeB;
        if (NodeB->prev) NodeB->prev->next = NodeA;

        // Swap the previous pointers of the nodes after the nodes to be swapped
        if (NodeA->next) NodeA->next->prev = NodeB;
        if (NodeB->next) NodeB->next->prev = NodeA;

        // Swap the prev pointers
        Node* Buffer = NodeA->prev;
        NodeA->prev = NodeB->prev;
        NodeB->prev = Buffer;

        // Swap the next pointers
        Buffer = NodeA->next;
        NodeA->next = NodeB->next;
        NodeB->next = Buffer;
    }

    // Modify the head if it is one of the nodes
    if (head == NodeA) head = NodeB;
    else if (head == NodeB) head = NodeA;
}