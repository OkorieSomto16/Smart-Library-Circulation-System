#include "LibraryItem.h"
#include <stdexcept>
#include <utility>

namespace library {
LibraryItem::LibraryItem(std::string id, std::string title, std::string author, int year)
    : id_(std::move(id)), title_(std::move(title)), author_(std::move(author)), year_(year) {
    if (id_.empty() || title_.empty() || author_.empty()) throw std::invalid_argument("Item ID, title and author are required.");
}
void LibraryItem::checkOut(const std::string& borrowerId, const std::string& dueDate) {
    if (!isAvailable()) throw std::logic_error("Item is already borrowed.");
    if (borrowerId.empty() || dueDate.empty()) throw std::invalid_argument("Borrower and due date are required.");
    borrowerId_ = borrowerId; dueDate_ = dueDate; ++borrowCount_;
}
void LibraryItem::checkIn() { borrowerId_.clear(); dueDate_.clear(); }
std::shared_ptr<LibraryItem> Book::clone() const { auto p=std::make_shared<Book>(id(),title(),author(),year());p->setBorrowCount(borrowCount());if(!isAvailable())p->checkOut(borrowerId(),dueDate());p->setBorrowCount(borrowCount());return p; }
std::shared_ptr<LibraryItem> Magazine::clone() const { auto p=std::make_shared<Magazine>(id(),title(),author(),year());p->setBorrowCount(borrowCount());if(!isAvailable())p->checkOut(borrowerId(),dueDate());p->setBorrowCount(borrowCount());return p; }
std::shared_ptr<LibraryItem> Journal::clone() const { auto p=std::make_shared<Journal>(id(),title(),author(),year());p->setBorrowCount(borrowCount());if(!isAvailable())p->checkOut(borrowerId(),dueDate());p->setBorrowCount(borrowCount());return p; }
std::string toString(ItemType t) { switch(t){case ItemType::Book:return "Book";case ItemType::Magazine:return "Magazine";case ItemType::Journal:return "Journal";}return "Book"; }
ItemType itemTypeFromString(const std::string& s) { if(s=="Book")return ItemType::Book;if(s=="Magazine")return ItemType::Magazine;if(s=="Journal")return ItemType::Journal;throw std::invalid_argument("Unknown item type."); }
}
