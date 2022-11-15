#include <bits/stdc++.h>
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
    return (abs(dayCount1 - dayCount2 - 693991));
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
    void Defaulters();
    void IssuedBooks();
    void Login(string Username);
    void Login(string Username, string Password1);
    void AfterLoginUser(string Username);
    void AfterLoginAdmin(string Username);
    void Student();
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
                cout << "Sorry! We are out of copies.\n." << endl;
        }
        ptr = ptr->next;
    }

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
}

void Librarylist::fine(int LateDays)
{
    cout << "You have to pay fine of Rs." << LateDays * 10 << "/- for " << LateDays << " days of late return." << endl;
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
    string bookName2;
    int day2, month2, year2;
    int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    fin.open("IssuedBooksData.txt");
    while (!fin.eof())
    {
        getline(fin, Username2);
        getline(fin, bookName2);
        if (Username2 == Username && bookName2 == bookName)
        {
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
            cout << bookName << " by " << authorName << " returned." << endl;
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

void Librarylist::Defaulters()
{
    ifstream fin;
    string Username;
    string BookName;
    int day2, month2, year2;
    int dateReturn[3] = {ltm->tm_mday, ltm->tm_mon, ltm->tm_year};
    fin.open("IssuedBooksData.txt");
    bool flag = false;
    while (!fin.eof())
    {
        getline(fin, Username);
        getline(fin, BookName);
        fin >> day2 >> ws;
        fin >> month2 >> ws;
        fin >> year2 >> ws;
        int dateIssue[3] = {day2, month2, year2};
        if (countNoOfDays(dateIssue, dateReturn) > 15)
        {
            flag = true;
            int i = 1;
            cout << i << "." << Username << " for book " << BookName << ", "
                 << countNoOfDays(dateIssue, dateReturn) << " days passed since issue. " << endl;
            i++;
        }
    }
    if (!flag)
        cout << "No defaulters." << endl;
    fin.close();
}

void Librarylist::IssuedBooks()
{
    ifstream fin;
    string BookName;
    string Username;
    int Day, Month, Year;
    fin.open("IssuedBooksData.txt");
    while (!fin.eof())
    {
        getline(fin, Username);
        getline(fin, BookName);
        fin >> Day >> ws;
        fin >> Month >> ws;
        fin >> Year >> ws;
        cout << Username << " issued " << BookName << " book on " << Day << "/" << Month << "/" << Year << "." << endl;
    }
    fin.close();
}

//=======================================================login/signup===============================================//

// Student
void Librarylist::Login(string Username)
{
    ifstream fin;
    ofstream fout;
    fin.open("Users.txt");
    string Username2;
    string Password;
    string Password2;
    cout << "Enter password\n >>";
    cin >> Password;
    bool flag = true;
    while (!fin.eof())
    {
        getline(fin, Username2);
        getline(fin, Password2);
        if (Username2 == Username && Password2 == Password)
            AfterLoginUser(Username);
        else
            flag = false;
    }
    if (!flag)
        cout << "Incorrect useranme or password." << endl;
}

// Admin
void Librarylist::Login(string Username, string Password1)
{
    ifstream fin;
    ofstream fout;
    fin.open("adminUsers.txt");
    string Username2;
    string Password2;
    string Password1_check;
    string Password2_check;
    cout << "Enter password 2\n >>";
    cin >> Password2;
    bool flag = true;
    while (!fin.eof())
    {
        fin >> Username2 >> ws;
        fin >> Password1_check >> ws;
        fin >> Password2_check >> ws;
        if (Username2 == Username && Password1_check == Password1 && Password2_check == Password2)
            AfterLoginAdmin(Username);
        else
            flag = false;
    }
    if (!flag)
        cout << "Incorrect useranme or password." << endl;
    fin.close();
}

void Librarylist::AfterLoginAdmin(string Username)
{
    int choice;
    do
    {

        cout << "\n1.Search.\n2.See available books.\n3.See requested books.\n4.Isseud books.\n5.Defaulters List.\n6.Add books in Library.\n99.Exit\n>>";
        
        cout << "\n1.Search.\n2.See available books.\n3.See requested books.\n4.Isseud books.\n5.Defaulters List.\n99.Exit\n>>";

        cin >> choice;
        switch (choice)
        {
        case 1:
            search(Username);
            break;
            break;
        case 2:
            printLibList();
            break;
        case 3:
            printRequestList();
            break;
        case 4:
            IssuedBooks();
            break;
        case 5:
            Defaulters();
            break;

        case 6:
        {
            int numberOfCopies;
            string title, author;
            cout << "\nEnter the book name to add to the library\n>>";
            cin >> title;
            cout << "\nEnter the book name to add to the library\n>>";
            cin >> author;
            cout << "\nEnter the book name to add to the library\n>>";
            cin >> numberOfCopies;
            insertNodeLibList(numberOfCopies, title, author);
        }
        break;
        case 99:
            break;
        default:
            cout << "Please enter valid data ! ";
            break;
        }
    } while (choice != 99);
}

void Librarylist::AfterLoginUser(string Username)
{
    int choice;
    do
    {
        cout << "\n1.Search\n2.Issue\n3.Reutrn.\n99.Exit\n>>";
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
        case 99:
            break;
        default:
            cout << "Please enter valid data ! ";
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
            Login(Username);
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

void Librarylist::Student()
{
    int choice;
    do
    {
        cout << "\n1.Login\n2.Signup\n99.Exit\n>>";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            string Username;
            cout << "Enter username\n>>";
            cin >> Username;
            Login(Username);
        }
        break;
        case 2:
            Signup();
            break;
        case 99:
            break;
        default:
            cout << "Please enter valid data ! ";
            break;
        }
    } while (choice != 99);
}

//=====================================================main function===============================================//

int main()
{
    Librarylist list;
    int choice;
    list.LibraryRecords();
    do
    {
        cout << "\n1.Student\n2.Admin\n99.Exit\n>>";
        cin >> choice;
        switch (choice)
        {
        case 1:
            list.Student();
            break;
        case 2:
        {
            string Username;
            string Password1;
            cout << "Enter username\n>>";
            cin >> Username;
            cout << "Enter password 1\n >>";
            cin >> Password1;
            list.Login(Username, Password1);
        }
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