cmake_minimum_required(VERSION 3.20)
project(SmartLibraryCirculation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(SmartLibrary WIN32
    src/main.cpp
    src/model/LibraryItem.cpp
    src/model/LibraryDatabase.cpp
    src/controller/BorrowController.cpp
    src/controller/SearchEngine.cpp
    src/controller/LibraryManager.cpp
    src/utils/FileHandler.cpp
    src/utils/IDGenerator.cpp
    src/gui/MainWindow.cpp
)
target_include_directories(SmartLibrary PRIVATE src)
target_link_libraries(SmartLibrary PRIVATE comctl32 comdlg32)
if(MSVC)
  target_compile_options(SmartLibrary PRIVATE /W4 /permissive- /utf-8)
else()
  target_compile_options(SmartLibrary PRIVATE -Wall -Wextra -Wpedantic)
endif()
