#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

class Book;
class Member;
class Transaction;

// ==================== BASE CLASSES ====================

// Person class - demonstrates inheritance
class Person {
protected:
    string name;
    int id;
    string contact;

public:
    Person(string n = "", int i = 0, string c = "") : name(n), id(i), contact(c) {}
    
    virtual void display() const {
        cout << "ID: " << id << ", Name: " << name << ", Contact: " << contact;
    }
    
    int getId() const { return id; }
    string getName() const { return name; }
    virtual ~Person() {}
};

// ==================== BOOK CLASS ====================

class Book {
private:
    int bookId;
    string title;
    string author;
    string isbn;
    bool isAvailable;
    int borrowedBy; // Member ID who borrowed it

public:
    Book(int id = 0, string t = "", string a = "", string i = "") 
        : bookId(id), title(t), author(a), isbn(i), isAvailable(true), borrowedBy(-1) {}
    
    // Getters
    int getBookId() const { return bookId; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getIsbn() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    int getBorrowedBy() const { return borrowedBy; }
    
    // Setters
    void setAvailability(bool status) { isAvailable = status; }
    void setBorrowedBy(int memberId) { borrowedBy = memberId; }
    
    void display() const {
        cout << "\n--- Book Details ---" << endl;
        cout << "Book ID: " << bookId << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Status: " << (isAvailable ? "Available" : "Borrowed") << endl;
        if (!isAvailable) {
            cout << "Borrowed by Member ID: " << borrowedBy << endl;
        }
    }
};

// ==================== MEMBER CLASS ====================

class Member : public Person {
private:
    vector<int> borrowedBooks; // Book IDs
    int maxBooks;
    double fineAmount;

public:
    Member(string n = "", int i = 0, string c = "", int max = 3) 
        : Person(n, i, c), maxBooks(max), fineAmount(0.0) {}
    
    bool canBorrow() const {
        return borrowedBooks.size() < maxBooks;
    }
    
    void borrowBook(int bookId) {
        borrowedBooks.push_back(bookId);
    }
    
    bool returnBook(int bookId) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookId);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            return true;
        }
        return false;
    }
    
    vector<int> getBorrowedBooks() const { return borrowedBooks; }
    
    void addFine(double amount) { fineAmount += amount; }
    double getFine() const { return fineAmount; }
    void clearFine() { fineAmount = 0.0; }
    
    void display() const override {
        cout << "\n--- Member Details ---" << endl;
        Person::display();
        cout << "\nBooks Borrowed: " << borrowedBooks.size() << "/" << maxBooks << endl;
        cout << "Fine Amount: $" << fixed << setprecision(2) << fineAmount << endl;
        if (!borrowedBooks.empty()) {
            cout << "Borrowed Book IDs: ";
            for (int id : borrowedBooks) {
                cout << id << " ";
            }
            cout << endl;
        }
    }
};

// ==================== TRANSACTION CLASS ====================

class Transaction {
private:
    static int transactionCounter;
    int transactionId;
    int memberId;
    int bookId;
    time_t issueDate;
    time_t returnDate;
    bool isReturned;

public:
    Transaction(int mId, int bId) 
        : memberId(mId), bookId(bId), isReturned(false) {
        transactionId = ++transactionCounter;
        issueDate = time(0);
        returnDate = 0;
    }
    
    void markReturned() {
        isReturned = true;
        returnDate = time(0);
    }
    
    int getDaysOverdue() const {
        time_t currentTime = time(0);
        int daysBorrowed = (currentTime - issueDate) / (24 * 3600);
        return max(0, daysBorrowed - 14); // 14 days borrowing period
    }
    
    void display() const {
        cout << "\n--- Transaction Details ---" << endl;
        cout << "Transaction ID: " << transactionId << endl;
        cout << "Member ID: " << memberId << endl;
        cout << "Book ID: " << bookId << endl;
        cout << "Issue Date: " << ctime(&issueDate);
        if (isReturned) {
            cout << "Return Date: " << ctime(&returnDate);
        } else {
            cout << "Status: Not Returned" << endl;
            cout << "Days Overdue: " << getDaysOverdue() << endl;
        }
    }
    
    int getMemberId() const { return memberId; }
    int getBookId() const { return bookId; }
    bool getIsReturned() const { return isReturned; }
};

int Transaction::transactionCounter = 0;

// ==================== LIBRARY CLASS ====================

class Library {
private:
    map<int, Book> books;
    map<int, Member> members;
    vector<Transaction> transactions;
    
    int nextBookId;
    int nextMemberId;

public:
    Library() : nextBookId(1001), nextMemberId(1) {}
    
    // Add book
    void addBook(string title, string author, string isbn) {
        Book book(nextBookId++, title, author, isbn);
        books[book.getBookId()] = book;
        cout << "\n Book added successfully! Book ID: " << book.getBookId() << endl;
    }
    
    // Add member
    void addMember(string name, string contact) {
        Member member(name, nextMemberId++, contact);
        members[member.getId()] = member;
        cout << "\n Member registered successfully! Member ID: " << member.getId() << endl;
    }
    
