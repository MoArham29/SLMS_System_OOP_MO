#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "Member.h"
#include "Librarian.h"
#include "Admin.h"
#include "Database.h"

using namespace std;

/* Declaring the Functions in Library */
/* This is the main systems class which stores all the books and the actions */

class Library
{
private:
    vector<Book> books;
    int borrowingLimit;
    int loanDays;
    double latePenaltyPerDay;
    Database database;

    int findBookIndexById(const string& bookId) const;

public:
    Library();

    void seedSampleData();
    void listAllBooks(int today);
    void displayBooksByIndexes(const vector<int>& indexes, int today);

    vector<int> searchByTitle(const string& query);
    vector<int> searchByAuthor(const string& query);
    vector<string> getBorrowedBooksForMember(const string& memberId);

    bool borrowBook(const string& bookId, Member& member, int today);
    bool returnBook(const string& bookId, Member& member, int today);
    bool reserveBook(const string& bookId, Member& member, int today);

    bool addBook(const Book& book, const Librarian& librarian);
    bool removeBook(const string& bookId, const Librarian& librarian);

    void overdueReport(int today);
    bool setBorrowingLimit(int limit, const Admin& admin);
    bool setLatePenalty(double penalty, const Admin& admin);
};