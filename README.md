# 📚 Library Management System

A comprehensive console-based Library Management System built in C++ demonstrating object-oriented programming principles and efficient data structure implementation.

## 🎯 Features

- **Book Management**
  - Add new books with ISBN tracking
  - Search books by title or author
  - Real-time availability status
  - Complete book catalog viewing

- **Member Management**
  - Register new members with contact information
  - Track borrowing history
  - Enforce borrowing limits (max 3 books per member)
  - Member profile viewing

- **Transaction System**
  - Issue books to members
  - Return books with automatic date tracking
  - Complete transaction history
  - Overdue detection system

- **Fine Management**
  - Automatic fine calculation for overdue books ($1/day after 14 days)
  - Fine payment processing
  - Outstanding fine tracking
  - Prevents borrowing with unpaid fines

## 🛠️ Technical Implementation

### Object-Oriented Concepts
- **Encapsulation**: Private data members with controlled access through getters/setters
- **Inheritance**: `Member` class inherits from `Person` base class
- **Polymorphism**: Virtual functions for dynamic binding (`display()` method)
- **Abstraction**: Clean interfaces hiding implementation complexity
- **Association**: Library class manages relationships between Books and Members
- **Aggregation**: Member class contains collection of borrowed books

### Data Structures & STL
- `std::map<int, Book>` - O(log n) book lookups by ID
- `std::map<int, Member>` - O(log n) member lookups by ID
- `std::vector<Transaction>` - Transaction history storage
- `std::vector<int>` - Member's borrowed books tracking
- STL algorithms: `find()`, `transform()`, `max()`

### Design Patterns
- **Singleton-like Library Management**: Single Library instance manages all operations
- **Static Counter**: Auto-incrementing transaction IDs
- **Business Logic Validation**: Pre-condition checks before operations

## 📋 Prerequisites

- C++ Compiler with C++11 support (g++, clang++, MSVC)
- Standard Template Library (STL)

## 🚀 Installation & Usage

### Compilation

```bash
# Using g++
g++ -std=c++11 library_management.cpp -o library

# Using clang++
clang++ -std=c++11 library_management.cpp -o library

# Using MSVC (Windows)
cl /EHsc /std:c++11 library_management.cpp
```

### Running the Program

```bash
# Linux/Mac
./library

# Windows
library.exe
```

## 📖 How to Use

### Main Menu Options

1. **Add Book** - Register new books in the system
2. **Add Member** - Register new library members
3. **Issue Book** - Lend a book to a member
4. **Return Book** - Process book returns and calculate fines
5. **Search Books** - Find books by title or author
6. **Display All Books** - View complete book catalog
7. **Display All Members** - View all registered members
8. **Pay Fine** - Process fine payments
9. **Exit** - Close the application

### Sample Workflow

```
1. Add books to the library
2. Register members
3. Issue books using Member ID and Book ID
4. Return books (system automatically calculates fines if overdue)
5. Pay any outstanding fines
```

## 💡 Example Usage

```cpp
// Pre-loaded sample data:
Books:
- "The C++ Programming Language" by Bjarne Stroustrup
- "Effective C++" by Scott Meyers
- "Design Patterns" by Gang of Four

Members:
- John Doe (ID: 1)
- Jane Smith (ID: 2)

// Issue a book
Enter Member ID: 1
Enter Book ID: 1001
✓ Book issued successfully!

// Return book after 16 days
Enter Member ID: 1
Enter Book ID: 1001
✓ Book returned successfully!
Overdue by 2 days. Fine: $2.00
```

## 🏗️ Project Structure

```
library-management-system/
│
├── library_management.cpp    # Main source file
├── README.md                 # Project documentation
└── .gitignore               # Git ignore file
```

## 🔑 Key Classes

### Person (Base Class)
- Attributes: name, id, contact
- Methods: display(), getters

### Member (Derived from Person)
- Attributes: borrowedBooks, maxBooks, fineAmount
- Methods: borrowBook(), returnBook(), canBorrow(), addFine()

### Book
- Attributes: bookId, title, author, isbn, isAvailable
- Methods: getters, setters, display()

### Transaction
- Attributes: transactionId, memberId, bookId, dates
- Methods: markReturned(), getDaysOverdue(), display()

### Library (Manager Class)
- Attributes: books (map), members (map), transactions (vector)
- Methods: addBook(), addMember(), issueBook(), returnBook(), searchBooks()

## 🎓 Learning Outcomes

- Practical implementation of OOP principles
- STL container usage and selection
- Memory management and object lifecycle
- Business logic implementation
- Error handling and input validation
- Code organization and modularity

---

⭐ If you found this project helpful, please give it a star!
