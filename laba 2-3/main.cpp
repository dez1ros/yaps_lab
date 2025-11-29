#include <iostream>

using namespace std;

// new 
void inputData(float* p, int n);
float average(const float* p, int n);
float minValue(const float* p, int n);
float maxValue(const float* p, int n);
float* filterAboveAverage(float* p, int n, int& newCount);

int main() {
    int n;
    cout << "=== Анализ сенсора ===\nВведите количество измерений: ";
    cin >> n;
    float* data = new float[n];
    
    inputData(data, n);

    cout << "Среднее значение: " << average(data, n) << endl;
    cout << "Минимальное значение: " << minValue(data, n) << endl;
    cout << "Максимальное значение: " << maxValue(data, n) << endl;

    int newCount = n;
    
    float* newData = filterAboveAverage(data, n, newCount);

    cout << "Значения выше среднего: " << endl;
    for (int i = 0; i < newCount; i++) {
        cout << *(newData + i) << " ";
    }
    cout << endl;

    delete[] data;
    delete[] newData;
}

void inputData(float* p, int n){
    cout << "Введите измерения:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> *(p + i);
    }
}

float average(const float* p, int n){
    float sum = 0;
        
    for (int i = 0; i < n; i++) {
        sum += *(p + i);
    }

    return sum / n;
}

float minValue(const float* p, int n){
    float min_n = *p;
        
    for (int i = 0; i < n; i++) {
        if (*(p + i) < min_n){
            min_n = *(p + i);
        }
    }

    return min_n;
}

float maxValue(const float* p, int n){
    float max_n = *p;
        
    for (int i = 0; i < n; i++) {
        if (*(p + i) > max_n){
            max_n = *(p + i);
        }
    }

    return max_n;
}

float* filterAboveAverage(float* p, int n, int& newCount){
    float average_n = average(p, n);
    for (int i = 0; i < n; i++) {
        if (*(p + i) < average_n){
            newCount--;
        }
    }
    float* newData = new float[newCount];
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (*(p + i) > average_n){
            *(newData + index++) = *(p + i);
        }
    }
    return newData;
}       

