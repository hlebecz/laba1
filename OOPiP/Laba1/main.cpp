#include <string>
#include <iostream>
#include <Windows.h>
#include <limits>
#include <conio.h>
#include <vector>

#ifdef max
#undef max
#endif

using namespace std;

int enableMenu( const vector<string>);
void clearScreen() {   //������� ������� ������
	std::cout << "\x1b[2J";
	std::cout << "\x1b[H";
	//system("cls");
}


class Book {
public:
	int id;
	string book_title = "";
	string author = "";
	int release_date = 0;
	void display(int i) {
		cout << "\n����� �" << i + 1 << " :" << endl;
		cout << "ID: " << id << endl;
		cout << "---------------------------------------" << endl;
		cout << "��� ������: \n " << author << endl;
		cout << "�������� �����: \n " << book_title << endl;
		cout << "��� �������: \n " << release_date << endl;
		cout << "---------------------------------------" << endl;
	}
	void set_book_title(string args) {
		this->book_title = args;
	}
	void set_author(string args) {
		this->author = args;
	}
	void set_release_date(int args) {
		this->release_date = args;
	}
};

class Library {
	int id = 1;
	Book* books;
	int size;
public:
	
	
	Library(int size = 0);
	Library(const Library& obj);
	~Library();
	
	void add();
	void input();
	void display();
	void search();
	void change_book(int);
	void delete_book(int);

};

Library::Library(int size) {
	this->size = size;
	this->books = new Book[this->size];
}

Library::Library(const Library& obj) {
	size = obj.size;
	books = new Book[size];
	for (int i = 0; i < size; i++) {
		books[i] = obj.books[i];
	}
}

