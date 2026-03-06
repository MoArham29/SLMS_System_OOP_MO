#pragma once
#include "User.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/* This section is for the library member class */

class Member : public User
{
private:
    vector<string> borrowedBookIds; // stores the book Ids

public:
    Member(const string& name, const string& id) : User(name, id) {}

    string role() const override { return "Member"; }
    bool canBorrow() const override { return true; }

    int borrowedCount() const
    {
        return static_cast<int>(borrowedBookIds.size());

    }
    bool hasBorrowed(const string& bookId) const
    {
        return find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId) != borrowedBookIds.end();
    }
    void addBorrowed(const string& bookId)
    { 
        borrowedBookIds.push_back(bookId);
    }
    bool removeBorrowed(const string& bookId)
    {
        auto it = find(borrowedBookIds.begin(), borrowedBookIds.end(), bookId);
        if (it == borrowedBookIds.end())
            return false;
        
        borrowedBookIds.erase(it);
        return true;
    }
    void displayBorrowedBooks() const
    {
        cout << "Borrowed Books:/n";
        if (borrowedBookIds.empty())
        {
            cout << "No books borrowed./n";
            return;
        }
        for (const auto& Id : borrowedBookIds)
        {
            cout << "- " << Id << "/n";
        }
    }
};
