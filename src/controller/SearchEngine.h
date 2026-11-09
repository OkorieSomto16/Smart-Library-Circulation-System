#pragma once
#include "../model/LibraryItem.h"
#include <string>
#include <vector>

namespace library {
enum class SearchField { Title, Author, Type };
enum class SearchStrategy { Linear, Binary, Recursive };
enum class SortField { Title, Author, Year };
enum class SortAlgorithm { Selection, Insertion, Merge, Quick };
class SearchEngine {
public:
    using Items = std::vector<std::shared_ptr<LibraryItem>>;
    static Items search(const Items& source,const std::string& query,SearchField field,SearchStrategy strategy);
    static Items sort(const Items& source,SortField field,SortAlgorithm algorithm);
    static std::string label(SearchField f);
    static std::string label(SortField f);
    static std::string label(SortAlgorithm a);
};
}
