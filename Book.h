#pragma once
#include <string>
using namespace std;

/* Bokk Statuses*/ 

enum class BookStatus
{
    Available,
    Borrowed,
    Reserved
};

string statusToString(BookStatus status)

/* This section is for the book in the library and it encapsulates book state and book actions */

class Book
{
private:
    string bookId;
    string title;
    string author;
    BookStatus status;
    string borrowerId;
    string reservedById;
    int dueDay;
    int reservationExpiryDay;

public:
    Book();
    Book(const string& id, const string& title, const string& author);
    string getBookId() const;
    string getTitle() const;
    string getAuthor() const;
    string getBorrowerId() const;
    string getReservedById() const;
    BookStatus getStatus() const;
    int getDueDay() const;
    int getReservationExpiryDay() const;

    bool isAvailable() const;
    bool borrow(const string& memberId, int today, int loanDays);
    void returnBook();
    bool reserve(const string& memberId, int today);
    bool isOverdue(int today) const;
    void refreshReservation(int today);
    bool isBorrowedOrReserved() const;
    string toString(int today);
};