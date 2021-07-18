#include <iostream>
#include "List.h"
#include <fstream>
#include <cstdio>

using namespace std;
void fileRead(List<int>& lst, string filename);
void fileSave(List<int>& lst, string filename);
int rand(int begin, int end);
void randFill(List<int>& lst, int n, int begin, int end);
void print(List<int>& lst);


void fileRead(List<int>& lst, string filename)
{
	ifstream fin(filename);
	for (int buff; fin >> buff;)
	{
		lst.push_back(buff);
	}
}

void fileSave(List<int>& lst, string filename)
{
	ofstream fout(filename);
	List<int>::iterator it = lst.GetBegin();
	if (!fout || lst.isEmpty())
	{
		cerr << "Файл не может быть открыт или очередь пустая!" << endl;
		exit(1);
	}
	while (it != nullptr)
	{
		fout << lst.GetValue(it) << " ";
		it = lst.GetNext(it);
	}
	cout << endl;
}

int rand(int begin, int end)
{
	if (begin == end) return begin;
	else return begin + rand() % (end - begin);
}

void randFill(List<int>& lst, int n, int begin, int end)
{
	srand(time(NULL));
	for (int i = 0; i < n; ++i) lst.push_back(rand(begin, end));
}


void print(List<int>& lst)
{
	cout << "Прямой вывод: " << endl;
	List<int>::iterator it = lst.GetBegin();
	while (it != nullptr)
	{
		cout << lst.GetValue(it) << " ";
		it = lst.GetNext(it);
	}
	cout << endl;

	List<int>::iterator it1 = lst.GetLast();
	cout << "Обратный вывод: " << endl;
	while (it1 != nullptr)
	{
		cout << lst.GetValue(it1) << " ";
		it1 = lst.GetPrev(it1);
	}
	cout << endl;
}

int main()
{
	setlocale(LC_ALL, "RU");
	List<int> lst;
	int selected = 0;
	int data, index;
	int count, begin, end;
	string filename;
	do
	{
		cout << "\tМеню\n"
			<< "1. Добавить элемент в начало\n"
			<< "2. Добавить элемент в конец\n"
			<< "3. Добавить элемент по указанному номеру\n"
			<< "4. Удалить элемент с начала\n"
			<< "5. Удалить элемент с конца\n"
			<< "6. Удалить элемент по указанному номеру\n"
			<< "7. Получить данные вершины\n"
			<< "8. Получить данные конца\n"
			<< "9. Создать и заполнить рандомными элементами\n"
			<< "10. Считать из файла\n"
			<< "11. Вывести в файл\n"
			<< "12. Вывести на консоль\n"
			<< "13. Очистить\n"
			<< "14. Найти элемент по значению\n"
			<< "15. Проверить на пустоту\n"
			<< "16. Узнать количество элементов\n"
			<< "17. Отсортировать по возрастанию\n"
			<< "0. Выход\n";
		if (cin >> selected)
		{
			switch (selected)
			{
			case 1:
				cout << "Введите значение элемента\n";
				cin >> data;
				lst.push_front(data);
				cout << "Элемент добавлен\n";
				break;
			case 2:
				cout << "Введите значение элемента\n";
				cin >> data;
				lst.push_back(data);
				cout << "Элемент добавлен\n";
				break;
			case 3:
				cout << "Введите значение и номер\n";
				cin >> data >> index;
				lst.push(data, index);
				cout << "Элемент добавлен\n";
				break;
			case 4:
				try
				{
					lst.pop_front();
					cout << "Элемент удален\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 5:
				try
				{
					lst.pop_back();
					cout << "Элемент удален\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 6:
				try
				{
					cout << "Введите номер элемента: \n";
					cin >> index;
					lst.pop(index);
					cout << "Элемент удален\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 7:
				try
				{
					cout << "Данные вершины: " << lst.top() << endl;
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 8:
				cout << "Данные конца: " << lst.down() << endl;
			case 9:
				cout << "Введите количество элементов: \n";
				cin >> count;
				cout << "Введите начало диапазона: \n";
				cin >> begin;
				cout << "Введите конец диапазона: \n";
				cin >> end;
				if (begin > end) cout << "Начало диапазона не может быть больше конечного" << endl;
				else randFill(lst, count, begin, end);
				break;
			case 10:
				cout << "Введите имя файла\n";
				cin >> filename;
				try
				{
					fileRead(lst, filename);
					cout << "Файл считан\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}
				break;
			case 11:
				cout << "Введите имя файла с расширением\n";
				cin >> filename;
				try
				{
					fileSave(lst, filename);
					cout << "Выведено в файл успешно\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 12:
				if (!lst.isEmpty())
				{
					cout << "Элементы в списке: ";
					print(lst);
				}
				else
				{
					cout << "Список пуст\n";
				}
				break;
			case 13:
				lst.clear();
				cout << "Список очищен\n";
				break;
			case 14:
				cout << "Введите значение\n";
				cin >> data;
				cout << lst.parse(data) << endl;
				break;
			case 15:
				if (lst.isEmpty())
				{
					cout << "Список пуст\n";
				}
				else
				{
					cout << "Список не пуст\n";
				}
				break;
			case 16:
				cout << "В списке " << lst.GetSize() << " элементов\n";
				break;
			case 17:
				try
				{
					lst.sort();
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}
				break;
			default:
				cout << "Команда отсутствует\n";
				break;
			case 0:
				break;
			}
		}
		else
		{
			cout << "Команда отсутствует\n";
		}
		system("pause");
		cout << "\n";
	} while (selected != 0);
	return 0;
}