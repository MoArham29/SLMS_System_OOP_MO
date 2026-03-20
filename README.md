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


<img width="400" height="318" alt="Screenshot 2026-03-16 at 1 25 08 pm" src="https://github.com/user-attachments/assets/fe23283c-779f-4bff-8da3-9b9879e71492" />


## How to Run

Please Use Visual Studio Code and make sure Clang ++ is installed 

In Terminal Type 

clang -c sqlite3.c -o sqlite3.o

clang++ -std=c++17 main.cpp Book.cpp Library.cpp Database.cpp sqlite3.o -o slms

./slms

After these three steps the system will start running 

## Demo Accounts

Admin
username: admin
password: admin123

Librarian
username: librarian
password: lib123




