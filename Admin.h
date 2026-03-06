#pragma once
#include "User.h"

/* Declaring Functions in Admin */
/* Represents an admin user */

class Admin : public User
{
public:
    Admin(const string& id, const string& name) : User(id, name) {}

    string role() const override { return "Admin"; }
    bool canManageRules() const override { return true; }
};