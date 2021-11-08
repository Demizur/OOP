#include <iostream>
#include <cmath> 
#include <math.h>
#include <fstream>
 
using namespace std;

double Z(double x, double a) {
    return pow((a * x * cos(3 * a) + exp(4 * x) * (x + a)), 0.2);
}

void ARYFM_VYR() {  
    cout << " Вычисление арифметического выражения вида:\n Z=(a*x*cos(3*a)+exp(4*x)*(x+a))^1/5\n ";
    const double cx = 5.121, ca = 2;
    double x, a;
    cout << "\n При x=5.121 и a=2 , выражение Z= " << Z(cx,ca) << "\n Теперь введите произвольные x и a через пробел\n";
    cin >> x >> a;
    cout << "\n При x= " << x << " и a= " << a << " ,выражение Z= " << Z(x,a) << "\n";
}

bool L(bool A, bool B, bool C, double K) {
    if ((A || B || C) && ((!(A && B)) && (!(A && C)) && (!(B && C))) && (K > 0)) {
        return 1;
    }
    else {
        return 0;
    }
}
void LOGIK_VYR() {
    cout << " Вычисление логического выражения, которое должно быть верно при условии, что только\n одна из переменных А, В и С верна и переменная К больше 0.\n";
    const bool cA = 1, cB = 0, cC = 0;
    bool A, B, C;
    const double cK = 5;
    double K;
    cout << " При A=1, B=0, C=0, K=5, Логическое выражение L= " << L(cA,cB,cC,cK) << "\n Теперь введите А,В,С и К через пробелы. ( А,В,С могут принимать только значения 0 или 1)  \n";
    cin >> A >> B >> C >> K;
    cout << "\n При A=" << A <<", B=" << B << ", C=" << C << ", K=" << K << ", Логическое выражение L= " << L(A, B, C, K) << "\n";
}

void RAZLOZ_FUNK() {
    cout << "Вычисление значения функции на основе разложения (в сходящийся ряд) с использованием оператора цикла while.\n";
    double a = 1, s = 0,x=0.5,e=1E-7;
    int i = 0;

        while ((abs(a)) >= e ) {
            a = pow(x,2*i+1)/(2*i+1);
            i++;
            s = s + a;
        }
        s = 2*s;

        cout <<"Сумма ряда ln((1 + x) / (1 - x))= "<< s << ", при x=0.5.\n";
        cout << "Численное решенение функции: " << (log((1 + x) / (1 - x))) << "\n";
}

void vivod(int i, int j, double **M) {
    for (int k = 0; i > k; k++) {
        for (int l = 0; j > l; l++) {
            cout << M[k][l] << " ";
        }
        cout << endl;
    }
}

int min_ind(int p, double** M_p);

void obrabotka(int i, int j, double** M) {
    int p=0;
    double** M_p = new double* [i*j];
    cout << "\n Массив из положительных элементов каждой четной строки и индексы элементов из исходного массива:\n";
    for (int k = 1; i > k; k=k+2) {
       
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
    cout << "\n Минимальный элемент сформированного массива и его индексы в исходном массиве:\n";
    int pm = min_ind(p,M_p);
    for (int k = 0; 3 > k; k++) {
        cout << " " << M_p[pm][k];
    }
    cout << endl;

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
     double **M =new double*[i];
     for (int k = 0; i > k; k++) {
         M[k] = new double[j];
     }
     for (int k = 0; i > k; k++) {
         for (int l = 0; j > l; l++) {
            file >> M[k][l];
         }   
     }

     vivod(i,j,M);
     obrabotka(i,j,M);
     for (int k = 0; i > k; k++) {
         delete []M[k];
     }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    cout << " Добро пожаловать в программу!\n Автор: Павлова Светлана,группа ПМ 4-1. \n Лабораторная работа №1 по ООП. \n \n";
    int v;
    do{
        cout << "\n Меню: \n 1- Вычисление арифметического выражения. \n 2- Вычисление логического выражения. \n 3- Вычисление суммы сходящегося ряда. \n 4- Работа с арифметическим динамическим массивом.\n 0- ВЫХОД.\n Выберите интересующую вас задачу:\n " ;
    cin >> v;
    cout << endl;
    switch (v) {
    case 1:
        ARYFM_VYR();
        break;
    case 2:
        LOGIK_VYR();
        break;
    case 3:
        RAZLOZ_FUNK();
        break;
    case 4:
        DYN_MASS();
        break;
    }
    } while (v != 0);
   
    
    
}


