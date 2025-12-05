#include <iostream> 

using namespace std; 

void inputData(float* p, int n) 
{
    cout << "Enter values: "; 
    for (int i = 0; i < n; i++) 
    {
        cin >> *(p + i); 
    }
}


float average(const float* p, int n)
{
    float sum = 0;
    for (int i = 0; i < n; i ++)
    {
        sum += *(p + i);
    }
    return sum / n;
}


float minValue(const float* p, int n)
{
    float  minVal = *(p + 0); 
    for (int i = 1; i < n; i ++) 
    {
        if (*(p + i) < minVal) 
        {
            minVal = *(p + i); 
        }
    }
    return minVal;
}


float maxValue(const float* p, int n)
{
    float maxVal = *(p + 0); 
    for (int i = 1; i < n; i++) 
    {
        if (*(p + i) > maxVal) 
        {
            maxVal = *(p + i); 
        }
    }
    return maxVal;
}


float* filterAboveAverage(float* p, int n, int& newCount)
{
    float avg = average(p, n); 
    newCount = 0; 
    
    for (int i = 0; i < n; i++) 
    {
        if (*(p + i) > avg) 
        {
            newCount++;
        }
    }
    
    float* newArray = new float[newCount]; 
    int index = 0; 
    
    for (int i = 0; i < n; i++)
    {
        if (*(p + i) > avg)
        {
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

