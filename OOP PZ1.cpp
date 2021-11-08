#include <iostream>
using namespace std;

template <class T> class VYCH // шаблон класса
{
private:
    double e = 1E-7;
    T x;

public: 
    VYCH(T _x) : x(_x){};                           // конструктор
    ~VYCH() { cout << "\n Уничтожаем объект\n"; }; // деструктор 

    void message() // функция (метод класса) выводящая сообщение на экран
    {

        cout << "log((1 + x) / (1 - x)): " << sum(x, e) << ", при x= " << x << endl;
    }

    double sum(double x, double e) {
        int i = 0;
        double a = 1, s = 0;
        while ((abs(a)) >= e) {
            a = pow(x, 2 * i + 1) / (2 * i + 1);
            i++;
            s = s + a;
        }
        s = 2 * s;
        return s;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");      // установка локали
    cout << "\n Павлова Светлана \n ПМ4-1 \n Практическое занятие \n Вариант - 8 \n";
    VYCH<double> obj2(0.7);        // объявление объекта с параметром
    obj2.message();
}
