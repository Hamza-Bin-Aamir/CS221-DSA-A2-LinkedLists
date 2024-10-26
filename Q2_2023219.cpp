// Address Book v1.0 by Hamza Bin Aamir

// ------ LIBRARIES ------ 
#include <iostream>
#include <exception> // to add special exceptions
#include <string> // to use the getline function

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
    const string& getName() const {return Name;}
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
    void Insert(const string&, const string&, const string&);
    const Person& Find(string) const;
    void Show() const;
};

// ------ ENTRY POINT ------ 
int main()
{
    cout << "Welcome to Address Book v1.0!";
    bool Continue = true;
    DLList AddressBook;
    string BufferA, BufferB, BufferC;
    uint8_t choice = 0; // we can use a smaller integer to optimise

    while (Continue)
    {
        cout << endl << "Here are your options: ";
        cout << endl << "\t1. Enter a new person";
        cout << endl << "\t2. Add 5 example people";
        cout << endl << "\t3. Show the list";
        cout << endl << "\t4. Find a person (by Name)";
        cout << endl << "\t5. Exit";
        cout << "Please enter your choice (int): ";
        cin >> choice;

        switch (choice)
        {
            case 5:
                Continue = false;
            break;

            case 1:
                cout << endl << "Please enter the person's name: ";
                getline(cin, BufferA); // we need to use getline because it may contain spaces
                cout << endl << "Please enter " << BufferA << "'s phone number: ";
                getline(cin, BufferB);
                cout << endl << "Please enter " << BufferA << "'s address: ";
                getline(cin, BufferC);

                AddressBook.Insert(BufferA, BufferB, BufferC);

                cout << endl << "SUCCESS! List is currently: ";
                AddressBook.Show();
            break;

            case 2:
                AddressBook.Insert("Qasim Riaz", "+1 4401-123", "Flat 06, 9th Avenue, NYC");
                AddressBook.Insert("Hamza Bin Aamir", "+92 (000) 121313", "Hostel 10 Room 69");
                AddressBook.Insert("Syed Areeb Zaheer", "+92 (001) 45353", "Hostel 10 Room 66A");
                AddressBook.Insert("Azeem Liaqat", "+92 (002) 45353", "Hostel 10 Room 66B");
                AddressBook.Insert("Muhammad Sanawar", "+92 (003) 789987", "Hostel 10 Room 90");

                cout << endl << "SUCCESS! List is currently: ";
                AddressBook.Show();
            break;

            case 3:
                AddressBook.Show();
            break;

            case 4:
                cout << endl << "Please enter the person's name: ";
                getline(cin, BufferA); 

                try{
                    AddressBook.Find(BufferA);
                }
                catch(...){
                    cout << endl << "NO MATCHES";
                }
            break;
        }
    }

    cout << endl << "EXITING...";
    return NO_ERRORS;
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

void DLList::Insert(const string& Name, const string& PhoneNo, const string& Address)
{
    Person* insertion = new Person(Name, Address, PhoneNo);
    DLList::Insert(*insertion);
}

void DLList::Show() const
{
    Node* Position = head;

    cout << endl << "[ ";
    while(Position)
    {
        cout << Position->data.getName() << " -> ";
        Position = Position->next;
    }
    cout << " NULL (pointer) ]"; 
}

const Person& DLList::Find(string Name) const
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