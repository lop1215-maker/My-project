#include "Library.h"
#include <iostream>

void showMenu() {
    std::cout << "\n";
    std::cout << "=== БИБЛИОТЕКА ===\n";
    std::cout << "1. Просмотреть все книги\n";
    std::cout << "2. Просмотреть всех пользователей\n";
    std::cout << "3. Добавить новую книгу\n";
    std::cout << "4. Зарегистрировать пользователя\n";
    std::cout << "5. Выдать книгу пользователю\n";
    std::cout << "6. Принять книгу от пользователя\n";
    std::cout << "7. Поиск книги по ISBN\n";
    std::cout << "8. Просмотреть профиль пользователя\n";
    std::cout << "9. Сохранить данные в файл\n";
    std::cout << "10. Выход\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    Library library("data/library_data.txt");
    int choice;
    
    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(); // чистим буфер ввода
        
        if (choice == 1) {
            // просмотр книг
            library.displayAllBooks();
        }
        else if (choice == 2) {
            // просмотр пользователей
            library.displayAllUsers();
        }
        else if (choice == 3) {
            // добавить книгу
            std::string title, author, isbn;
            int year;
            
            std::cout << "Введите название книги: ";
            std::getline(std::cin, title);
            
            std::cout << "Введите автора: ";
            std::getline(std::cin, author);
            
            std::cout << "Введите год издания: ";
            std::cin >> year;
            std::cin.ignore();
            
            std::cout << "Введите ISBN: ";
            std::getline(std::cin, isbn);
            
            Book newBook(title, author, year, isbn);
            library.addBook(newBook);
            std::cout << "Книга добавлена!\n";
        }
        else if (choice == 4) {
            // зарегистрировать пользователя
            std::string name, userId;
            
            std::cout << "Введите фамилию пользователя: ";
            std::getline(std::cin, name);
            
            std::cout << "Введите ID пользователя (например, USR_001): ";
            std::getline(std::cin, userId);
            
            User newUser(name, userId);
            library.addUser(newUser);
            std::cout << "Пользователь зарегистрирован!\n";
        }
        else if (choice == 5) {
            // выдать книгу
            std::string userName, isbn;
            
            std::cout << "Введите фамилию пользователя: ";
            std::getline(std::cin, userName);
            
            std::cout << "Введите ISBN книги: ";
            std::getline(std::cin, isbn);
            
            library.borrowBook(userName, isbn);
        }
        else if (choice == 6) {
            // вернуть книгу
            std::string isbn;
            
            std::cout << "Введите ISBN книги: ";
            std::getline(std::cin, isbn);
            
            library.returnBook(isbn);
        }
        else if (choice == 7) {
            // поиск по ISBN
            std::string isbn;
            
            std::cout << "Введите ISBN для поиска: ";
            std::getline(std::cin, isbn);
            
            Book* book = library.findBookByISBN(isbn);
            if (book != NULL) {
                book->displayInfo();
            } else {
                std::cout << "\nКнига не найдена.\n\n";
            }
        }
        else if (choice == 8) {
            // профиль пользователя
            std::string name;
            
            std::cout << "Введите фамилию пользователя: ";
            std::getline(std::cin, name);
            
            User* user = library.findUserByName(name);
            if (user != NULL) {
                user->displayProfile();
            } else {
                std::cout << "\nПользователь не найден.\n\n";
            }
        }
        else if (choice == 9) {
            // сохранить
            library.saveToFile();
            std::cout << "Данные сохранены!\n";
        }
        else if (choice == 10) {
            // выход
            std::cout << "До встречи!\n";
            break;
        }
        else {
            std::cout << "Неверный выбор!\n";
        }
    }
    
    return 0;
}
