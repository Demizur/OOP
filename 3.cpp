#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct DATA {
	string name;  // Название вируса
	int    year;  // год появления
	DATA* operator=(DATA& d);
	
};

DATA* DATA :: operator=(DATA& d) {
	DATA* new_el= new DATA;
	new_el->name = d.name;
	new_el->year = d.year;
	return new_el;

}
class LIST {
private:
	struct List {   // Двухсвязный список
		DATA data;
		List* next;
		List* prev;
	};
	List* pbeg, *pend;  //List* pbeg = NULL,* pend = NULL;
	List *d_list;
public:
	LIST() :pbeg(NULL), pend(NULL) {}; //Инициализация пустых указателей;
	~LIST();
	LIST(DATA& d);
	//Перегрузка операторов
	 List* operator+(DATA& d) {
		List* new_el = new List(); // добавляемый элемент
		this->add(d);
		return new_el;
	}

	 List* operator-(string& st) {
		 List* del_el = new List(); // удаляемый элемент
		 this->remove(st);
		 return del_el;
	 }
	// --------------------------------------------------------
	// Добавление в список (упорядоченный по годам)
	void add(DATA S) {
		List* new_el = new List(); // добавляемый элемент
		if (pbeg == 0) {
			pbeg = pend = new_el; // Первый узел списка 
			new_el->data.year = S.year;
			new_el->data.name = S.name;
		}
		else {
		new_el->data.year = S.year;
		new_el->data.name = S.name;
		List* pt = pbeg;
		while (pt) { // просмотр списка
			if (S.year < pt->data.year) { // занести перед текущим элементом (pt)
				new_el->next = pt;
				if (pt == pbeg) { // в начало списка
					new_el->prev = 0;
					pbeg = new_el;
				}
				else { // в середину списка
					(pt->prev)->next = new_el;
					new_el->prev = pt->prev;
				}
				pt->prev = new_el;
				return;
			}
			pt = pt->next;
		}
		new_el->prev = pend;
		pend->next = new_el;
		pend = new_el;
		}
	}
	//-----------------------------------------------
	// Поиск элемента по названию
	List* find(List* const pbeg, string name) {
		List* temp = pbeg;
		while (temp) {
			if (temp->data.name == name)break;
			temp = temp->next;
		}
		return temp;
	}
	//---------------------------------------------
	// Удаление элемента
	void remove( string key) {
		if (List* pkey = find(pbeg, key)) {

			if (pkey == pbeg) {
				pbeg = (pbeg)->next;
				(pbeg)->prev = 0;
			}
			else if (pkey == pend) {
				pend = (pend)->prev;
				(pend)->next = 0;
			}

			else {
				(pkey->prev)->next = pkey->next;
				(pkey->next)->prev = pkey->prev;
			}
			delete pkey;
			cout << "\n Вирус '" << key << "' удален\n\n";
		}
		else cout << "\nУдаление невозможно! Вирус не найден!\n\n";
	}
	//---------------------------------------------
	// Поиск вируса по названию
	void find_name(string key) {
		if (List* pkey = find(pbeg, key)) {
			cout << "Найден вирус " << pkey->data.name << ", год создания:" << pkey->data.year << endl;
		}
		else {
			cout << "Такого вируса нет " << endl;
		}
	}
	//---------------------------------------------
	// Поиск вирусов, созданных позднее заданного года
	void find_year(int key) {
	cout << "\n Поиск вирусов,созданных позднее "<< key <<" года:\n";
		List* pkey = pbeg;
			while (pkey) {
				if (pkey->data.year > key) {
					cout.width(15);
					cout << pkey->data.name << ' ' << pkey->data.year << endl;
				}

				pkey = pkey->next;
			}

		cout << endl;
	}
	//---------------------------------------------
	// Печать списка
	void print() {
		List* temp = pbeg;
		while (temp) { 
			cout.width(15);
			cout << temp->data.name << ' ' << temp->data.year << endl;
			temp = temp->next;
		}
	}
};

// Деструктор
LIST::~LIST()
{
	if(pbeg != 0) {
		List* temp = pbeg;
		while (temp) {
			temp = temp->next;
			delete pbeg;
			pbeg = temp;
		}
	}
	cout << " Список удален " << endl;
}

LIST::LIST(DATA& d)
{
	this->d_list->data = d;
	this->pbeg = d_list;

}

class QUEUE  {
private:
	struct Queue {   // Очередь
		string name;  // Название вируса
		int    year;  // год появления
		Queue* next;
	};
	Queue* pbeg, * pend;
	
public:	
	QUEUE() :pbeg(NULL), pend(NULL) {}; //Инициализация пустых указателей;
	~QUEUE();
	//Перегрузка операторов
	Queue* operator+(DATA& d) {
		Queue* new_el = new Queue(); // добавляемый элемент
		this->add(d);
		return new_el;
	}

