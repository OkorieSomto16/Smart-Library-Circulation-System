# Smart Library Circulation & Automation System (C++)

Native Windows desktop application written in C++20 with the Win32 API. It has catalogue, circulation, admin, and search/sort tabs, plus local text-file persistence.

## Build and run

Install Visual Studio 2022 Community or Build Tools with the **Desktop development with C++** workload (including the MSVC compiler and CMake). Open **Developer PowerShell for VS 2022**, navigate to this project folder, and run:

```powershell
cmake -S . -B build
cmake --build build --config Release
.\build\Release\SmartLibrary.exe
```

The app creates `library-data.txt` in its working directory on first run. Use **Admin → Save As / Load From** to choose another data file. The file stores catalogue items, borrower accounts and histories, reservations, borrow totals, and access counts.

## Features

- Abstract `LibraryItem`, `Borrowable` interface, and `Book`, `Magazine`, and `Journal` subclasses.
- Add/delete items, undo the last admin add/delete, borrow, return, and FIFO reservation queue.
- Linear and recursive partial search; binary exact-match search over a sorted temporary copy.
- Selection, insertion, merge, and quick sort by title, author, or year.
- `std::vector` catalogue, `std::deque` reservation queue, `std::stack` undo history, and fixed-size array for the eight most accessed items.
- Timer-based overdue reminders, validation dialogs, native file chooser, and reports for most borrowed items, overdue users, and category totals.

## Policy defaults

The source brief does not define local circulation policy. The app currently uses 14-day loans, a maximum of five active loans per borrower, and an estimated overdue charge of 50 currency units per day. Update the constants in `src/controller/LibraryManager.h` for your institution.

## Project layout

- `src/model`: item and database classes
- `src/controller`: circulation and search/sorting algorithms
- `src/gui`: native Windows interface
- `src/utils`: IDs and text-file persistence

This is a local teaching-project application. It does not implement authentication, network synchronization, or payments.