void Library::input() {
	clearScreen();
	cout << "������� �������� �����; ��� ������; ��� �������  " << endl;
	for (int i = 0;i < size; i++) {
		cout << "����� �" << i + 1 << " :" << endl;
		books[i].id = this->id;
		this->id++;
		getline(cin, books[i].author);
		getline(cin, books[i].book_title);
		while (true) {
			if (cin >> books[i].release_date && books[i].release_date < 2026 && books[i].release_date > -1000) {
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			else {
				cout << "����������, ������� �����  �� -999 �� 2025" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			}
		}
	}
}
void Library::add() {
	Book* temp;
	temp = new Book[size];
	for (int i = 0; i < size; i++) {
		temp[i] = books[i];
	}
	delete[] books;
	this -> books = new Book[size + 1];
	for (int i = 0; i < size; i++) {
		this -> books[i] = temp[i];
	}
	size++;
	delete[] temp;
	clearScreen();
	cout << "\n������� �������� �����; ��� ������; ��� �������  " << endl;
	books[size - 1].id = this->id;
	this->id++;
	getline(cin, books[size - 1].author);
	getline(cin, books[size - 1].book_title);
	while (true) {
		if (cin >> books[size - 1].release_date && books[size - 1].release_date < 2026 && books[size - 1].release_date > -1000) {
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
		else {
			cout << "����������, ������� �����  �� -999 �� 2025" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		}
	}
	
}
void Library::display() {
	if (size == 0) {
		cout << "\n ��� �������" << endl;
	}
	else {
		for (int i = 0; i < size; i++) {
			books[i].display(i);
		}
	}
	system("pause");
}
void Library::search() {
	int count = 0;
	int choice = 4;
	do {
		string tmp;
		int tmp_int;
		clearScreen();
		cout << "\n�� ��� �� ������ ������?" << endl;
		choice = enableMenu({ "1) �������� �����", "2) ������", "3) ��� �������", "4) �����" });
		switch (choice) {
		case 1:
			cout << "\n������� �������� �����" << endl;
			getline(cin, tmp);
			for (int i = 0; i < this->size; i++) {
				if (books[i].book_title == tmp) {
					count++;
					books[i].display(i);
				}
			}
			if (count > 0) {
				cout << "������� " << count << " ��." << endl;
				_getch();
			}
			else {
				cout << "���������� �� �������" << endl;
			}
			break;
		case 2:
			cout << "\n������� ��� ������" << endl;
			getline(cin, tmp);
			for (int i = 0; i < this->size; i++) {
				if (books[i].author == tmp) {
					count++;
					books[i].display(i);
				}	
			}
			if (count > 0) {
				cout << "������� " << count << " ��." << endl;
				_getch();
			}
			else {
				cout << "���������� �� �������" << endl;
			}
			break;
		case 3:
			while (true) {
				cout << "\n������� ��� �������" << endl;
				if (cin >> tmp_int && tmp_int < 2026 && tmp_int > -1000) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					for (int i = 0; i < this->size; i++) {
						if (books[i].release_date == tmp_int) {
							count++;
							books[i].display(i);
						}
					}
					if (count > 0) {
						cout << "������� " << count << " ��." << endl;
						_getch();
					}
					else {
						cout << "���������� �� �������" << endl;
					}
					break;
				}
				else {
					clearScreen();
					cout << "����������, ������� �����  �� -999 �� 2025" << endl;
					std::cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			break;
		case 4:
			break;
		case -1:
			break;
		}
	} while (choice != 4 && choice != -1);
}
void Library::change_book(int number){
	int index = -1;
	for (int i = 0; i < this->size;i++) {
		if (this->books[i].id == number) {
			index = i;
			break;
		}
	}
	if (index < 0) {
		cout << "\n����� � ����� ID �� ����������" << endl;
		_getch();
		return;
	}
	int choice = 4;
	do {
		string tmp;
		int tmp_int;
		clearScreen();
		cout << "��� �� ������ ��������?" << endl;
		choice = enableMenu({ "1) �������� �����", "2) ������", "3) ��� �������", "4) �����" });
		switch (choice) {
		case 1:
			cout << "\n������� ����� �������� �����" << endl;
			getline(cin, tmp);
			books[index].set_book_title(tmp);
			break;
		case 2:
			cout << "\n������� ����� ��� ������" << endl;
			getline(cin, tmp);
			books[index].set_author(tmp);
			break;
		case 3:
			while (true) {
				cout << "\n������� ����� ��� �������" << endl;
				if (cin >> tmp_int && tmp_int < 2026 && tmp_int > -1000) {
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					books[index].set_release_date(tmp_int);
					break;
				}
				else {
					clearScreen();
					cout << "����������, ������� �����  �� -999 �� 2025" << endl;
					std::cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			}
			break;
		case 4:
			break;
		case -1:
			break;
		}
	} while (choice != 4 && choice != -1);
}
void Library::delete_book(int number) {
	int index = -1;
	for (int i = 0; i < this -> size;i++) {
		if (this->books[i].id == number) {
			index = i;
			break;
		}
	}
	if (index < 0) {
		cout << "����� � ����� ID �� ����������" << endl;
		_getch();
		return;
	}
	Book* temp;
	temp = new Book[this -> size];
	for (int i = 0; i < this -> size; i++) {
		temp[i] = books[i];
		
	}
	delete[] books;
	this->books = new Book[this -> size - 1];
	int j = 0;
	for (int i = 0; i < this -> size; i++) {
		if (i != index) {
			this->books[i - j] = temp[i];
		}
		else {
			j++;
		}
	}
	this -> size--;
	delete[] temp;
}

Library::~Library() {
	delete[] books;
}


int enableMenu(const vector <string> menu) {
	int key = 1;
	int arrow_pos = 1;
	int str_count = size(menu);

	cout << "����:";
	for (int i = 0; i < str_count; i++) {
		i + 1 == arrow_pos ? cout << "\n--->" : cout << "\n    ";
		cout << menu[i];
	}
	do {

		if (_kbhit()) {
			key = _getch();
			//cout << " ������: " << key;
			if (key != 224) {
				if (key == 72) {
					arrow_pos == 1 ? arrow_pos = str_count : arrow_pos--;
				}
				if (key == 80) {
					arrow_pos == str_count ? arrow_pos = 1 : arrow_pos++;
				}
				for (int i = 0; i < str_count; i++) {
					cout << "\033[A";
				}
				for (int i = 0; i < size(menu[str_count - 1]) + 4;i++) {
					cout << "\b";
				}
				cout << "����:";
				for (int i = 0; i < str_count; i++) {
					i + 1 == arrow_pos ? cout << "\n--->" : cout << "\n    ";
					cout << menu[i];
				}
			}
		}
	} while (key != 27 && key != 13);
	if (key == 27) arrow_pos = -1;
	return arrow_pos;
}

int main() {
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);



	int choice = 0;
	Library* lib = nullptr; // ��������� �� ����������
	
	do {
		clearScreen();
		choice = enableMenu({ "1) ����;","2) ����������","3) �����","4) ����� �� ��������� ���������;","5) ���������;","6) ��������;","7) �����"});
		//cout << choice;
		{
			switch (choice) {
			case 1:
				int size;
				clearScreen();
				while (true) {
					cout << "\n������� ���������� ����: ";
					if (cin >> size) {
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						lib = new Library(size); // ������� ����� ����������
						lib->input();
						break;
					}
					else {
						clearScreen();
						cout << "����������, ������� �����" << endl;
						std::cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				}
				break;
			case 2:
				if (lib) {
					lib->add();
				}
				else {
					cout << "\n���������� �� �������. ������� ������� ������." << endl;
					system("pause");
				}
				break;
			case 3:
				if (lib) {
					lib->display();
				}
				else {
					cout << "\n���������� �� �������. ������� ������� ������." << endl;
					_getch();
				}
				break;
			case 4:
				if (lib) {
					lib->search();
					
				}
				else {
					cout << "\n���������� �� �������. ������� ������� ������." << endl;
					_getch();
				}
				break;
			case 5:
				if (lib) {
					while (true) {
						cout << "\n������� ID ����� ��� ���������: ";
						int change_id;
						if (cin >> change_id) {

							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							lib->change_book(change_id);
							clearScreen();
							cout << "�������� ��� ���� �����?" << endl;
							int choice = enableMenu({ "1) �� ", "2) ���" });
							if (choice != 1)
								break;
						}
						else {
							clearScreen();
							cout << "����������, ������� �����" << endl;
							std::cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					}
				}
				else {
					cout << "\n���������� �� �������. ������� ������� ������." << endl;
					_getch();
				}
				break;
			case 6:
				if (lib) {
					while (true) {
					cout << "\n������� ID ����� ��� ��������: ";
					int delete_id;
					if (cin >> delete_id) {
						
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
							lib->delete_book(delete_id);
							clearScreen();
							cout << "������� ��� ���� �����?" << endl;
							int choice = enableMenu({ "1) �� ", "2) ���" });
							if (choice != 1)
								break;
						}
					else {
							clearScreen();
							cout << "����������, ������� �����" << endl;
							std::cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					}
					
				}
				else {
					cout << "\n���������� �� �������. ������� ������� ������." << endl;
					_getch();
				}
				break;
			case 7:
				std::cout << "\n����� �� ���������." << std::endl;
				break;
			case -1:
				std::cout << "\n����� �� ���������." << std::endl;
				break;
			default:
				clearScreen();
				cout << "\n�������� �����. ����������, �������� ����� \n" << endl;
				break;
			}
		}
	} while (choice != 7 && choice != -1);

	delete lib;
	return 0;
}
