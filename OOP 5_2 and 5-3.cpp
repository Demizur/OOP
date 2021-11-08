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
	DATA* new_el = new DATA;
	new_el->name = d.name;
	new_el->year = d.year;
	return new_el;

}
//Элемент записи 
DATA* data(string add, int y) {
	DATA* S = new DATA;
	S->name = add;
	S->year = y;
	return S;
}

// Функция-манипулятор  горизонтальный разделитель
ostream& sh(ostream& stream)
{
	for (int i = 0; i < 16; i++) stream << "_";
	stream << endl;
	return stream;
}

//Перегрузка оператора вывода
ostream& operator << (ostream& out, DATA* d)
{

	out << d->year << "  |  "  << d->name << endl;
	return out;
}
// --------------------------------------------------------
	//Запись в двоичный файл
	void binary_add() {
		ifstream f("viruses.txt");
		ofstream r_file("result_2.txt", ios::trunc);
		ofstream binar_file("binar_file", ios::trunc);
		binar_file.close();
		if (!f) cout << "Невозможно открыть файл\n";

		string str, st;

		// Заполнение бинарного файла
		ofstream binar_fout("binar_file", ios::out | ios::binary);
		while (!f.eof()) {
			f >> st;
			f >> str;
			cout << str << "   " << st <<endl;
			binar_fout.write((char*)data(st, stoi(str)), sizeof(DATA));  //Добавление элемента в бинарный файл
		}

		f.close();
		r_file.close();
		binar_fout.close();
	}
	//Чтение двоичного файла и его вывод в текстовый файл
	void binary_print() {
		ifstream binar_fin("binar_file", ios::in | ios::binary);
		ofstream r_file("result_2.txt", ios::app);

		r_file <<sh<< "Год    |    Вирус "  << endl<<sh;

		DATA* temp = new DATA;
		binar_fin.seekg(0, ios::beg);

			while (binar_fin.read((char*)temp, sizeof(DATA))) {		
				r_file << temp;
			}

		r_file << endl;
		binar_fin.close();
		r_file.close();
	}
	//Модификация данных двоичного файла(Поиск и замена названия и года )
	void binary_mod() {
		string ud, ch;
		int ych;
		cout << "\nПоиск и замена названия и года вируса\nВведите название вируса который надо заменить: ";
		cin >> ud;
		cout << "Введите новое название: ";
		cin >> ch;
		cout << "Введите новый год создания: ";
		cin >> ych;

		fstream binar_file("binar_file", ios::out | ios::binary | ios::in);
		if (!binar_file)  {
			cout << "Невозможно открыть бинарный файл "; return;

		}
		DATA* temp = new DATA;
		
		while (!binar_file.eof()) {
			long S = binar_file.tellp();
			binar_file.read((char*)temp, sizeof(DATA));
			if (temp->name == ud) {
				temp->name = ch;
				temp->year = ych;
				binar_file.seekp(S);
				binar_file.write((char*)temp, sizeof(DATA));
				binar_file.seekp(S);

			}
		}
		binar_file.close();
		ofstream r_file("result_2.txt", ios::app);
		r_file << "Данные после модификации: " << endl;
		r_file.close();
	}
	//Удаление данных из бинарного файла
	void binary_delete() {
		string ud;
		cout << "\nУдаление вируса\nВведите название вируса который надо удалить: ";
		cin >> ud;
		fstream binar_file("binar_file", ios::out | ios::binary | ios::in);
		ofstream binar_fout("binar_fout", ios::out | ios::binary );

		if (!binar_file) {
			cout << "Невозможно открыть бинарный файл "; return;

		}
		DATA* temp = new DATA;

		while (binar_file.read((char*)temp, sizeof(DATA))) {
	
			if (temp->name != ud) {
				binar_fout.write((char*)temp, sizeof(DATA));
			}
			
		}
	
		binar_file.close();
		binar_fout.close();
		
		remove("binar_file");
		rename("binar_fout", "binar_file");
		ofstream r_file("result_2.txt", ios::app);
		r_file << "Данные после удаления: " << endl;
		r_file.close();

	}
// Арифметическая обработка данных
	void binary_process() {
		ifstream binar_file("binar_file", ios::binary | ios::in);
		if (!binar_file) {
			cout << "Невозможно открыть бинарный файл "; return;

		}
		DATA* temp = new DATA;
		int k = 0;
		int sum = 0;
		while (binar_file.read((char*)temp, sizeof(DATA))) {
			 sum = sum + temp->year;
			++k;
		}
		double med = sum / k;
		binar_file.close();
		ofstream r_file("result_2.txt", ios::app);
		r_file << "Средний год создания вирусов: "<<med << endl;
		r_file.close();
	}


//----------ОСНОВНАЯ ПРОГРАММА--------------------------
int main()
{
	setlocale(LC_ALL, "Russian");

	binary_add();
	binary_print();
	binary_mod();
	binary_print();
	binary_delete();
	binary_print();
	binary_process();
}