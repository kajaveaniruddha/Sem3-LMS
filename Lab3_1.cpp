#include <bits/stdc++.h>
#include <fstream>
using namespace std;

//================================Node class for linked list of Library-List=======================================//

class Node
{
public:
    int numberOfcopies;
    string title, author;
    Node *next;
    // Parameterised Constructor
    Node(int numberOfCopies, string title, string author)
    {
        this->title = title;
        this->author = author;
        this->numberOfcopies = numberOfCopies;
        this->next = NULL;
    }
};

//====================================Linked list for Library-List================================================//

class Librarylist
{
    Node *head;
    Node *head2;

public:
    // Default constructor
    Librarylist()
    {
        head = NULL;
        head2 = NULL;
    }
    void insertNodeLibList(int numberOfCopies, string title, string author);
    void printLibList();
    void LibraryRecords();
    void issueBook(string Username, string bookName, string authorName);
    void search(string username);
    void returnBook();
    void RequestRecords(int numberOfCopies, string title, string author);
    void printRequestList();
    void insertNodeReqList(int numberOfCopies, string title, string author);
    void Login();
    void AfterLogin(string Username);
    void Signup();
};

//=========================================Request List functions================================================//

void Librarylist::RequestRecords(int numberOfCopies, string title, string author)
{
    Node *ptr = head2;
    while (ptr != NULL)
    {
        if (ptr->title == title)
        {
            ptr->numberOfcopies++;
            break;
        }
        ptr = ptr->next;
    }
    if (ptr == NULL)
        insertNodeReqList(numberOfCopies, title, author);
}

void Librarylist::printRequestList()
{
    Node *temp = head2;

    if (head2 == NULL)
    {
        cout << "List empty" << endl;
        return;
    }
    while (temp != NULL)
    {
        cout << "TITLE - " << temp->title << "\t"
             << "AUTHOR - " << temp->author << "\t"
             << "# OF COPIES - " << temp->numberOfcopies
             << endl;
        temp = temp->next;
    }
    cout << "\n";
}

