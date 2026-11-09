#pragma once
#include "LibraryItem.h"
#include <array>
#include <deque>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace library {
struct BorrowRecord { std::string itemId, title, borrowedOn, returnedOn; };
struct UserAccount { std::string id, displayName; std::vector<BorrowRecord> history; };
struct Reservation { std::string itemId, userId, placedAt; };

class LibraryDatabase {
public:
    const std::vector<std::shared_ptr<LibraryItem>>& items() const { return items_; }
    std::vector<std::shared_ptr<LibraryItem>>& items() { return items_; }
    const std::unordered_map<std::string, UserAccount>& users() const { return users_; }
    std::unordered_map<std::string, UserAccount>& users() { return users_; }
    std::deque<Reservation>& reservations() { return reservations_; }
    const std::deque<Reservation>& reservations() const { return reservations_; }
    LibraryItem* findItem(const std::string& id) const;
    UserAccount& getOrCreateUser(const std::string& id);
    void addItem(std::shared_ptr<LibraryItem> item);
    std::shared_ptr<LibraryItem> removeItem(const std::string& id);
    void recordAccess(LibraryItem* item);
    void restoreAccessCount(const std::string& id, long count);
    long accessCount(const std::string& id) const;
    const std::array<LibraryItem*,8>& frequentlyAccessed() const { return frequent_; }
    void rebuildCache();
    void clear();
private:
    std::vector<std::shared_ptr<LibraryItem>> items_;
    std::unordered_map<std::string, UserAccount> users_;
    std::deque<Reservation> reservations_;
    std::unordered_map<std::string,long> accessCounts_;
    std::array<LibraryItem*,8> frequent_{};
};
}
