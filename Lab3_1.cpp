#include <bits/stdc++.h>
#include <fstream>
#include <ctime>
using namespace std;

//===================================================Functions for Time==========================================================//

time_t now = time(0);
tm *ltm = localtime(&now);

const int monthDays[12] = {31, 59, 90, 120, 151, 181, 212, 243,
                           273, 304, 334, 365};
int countLeapYearDays(int d[])
{
    int years = d[2];
    if (d[1] <= 2)
        years--;
    return ((years / 4) - (years / 100) + (years / 400));
}
int countNoOfDays(int date1[], int date2[])
{
    long int dayCount1 = (date1[2] * 365);
    dayCount1 += monthDays[date1[1]];
    dayCount1 += date1[0];
    dayCount1 += countLeapYearDays(date1);
    long int dayCount2 = (date2[2] * 365);
    dayCount2 += monthDays[date2[1]];
    dayCount2 += date2[0];
    dayCount2 += countLeapYearDays(date2);
    return (abs(dayCount1 - dayCount2));
}

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
    void fine(int);
    void returnBook(string Username);
    void RequestRecords();
    void printRequestList();
    void insertNodeReqList(int numberOfCopies, string title, string author);
    void Login();
    void AfterLogin(string Username);
    void Signup();
};

//=========================================Request List functions================================================//

void Librarylist::RequestRecords()
{
    ifstream fin;
    string title;
    string author;
    int numberOfCopies;
    fin.open("RequestedBooksData.txt");
    while (!fin.eof())
    {
        getline(fin >> ws, title);
        getline(fin >> ws, author);
        fin >> numberOfCopies;
        insertNodeReqList(numberOfCopies, title, author);
    }
    fin.close();
}

void Librarylist::printRequestList()
{
    RequestRecords();
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
        getline(fin >> ws, title);
        getline(fin >> ws, author);
        fin >> numberOfCopies;
        insertNodeLibList(numberOfCopies, title, author);
    }
    fin.close();
}

void Librarylist::issueBook(string Username, string bookName, string authorName)
{
    //--------------------no consecutive issue of same books-----------------------------//
    ifstream fin;
    string Username2;
    string bookName2;
    fin.open("IssuedBooksData.txt");
    while (!fin.eof())
    {
        getline(fin, Username2);
        if (Username2 == Username)
        {
            fin >> ws;
            getline(fin, bookName2);
            if (bookName2 == bookName)
            {
                cout << "Sorry! consecutive issue of same book is not allowed." << endl;
                return;
            }
        }
    }

    //----------------------------------------------issue a book-------------------------------------//

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
                fout.open("IssuedBooksData.txt", ios::app);
                fout << Username << endl;
                fout << ptr->title << endl;
                fout << ltm->tm_mday << endl;
                fout << 1 + ltm->tm_mon << endl;
                fout << 1900 + ltm->tm_year << endl;
                fout.close();
                break;
            }
            else
                cout << "Sorry! We are out of copies.\n"
                     << endl;
        }
        ptr = ptr->next;
    }
    //-----------------------------------------------send to request list----------------------------------------- //
    if (!flag)
    {
        ofstream fout;
        fout.open("RequestedBooksData.txt");
        // fout << Username << "\n";
        fout << bookName << "\n";
        fout << authorName << "\n";
        fout << 1 << "\n";
        fout.close();
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
    if (ptr == NULL)
        cout << "Sorry we don't have this book." << endl;
}

void Librarylist::fine(int LateDays)
{
    cout << "You have to pay fine of Rs" << LateDays * 10 << "/- for " << LateDays << " days of late return.";
}

void Librarylist::returnBook(string Username)
{
    cout << "Type the title of book: " << endl;
    cout << ">>";
    string bookName;
    cin >> bookName;
    cout << "Type the author of book: " << endl;
    cout << ">>";
    string authorName;
    cin >> authorName;

    ifstream fin;
    string Username2;
    int day2, month2, year2;
    int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    fin.open("IssuedBooksData.txt");
    while (!fin.eof())
    {
        getline(fin, Username2);
        if (Username2 == Username)
        {
            fin >> ws;
            fin >> ws;
            fin >> day2 >> ws;
            fin >> month2 >> ws;
            fin >> year2 >> ws;
            int dateIssue[3] = {day2, month2, year2};
            if (countNoOfDays(dateIssue, dateReturn) > 15)
                fine(countNoOfDays(dateIssue, dateReturn));
        }
    }

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
    bool flag = true;
    while (!fin.eof())
    {
        getline(fin, Username2);
        getline(fin, Password2);
        if (Username2 == Username && Password2 == Password)
            AfterLogin(Username);
        else
            flag = false;
    }
    if (!flag)
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
            returnBook(Username);
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
    fout.open("Users.txt", ios::app);
    fout << Username << endl;
    fout << Password << endl;
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