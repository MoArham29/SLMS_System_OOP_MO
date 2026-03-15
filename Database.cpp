#include "Database.h"
#include <iostream>

Database::Database() : db(nullptr) {}

Database::~Database()
{
    close();
}

bool Database::open(const string& filename)
{
    if (sqlite3_open(filename.c_str(), &db) != SQLITE_OK)
    {
        cerr << "Failed to open database: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    return true;
}

void Database::close()
{
    if (db != nullptr)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::createTables()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS books ("
        "book_id TEXT PRIMARY KEY,"
        "title TEXT NOT NULL,"
        "author TEXT NOT NULL,"
        "status TEXT NOT NULL,"
        "borrower_id TEXT,"
        "reserved_by_id TEXT,"
        "due_day INTEGER,"
        "reservation_start_day INTEGER,"
        "reservation_expiry_day INTEGER"
        ");";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        cerr << "Failed to create books table: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool Database::isBooksTableEmpty()
{
    const char* sql = "SELECT COUNT(*) FROM books;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare count query.\n";
        return true;
    }

    bool empty = true;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int count = sqlite3_column_int(stmt, 0);
        empty = (count == 0);
    }

    sqlite3_finalize(stmt);
    return empty;
}

bool Database::insertBook(const Book& book)
{
    const char* sql =
        "INSERT INTO books "
        "(book_id, title, author, status, borrower_id, reserved_by_id, due_day, reservation_start_day, reservation_expiry_day) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare insert statement.\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, book.getBookId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, statusToString(book.getStatus()).c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.getBorrowerId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, book.getReservedById().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, book.getDueDay());
    sqlite3_bind_int(stmt, 8, book.getReservationStartDay());
    sqlite3_bind_int(stmt, 9, book.getReservationExpiryDay());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool Database::updateBook(const Book& book)
{
    const char* sql =
        "UPDATE books SET "
        "title = ?, "
        "author = ?, "
        "status = ?, "
        "borrower_id = ?, "
        "reserved_by_id = ?, "
        "due_day = ?, "
        "reservation_start_day = ?, "
        "reservation_expiry_day = ? "
        "WHERE book_id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare update statement.\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, book.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.getAuthor().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, statusToString(book.getStatus()).c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, book.getBorrowerId().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.getReservedById().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, book.getDueDay());
    sqlite3_bind_int(stmt, 7, book.getReservationStartDay());
    sqlite3_bind_int(stmt, 8, book.getReservationExpiryDay());
    sqlite3_bind_text(stmt, 9, book.getBookId().c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool Database::deleteBook(const string& bookId)
{
    const char* sql = "DELETE FROM books WHERE book_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare delete statement.\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, bookId.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

vector<Book> Database::loadBooks()
{
    vector<Book> books;
    const char* sql =
        "SELECT book_id, title, author, status, borrower_id, reserved_by_id, due_day, reservation_start_day, reservation_expiry_day "
        "FROM books;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cerr << "Failed to prepare select statement.\n";
        return books;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        string bookId = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string statusText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        const unsigned char* borrowerPtr = sqlite3_column_text(stmt, 4);
        const unsigned char* reservedPtr = sqlite3_column_text(stmt, 5);

        string borrowerId = borrowerPtr ? reinterpret_cast<const char*>(borrowerPtr) : "";
        string reservedById = reservedPtr ? reinterpret_cast<const char*>(reservedPtr) : "";

        int dueDay = sqlite3_column_int(stmt, 6);
        int reservationStartDay = sqlite3_column_int(stmt, 7);
        int reservationExpiryDay = sqlite3_column_int(stmt, 8);

        Book book(
            bookId,
            title,
            author,
            stringToStatus(statusText),
            borrowerId,
            reservedById,
            dueDay,
            reservationStartDay,
            reservationExpiryDay
        );

        books.push_back(book);
    }

    sqlite3_finalize(stmt);
    return books;
}