void Librarylist::insertNodeReqList(int numberOfCopies, string title, string author)
{
    Node *newNode = new Node(numberOfCopies, title, author);
    if (head2 == NULL)
    {
        head2 = newNode;
        return;
    }
    Node *temp = head2;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

//=========================================Library List functions================================================//

void Librarylist::insertNodeLibList(int numberOfCopies, string title, string author)
{
    Node *newNode = new Node(numberOfCopies, title, author);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void Librarylist::printLibList()
{
    Node *temp = head;

    if (head == NULL)
    {
        cout << "List empty" << endl;
        return;
    }
    while (temp != NULL)
    {
        cout << "TITLE - " << temp->title << "\t"
             << "AUTHOR - " << temp->author << "\t"
             << "# OF COPIES - " << temp->numberOfcopies << "\t"
             << endl;
        temp = temp->next;
    }
    cout << "\n";
}

void Librarylist::LibraryRecords()
{
    ifstream fin;
    string title;
    string author;
    int numberOfCopies;
    fin.open("BooksData.txt");
    while (!fin.eof())
    {
        getline(fin, title);
        getline(fin, author);
        fin>> numberOfCopies;
        insertNodeLibList(numberOfCopies, title, author);
    }
    fin.close();
}

void Librarylist::issueBook(string Username, string bookName, string authorName)
{
    Node *ptr = head;
    bool flag = false;
    while (ptr != NULL)
    {
        if (ptr->title == bookName && ptr->author == authorName)
        {
            flag = true;
            if (ptr->numberOfcopies > 0)
            {
                cout << bookName << " by " << authorName << " issue successfull !" << endl;
                ptr->numberOfcopies--;
                ofstream fout;
                fout.open("IssuedBooksData.txt");
                fout << Username;
                fout << ptr->title;
                fout.close();
                break;
            }
            else
                cout << "Sorry! We are out of copies.\n." << endl;
        }
        ptr = ptr->next;
    }

    if (!flag)
    {
        RequestRecords(1, bookName, authorName);
        cout << "\nBook not found in records...\n"
             << bookName << " book added in request list." << endl;
    }
}

void Librarylist::search(string username)
{
    cout << "Type the title of book: " << endl;
    cout << ">>";
    string bookName;
    cin >> bookName;
    cout << "Type the author of book: " << endl;
    cout << ">>";
    string authorName;
    cin >> authorName;
    Node *ptr = head;
    while (ptr != NULL)
    {
        if (ptr->title == bookName && ptr->author == authorName)
        {
            if (ptr->numberOfcopies > 0)
            {
                cout << bookName << " by " << authorName << " is available." << endl;
                cout << "Would you like to issue the book? y/n" << endl;
                char choice;
                cin >> choice;
                if (choice == 'y')
                {
                    issueBook(username, ptr->title, ptr->author);
                    break;
                }
                else
                {
                    cout << "Nevermind !" << endl;
                    break;
                }
            }
            else
                cout << "Sorry! We are out of copies." << endl;
        }
        ptr = ptr->next;
    }
}

void Librarylist::returnBook()
{
    cout << "Type the title of book: " << endl;
    cout << ">>";
    string bookName;
    cin >> bookName;
    cout << "Type the author of book: " << endl;
    cout << ">>";
    string authorName;
    cin >> authorName;

    Node *ptr = head;
    Node *ptr2 = head2;
    while (ptr2 != NULL)
    {
        if (ptr2->title == bookName && ptr2->author == authorName)
        {
            ptr2->numberOfcopies--;
            ptr->numberOfcopies++;
            cout << "1 copy of " << bookName << " removed from request list." << endl;
            break;
        }
        ptr2 = ptr2->next;
    }
    if (ptr2 == NULL)
    {
        while (ptr != NULL)
        {
            if (ptr->title == bookName && ptr->author == authorName)
            {
                cout << bookName << " by " << authorName << " returned." << endl;
                ptr->numberOfcopies++;
                break;
            }
            ptr = ptr->next;
        }
    }
}

//=======================================================login/signup===============================================//

void Librarylist::Login()
{
    ifstream fin;
    ofstream fout;
    fin.open("Users.txt");
    string Username;
    string Username2;
    string Password;
    string Password2;
    cout << "Enter username\n>>";
    cin >> Username;
    cout << "Enter password\n>>";
    cin >> Password;
    while (!fin.eof())
    {
        getline(fin, Username2);
        getline(fin, Password2);
        if (Username2 == Username && Password2 == Password)
            AfterLogin(Username);
    }
    cout << "Incorrect useranme or password." << endl;
}

void Librarylist::AfterLogin(string Username)
{
    int choice;
    // LibraryRecords();
    do
    {
        cout << "\n1.Search\n2.Issue\n3.Reutrn\n4.See available books.\n5.See requested books.\n99.Exit\n>>";
        cin >> choice;
        switch (choice)
        {
        case 1:
            search(Username);
            break;
        case 2:
        {
            cout << "Type the title of book: " << endl;
            cout << ">>";
            string bookName;
            cin >> bookName;

            cout << "Type the author of book: " << endl;
            cout << ">>";
            string authorName;
            cin >> authorName;
            issueBook(Username, bookName, authorName);
        }
        break;
        case 3:
            returnBook();
            break;
        case 4:
            printLibList();
            break;
        case 5:
            printRequestList();
            break;
        case 99:
            break;
        default:
            cout << "PLease enter valid data ! ";
            break;
        }
    } while (choice != 99);
}

void Librarylist::Signup()
{
    ifstream fin;
    fin.open("Users.txt");
    string Username;
    string Username2;
    string Password;
    cout << "Enter username\n>>";
    cin >> Username;
    while (!fin.eof())
    {
        getline(fin, Username2);
        if (Username2 == Username)
        {
            cout << "User alread exist!\n Redirecting to login page..." << endl;
            Login();
            return;
        }
    }
    cout << "Enter password\n>>";
    cin >> Password;
    fin.close();
    ofstream fout;
    fout.open("Users.txt");
    fout << Username << endl;
    fout << Password;
    fout.close();
}

//=====================================================main function===============================================//

int main()
{
    Librarylist list;
    int choice;
    list.LibraryRecords();
    do
    {
        cout << "\n1.Log in\n2.Sign up\n99.Exit\n>>";
        cin >> choice;
        switch (choice)
        {
        case 1:
            list.Login();
            break;
        case 2:
            list.Signup();
            break;
        case 99:
            break;
        default:
            cout << "Please enter valid data ! ";
            break;
        }
    } while (choice != 99);

    return 0;
}