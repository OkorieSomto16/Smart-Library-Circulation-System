#pragma once
#include <memory>
#include <string>

namespace library {
enum class ItemType { Book, Magazine, Journal };

class Borrowable {
public:
    virtual ~Borrowable() = default;
    virtual bool isAvailable() const = 0;
    virtual void checkOut(const std::string& borrowerId, const std::string& dueDate) = 0;
    virtual void checkIn() = 0;
};

class LibraryItem : public Borrowable {
public:
    LibraryItem(std::string id, std::string title, std::string author, int year);
    virtual ~LibraryItem() = default;
    const std::string& id() const { return id_; }
    const std::string& title() const { return title_; }
    const std::string& author() const { return author_; }
    int year() const { return year_; }
    const std::string& borrowerId() const { return borrowerId_; }
    const std::string& dueDate() const { return dueDate_; }
    long borrowCount() const { return borrowCount_; }
    void setBorrowCount(long count) { borrowCount_ = count < 0 ? 0 : count; }
    bool isAvailable() const override { return borrowerId_.empty(); }
    void checkOut(const std::string& borrowerId, const std::string& dueDate) override;
    void checkIn() override;
    virtual ItemType type() const = 0;
    virtual std::shared_ptr<LibraryItem> clone() const = 0;
private:
    std::string id_, title_, author_, borrowerId_, dueDate_;
    int year_;
    long borrowCount_ = 0;
};

#define LIBRARY_ITEM_CLASS(ClassName, TypeValue) \
class ClassName final : public LibraryItem { \
public: using LibraryItem::LibraryItem; \
    ItemType type() const override { return ItemType::TypeValue; } \
    std::shared_ptr<LibraryItem> clone() const override; \
};
LIBRARY_ITEM_CLASS(Book, Book)
LIBRARY_ITEM_CLASS(Magazine, Magazine)
LIBRARY_ITEM_CLASS(Journal, Journal)
#undef LIBRARY_ITEM_CLASS

std::string toString(ItemType type);
ItemType itemTypeFromString(const std::string& value);
}
