#include "Book.h"
#include <iostream>
#include <ctime>

Book::Book(std::string t, std::string a, int y, std::string i) {
    title = t;
    author = a;
    year = y;
    isbn = i;
    isAvailable = true;
    borrowedBy = "";
    
    // простая проверка года
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int currentYear = 1900 + timeinfo->tm_year;
    
    if (year < 1450 || year > currentYear) {
        std::cout << "ОШИБКА: Неверный год издания!\n";
    }
}

std::string Book::getTitle() {
    return title;
}

std::string Book::getAuthor() {
    return author;
}

int Book::getYear() {
    return year;
}

std::string Book::getIsbn() {
    return isbn;
}

bool Book::getAvailable() {
    return isAvailable;
}

std::string Book::getBorrowedBy() {
    return borrowedBy;
}

void Book::borrowBook(std::string userName) {
    if (isAvailable == false) {
        std::cout << "ОШИБКА: Книга уже выдана!\n";
        return;
    }
    
    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook() {
    if (isAvailable == true) {
        std::cout << "ОШИБКА: Эта книга не была выдана!\n";
        return;
    }
    
    isAvailable = true;
    borrowedBy = "";
}

void Book::displayInfo() {
    std::cout << "\n--- Информация о книге ---\n";
    std::cout << "Название: " << title << "\n";
    std::cout << "Автор: " << author << "\n";
    std::cout << "Год: " << year << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    
    if (isAvailable) {
        std::cout << "Статус: ДОСТУПНА\n";
    } else {
        std::cout << "Статус: ВЫДАНА (" << borrowedBy << ")\n";
    }
    std::cout << "\n";
}
