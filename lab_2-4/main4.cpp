#include <iostream> /*Подключаем библиотеку ввода/вывода*/
using namespace std; /*Используем стандартное пространство имён*/

/*Функция для ввода значений в двухмерный массив*/
void inputData(float** p, int d, int h)
{
    for (int i = 0; i < d; i++) /*Цикл по дням*/
    {
        cout << "Day " << (i + 1) << ": ";
        
        for (int j = 0; j < h; j++) /*Цикл по измерениям в дне*/
        {
            cin >> *(*(p + i) + j); /*Записываем значения каждого дня*/
        }
    }
}

/*Функция расчёта средней температуры за день*/
float dayAverage(float* row, int h)
{
    float sum = 0;
    
    for (int i = 0; i < h; i++)
    {
        sum += *(row + i);
    }
    
    return sum / h;
}

/*Функция расчёта средней температуры за все дни*/
float overallAverage(float** p, int d, int h)
{
    float total = 0; /*Общая температура за все дни*/
    
    for (int i = 0; i < d; i++)
    {
        total += dayAverage(*(p + i), h);
    }
    return total / d;
}

/*Функция нахождения дней, в которых температура выше средней*/
void showHotDays(float** p, int d, int h)
{
    float overall = overallAverage(p, d, h);
    float* dayAverages = new float[d];

    for (int i = 0; i < d; i++)
    {
        dayAverages[i] = dayAverage(*(p + i), h);
    }

    cout << "\nWarm days: ";
    bool found = false;

    for (int i = 0; i < d; i++)
    {
        if (dayAverages[i] > overall)
        {
            cout << "\nDay " << (i + 1) << " (average = " << dayAverages[i] << ")\n";
            found = true;
        }
    }
    if (!found)
    {
        cout << "There are no warm days\n";
    }
    delete[] dayAverages;
}

int main()
{
    int d, h; /*Кол-во дней и значений в каждом дне*/

    cout << "Enter the number of days: "; /*Введите кол-во дней*/
    cin >> d;
    cout << "Enter the number of measurements per day: "; /*Введите кол-во значений в дне*/
    cin >> h;

    float** data = new float*[d]; /*Создание двумерного массива*/
    
    for (int i = 0; i < d; i++) /*Заполняем массив другими массивами*/
    {
        *(data + i) = new float[h];
    }

    inputData(data, d, h); /*Заполняем значения массива*/

    float overall = overallAverage(data, d, h); /*Находим значение средней температуры за все дни*/

    cout << "Overall average temperature: " << overall << endl;

    showHotDays(data, d, h);

    for (int i = 0; i < d; i++) /*Удаляем наши массивы измерений*/
    {
        delete[] *(data + i);
    }
    delete[] data; /*Удаляем массив указателей*/

    return 0;
}
