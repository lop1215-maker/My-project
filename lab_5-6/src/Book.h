#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isAvailable;
    std::string borrowedBy;

public:
    // конструктор
    Book(std::string t, std::string a, int y, std::string i);
    
    // геттеры - просто возвращаем значения
    std::string getTitle();
    std::string getAuthor();
    int getYear();
    std::string getIsbn();
    bool getAvailable();
    std::string getBorrowedBy();
    
    // методы для операций
    void borrowBook(std::string userName);
    void returnBook();
    void displayInfo();
};

#endif
