#include "Library.h"
#include <iostream>
#include <fstream>
#include <sstream>

Library::Library(std::string dataFilePath) {
    dataFile = dataFilePath;
    loadFromFile();
}

void Library::addBook(Book book) {
    // проверка уникальности ISBN
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == book.getIsbn()) {
            std::cout << "ОШИБКА: Книга с таким ISBN уже существует!\n";
            return;
        }
    }
    books.push_back(book);
}

void Library::addUser(User user) {
    // проверка уникальности ID
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUserId() == user.getUserId()) {
            std::cout << "ОШИБКА: Пользователь с таким ID уже существует!\n";
            return;
        }
    }
    users.push_back(user);
}

Book* Library::findBookByISBN(std::string isbn) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getIsbn() == isbn) {
            return &books[i];
        }
    }
    return NULL; // nullptr в старом стиле
}

User* Library::findUserByName(std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return &users[i];
        }
    }
    return NULL;
}

void Library::borrowBook(std::string userName, std::string isbn) {
    // ищем пользователя
    User* user = findUserByName(userName);
    if (user == NULL) {
        std::cout << "ОШИБКА: Пользователь не найден!\n";
        return;
    }
    
    // проверка лимита
    if (user->canBorrowMore() == false) {
        std::cout << "ОШИБКА: Пользователь достиг лимита книг!\n";
        return;
    }
    
    // ищем книгу
    Book* book = findBookByISBN(isbn);
    if (book == NULL) {
        std::cout << "ОШИБКА: Книга не найдена!\n";
        return;
    }
    
    // выдаём
    book->borrowBook(userName);
    user->addBook(isbn);
    std::cout << "Успешно!\n";
}

void Library::returnBook(std::string isbn) {
    // ищем книгу
    Book* book = findBookByISBN(isbn);
    if (book == NULL) {
        std::cout << "ОШИБКА: Книга не найдена!\n";
        return;
    }
    
    if (book->getAvailable()) {
        std::cout << "ОШИБКА: Эта книга не была выдана!\n";
        return;
    }
    
    // получаем, кто её брал
    std::string borrowedBy = book->getBorrowedBy();
    
    // возвращаем
    book->returnBook();
    
    // удаляем из списка пользователя
    User* user = findUserByName(borrowedBy);
    if (user != NULL) {
        user->removeBook(isbn);
    }
    
    std::cout << "Успешно!\n";
}

void Library::displayAllBooks() {
    if (books.size() == 0) {
        std::cout << "\nБиблиотека пуста\n\n";
        return;
    }
    
    std::cout << "\n=== ВСЕ КНИГИ В БИБЛИОТЕКЕ ===\n";
    
    for (int i = 0; i < books.size(); i++) {
        books[i].displayInfo();
    }
}

void Library::displayAllUsers() {
    if (users.size() == 0) {
        std::cout << "\nНет зарегистрированных пользователей\n\n";
        return;
    }
    
    std::cout << "\n=== ВСЕ ПОЛЬЗОВАТЕЛИ ===\n";
    
    for (int i = 0; i < users.size(); i++) {
        users[i].displayProfile();
    }
}

void Library::saveToFile() {
    std::ofstream file(dataFile);
    
    // сохраняем книги
    for (int i = 0; i < books.size(); i++) {
        file << "BOOK\n";
        file << "Title: " << books[i].getTitle() << "\n";
        file << "Author: " << books[i].getAuthor() << "\n";
        file << "Year: " << books[i].getYear() << "\n";
        file << "ISBN: " << books[i].getIsbn() << "\n";
        
        if (books[i].getAvailable()) {
            file << "Available: yes\n";
        } else {
            file << "Available: no\n";
        }
        
        file << "BorrowedBy: " << books[i].getBorrowedBy() << "\n";
    }
    
    file << "---USERS---\n";
    
    // сохраняем пользователей
    for (int i = 0; i < users.size(); i++) {
        file << "USER\n";
        file << "Name: " << users[i].getName() << "\n";
        file << "UserID: " << users[i].getUserId() << "\n";
        
        file << "BorrowedBooks: ";
        std::vector<std::string> bookList = users[i].getBorrowedBooks();
        for (int j = 0; j < bookList.size(); j++) {
            file << bookList[j];
            if (j < bookList.size() - 1) {
                file << "|";
            }
        }
        file << "\n";
        
        file << "MaxBooks: " << users[i].getMaxBooksAllowed() << "\n";
    }
    
    file.close();
}

void Library::loadFromFile() {
    std::ifstream file(dataFile);
    
    if (!file.is_open()) {
        // файла нет - это норма при первом запуске
        return;
    }
    
    std::string line;
    bool isUserSection = false;
    
    while (std::getline(file, line)) {
        // ищем маркер переключения на секцию пользователей
        if (line == "---USERS---") {
            isUserSection = true;
            continue;
        }
        
        if (line == "BOOK" && !isUserSection) {
            std::string title, author, isbn;
            int year;
            std::string availableStr;
            
            std::getline(file, line); // Title: ...
            title = line.substr(7);
            
            std::getline(file, line); // Author: ...
            author = line.substr(8);
            
            std::getline(file, line); // Year: ...
            year = std::stoi(line.substr(6));
            
            std::getline(file, line); // ISBN: ...
            isbn = line.substr(6);
            
            std::getline(file, line); // Available: ...
            availableStr = line.substr(11);
            
            std::getline(file, line); // BorrowedBy: ...
            std::string borrowedBy = line.substr(11);
            
            // создаём и добавляем книгу
            Book book(title, author, year, isbn);
            
            // если была выдана, восстанавливаем
            if (availableStr != "yes") {
                book.borrowBook(borrowedBy);
            }
            
            books.push_back(book);
        }
        
        if (line == "USER" && isUserSection) {
            std::string name, userId;
            
            std::getline(file, line); // Name: ...
            name = line.substr(6);
            
            std::getline(file, line); // UserID: ...
            userId = line.substr(8);
            
            std::getline(file, line); // BorrowedBooks: ...
            std::string booksStr = line.substr(15);
            
            std::getline(file, line); // MaxBooks: ...
            
            // создаём пользователя
            User user(name, userId);
            
            // добавляем его книги (если были)
            if (booksStr.size() > 0) {
                std::stringstream ss(booksStr);
                std::string isbn;
                while (std::getline(ss, isbn, '|')) {
                    user.addBook(isbn);
                }
            }
            
            users.push_back(user);
        }
    }
    
    file.close();
}
