#pragma once
#include "LibraryManager.h"
namespace library {
class BorrowController {
public:
    explicit BorrowController(LibraryManager& manager):manager_(manager){}
    std::shared_ptr<LibraryItem> borrow(const std::string& itemId,const std::string& userId){return manager_.borrow(itemId,userId);}
    std::string returnItem(const std::string& itemId,const std::string& userId){return manager_.returnItem(itemId,userId);}
    void reserve(const std::string& itemId,const std::string& userId){manager_.reserve(itemId,userId);}
private: LibraryManager& manager_;
};
}
