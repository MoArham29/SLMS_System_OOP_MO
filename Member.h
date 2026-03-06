#pragma once
#include "User.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/* Declaring Functions in Member */
/* This section is for the library member class */

class Member : public User
{
private:
    vector<string> borrowedBookIds;

public:
    Member(const string& id, const string& name)
        : User(id, name) {}

    // Polymorphism
    string role() const override
    {
        return "Member";
    }

    bool canBorrow() const override
    {
        return true;
    }

    int borrowedCount() const
    {
        return borrowedBookIds.size();
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
};