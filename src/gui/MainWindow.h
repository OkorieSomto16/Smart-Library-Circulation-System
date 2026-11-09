#pragma once
#include "../controller/LibraryManager.h"
#include "../controller/BorrowController.h"
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <commctrl.h>
#include <string>
#include <unordered_set>

namespace library {
class MainWindow {
public:
    explicit MainWindow(LibraryDatabase& db):manager_(db),borrowController_(manager_){}
    int run(HINSTANCE instance,int showCommand);
private:
    static LRESULT CALLBACK windowProc(HWND,UINT,WPARAM,LPARAM);
    LRESULT handle(HWND,UINT,WPARAM,LPARAM);
    void createControls();
    void layout(int width,int height);
    void refresh();
    void switchTab(int index);
    void handleCommand(int id);
    void showItems(HWND table,const SearchEngine::Items& items);
    std::string fieldText(int id) const;
    void setStatus(const std::string& text);
    void showError(const std::string& text);
    void saveAs(bool load);
    void showReports();
    void checkOverdue();
    LibraryManager manager_;
    BorrowController borrowController_;
    HWND hwnd_=nullptr,tab_=nullptr,status_=nullptr;
    HWND viewTable_=nullptr,searchTable_=nullptr,cacheTable_=nullptr;
    HWND lblItemId_=nullptr,lblUserId_=nullptr,lblType_=nullptr,lblTitle_=nullptr,lblAuthor_=nullptr,lblYear_=nullptr,lblAdminId_=nullptr,lblQuery_=nullptr,lblSortField_=nullptr;
    HWND itemId_=nullptr,userId_=nullptr,borrowResult_=nullptr,snapshot_=nullptr;
    HWND itemType_=nullptr,title_=nullptr,author_=nullptr,year_=nullptr,adminId_=nullptr,adminMessage_=nullptr;
    HWND query_=nullptr,searchField_=nullptr,searchStrategy_=nullptr,sortField_=nullptr,sortAlgorithm_=nullptr,searchMessage_=nullptr;
    int tabIndex_=0;bool showingCache_=false;
    std::unordered_set<std::string> reminded_;
};
}
