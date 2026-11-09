#include "LibraryDatabase.h"
#include <algorithm>
#include <stdexcept>

namespace library {
LibraryItem* LibraryDatabase::findItem(const std::string& id) const { for(const auto& i:items_)if(i->id()==id)return i.get();return nullptr; }
UserAccount& LibraryDatabase::getOrCreateUser(const std::string& id) { if(id.empty())throw std::invalid_argument("Borrower ID is required.");auto [it,inserted]=users_.try_emplace(id,UserAccount{id,id,{}});(void)inserted;return it->second; }
void LibraryDatabase::addItem(std::shared_ptr<LibraryItem> item) { if(!item||findItem(item->id()))throw std::invalid_argument("Duplicate or invalid item ID.");items_.push_back(std::move(item));rebuildCache(); }
std::shared_ptr<LibraryItem> LibraryDatabase::removeItem(const std::string& id) { auto it=std::find_if(items_.begin(),items_.end(),[&](const auto& x){return x->id()==id;});if(it==items_.end())return {};auto item=*it;items_.erase(it);accessCounts_.erase(id);rebuildCache();return item; }
void LibraryDatabase::recordAccess(LibraryItem* item) { if(item){++accessCounts_[item->id()];rebuildCache();} }
void LibraryDatabase::restoreAccessCount(const std::string& id,long count) { if(count>0)accessCounts_[id]=count;rebuildCache(); }
long LibraryDatabase::accessCount(const std::string& id) const { auto it=accessCounts_.find(id);return it==accessCounts_.end()?0:it->second; }
void LibraryDatabase::rebuildCache() { frequent_.fill(nullptr);std::vector<LibraryItem*> leaders;for(auto& i:items_)if(accessCount(i->id())>0)leaders.push_back(i.get());std::stable_sort(leaders.begin(),leaders.end(),[&](auto a,auto b){return accessCount(a->id())>accessCount(b->id());});for(size_t i=0;i<std::min(leaders.size(),frequent_.size());++i)frequent_[i]=leaders[i]; }
void LibraryDatabase::clear() { items_.clear();users_.clear();reservations_.clear();accessCounts_.clear();frequent_.fill(nullptr); }
}
