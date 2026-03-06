#pragma once
#include <string>

using namespace std;

/* an Abstract class for all the users of the system. Abstaraction and polymorphism are used here. */

class User
{
protected:
    string id;
    string name;

public:
    User(const string& id, const string& name) : id(id), name(name) {}
    virtual ~User() = default;

    string getName() const { return name; }
    string getId() const { return id; }

    virtual string role() const = 0;
    virtual bool canBorrow() const { return false; }
    virtual bool canManageBooks() const { return false; }
    virtual bool canManageRules() const { return false; }

};
