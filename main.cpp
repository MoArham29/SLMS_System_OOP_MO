#include <iostream>
#include <string>
#include "Library.h"

using namespace std;

// Safe integer input
int readInt()
{
    int value;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cin.ignore(10000, '\n');
    return value;
}

// Safe double input
double readDouble()
{
    double value;
    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    cin.ignore(10000, '\n');
    return value;
}

// Reads full line input
string readLine(const string& prompt)
{
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}

int main()
{
    Library library;
    int today = 0;

    while (true)
    {
        cout << "\n=====================================\n";
        cout << " SMART LIBRARY MANAGEMENT SYSTEM\n";
        cout << " Current Day: " << today << "\n";
        cout << "=====================================\n";
        cout << "1. Login as Member\n";
        cout << "2. Login as Librarian\n";
        cout << "3. Login as Admin\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";

        int choice = readInt();

        if (choice == 0)
        {
            cout << "Exiting program.\n";
            break;
        }

        string id = readLine("Enter ID: ");
        string name = readLine("Enter Name: ");

        if (choice == 1)
        {
            Member member(id, name);

            bool loggedIn = true;
            while (loggedIn)
            {
                cout << "\n--- Member Menu ---\n";
                cout << "1. List all books\n";
                cout << "2. Search by title\n";
                cout << "3. Search by author\n";
                cout << "4. Borrow book\n";
                cout << "5. Return book\n";
                cout << "6. Reserve book\n";
                cout << "7. View my borrowed books\n";
                cout << "8. Advance day\n";
                cout << "0. Logout\n";
                cout << "Choose option: ";

                int action = readInt();

                if (action == 0)
                {
                    loggedIn = false;
                }
                else if (action == 1)
                {
                    library.listAllBooks(today);
                }
                else if (action == 2)
                {
                    string query = readLine("Enter title search: ");
                    auto results = library.searchByTitle(query);
                    library.displayBooksByIndexes(results, today);
                }
                else if (action == 3)
                {
                    string query = readLine("Enter author search: ");
                    auto results = library.searchByAuthor(query);
                    library.displayBooksByIndexes(results, today);
                }
                else if (action == 4)
                {
                    string bookId = readLine("Enter Book ID to borrow: ");
                    library.borrowBook(bookId, member, today);
                }
                else if (action == 5)
                {
                    string bookId = readLine("Enter Book ID to return: ");
                    library.returnBook(bookId, member, today);
                }
                else if (action == 6)
                {
                    string bookId = readLine("Enter Book ID to reserve: ");
                    library.reserveBook(bookId, member, today);
                }
                else if (action == 7)
                {
                    vector<string> borrowed = library.getBorrowedBooksForMember(member.getId());

                    cout << "\nBorrowed books:\n";
                    if (borrowed.empty())
                    {
                        cout << "None\n";
                    }
                    else
                    {
                        for (const auto& bookId : borrowed)
                        {
                           cout << "- " << bookId << "\n";
                        }
                    }
                }
                else if (action == 8)
                {
                    today++;
                    cout << "Day advanced to " << today << ".\n";
                }
                else
                {
                    cout << "Invalid option.\n";
                }
            }
        }
        else if (choice == 2)
        {
            Librarian librarian(id, name);

            bool loggedIn = true;
            while (loggedIn)
            {
                cout << "\n--- Librarian Menu ---\n";
                cout << "1. List all books\n";
                cout << "2. Add book\n";
                cout << "3. Remove book\n";
                cout << "4. Overdue report\n";
                cout << "5. Advance day\n";
                cout << "0. Logout\n";
                cout << "Choose option: ";

                int action = readInt();

                if (action == 0)
                {
                    loggedIn = false;
                }
                else if (action == 1)
                {
                    library.listAllBooks(today);
                }
                else if (action == 2)
                {
                    string newId = readLine("Enter new Book ID: ");
                    string title = readLine("Enter book title: ");
                    string author = readLine("Enter author name: ");

                    Book newBook(newId, title, author);
                    library.addBook(newBook, librarian);
                }
                else if (action == 3)
                {
                    string bookId = readLine("Enter Book ID to remove: ");
                    library.removeBook(bookId, librarian);
                }
                else if (action == 4)
                {
                    library.overdueReport(today);
                }
                else if (action == 5)
                {
                    today++;
                    cout << "Day advanced to " << today << ".\n";
                }
                else
                {
                    cout << "Invalid option.\n";
                }
            }
        }
        else if (choice == 3)
        {
            Admin admin(id, name);

            bool loggedIn = true;
            while (loggedIn)
            {
                cout << "\n--- Admin Menu ---\n";
                cout << "1. Set borrowing limit\n";
                cout << "2. Set late penalty\n";
                cout << "3. Advance day\n";
                cout << "0. Logout\n";
                cout << "Choose option: ";

                int action = readInt();

                if (action == 0)
                {
                    loggedIn = false;
                }
                else if (action == 1)
                {
                    cout << "Enter new borrowing limit: ";
                    int limit = readInt();
                    library.setBorrowingLimit(limit, admin);
                }
                else if (action == 2)
                {
                    cout << "Enter new late penalty per day: ";
                    double penalty = readDouble();
                    library.setLatePenalty(penalty, admin);
                }
                else if (action == 3)
                {
                    today++;
                    cout << "Day advanced to " << today << ".\n";
                }
                else
                {
                    cout << "Invalid option.\n";
                }
            }
        }
        else
        {
            cout << "Invalid login option.\n";
        }
    }

    return 0;
}