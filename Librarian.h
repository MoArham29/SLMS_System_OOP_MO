#pragma once 
#include "User.h"

/* Declaring Functions in Librarian */
/* This section is for the librarian class */

class Librarian : public User
{
public:
    Librarian(const string& id, const string& name)
        : User(id, name) {}
    
    string role() const override { return "Librarian"; }
    bool canManageBooks() const override { return true; }
};
