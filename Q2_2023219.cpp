// Address Book v1.0 by Hamza Bin Aamir

// ------ LIBRARIES ------ 
#include <iostream>

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
    bool operator ==(const Person&) const; 
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
    Person& Find(string);
};

// ------ ENTRY POINT ------ 
int main()
{

}

// ------ DLList Function Definitions ------

void Insert(const Person& data)
{
    
}