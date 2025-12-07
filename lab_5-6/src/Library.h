#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "User.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;
    std::vector<User> users;
    std::string dataFile;

public:
    // конструктор
    Library(std::string dataFilePath);
    
    // методы
    void addBook(Book book);
    void addUser(User user);
    void borrowBook(std::string userName, std::string isbn);
    void returnBook(std::string isbn);
    
    Book* findBookByISBN(std::string isbn);
    User* findUserByName(std::string name);
    
    void displayAllBooks();
    void displayAllUsers();
    void saveToFile();
    void loadFromFile();
};

#endif
