// Address Book v1.0 by Hamza Bin Aamir

// ------ LIBRARIES ------ 
#include <iostream>
#include <exception>

// ------ PRE-PROC CONSTS ------ 
#define NO_ERRORS 0

using namespace std; // so we don't have to repeatedly say std::cout, std::cin

// ------ CLASS DEFS ------

// Person class has useful information about a person, and it contains binary comparator functions
class Person
{
private:
    string Name;
    string Address;
    string PhoneNumber;
public:
    Person(string Name, string Address, string PhoneNumber): Name(Name), Address(Address), PhoneNumber(PhoneNumber) {};
    bool operator <(const Person&) const;
    bool operator >(const Person&) const;
    bool operator !=(const string&) const; 
    void Show() const;
};

// We will be using these nodes for our DLL
struct Node
{
    Person data;
    Node* next;
    Node* prev;

    Node(const Person& data, Node* next, Node* prev) : data(data), next(next), prev(prev) {};
};

// An implementation of a doubly linked list with Person classes as our data and special alphabetical insertions
class DLList
{
private:
    Node* head;
public:
    DLList() : head(nullptr) {};
    void Insert(const Person&);
    Person& Find(string) const;
    void Show() const;
};

// ------ ENTRY POINT ------ 
int main()
{

}

// ------ DLList Function Definitions ------

void DLList::Insert(const Person& data)
{
    // CASE A: There are no elements in the list
    if (!head)
    {
        head = new Node(data, nullptr, nullptr);
    }

    // CASE B: List contains some elements
    Node* insertion = new Node(data, nullptr, nullptr);
    Node* position = head;
    while (position < insertion && position)
    {
        position = position->next;
    }
    insertion->prev = position->prev;
    insertion->next = position;
    insertion->prev->next = insertion;
}

void DLList::Show() const
{
    Node* Position = head;

    cout << endl << "[ ";
    while(Position)
    {
        
    }
    cout << "NULL (POINTER) ]"; 
}

Person& DLList::Find(string Name) const
{
    Node* Position = head;
    while (Position->data != Name)
    {
        Position = Position->next;
        if (!Position)
        {
            throw domain_error("");
        }
    }
    return Position->data;
}


// ------ Person Function Definitions ------
bool Person::operator !=(const string& Name) const
{
    if(this->Name == Name)
    {
        return true;
    }
    return false;
}

bool Person::operator <(const Person& Comparee) const
{
    if (this->Name < Comparee.Name) 
    {
        return true;
    }
    return false;
}

bool Person::operator >(const Person& Comparee) const
{
    if (this->Name > Comparee.Name)
    {
        return true;
    }
    return false;
}

void Person::Show() const
{
    cout << endl << "*** Information for " << this->Name << " ***" << endl;
    cout << "\tPhone No: " << PhoneNumber << endl;
    cout << "\tAddress: " << Address << endl;
}