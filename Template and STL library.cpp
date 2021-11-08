#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <queue>

using namespace std;

template<typename N, typename Y>
struct DATA {
	N name;  // Название вируса
	Y year;  // год появления
	DATA<N, Y>* operator=(DATA<N, Y>& d);

};
template<typename N, typename Y>
DATA<N,Y>* DATA<N, Y> :: operator=(DATA<N, Y>& d) {
	DATA<N, Y>* new_el = new DATA<N, Y>;
	new_el->name = d.name;
	new_el->year = d.year;
	return new_el;

}
//Элемент записи 
template<typename N, typename Y>
DATA<N, Y>* data(N name, Y y) {
	DATA<N, Y>* S = new DATA<N, Y>;
	S->name = name;
	S->year = y;
	return S;
}

template<typename N, typename Y>
class LIST {
private:
	struct List {   // Двухсвязный список
		DATA<N, Y> data;
		List* next;
		List* prev;
	};
	List* pbeg, * pend;  //List* pbeg = NULL,* pend = NULL;
	List* d_list;
public:
	LIST() :pbeg(NULL), pend(NULL) {}; //Инициализация пустых указателей;
	~LIST();
	LIST(DATA<N, Y>& d);
	//Перегрузка операторов
	List* operator+(DATA<N, Y>& d) {
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
	void add(DATA<N, Y> S) {
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
	List* find(List* const pbeg, N name) {
		List* temp = pbeg;
		while (temp) {
			if (temp->data.name == name)break;
			temp = temp->next;
		}
		return temp;
	}
	//---------------------------------------------
	// Удаление элемента
	void remove(N key) {
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
		}
		else {
			cout << "Удаление невозможно! Вирус не найден!\n";
			
		}
	}
	//---------------------------------------------
	// Поиск вируса по названию
	void find_name(N key, ostream& out) {
		if (List* pkey = find(pbeg, key)) {
			out << "Найден вирус " << pkey->data.name << ", год создания:" << pkey->data.year << endl;
		}
		else {
			cout << "Такого вируса нет " << endl;
			out << "Такого вируса нет " << endl;
		}
	}
	//---------------------------------------------
	// Поиск вирусов, созданных позднее заданного года
	void find_year(Y key, ostream& out) {
		out << endl<<" Поиск вирусов,созданных позднее " << key << " года:"<<endl;
		List* pkey = pbeg;
		while (pkey) {
			if (pkey->data.year > key) {
				out << pkey->data.year << "   " << pkey->data.name << endl;
			}

			pkey = pkey->next;
		}

		out << endl;
	}
	//---------------------------------------------
	// Печать списка
	void print(ostream& out) {
		List* temp = pbeg;
		while (temp) {
			out << temp->data.year << "   " << temp->data.name << endl;
			temp = temp->next;
		}
	}
};

// Деструктор
template<typename N, typename Y>
LIST<N,Y>::~LIST<N, Y>()
{
	if (pbeg != 0) {
		List* temp = pbeg;
		while (temp) {
			temp = temp->next;
			delete pbeg;
			pbeg = temp;
		}
	}
	cout << " Список удален " << endl;
}

template<typename N, typename Y>
LIST<N, Y>::LIST<N, Y>(DATA<N,Y>& d)
{
	this->d_list->data = d;
	this->pbeg = d_list;

}

//Перегрузка оператора вывода
template<typename N, typename Y>
ostream& operator << (ostream& out, queue<DATA<N, Y>> d)
{
	out << d.front().year << "   " << d.front().name << endl;
	return out;
}

template<typename N, typename Y>
void print(queue<DATA<N, Y>> q, ostream& out) {
	queue<DATA<string, int>> _q = q;
	while (!_q.empty()) {
		out << _q;
		_q.pop();
	}
}

// Функция-манипулятор  горизонтальный разделитель
ostream& sh(ostream& stream)
{
	for (int i = 0; i < 25; i++) stream << "=";
	stream << endl;
	return stream;
}
//----------ОСНОВНАЯ ПРОГРАММА--------------------------
int main() {
	setlocale(LC_ALL, "Russian");
	LIST<string,int> list;      
	queue<DATA<string,int>> q;

	ifstream f("viruses.txt");
	ofstream r_file("List_rez.txt", ios::trunc);
	ofstream rq_file("Queue_rez.txt", ios::trunc);
	if (!f) cout << "Невозможно открыть файл\n";

	string str, st;
	// Заполнение списка и очереди
	while (!f.eof()) {
		f >> st;
		f >> str;
		list + *data<string,int>(st, stoi(str));   //Добавление элемента в список
		q.push({st,stoi(str)});
	}
	f.close();

	int c, y, n, ypoisk;
	string del, poisk, add;

	do {
		cout << "\nВыберите тип структуры:(При повторном выборе структуры все изменения в структуре соханяются)\n1-Список\n2-Очередь\n0-Выход\n";
		cin >> c;	
		switch (c)		
		{
		case 1:
			r_file << sh;
			list.print(r_file);
			list.print(cout);

			cout << "Введите название вируса для добавления: ";
			cin >> add;
			cout << "\nВведите год создания вируса для добавления: ";
			cin >> y;
			r_file << endl<<" Добавление вируса '" << add << "':"<<endl;
			list + *data<string, int>(add, y);
			list.print(r_file);

			cout << "\nВведите название вируса для удаления: ";
			cin >> del;
			list - del;
			r_file << endl << "Список после удаления вируса "<<del << ":" << endl;
			list.print(r_file);

			cout << "\nВведите название вируса для поиска: ";
			cin >> poisk;
			r_file << endl << "Поиск вируса " << poisk << ":" << endl;
			list.find_name(poisk, r_file);

			cout << "\nВведите год создания вируса для поиска вирусов, созданных позднее введенного года: ";
			cin >> ypoisk;
			list.find_year(ypoisk,r_file);
			
			break;

		case 2:
			rq_file << sh;
			print(q,cout);
			print(q,rq_file);
			cout << "Введите название вируса для добавления: ";
			cin >> add;
			cout << "\nВведите год создания вируса для добавления: ";
			cin >> y;
			rq_file << endl <<" Добавление вируса '" << add << "':"<<endl;
			q.push({ add,y });
			print(q,rq_file);
			cout << "\nВведите число элементов для изъятия из очереди: ";
			cin >> n;
				if (n > q.size()) {
					cout << "Количество удаляемых элементов больше длины очереди!\nДлина очереди: " << q.size() << endl;
				}	 else {
					for (int i = 0; i < n; i++) {
						q.pop();
					}
					rq_file << endl <<"Очередь после изъятия " <<n<< " элементов:"<< endl ;
					print(q, rq_file);
				}
				
			break;
			
		}

	} while (c != 0);

	r_file.close();
	rq_file.close();
}