    // Issue book
    void issueBook(int memberId, int bookId) {
        if (members.find(memberId) == members.end()) {
            cout << "\n Member not found!" << endl;
            return;
        }
        
        if (books.find(bookId) == books.end()) {
            cout << "\n Book not found!" << endl;
            return;
        }
        
        Member& member = members[memberId];
        Book& book = books[bookId];
        
        if (!book.getAvailability()) {
            cout << "\n Book is currently borrowed!" << endl;
            return;
        }
        
        if (!member.canBorrow()) {
            cout << "\n Member has reached maximum borrowing limit!" << endl;
            return;
        }
        
        if (member.getFine() > 0) {
            cout << "\n Member has pending fine of $" << member.getFine() << endl;
            return;
        }
        
        // Issue the book
        book.setAvailability(false);
        book.setBorrowedBy(memberId);
        member.borrowBook(bookId);
        transactions.push_back(Transaction(memberId, bookId));
        
        cout << "\n Book issued successfully!" << endl;
        cout << "Member: " << member.getName() << endl;
        cout << "Book: " << book.getTitle() << endl;
        cout << "Return within 14 days to avoid fine." << endl;
    }
    
    // Return book
    void returnBook(int memberId, int bookId) {
        if (members.find(memberId) == members.end()) {
            cout << "\n Member not found!" << endl;
            return;
        }
        
        if (books.find(bookId) == books.end()) {
            cout << "\n Book not found!" << endl;
            return;
        }
        
        Member& member = members[memberId];
        Book& book = books[bookId];
        
        if (book.getAvailability() || book.getBorrowedBy() != memberId) {
            cout << "\n This book was not borrowed by this member!" << endl;
            return;
        }
        
        // Find transaction
        for (auto& trans : transactions) {
            if (trans.getMemberId() == memberId && trans.getBookId() == bookId && !trans.getIsReturned()) {
                trans.markReturned();
                
                int overdueDays = trans.getDaysOverdue();
                double fine = overdueDays * 1.0; // $1 per day
                
                book.setAvailability(true);
                book.setBorrowedBy(-1);
                member.returnBook(bookId);
                
                cout << "\n Book returned successfully!" << endl;
                if (overdueDays > 0) {
                    member.addFine(fine);
                    cout << "Overdue by " << overdueDays << " days. Fine: $" << fine << endl;
                }
                return;
            }
        }
    }
    
    // Search books
    void searchBooks(string query) {
        cout << "\n--- Search Results ---" << endl;
        bool found = false;
        
        transform(query.begin(), query.end(), query.begin(), ::tolower);
        
        for (auto& pair : books) {
            Book& book = pair.second;
            string title = book.getTitle();
            string author = book.getAuthor();
            transform(title.begin(), title.end(), title.begin(), ::tolower);
            transform(author.begin(), author.end(), author.begin(), ::tolower);
            
            if (title.find(query) != string::npos || author.find(query) != string::npos) {
                book.display();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No books found matching: " << query << endl;
        }
    }
    
    // Display all books
    void displayAllBooks() {
        if (books.empty()) {
            cout << "\nNo books in library." << endl;
            return;
        }
        
        cout << "\n========== ALL BOOKS ==========" << endl;
        for (auto& pair : books) {
            pair.second.display();
        }
    }
    
    // Display all members
    void displayAllMembers() {
        if (members.empty()) {
            cout << "\nNo members registered." << endl;
            return;
        }
        
        cout << "\n========== ALL MEMBERS ==========" << endl;
        for (auto& pair : members) {
            pair.second.display();
        }
    }
    
    // Pay fine
    void payFine(int memberId) {
        if (members.find(memberId) == members.end()) {
            cout << "\n Member not found!" << endl;
            return;
        }
        
        Member& member = members[memberId];
        double fine = member.getFine();
        
        if (fine == 0) {
            cout << "\n No pending fine!" << endl;
            return;
        }
        
        cout << "\nFine Amount: $" << fine << endl;
        cout << "Do you want to pay? (y/n): ";
        char choice;
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            member.clearFine();
            cout << " Fine paid successfully!" << endl;
        }
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    Library library;
    int choice;
 
    while (true) {
        cout << "\n\n========================================" << endl;
        cout << "   LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << "========================================" << endl;
        cout << "1.  Add Book" << endl;
        cout << "2.  Add Member" << endl;
        cout << "3.  Issue Book" << endl;
        cout << "4.  Return Book" << endl;
        cout << "5.  Search Books" << endl;
        cout << "6.  Display All Books" << endl;
        cout << "7.  Display All Members" << endl;
        cout << "8.  Pay Fine" << endl;
        cout << "9.  Exit" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                string title, author, isbn;
                cout << "\nEnter Book Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                cout << "Enter ISBN: ";
                getline(cin, isbn);
                library.addBook(title, author, isbn);
                break;
            }
            case 2: {
                string name, contact;
                cout << "\nEnter Member Name: ";
                getline(cin, name);
                cout << "Enter Contact: ";
                getline(cin, contact);
                library.addMember(name, contact);
                break;
            }
            case 3: {
                int memberId, bookId;
                cout << "\nEnter Member ID: ";
                cin >> memberId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.issueBook(memberId, bookId);
                break;
            }
            case 4: {
                int memberId, bookId;
                cout << "\nEnter Member ID: ";
                cin >> memberId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                library.returnBook(memberId, bookId);
                break;
            }
            case 5: {
                string query;
                cout << "\nEnter search query (title/author): ";
                getline(cin, query);
                library.searchBooks(query);
                break;
            }
            case 6: {
                library.displayAllBooks();
                break;
            }
            case 7: {
                library.displayAllMembers();
                break;
            }
            case 8: {
                int memberId;
                cout << "\nEnter Member ID: ";
                cin >> memberId;
                library.payFine(memberId);
                break;
            }
            case 9: {
                cout << "\nThank you for using Library Management System!" << endl;
                return 0;
            }
            default: {
                cout << "\n Invalid choice! Please try again." << endl;
            }
        }
    }
    
    return 0;
}