	Queue* operator-(int& n) {
		Queue* del_el = new Queue(); // удаляемый элемент
		this->del(n);
		return del_el;
	}
	// Поиск вируса по названию
	void find_name(string key) {
		if (Queue* pkey = find(pbeg, key)) {
			cout << "Найден вирус " << pkey->name << ", год создания:" << pkey->year << endl;
		}
		else {
			cout << "Такого вируса нет " << endl;
		}
	}
	// --------------------------------------------------------
	// Добавление в очередь
	void add(DATA S) {
		Queue* new_el = new Queue; // добавляемый элемент
		new_el->year = S.year;
		new_el->name = S.name;
		new_el->next = 0;
		if (pbeg == 0) {  // Первый узел очереди
			pend = pbeg = new_el;
		}
		else {
			pend->next = new_el;
			pend = new_el;
		}
	}
	// --------------------------------------------------------
	//Изьятие элемента из очереди
	void del(int n) {
		for (int i = 0; i < n; i++) {
			if (pbeg != NULL) {
				Queue* temp = pbeg;		
				pbeg = pbeg->next;
				delete temp;
			}
		}
	}
	//-----------------------------------------------
	// Поиск элемента по названию
	Queue* find(Queue* const pbeg, string st) {
		Queue* temp = pbeg;
		while (temp) {
			if (temp->name == st)break;
			temp = temp->next;
		}
		return temp;
	}
	
	//---------------------------------------------
	
	//---------------------------------------------
	// Поиск вирусов, созданных позднее заданного года
	void find_year(int key) {
		cout << "\n Поиск вирусов,созданных позднее " << key << " года:\n";
		Queue* pkey = pbeg;
		while (pkey) {
			if (pkey->year > key) {
				cout.width(15);
				cout << pkey->name << ' ' << pkey->year << endl;
			}

			pkey = pkey->next;
		}

		cout << endl;
	}
	//-----------------------------------------------
	// Печать очереди
	void print() {
		Queue* temp = pbeg;
		while (temp != NULL) {
			cout.width(15);
			cout << temp->name << " " << temp->year << endl;
			temp = temp->next;
		}
	}
};

// Деструктор
QUEUE::~QUEUE()
{
	Queue* temp = pbeg;
	while (temp != NULL) {
		temp = pbeg->next;
		delete pbeg;
		pbeg = temp;
	}
	cout << " Очередь удалена " << endl;
}

//Элемент записи 
DATA* data(string add, int y) {
	DATA* S = new DATA;
	S->name = add;
	S->year = y;
	return S;
}

//----------ОСНОВНАЯ ПРОГРАММА--------------------------
int main() {
	setlocale(LC_ALL, "Russian");
	LIST list;       //Конструктор класса
	QUEUE queue;

	ifstream f("viruses.txt");

	if (!f) cout << "Невозможно откыть файл\n";

	string str, st;
	// Заполнение списка и очереди
	while (!f.eof()) {
		f >> st;
		f >> str;
		list + *data(st, stoi(str));   //Добавление элемента в список
		queue.add(*data(st, stoi(str)));  //Добавление элемента в очередь
	}
	f.close();

	int c, y, n, ypoisk;
	string del, poisk, add;
	
	do {
	cout << "\nВыберите тип структуры:(При повторном выборе структуры все изменения в структуре сохраняются)\n1-Список\n2-Очередь\n0-Выход\n";
	cin >> c;
	
		switch (c)
		{
		case 1:		
			list.print();

			cout << "Введите название вируса для добавления: ";
			cin >> add;
			cout << "\nВведите год создания вируса для добавления: ";
			cin >> y;
			cout << "\n Добавление вируса '" << add << "':\n";
			list+*data(add,y);
			list.print();

			cout << "\nВведите название вируса для удаления: ";
			cin >> del;	
			list-del;		
			list.print();

			cout << "\nВведите название вируса для поиска: ";
			cin >> poisk;
			list.find_name(poisk);

			cout << "\nВведите год создания вируса для поиска вирусов, созданных позднее введенного года: ";
			cin >> ypoisk;
			list.find_year(ypoisk);
			break;

		case 2:
			queue.print();
			cout << "Введите название вируса для добавления: ";
			cin >> add;
			cout << "\nВведите год создания вируса для добавления: ";
			cin >> y;
			cout << "\n Добавление вируса '" << add << "':\n";
			queue+*data(add, y);
			queue.print();

			cout << "\nВведите число элементов для изъятия из очереди: ";
			cin >> n;
			queue-n;

			cout << "\nОчередь после изъятия: \n";
			queue.print();

			cout << "\nВведите название вируса для поиска: ";
			cin >> poisk;
			queue.find_name(poisk);

			cout << "\nВведите год создания вируса для поиска: ";
			cin >> ypoisk;
			queue.find_year(ypoisk);
			break;
		}
		
	} while (c != 0);



}
