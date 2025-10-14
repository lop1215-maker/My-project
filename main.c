#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book{
    char name[101];
    char author[51];
    int year;
    float scale;
};

struct Book library[1000];
int bookCount = 0;
const char* filename = "books.txt";

void clearInputBuffer()
{
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF);
}

void addBook()
{
    if (bookCount >= 1000)
    {
        printf("Достигнут лимит в 1000 книг!\n");
        return;
    }
    printf("Введите название книги: \n");
    // scanf(" %100[^\n]", library[bookCount].name);
    // clearInputBuffer();

    printf("Введите год прочтения: \n");
    // while (scanf("%d", &library[bookCount].year) != 1)
    {
        printf("Ошибка, введите число: \n");
        clearInputBuffer();
    }
    clearInputBuffer();

    printf("Введите оценку (0-10): \n");
    while (scanf("%f", &library[bookCount].scale) != 1 ||
        library[bookCount].scale < 0 ||
        library[bookCount].scale > 10)
        {
            printf("Ошибка! Введите число от 0 до 10: \n");
            clearInputBuffer();
        }
        clearInputBuffer();

        bookCount++;
        printf("Книга добавлена!\n\n");
}

void showBooks()
{
    if (bookCount == 0)
    {
        printf("Библиотека пуста!\n\n");
        return;
    }

    printf("\n=== Ваша библиотека ===\n");
    for (int i = 0; i < bookCount; i ++)
    {
        printf("%d. %s - %s (%d год прочтения) - оценка: %.1f\n",
               i + 1,
               library[i].name,
               library[i].author,
               library[i].year,
               library[i].scale);
    }
}

void showStaticstics()
{
    if (bookCount == 0)
    {
        printf("Библиотека пуста! Нет данных для статистики.\n\n");
        return;
    }

    printf("\n=== Статистика ===\n");

    printf("Количество прочитанных книг: %d\n", bookCount);

    float totalScore = 0;
    for (int i = 0; i < bookCount; i++)
    {
        totalScore += library[i].scale;
    }
    float averageScore = totalScore / bookCount;
    printf("Средняя оценка: %f\n", averageScore);

    float maxScore = -1;
    int bestBookIndex = -1;
    for (int i = 0; i < bookCount; i++)
    {
        if (library[i].scale > maxScore)
        {
            maxScore = library[i].scale;
            bestBookIndex = i;
        }
    }

    if (bestBookIndex != -1)
    {
        printf("Самая высокооценнёная кнгиа: \n");
        printf(" %s - %s (оценка: %f)\n",
               library[bestBookIndex].name,
               library[bestBookIndex].author,
               library[bestBookIndex].scale);
    }

    int currentYear = 2025;
    int currentYearBooks = 0;
    for (int i = 0; i < bookCount; i++)
    {
        if (library[i].year == currentYear)
        {
            currentYearBooks++;
        }
    }
    printf("Книг прочитано в этом году(%d): %d\n", currentYear, currentYearBooks);
}


int showMenu()
{
    int choice;
    printf("=== МЕНЮ ===\n");
    printf("1. Добавить книгу \n");
    printf("2. Показать все книги\n");
    printf("3. Показать статистику\n");
    printf("4. Выйти\n");
    printf("Выберите: \n");

    scanf("%d", &choice);
    clearInputBuffer();
    return choice;
}

int main()
{
    printf("=== Трекер книг ===\n");

    while(1)
    {
        int choice = showMenu();

        switch(choice)
        {
            case 1:
                addBook();
                break;
            case 2:
                showBooks();
                break;
            case 3:
                showStaticstics();
                break;
            case 4:
                printf("Выход из программы. \n");
                return 0;
            default:
                printf("Неверный выбор! Введите 1-4. \n\n");

        } 
    }
    return 0;
}