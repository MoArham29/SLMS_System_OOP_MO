#include "Library.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

// Converts string to lowercase for case-insensitive search
static string toLowerCase(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return static_cast<char>(tolower(c)); });
    return s;
}

Library::Library()
{
    borrowingLimit = 5;
    loanDays = 14;
    latePenaltyPerDay = 0.50;
}

int Library::findBookIndexById(const string& bookId) const
{
    for (int i = 0; i < static_cast<int>(books.size()); i++)
    {
        if (books[i].getBookId() == bookId)
            return i;
    }
    return -1;
}

void Library::seedSampleData()
{
    books.emplace_back("B001", "Clean Code", "Robert C. Martin");
    books.emplace_back("B002", "The Pragmatic Programmer", "Andrew Hunt");
    books.emplace_back("B003", "Design Patterns", "Erich Gamma");
    books.emplace_back("B004", "C++ Primer", "Stanley Lippman");
    books.emplace_back("B005", "Introduction to Algorithms", "Thomas Cormen");
}

void Library::listAllBooks(int today)
{
    cout << "\n--- Library Catalogue ---\n";

    if (books.empty())
    {
        cout << "No books found.\n";
        return;
    }

    for (auto& book : books)
    {
        cout << book.toString(today) << "\n";
    }
}

void Library::displayBooksByIndexes(const vector<int>& indexes, int today)
{
    if (indexes.empty())
    {
        cout << "No matching books found.\n";
        return;
    }

    for (int index : indexes)
    {
        cout << books[index].toString(today) << "\n";
    }
}

vector<int> Library::searchByTitle(const string& query)
{
    vector<int> results;
    string q = toLowerCase(query);

    for (int i = 0; i < static_cast<int>(books.size()); i++)
    {
        if (toLowerCase(books[i].getTitle()).find(q) != string::npos)
            results.push_back(i);
    }

    return results;
}

vector<int> Library::searchByAuthor(const string& query)
{
    vector<int> results;
    string q = toLowerCase(query);

    for (int i = 0; i < static_cast<int>(books.size()); i++)
    {
        if (toLowerCase(books[i].getAuthor()).find(q) != string::npos)
            results.push_back(i);
    }

    return results;
}

bool Library::borrowBook(const string& bookId, Member& member, int today)
{
    if (member.borrowedCount() >= borrowingLimit)
    {
        cout << "Borrow denied: borrowing limit reached.\n";
        return false;
    }

    int index = findBookIndexById(bookId);
    if (index == -1)
    {
        cout << "Borrow denied: book not found.\n";
        return false;
    }

    books[index].refreshReservation(today);

    if (!books[index].isAvailable())
    {
        cout << "Borrow denied: book is not available.\n";
        return false;
    }

    if (books[index].borrow(member.getId(), today, loanDays))
    {
        member.addBorrowed(bookId);
        cout << "Borrow successful.\n";
        return true;
    }

    return false;
}

bool Library::returnBook(const string& bookId, Member& member)
{
    int index = findBookIndexById(bookId);
    if (index == -1)
    {
        cout << "Return denied: book not found.\n";
        return false;
    }

    if (!member.hasBorrowed(bookId))
    {
        cout << "Return denied: this member did not borrow that book.\n";
        return false;
    }

    books[index].returnBook();
    member.removeBorrowed(bookId);

    cout << "Return successful.\n";
    return true;
}

bool Library::reserveBook(const string& bookId, Member& member, int today)
{
    int index = findBookIndexById(bookId);
    if (index == -1)
    {
        cout << "Reservation denied: book not found.\n";
        return false;
    }

    books[index].refreshReservation(today);

    if (books[index].reserve(member.getId(), today))
    {
        cout << "Reservation successful.\n";
        return true;
    }

    cout << "Reservation denied: book must already be on loan to another member.\n";
    return false;
}

bool Library::addBook(const Book& book, const Librarian& librarian)
{
    (void)librarian; // Role checked in main menu

    if (findBookIndexById(book.getBookId()) != -1)
    {
        cout << "Add denied: duplicate book ID.\n";
        return false;
    }

    books.push_back(book);
    cout << "Book added successfully.\n";
    return true;
}

bool Library::removeBook(const string& bookId, const Librarian& librarian)
{
    (void)librarian; // Role checked in main menu

    int index = findBookIndexById(bookId);
    if (index == -1)
    {
        cout << "Remove denied: book not found.\n";
        return false;
    }

    if (books[index].isBorrowedOrReserved())
    {
        cout << "Remove denied: book is borrowed or reserved.\n";
        return false;
    }

    books.erase(books.begin() + index);
    cout << "Book removed successfully.\n";
    return true;
}

void Library::overdueReport(int today)
{
    cout << "\n--- Overdue Report ---\n";
    bool found = false;

    for (auto& book : books)
    {
        if (book.isOverdue(today))
        {
            cout << book.toString(today) << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "No overdue books.\n";
}

bool Library::setBorrowingLimit(int limit, const Admin& admin)
{
    (void)admin; // Role checked in main menu

    if (limit < 1 || limit > 20)
    {
        cout << "Invalid borrowing limit.\n";
        return false;
    }

    borrowingLimit = limit;
    cout << "Borrowing limit updated to " << borrowingLimit << ".\n";
    return true;
}

bool Library::setLatePenalty(double penalty, const Admin& admin)
{
    (void)admin; // Role checked in main menu.

    if (penalty < 0)
    {
        cout << "Invalid penalty value.\n";
        return false;
    }

    latePenaltyPerDay = penalty;
    cout << "Late penalty updated to " << latePenaltyPerDay << ".\n";
    return true;
}