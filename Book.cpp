#include "Book.h"
#include <sstream>

string statusToString(BookStatus status)
{
    switch (status)
    {
        case BookStatus::Available: return "Available";
        case BookStatus::Borrowed: return "Borrowed";
        case BookStatus::Reserved: return "Reserved";
        default: return "Unknown";
    }
}

Book::Book()
    : bookId(""), title(""), author(""),
      status(BookStatus::Available),
      borrowerId(""), reservedById(""),
      dueDay(-1), reservationExpiryDay(-1)
{
}

Book::Book(const string& id, const string& title, const string& author)
    : bookId(id), title(title), author(author),
      status(BookStatus::Available),
      borrowerId(""), reservedById(""),
      dueDay(-1), reservationExpiryDay(-1)
{
}

string Book::getBookId() const { return bookId; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getBorrowerId() const { return borrowerId; }
string Book::getReservedById() const { return reservedById; }
BookStatus Book::getStatus() const { return status; }
int Book::getDueDay() const { return dueDay; }
int Book::getReservationExpiryDay() const { return reservationExpiryDay; }

bool Book::isAvailable() const
{
    return status == BookStatus::Available;
}

bool Book::borrow(const string& memberId, int today, int loanDays)
{
    if (status != BookStatus::Available)
        return false;

    status = BookStatus::Borrowed;
    borrowerId = memberId;
    dueDay = today + loanDays;
    return true;
}

void Book::returnBook()
{
    borrowerId = "";
    dueDay = -1;

    if (!reservedById.empty())
        status = BookStatus::Reserved;
    else
        status = BookStatus::Available;
}

bool Book::reserve(const string& memberId, int today)
{
    if ((status == BookStatus::Borrowed || status == BookStatus::Reserved) && borrowerId != memberId && borrowerId != "")
    {
        status = BookStatus::Reserved;
        reservedById = memberId;
        reservationExpiryDay = today + 3;
        return true;
    }

    return false;
}

bool Book::isOverdue(int today) const
{
    return (borrowerId != "" && dueDay != -1 && today > dueDay);
}

void Book::refreshReservation(int today)
{
    if (status == BookStatus::Reserved && reservationExpiryDay != -1 && today > reservationExpiryDay)
    {
        reservedById = "";
        reservationExpiryDay = -1;

        if (borrowerId != "")
            status = BookStatus::Borrowed;
        else
            status = BookStatus::Available;
    }
}

bool Book::isBorrowedOrReserved() const
{
    return status == BookStatus::Borrowed || status == BookStatus::Reserved;
}

string Book::toString(int today)
{
    refreshReservation(today);

    stringstream ss;
    ss << "ID: " << bookId
       << " | Title: " << title
       << " | Author: " << author
       << " | Status: " << statusToString(status);

    if (borrowerId != "")
    {
        ss << " | Borrower: " << borrowerId
           << " | Due Day: " << dueDay;
    }

    if (reservedById != "")
    {
        ss << " | Reserved By: " << reservedById
           << " | Reservation Expiry: " << reservationExpiryDay;
    }

    return ss.str();
}