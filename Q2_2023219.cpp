// Address Book v1.0 by Hamza Bin Aamir

// ------ LIBRARIES ------ 
#include <iostream>
#include <exception> // to add special exceptions
#include <string> // to use the getline function
#include <limits> // used in conjunction with cin.ignore

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
    Person(const string& Name, const string& Address, const string& PhoneNumber): Name(Name), Address(Address), PhoneNumber(PhoneNumber) {};
    bool operator <(const Person&) const;
    bool operator >(const Person&) const;
    bool operator !=(const string&) const; 
    const string& getName() const {return Name;}
    void Show() const;
};

// We will be using these nodes for our SLL
struct Node
{
    Person data;
    Node* next;

    Node(const Person& data, Node* next) : data(data), next(next) {};
};

// An implementation of a singly linked list with Person classes as our data and special alphabetical insertions
class SLList
{
private:
    Node* head;
public:
    SLList() : head(nullptr) {};
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
    SLList AddressBook;
    string BufferA, BufferB, BufferC;
    int choice = 0; // we can use a smaller integer to optimise

    while (Continue)
    {
        cout << endl << "Here are your options: ";
        cout << endl << "\t1. Enter a new person";
        cout << endl << "\t2. Add 5 example people";
        cout << endl << "\t3. Show the list";
        cout << endl << "\t4. Find a person (by Name)";
        cout << endl << "\t5. Exit";
        cout << endl << "Please enter your choice (int): ";
        cin >> choice;

        switch (choice)
        {
            case 5:
                Continue = false;
            break;

            case 1:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter the person's name: ";
                getline(cin, BufferA); // we need to use getline because it may contain spaces
                cout << "Please enter " << BufferA << "'s phone number: ";
                getline(cin, BufferB);
                cout << "Please enter " << BufferA << "'s address: ";
                getline(cin, BufferC);

                AddressBook.Insert(BufferA, BufferB, BufferC);

                cout << "SUCCESS! List is currently: ";
                AddressBook.Show();
            break;

            case 2:
                AddressBook.Insert("Qasim Riaz", "+1 4401-123", "Flat 06, 9th Avenue, NYC");
                AddressBook.Insert("Hamza Bin Aamir", "+92 (000) 121313", "Hostel 10 Room 69");
                AddressBook.Insert("Syed Areeb Zaheer", "+92 (001) 45353", "Hostel 10 Room 66A");
                AddressBook.Insert("Azeem Liaqat", "+92 (002) 45353", "Hostel 10 Room 66B");
                AddressBook.Insert("Muhammad Sanawar", "+92 (003) 789987", "Hostel 10 Room 90");

                cout << "SUCCESS! List is currently: ";
                AddressBook.Show();
            break;

            case 3:
                AddressBook.Show();
            break;

            case 4:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter the person's name: ";
                getline(cin, BufferA); 

                try{
                    AddressBook.Find(BufferA).Show();
                }
                catch(...){
                    cout << "NO MATCHES";
                }
            break;
        }
    }

    cout << "EXITING...";
    return NO_ERRORS;
}

// ------ DLList Function Definitions ------

void SLList::Insert(const Person& data)
{
    Node* insertion = new Node(data, nullptr); 
    // CASE A: There are no elements in the list
    if (!head)
    {
        head = insertion;
        return;
    }

    // CASE B: Insert at the beginning
    if (data < head->data) {
        insertion->next = head;
        head = insertion;
        return;
    }

    // CASE C: Insert in the middle or at the end
    Node* position = head;
    while (position->next && position->next->data < data) {
        position = position->next;
    }

    insertion->next = position->next;
    position->next = insertion;
}

void SLList::Insert(const string& Name, const string& PhoneNo, const string& Address)
{
    Person insertion = Person(Name, Address, PhoneNo);
    Insert(insertion);
}

void SLList::Show() const
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

const Person& SLList::Find(string Name) const
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