// Loop Detector v1.0 by Hamza Bin Aamir

// ------ LIBRARIES ------ 
#include <iostream>

// ------ PRE-PROC CONSTS ------ 
#define NO_ERRORS 0

using namespace std; // so we don't have to repeatedly say std::cout, std::cin

// ------ CLASS DEFS ------

// A node for a singly linked list that accepts any data type using C++ templates
struct Node {
    Node* next;
    int data;
    Node(Node* next, int data): next(next), data(data) {};
};

class SLList {
private:
    Node* head;
public:
    SLList() : head(nullptr) {};
    void PushFront(int);
    void InsertLoop(int);
    void Show();
    void FixLoops();
};


// ------ ENTRY POINT ------ 
int main()
{
    SLList A;
    A.PushFront(1);
    A.PushFront(3);
    A.PushFront(4);
    A.PushFront(5);
    A.Show();
    
    A.InsertLoop(2);

    A.FixLoops();
    A.Show();

    return NO_ERRORS;
}

// ------ SINGLY LINKED LIST FUNCTION DEFINITIONS ------

// This function adds a new element to the front (head-side) of the list
// Parameters:
//      1. Data: The data to insert
void SLList::PushFront(int Data)
{
    // CASE A: there are no elements in the list
    if (!head) 
    {
        head = new Node(nullptr, Data); return;
    }

    // CASE B: there is an element in the list
    Node* insertion = new Node(head, Data);
    head = insertion;
}

// This function creates a loop by manipulating the tail of the list
// Parameters:
//      1. TargetPosition: The index position where the loop should be applied (counting starts from one)
void SLList::InsertLoop(int TargetPosition)
{
    int PositionCounter = 1;
    Node* Position = head;
    Node* LoopAdd = nullptr;

    while(Position->next)
    {
        if(PositionCounter == TargetPosition)
        {
            LoopAdd = Position; // Stores the address of the loop target
        }

        Position = Position->next;
        PositionCounter++;
    }

    cout << endl << "Loop added from Node #" << PositionCounter << " to Node #" << TargetPosition;
    Position->next = LoopAdd; // assigns the loop target as the next element to the last element
}

// Uses three runners to find the node that contains the offender
// Assumes that a loop indeed exists
void SLList::FixLoops()
{
    Node* Slow = head; Node* Fast = nullptr; Node* Final = nullptr; Node* Offender = nullptr;
    int idx = 0; int offender_idx = 0;

    while(Slow != Fast)
    {
        if (Fast == nullptr) { Fast = head; }

        Fast = Fast->next->next;
        Slow = Slow->next;
    }

    while(Final != Slow)
    {
        if (Final == nullptr) { Final = head; }
        Slow = Slow->next;
        Final = Final->next;
        idx++;
    }

    Offender = Final; offender_idx = idx;

    while (Final->next != Offender)
    {
        Final = Final->next;
        idx++;
    }

    cout << endl;
    cout << "Loop removed from Node #" << idx+1 << " to Node #" << offender_idx;
    Final->next = nullptr;
}

void SLList::Show()
{
    cout << endl;
    Node* Position = head;
    while(Position){
        cout << Position->data << "->";
        Position = Position->next;
    }
    cout << "NULL (Pointer)";
}