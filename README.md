# Smart Library Management System (SLMS)

## Overview
The Smart Library Management System is a C++ console application that demonstrates Object-Oriented Programming concepts including inheritance, encapsulation, and polymorphism.  
The system manages books, users, borrowing, reservations, and role-based access using a SQLite database.

## Features
- User authentication
- Role-based access (Member, Librarian, Admin)
- Book search by title and author
- Borrow and return books
- Reservation system
- Overdue reporting
- Persistent storage using SQLite

## Technologies
- C++
- SQLite
- Object-Oriented Programming
- VS Code / Terminal

## Project Structure

SLMS_System_OOP_MO
│
├── main.cpp
├── Book.cpp / Book.h
├── Library.cpp / Library.h
├── Database.cpp / Database.h
├── User.h
├── Member.h
├── Librarian.h
├── Admin.h
├── sqlite3.c
├── slms.db
│
├── UML diagrams
└── Wiki documentation

## How to Run

**clang -c sqlite3.c -o sqlite3.o

clang++ -std=c++17 main.cpp Book.cpp Library.cpp Database.cpp sqlite3.o -o slms

./slms**

## Demo Accounts

**Admin
username: admin
password: admin123

Librarian
username: librarian
password: lib123
**



