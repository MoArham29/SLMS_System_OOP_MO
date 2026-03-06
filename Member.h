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