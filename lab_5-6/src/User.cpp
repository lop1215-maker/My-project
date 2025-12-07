#include "User.h"
#include <iostream>

User::User(std::string n, std::string id) {
    name = n;
    userId = id;
    maxBooksAllowed = 3;
}

std::string User::getName() {
    return name;
}

std::string User::getUserId() {
    return userId;
}

std::vector<std::string> User::getBorrowedBooks() {
    return borrowedBooks;
}

int User::getMaxBooksAllowed() {
    return maxBooksAllowed;
}

bool User::canBorrowMore() {
    if (borrowedBooks.size() < 3) {
        return true;
    }
    return false;
}

void User::addBook(std::string isbn) {
    // проверка, не взял ли уже
    for (int i = 0; i < borrowedBooks.size(); i++) {
        if (borrowedBooks[i] == isbn) {
            std::cout << "ОШИБКА: Пользователь уже взял эту книгу!\n";
            return;
        }
    }
    
    borrowedBooks.push_back(isbn);
}

void User::removeBook(std::string isbn) {
    int idx = -1;
    
    // ищем индекс книги
    for (int i = 0; i < borrowedBooks.size(); i++) {
        if (borrowedBooks[i] == isbn) {
            idx = i;
            break;
        }
    }
    
    if (idx == -1) {
        std::cout << "ОШИБКА: Пользователь не брал эту книгу!\n";
        return;
    }
    
    // удаляем из вектора
    borrowedBooks.erase(borrowedBooks.begin() + idx);
}

void User::displayProfile() {
    std::cout << "\n--- Профиль пользователя ---\n";
    std::cout << "Фамилия: " << name << "\n";
    std::cout << "ID: " << userId << "\n";
    std::cout << "Взято книг: " << borrowedBooks.size() << "/" 
              << maxBooksAllowed << "\n";
    
    if (borrowedBooks.size() == 0) {
        std::cout << "Книги не взяты\n";
    } else {
        std::cout << "ISBN взятых книг:\n";
        for (int i = 0; i < borrowedBooks.size(); i++) {
            std::cout << "  - " << borrowedBooks[i] << "\n";
        }
    }
    std::cout << "\n";
}
