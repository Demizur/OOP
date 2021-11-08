
#include <iostream>
using namespace std;

class VYCH_1 // имя класса
{
private: // спецификатор доступа private
    int i = 0; 
    double a = 1, s = 0, x , e = 1E-7;
  
public: // спецификатор доступа public
    VYCH_1(); // конструктор без параметров
    VYCH_1(double cx); // конструктор с параметрами
    VYCH_1(double er,double cx);
    ~VYCH_1(); // деструктор без параметров
    inline double get_log() { return (log((1 + x) / (1 - x))); } // Встроенная функция

    void message() // функция (метод класса) выводящая сообщение на экран
    {
       
        cout << "WHILE: " << sum(x, e) << ", при x= " << x << endl;
    }

    void message2() // с постусловием
    {
        cout << "DO-WHILE: " << sum2(x, e) << ", при x= " << x << endl;
    }

    void message3() 
    {
        cout << "Численное решенение: " << get_log() << endl;  // Используется встроенная функция
    }

    void message4()
    {
        cout << "С рекурсией: " << rek(0,x,e) << endl;  
    }
    
    inline double sum(double x, double e) {
         i = 0, a = 1, s = 0;
         while ((abs(a)) >= e) {
        a = pow(x, 2 * i + 1) / (2 * i + 1);
        i++;
        s = s + a;
          }
        s = 2 * s;
         return s;
    }

    inline double sum2(double x, double e) {
        i = 0, a = 1, s = 0;
        do  {
            a = pow(x, 2 * i + 1) / (2 * i + 1);
            i++;
            s = s + a;
        } while ((abs(a)) >= e);
        s = 2 * s;
        return s;
    }

    double step(double x, int i){
        double st;
        if (x == 0) { st = 0; }
        else if (i == 0) { st = 1; }
        else if (i == 1) { st = (-1) * x * x; }
    else {
        st = (-1) * x *x * step(x, i - 1); // {рекурсия}
    }
        return st;
    }

    double fac(int i) {
        double f;
        if ((i == 0) || (i == 1)) {
            f = 1;
        }
        else { f = i * fac(i - 1); }    //рекурсия
        return f;
    }

     double rek(int i,double x, double e) { // Основная функция подсчета с помощью рекурсии
         double r;
         double mexp = step(x, i) / fac(i);
         if ((abs(mexp)) <= e) {
             r = mexp;
         }
         else {
             r = mexp + rek(i + 1, x, e);   //рекурсия
         }
        return s;
    }
  
}; 

// реализация конструкторов
// конструктор без параметров (конструктор по умолчанию)
VYCH_1::VYCH_1()
{
    x = 0.5;
}

// конструктор с параметром
VYCH_1::VYCH_1(double cx)
{
    x = cx;
}

// конструктор с параметром
VYCH_1::VYCH_1(double er,double cx)
{
    x = cx;
    e = er;
}

VYCH_1::~VYCH_1()
{
    cout << "\n Уничтожаем объект\n";
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus"); // установка локали
    cout << " Добро пожаловать в программу!\n Автор: Павлова Светлана,группа ПМ 4-1. \n Лабораторная работа №2 по ООП. \n \n";
    cout << " Вычисление значения функции на основе разложения (в сходящийся ряд) с использованием оператора цикла while.\n";

        cout << "\n1-Использовать конструктор без параметров. \n  ";

            VYCH_1 obj1; // объявление объекта (конструктор)
            obj1.message(); // вызов функции message класса VYCH_1

            cout << "\n2-Использовать конструктор с параметром. \n  Введите x (-1 < x < 1):\n";
            double cx;
            cin >> cx;
            VYCH_1 obj2(cx); // объявление объекта с параметром
            obj2.message();

            cout << "\n3-Вычислить N значений функции с заданным шагом и заданной точностью. \n 4-Вычислить N значений функции тремя способами с заданным шагом и заданной точностью с использованием массива объектов.\n";
            int n;
            double j, er;
            cout << " Введите начальное значение x:\n";
            cin >> cx;
            cout << " Введите n:\n";
            cin >> n;
            cout << " Введите размер шага j:\n";
            cin >> j;
            cout << " Введите точность er:\n";
            cin >> er;

            
            for (int i = 0; i < n; i++) {
                VYCH_1 obj3(er, cx);
                cout << " \n n =  " << (i+1) << " ,\n";
                obj3.message();
                obj3.message2();
                obj3.message3();
                obj3.message4();
                cx = cx+j;
            }

            cout << "\n 4-Вычислить N значений функции тремя способами с заданным шагом и заданной точностью с использованием массива объектов.\n";
            cout << " Введите начальное значение x:\n";
            cin >> cx;
            cout << " Введите n:\n";
            cin >> n;
            cout << " Введите размер шага j:\n";
            cin >> j;
            cout << " Введите точность er:\n";  
            cin >> er;
            VYCH_1* objarr = (VYCH_1*)operator new(sizeof(VYCH_1) * n);
     

            for (int i = 0; i < n; ++i) {
                new(&objarr[i]) VYCH_1(er, cx);
                 cout << "\n n = " << (i + 1) << " ,\n";
                 objarr[i].message();
                 objarr[i].message2();
                 objarr[i].message3();
                 objarr[i].message4();
                 cx = cx + j;
            }


}