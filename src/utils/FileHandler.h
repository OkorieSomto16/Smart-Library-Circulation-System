#pragma once
#include "../model/LibraryDatabase.h"
#include <filesystem>

namespace library {
class FileHandler {
public:
    static void save(const std::filesystem::path& path,const LibraryDatabase& database);
    static LibraryDatabase load(const std::filesystem::path& path);
};
}
