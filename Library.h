#pragma once
#include <vector>
#include <string>
#include "Book.h"
#include "User.h"
#include "Member.h"
#include "Librarian.h"
#include "Admin.h"

/* Declaring the Functions in Library */
/* This is the main systems class which stores all the books and the actions*/

class Library
{
private:
    vector<Book> books;
    int borrowingLimit;
    int loanDays;
    double latePenaltyPerDay;
    int findBookIndex(const string& bookId) const;

public:
    Library();
    void seedSampleData();
    void listBooks(int today);
    void displayBooksByIndexes(const vector<int>& indices, int today);

    vector<int> searchByTitle(const string& query);
    vector<int> searchByAuthor(const string& query);

    bool borrowBook(const string& bookId, Member& member, int today);
    bool returnBook(const string& bookId, Member& member);
    bool reserveBook(const string& bookId, Member& member, int today);

    bool addBook(const Book& book, const Librarian& librarian);
    bool removeBook(const string& bookId, const Librarian& librarian);

    void overdueReport(int today);
    bool setBorrowingLimit(int limit, const Admin& admin);
    bool setLatePenalty(double penalty, const Admin& admin);
};


