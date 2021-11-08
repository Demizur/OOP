#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
void vivod(int i, int j, double** M) {
    ofstream r_file("result.txt", ios::app);
    for (int k = 0; i > k; k++) {
        for (int l = 0; j > l; l++) {
            r_file  <<setw(10)<< M[k][l];
        }
        r_file << endl;
    }
}

int min_ind(int p, double** M_p);

void obrabotka(int i, int j, double** M) {
    ofstream r_file("result.txt", ios::app);
    int p = 0;
    double** M_p = new double* [i * j];
    r_file << "Массив из положительных элементов каждой четной строки и индексы элементов из исходного массива:"<<endl;
    for (int k = 1; i > k; k = k + 2) {

        for (int l = 0; j > l; l++) {
            if (M[k][l] > 0) {
                M_p[p] = new double[3];
                M_p[p][0] = M[k][l];
                M_p[p][1] = k;
                M_p[p][2] = l;
                p++;

            }

        }

    }
    vivod(p, 3, M_p);
    r_file << "Минимальный элемент сформированного массива и его индексы в исходном массиве:"<<endl;
    int pm = min_ind(p, M_p);
    for (int k = 0; 3 > k; k++) {
        r_file << setw(10) << M_p[pm][k];
    }
    r_file << endl;

    for (int k = 0; p > k; k++) {
        delete[]M_p[k];
    }
}

int min_ind(int p, double** M_p) {
    double min = 10000;
    int min_p = 0;
    for (int k = 0; p > k; k++) {
        if (min > M_p[k][0]) {
            min = M_p[k][0];
            min_p = k;
        }
    }

    return min_p;
}
void DYN_MASS() {
    cout << " Обработка динамического арифметического массива К(6,3). \n Введите число строк и столбцов через пробел.\n";
    int i, j;
    cin >> i >> j;
    cout << endl;
    ifstream file("mass.txt");
    ofstream r_file("result.txt", ios::trunc);
    r_file << "Обработка динамического арифметического массива К("<< i <<","<<j<<")"<<endl;
    double** M = new double* [i];
    for (int k = 0; i > k; k++) {
        M[k] = new double[j];
    }
    for (int k = 0; i > k; k++) {
        for (int l = 0; j > l; l++) {
            file >> M[k][l];
        }
    }

    vivod(i, j, M);
    obrabotka(i, j, M);
    for (int k = 0; i > k; k++) {
        delete[]M[k];
    }
}
int main()
{
    setlocale(LC_ALL, "RUS");
    DYN_MASS();
    cout << " Программа завершена. Результаты выведены в тексовый файл result.txt\n";
}

