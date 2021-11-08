#include <iostream>
using namespace std;
//Общий интерфейс для Заместителя и Объекта
class Interface {
public:
    virtual void Open(string password) const = 0;
};

// Реальный Объект
class RealSubject : public Interface {
public:
    void Open(string password) const override {
        cout << "Доступ разрешен\n";
    }
};

//Защитный Заместитель
class Proxy : public Interface {
private:
    RealSubject* real_subject_;
public:
    Proxy(RealSubject* real_subject) : real_subject_(new RealSubject(*real_subject)) {
    }

    void Open(string password) const override {
        if (password == "pass") {
            this->real_subject_->Open(password);
        }
        else {
            cout << "Доступ отклонен\n";

        }
    }
};



int main() {
    setlocale(LC_ALL, "rus");
    RealSubject* real_subject = new RealSubject;
    Proxy* proxy = new Proxy(real_subject);
    cout << "'Клиент вводит неправильный пароль':\n"; 
    proxy->Open("incorrect");

    cout << "\n'Клиент вводит правильный пароль':\n";
    proxy->Open("pass");
}