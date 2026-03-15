#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "sqlite3.h"

using namespace std;

/* Handles database operations for the system */
class Database
{
private:
    sqlite3* db;

public:
    Database();
    ~Database();

    bool open(const string& filename);
    void close();

    bool createTables();
    bool isBooksTableEmpty();

    bool insertBook(const Book& book);
    bool updateBook(const Book& book);
    bool deleteBook(const string& bookId);

    vector<Book> loadBooks();
};