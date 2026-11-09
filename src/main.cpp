#include "gui/MainWindow.h"
#include "utils/FileHandler.h"
#include <filesystem>
#include <memory>

namespace {
library::LibraryDatabase sample(){library::LibraryDatabase db;db.addItem(std::make_shared<library::Book>("ITM-1001","Things Fall Apart","Chinua Achebe",1958));db.addItem(std::make_shared<library::Book>("ITM-1002","Purple Hibiscus","Chimamanda Ngozi Adichie",2003));db.addItem(std::make_shared<library::Book>("ITM-1003","Half of a Yellow Sun","Chimamanda Ngozi Adichie",2006));db.addItem(std::make_shared<library::Magazine>("ITM-2001","African Review of Books","Editorial Board",2024));db.addItem(std::make_shared<library::Journal>("ITM-3001","Journal of Library Innovation","MIVA Research Group",2025));return db;}
}
int WINAPI wWinMain(HINSTANCE instance,HINSTANCE, PWSTR,int showCommand){library::LibraryDatabase db;const std::filesystem::path data="library-data.txt";try{if(std::filesystem::exists(data))db=library::FileHandler::load(data);else{db=sample();library::FileHandler::save(data,db);}}catch(const std::exception&e){MessageBoxA(nullptr,e.what(),"Library data warning",MB_OK|MB_ICONWARNING);db=sample();}library::MainWindow app(db);return app.run(instance,showCommand);}
