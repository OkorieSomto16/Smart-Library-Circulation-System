#pragma once
#include "SearchEngine.h"
#include "../model/LibraryDatabase.h"
#include "../utils/IDGenerator.h"
#include <stack>
#include <unordered_map>

namespace library {
class LibraryManager {
public:
    static constexpr int LoanDays=14, MaxActiveLoans=5, ChargePerDay=50;
    explicit LibraryManager(LibraryDatabase& database):db_(database){}
    LibraryDatabase& database(){return db_;}
    std::shared_ptr<LibraryItem> addItem(ItemType type,const std::string& title,const std::string& author,int year);
    void deleteItem(const std::string& id);
    bool undo();
    void clearUndoHistory(){undo_=std::stack<UndoAction>{};}
    std::shared_ptr<LibraryItem> borrow(const std::string& itemId,const std::string& userId);
    std::string returnItem(const std::string& itemId,const std::string& userId);
    void reserve(const std::string& itemId,const std::string& userId);
    long overdueCharge(const LibraryItem& item) const;
    std::vector<std::shared_ptr<LibraryItem>> mostBorrowed() const;
    std::vector<std::string> overdueUsers() const;
    std::unordered_map<std::string,size_t> categoryDistribution() const;
    static std::string today();
    static std::string dateAfter(int days);
private:
    struct UndoAction{bool wasAdd;std::shared_ptr<LibraryItem> item;long accessCount=0;};
    LibraryDatabase& db_;std::stack<UndoAction> undo_;
    LibraryItem& requiredItem(const std::string& id) const;
};
}
