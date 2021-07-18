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
		cerr << "���� �� ����� ���� ������ ��� ������� ������!" << endl;
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
	cout << "������ �����: " << endl;
	List<int>::iterator it = lst.GetBegin();
	while (it != nullptr)
	{
		cout << lst.GetValue(it) << " ";
		it = lst.GetNext(it);
	}
	cout << endl;

	List<int>::iterator it1 = lst.GetLast();
	cout << "�������� �����: " << endl;
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
		cout << "\t����\n"
			<< "1. �������� ������� � ������\n"
			<< "2. �������� ������� � �����\n"
			<< "3. �������� ������� �� ���������� ������\n"
			<< "4. ������� ������� � ������\n"
			<< "5. ������� ������� � �����\n"
			<< "6. ������� ������� �� ���������� ������\n"
			<< "7. �������� ������ �������\n"
			<< "8. �������� ������ �����\n"
			<< "9. ������� � ��������� ���������� ����������\n"
			<< "10. ������� �� �����\n"
			<< "11. ������� � ����\n"
			<< "12. ������� �� �������\n"
			<< "13. ��������\n"
			<< "14. ����� ������� �� ��������\n"
			<< "15. ��������� �� �������\n"
			<< "16. ������ ���������� ���������\n"
			<< "17. ������������� �� �����������\n"
			<< "0. �����\n";
		if (cin >> selected)
		{
			switch (selected)
			{
			case 1:
				cout << "������� �������� ��������\n";
				cin >> data;
				lst.push_front(data);
				cout << "������� ��������\n";
				break;
			case 2:
				cout << "������� �������� ��������\n";
				cin >> data;
				lst.push_back(data);
				cout << "������� ��������\n";
				break;
			case 3:
				cout << "������� �������� � �����\n";
				cin >> data >> index;
				lst.push(data, index);
				cout << "������� ��������\n";
				break;
			case 4:
				try
				{
					lst.pop_front();
					cout << "������� ������\n";
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
					cout << "������� ������\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 6:
				try
				{
					cout << "������� ����� ��������: \n";
					cin >> index;
					lst.pop(index);
					cout << "������� ������\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 7:
				try
				{
					cout << "������ �������: " << lst.top() << endl;
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 8:
				cout << "������ �����: " << lst.down() << endl;
			case 9:
				cout << "������� ���������� ���������: \n";
				cin >> count;
				cout << "������� ������ ���������: \n";
				cin >> begin;
				cout << "������� ����� ���������: \n";
				cin >> end;
				if (begin > end) cout << "������ ��������� �� ����� ���� ������ ���������" << endl;
				else randFill(lst, count, begin, end);
				break;
			case 10:
				cout << "������� ��� �����\n";
				cin >> filename;
				try
				{
					fileRead(lst, filename);
					cout << "���� ������\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << endl;
				}
				break;
			case 11:
				cout << "������� ��� ����� � �����������\n";
				cin >> filename;
				try
				{
					fileSave(lst, filename);
					cout << "�������� � ���� �������\n";
				}
				catch (exception ex)
				{
					cout << ex.what() << "\n";
				}
				break;
			case 12:
				if (!lst.isEmpty())
				{
					cout << "�������� � ������: ";
					print(lst);
				}
				else
				{
					cout << "������ ����\n";
				}
				break;
			case 13:
				lst.clear();
				cout << "������ ������\n";
				break;
			case 14:
				cout << "������� ��������\n";
				cin >> data;
				cout << lst.parse(data) << endl;
				break;
			case 15:
				if (lst.isEmpty())
				{
					cout << "������ ����\n";
				}
				else
				{
					cout << "������ �� ����\n";
				}
				break;
			case 16:
				cout << "� ������ " << lst.GetSize() << " ���������\n";
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
				cout << "������� �����������\n";
				break;
			case 0:
				break;
			}
		}
		else
		{
			cout << "������� �����������\n";
		}
		system("pause");
		cout << "\n";
	} while (selected != 0);
	return 0;
}