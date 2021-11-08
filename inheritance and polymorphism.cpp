#include <iostream>
#include <string.h>
#include <iomanip>

using namespace std;
    // Базовый класс транспорта
    class Transport
    {
    public:

        Transport()
        {   
            trip_no = "NO NUMBER";
            time_depart = 0;
            time_arrive = 0;
        };
        Transport(string t_no, int t_dep ,int t_arr)
        {
            this->trip_no = t_no;
            this->time_depart = t_dep;
            this->time_arrive = t_arr;
        }
        virtual ~Transport(){}
        virtual void Show() = 0;
        virtual double Speed() = 0;

    protected:
        string trip_no;          // номер рейса
        int time_depart;        // время отправления
        int time_arrive;       // время прибытия
    };
    // Базовый класс места 
    class Destination
    {
    public:

        Destination()
        {
            destination_name = "NO NAME";
            road_lenght = 0;

        };
        Destination(string d_name, double r_l )
        {
            this->destination_name = d_name;
            this->road_lenght = r_l;

        }
        virtual ~Destination() {}

    protected:
        string destination_name;  // название пункта назначени
        double road_lenght;      //расстояние до пункта назначения 
    };

    // Производный класс - САМОЛЕТ
    class Plane : public Transport,public Destination
    {
    public:
        Plane()
        {
            eco_number = 0;
            business_number = 0;
        }
        Plane(string d_name, string t_no,double r_l, int t_dep, int t_arr, int e_number, int b_number)
            : Transport(t_no,t_dep,t_arr), Destination(d_name,r_l)
        {
            this->eco_number = e_number;
            this->business_number = b_number;
        }
      virtual  void Show()
        {
            cout << "\nВид транспорта: Самолет " << "\n Место назначения: " << destination_name << "\n Номер рейса: " << trip_no
                << "\n Расстояние до места назначения: " << road_lenght << " км\n Время отправления: " <<
            setfill('0')<< setw(2)<<time_depart / 100 << ':' << setw(2) << time_depart % 100 << "\n Время прибытия: " <<
                setw(2) << time_arrive / 100 << ':' << setw(2) << time_arrive % 100 <<
                "\n Кол-во мест в экономе: " << eco_number << "\n Кол-во мест в бизнесе: " << business_number << endl << endl;
        }
       virtual double Speed()
        {
            int t1 = this->time_arrive, t2 = this->time_depart;
            int t1_h = t1 / 100, t1_m = t1 % 100, t2_h = t2 / 100, t2_m = t2 % 100;
            if (t2_m > t1_m) {
                --t1_h;
                t1_m += 60;
            }
            int d_h = t1_h - t2_h, d_m = t1_m - t2_m;
            double r = this->road_lenght / (d_h + d_m / 60);
            return r;
            
        }
    protected:
        int eco_number; // число кресел в эконом классе
        int business_number; // число кресел в бизнесс классе
    };

    // Производный класс - АВТОБУС
    class Bus : public Transport, public Destination
    {
    public:
        Bus()
        {
            place_number = 0;
        }
        Bus(string d_name, string t_no, double r_l, int t_dep, int t_arr, int p_number)
            : Transport(t_no, t_dep, t_arr), Destination(d_name, r_l)
        {
            this->place_number = p_number;
        }
        virtual  void Show()
        {
            cout <<"\nВид транспорта: Автобус "<< "\n Место назначения: " << destination_name << "\n Номер рейса: " << trip_no
                << "\n Расстояние до места назначения: " << road_lenght << " км\n Время отправления: " <<
                setfill('0') << setw(2) << time_depart / 100 << ':' << setw(2) << time_depart % 100 << "\n Время прибытия: " <<
                setw(2) << time_arrive / 100 << ':' << setw(2) << time_arrive % 100 <<
                "\n Кол-во мест: " << place_number << endl << endl;
        }
        virtual double Speed()
        {
            int t1 = this->time_arrive, t2 = this->time_depart;
            int t1_h = t1 / 100, t1_m = t1 % 100, t2_h = t2 / 100, t2_m = t2 % 100;
            if (t2_m > t1_m) {
                --t1_h;
                t1_m += 60;
            }
            int d_h = t1_h - t2_h, d_m = t1_m - t2_m;
            double r = this->road_lenght / (d_h + d_m / 60);
            return r;

        }
    protected:
        int place_number; // количество мест

    };

    // Производный класс - ПОЕЗД
    class Train : public Transport, public Destination
    {
    public:
        Train()
        {
            coach_number = 0;
            train_type = "NOTYPE";
        }
        Train(string d_name, string t_no, double r_l, int t_dep, int t_arr, int c_number,string t_type)
            : Transport(t_no, t_dep, t_arr), Destination(d_name, r_l)
        {
            this->coach_number = c_number;
            this->train_type = t_type;
        }
        virtual  void Show()
        {
            cout << "\nВид транспорта: Поезд" << "\n Место назначения: " << destination_name << "\n Номер рейса: " << trip_no
                << "\n Расстояние до места назначения: " << road_lenght << " км\n Время отправления: " <<
                setfill('0') << setw(2) << time_depart / 100 << ':' << setw(2) << time_depart % 100 << "\n Время прибытия: " <<
                setw(2) << time_arrive / 100 << ':' << setw(2) << time_arrive % 100 <<
                "\n Кол-во вагонов: " << coach_number << "\n Тип поезда: " << train_type << endl << endl;
        }
        virtual double Speed()
        {
            int t1 = this->time_arrive, t2 = this->time_depart;
            int t1_h = t1 / 100, t1_m = t1 % 100, t2_h = t2 / 100, t2_m = t2 % 100;
            if (t2_m > t1_m) {
                --t1_h;
                t1_m += 60;
            }
            int d_h = t1_h - t2_h, d_m = t1_m - t2_m;
            double r = this->road_lenght / (d_h + d_m / 60);
            return r;

        }
    protected:
        int coach_number; // количество вагонов
        string train_type; // тип поезда

    };
//============================================================================
    void Show_speed(Transport& trans) {
     cout << " Ожидаемая скорость: " << setprecision(3) << trans.Speed() << " км/ч\n\n";
    }
    int main(void)
    {
        setlocale(LC_ALL, "Russian");
        int obj, n;
        Plane* plane = new Plane("Волчок", "P101",1340, 1020,1230,12,10);
        Bus*bus = new Bus("Юрлово", "B203", 273.5, 900, 1555, 54);
        Train* train = new Train("Лифтхенштейн", "T890", 680, 730, 1740, 56, "грузовой");
        do {
        cout << "1-Самолет\n2-Автобус\n3-Поезд\n0-Выход\nВыберите объект:";
        cin >> obj;
        switch (obj)
        {
           case 1:  plane->Show(); Show_speed(*plane);
                    break;
           case 2:  bus->Show();  Show_speed(*bus);
                    break;
           case 3:  train->Show(); Show_speed(*train);
                    break;       
        }
         
        } while (obj != 0);
    }
