#include <iostream> /*Подкючаем библиотеку ввода/вывода*/

using namespace std; /*Используем стандартное пространство имён*/

/*Функция для ввода данных в массив*/
void inputData(float* p, int n) 
{
    cout << "Enter values: "; /*Выводим сообщение пользователю*/
    for (int i = 0; i < n; i++) /*Цикл по всем элементам массива*/
    {
        cin >> *(p + i); /*Читаем значение и сохраняем в массив через указатель*/
    }
}

/*Функция для вычисления среднего значения*/
float average(const float* p, int n)
{
    float sum = 0; /*Переменная для хранения суммы всех элементов*/
    for (int i = 0; i < n; i ++) /*Цикл по всем элементам массива*/
    {
        sum += *(p + i); /*Прибавляем текущий элемент к сумме*/
    }
    return sum / n; /*Возвращаем среднее значение*/
}

/*Функция для нахождения минимального элемента*/
float minValue(const float* p, int n)
{
    float  minVal = *(p + 0); /*Предполагаем, что минимальный элемент - первый*/
    for (int i = 1; i < n; i ++) /*Пропускаем первый элемент в массиве*/
    {
        if (*(p + i) < minVal) /*Сравниваем текущий элемент с минимальным*/
        {
            minVal = *(p + i); /*Обновляем минимальный*/
        }
    }
    return minVal;
}

/*Функция на нахождение максимального элемента*/
float maxValue(const float* p, int n)
{
    float maxVal = *(p + 0); /*Предполагаем, что первый элемент - максимальный*/
    for (int i = 1; i < n; i++) /*Пропускаем первый элемент в массиве*/
    {
        if (*(p + i) > maxVal) /*Сравниваем текущий с максимальным*/
        {
            maxVal = *(p + i); /*Обновляем максимальный элемент*/
        }
    }
    return maxVal;
}

/*Функция для фильтраций значений выше среднего*/
float* filterAboveAverage(float* p, int n, int& newCount)
{
    float avg = average(p, n); /*Вычисляем среднее значение массива*/
    newCount = 0; /*Счётчик для подходящих чисел*/
    
    float* newArray = new float[newCount]; /*Новый динамический массив для результатов*/
    int index = 0; /*Индекс для нового массива*/

    for (int i = 0; i < n; i++) /*Цикл по всем элементам*/
    {
        if (*(p + i) > avg) /*Если текущий больше среднего*/
        {
            newCount++;
            *(newArray + index) = *(p + i);
            index++;
        }
    }
    return newArray;
}

int main()
{
    cout << "=== Sector analysis ===" << endl;
    
    int n;

    cout << "Enter the number of dimensions: ";
    cin >> n;

    float* data = new float[n];

    inputData(data, n);

    float avg = average(data, n);
    float minVal = minValue(data, n);
    float maxVal = maxValue(data, n);

    cout << "\nAverage value: " << avg << endl;
    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;

    int newCount;
    float* aboveAverage = filterAboveAverage(data, n, newCount);

    cout << "Above average value: " << endl;
    for (int i = 0; i < newCount; i++)
    {
        cout << *(aboveAverage + i) << " ";
    }
    cout << endl;

    delete[] data;
    delete[] aboveAverage;

    return 0;
}

