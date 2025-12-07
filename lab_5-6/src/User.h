#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string name;
    std::string userId;
    std::vector<std::string> borrowedBooks;
    int maxBooksAllowed;

public:
    // конструктор
    User(std::string n, std::string id);
    
    // геттеры
    std::string getName();
    std::string getUserId();
    std::vector<std::string> getBorrowedBooks();
    int getMaxBooksAllowed();
    
    // методы
    bool canBorrowMore();
    void addBook(std::string isbn);
    void removeBook(std::string isbn);
    void displayProfile();
};

#endif
