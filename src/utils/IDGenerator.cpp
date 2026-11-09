#include "IDGenerator.h"
#include <chrono>
#include <atomic>
namespace library { std::string IDGenerator::nextItemId(){static std::atomic<unsigned long long> sequence{1};return "ITM-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+"-"+std::to_string(sequence.fetch_add(1));} }
