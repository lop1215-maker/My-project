ФИО: Морозов Владислав Александрович
Группа: СКБ25
Подгруппа: 1


1. Задание:
Создать программу, в которой пользователь может вести учёт прочитанных книг. Программа должна уметь:
1.	Добавлять информацию о книге:
   o Название (до 100 символов),
   o Автор (до 50 символов),
   o Год прочтения,
   o Оценка по 10-балльной шкале (float).
 2. Сохранять данные в файл books.txt.
 3. Загружать данные из файла при запуске.
 4. Показывать список всех книг.
 5. Показывать статистику:
    o Количество прочитанных книг;
    o Средняя оценка;
    o Самая высоко оценённая книга.


2.	 Описание алгоритма:

#inlude <stdio.h> - заголовочный файл ввода/вывода

#include <stdlib.h> - стандартная библиотека языка С

Структура “struct Book” создаёт массив, состоящий из 4 переменных:
-Имя книги (взяли 101, чтобы зарезервировать последний элемент сроки как \0)
-Имя автора (логика аналогична предыдущей переменной)
-Год прочтения 
-Оценка книги
Структура “struct Book library [1000]” создаёт массив из 1000 элементов  типа “struct Book”, чтобы мы могли работать с большим объёмом данных.
       
Функция “void clearInputBuffer()” очищает буфер, если в нём оказался символ перевода строки или EOF. 

Функция “void addBook()” считывает пользовательские данные и записывает их в массив library, увеличивает счётчик книг, проверяет корректность ввода.

Функция “void showBooks()” отображает все прочитанные книги.

Функция “void showStatistics()” считывает статистику и показывает:
-Количество прочитанных книг
-Среднюю оценку
-Самую высоко оценённую книгу

Функция “int showMenu()” запускает пользовательское меню выбора действия

Функция “int main()” – вход в программу, основная функция программы, выполняющая связующую роль для всех функций и вывод для пользователя. 


3.	 Код:

4.	#include <stdio.h>
5.	#include <stdlib.h>
6.	#include <string.h>
7.	
8.	struct Book{
9.	    char name[101];
10.	    char author[51];
11.	    int year;
12.	    float scale;
13.	};
14.	
15.	struct Book library[1000];
16.	int bookCount = 0;


void clearInputBuffer()
17.	{
18.	    int c;
19.	    while ((c = getchar()) != '\n' && c != EOF);
20.	}
21.	
22.	void addBook()
23.	{
24.	    if (bookCount >= 1000)
25.	    {
26.	        printf("Достигнут лимит в 1000 книг!\n");
27.	        return;
28.	    }
29.	    printf("Введите название книги: \n");
30.	    scanf(" %100[^\n]", library[bookCount].name);
31.	    clearInputBuffer();
32.	
33.	    printf("Введите год прочтения: \n");
34.	    while (scanf("%d", &library[bookCount].year) != 1)
35.	    {
36.	        printf("Ошибка, введите число: \n");
37.	        clearInputBuffer();
38.	    }
39.	    clearInputBuffer();
40.	
41.	    printf("Введите оценку (0-10): \n");
42.	    while (scanf("%f", &library[bookCount].scale) != 1 ||
43.	        library[bookCount].scale < 0 ||
44.	        library[bookCount].scale > 10)
45.	        {
46.	            printf("Ошибка! Введите число от 0 до 10: \n");
47.	            clearInputBuffer();
48.	        }
49.	        clearInputBuffer();
50.	
51.	        bookCount++;
52.	        printf("Книга добавлена!\n");
53.	}
54.	
55.	void showBooks()
56.	{
57.	    if (bookCount == 0)
58.	    {
59.	        printf("Библиотека пуста!\n");
60.	        return;
61.	    }
62.	
63.	    printf("=== Ваша библиотека ===\n");
64.	    for (int i = 0; i < bookCount; i ++)
65.	    {
66.	        printf("%d. %s - %s (%d год прочтения) - оценка: %f\n",
67.	               i + 1,
68.	               library[i].name,
69.	               library[i].author,
70.	               library[i].year,
71.	               library[i].scale);
72.	    }
73.	}
74.	
75.	void showStaticstics()
76.	{
77.	    if (bookCount == 0)
78.	    {
79.	        printf("Библиотека пуста! Нет данных для статистики.\n");
80.	        return;
81.	    }
82.	
83.	    printf("=== Статистика ===\n");
84.	
85.	    printf("Количество прочитанных книг: %d\n", bookCount);
86.	
87.	    float totalScore = 0;
88.	    for (int i = 0; i < bookCount; i++)
89.	    {
90.	        totalScore += library[i].scale;
91.	    }
92.	    float averageScore = totalScore / bookCount;
93.	    printf("Средняя оценка: %f\n", averageScore);
94.	
95.	    float maxScore = -1;
96.	    int bestBookIndex = -1;
97.	    for (int i = 0; i < bookCount; i++)
98.	    {
99.	        if (library[i].scale > maxScore)
100.	        {
101.	            maxScore = library[i].scale;
102.	            bestBookIndex = i;
103.	        }
104.	    }
105.	
106.	    if (bestBookIndex != -1)
107.	    {
108.	        printf("Самая высокооценнёная кнгиа: \n");
109.	        printf(" %s - %s (оценка: %f)\n",
110.	               library[bestBookIndex].name,
111.	               library[bestBookIndex].author,
112.	               library[bestBookIndex].scale);
113.	    }
114.	
115.	    int currentYear = 2025;
116.	    int currentYearBooks = 0;
117.	    for (int i = 0; i < bookCount; i++)
118.	    {
119.	        if (library[i].year == currentYear)
120.	        {
121.	            currentYearBooks++;
122.	        }
123.	    }
124.	    printf("Книг прочитано в этом году(%d): %d\n", currentYear, currentYearBooks);
125.	}
126.	
127.	int showMenu()
128.	{
129.	    int choice;
130.	    printf("=== МЕНЮ ===\n");
131.	    printf("1. Добавить книгу \n");
132.	    printf("2. Показать все книги\n");
133.	    printf("3. Показать статистику\n");
134.	    printf("4. Выйти\n");
135.	    printf("Выберите: \n");
136.	
137.	    scanf("%d", &choice);
138.	    clearInputBuffer();
139.	    return choice;
140.	}
141.	
142.	int main()
143.	{
144.	    printf("=== Трекер книг ===\n");
145.	
146.	    while(1)
147.	    {
148.	        int choice = showMenu();
149.	
150.	        switch(choice)
151.	        {
152.	            case 1:
153.	                addBook();
154.	                break;
155.	            case 2:
156.	                showBooks();
157.	                break;
158.	            case 3:
159.	                showStaticstics();
160.	                break;
161.	            case 4:
162.	                printf("Выход из программы. \n");
163.	                return 0;
164.	            default:
165.	                printf("Неверный выбор! Введите 1-4. \n");
166.	
167.	        } 
168.	    }
169.	    return 0;
170.	}

4.	 Ссылка на репозиторий: lop1215-maker/My-project
5.	 Вывод:
Написал программу на C, научился пользоваться заголовочными файлами и разными типами данных, научился пользоваться github.



