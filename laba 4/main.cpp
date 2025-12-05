#include <iostream>

using namespace std;

float dayAverage(float* row, int h);
float overallAverage(float** p, int d, int h);
void showHotDays(float** p, int d, int h);

int main() {
    int days, h;
    cout << "=== Анализ сенсора ===\nВведите количество дней: ";
    cin >> days;
    while (days > 30)
    {
        cout << "Количество дней не должно превышать 30. Введите снова: ";
        cin >> days;
    }
    
    cout << "Введите количество измерений в дне: ";
    cin >> h;
    while (h > 24)
    {
        cout << "Количество измерений не должно превышать 24. Введите снова: ";
        cin >> h;
    }

    float** data = new float*[days];
    for (int i = 0; i < days; i++) {
        *(data + i) = new float[h];
    }

    for (int i = 0; i < days; i++) {
        cout << "День " << i + 1 << ": ";
        for (int j = 0; j < h; j++) {
            cin >> *(*(data + i) + j);
        }
    }   

    cout << "Общая средняя температура: " << overallAverage(data, days, h) << endl << endl;
    showHotDays(data, days, h);

    for (int i = 0; i < days; i++) {
        delete[] data[i];
    }
    delete[] data;
}


float overallAverage(float** p, int d, int h) {    
    float sum = 0;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < h; j++) {
            sum += *(*(p + i) + j);
        }
    }
    return sum / (d * h);
}

float dayAverage(float* row, int h){
    float sum = 0;
    for (int i = 0; i < h; i++) {
        sum += *(row + i);
    }
    return sum / h;
}

void showHotDays(float** p, int d, int h){
    float overallAvg = overallAverage(p, d, h);
    cout << "Дни с температурой выше общей средней (" << overallAvg << "):\n";
    for (int i = 0; i < d; i++) {
        float dayAvg = dayAverage(*(p + i), h);
        if (dayAvg > overallAvg) {
            cout << "День " << i + 1 << " со средней температурой " << dayAvg << endl;
        }
    }
}