#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

#define PRIME_SIZE 29 

using namespace std;

class Person
{
public:
	Person* next;
	string name;
	string surname;
	string zodiac;
	string dd;
	string mm;
	string yy;

	Person()
	{
		this->next = NULL;
	}

	Person(string name, string surname, string zodiac, string dd, string mm, string yy)
	{
		this->name = name;
		this->surname = surname;
		this->zodiac = zodiac;
		this->dd = dd;
		this->mm = mm;
		this->yy = yy;
		this->next = NULL;
	}

	~Person()
	{

		if (this->next != NULL)
		{
			delete this->next;
		}
	}
};

class HashTable
{
	Person* table[PRIME_SIZE];
	static int hash(string str)
	{
		int asciisum = 0;
		for (int i = 0; i < str.length(); i++)
		{
			asciisum += str[i];
		}
		return asciisum % PRIME_SIZE;
	}

public:

	HashTable()
	{
		for (int i = 0; i < PRIME_SIZE; i++)
		{
			table[i] = NULL;
		}
	}

	~HashTable()
	{
		for (int i = 0; i < PRIME_SIZE; i++)
		{
			delete table[i];
		}
	}
	void push(string name, string surname, string zodiac, string dd, string mm, string yy)
	{
		int hashNumber = hash(mm);
		Person* pers = new Person(name, surname, zodiac, dd, mm, yy);
		Person* place = table[hashNumber];
		if (place == NULL)
		{
			table[hashNumber] = pers;
			return;
		}

		while (place->next != NULL)
		{
			place = place->next;
		}
		place->next = pers;
	}

	Person* findM(string mm)
	{
		int hashNumber = hash(mm);
		Person* result = table[hashNumber];
		if (!result)
		{
			cout << "������ � �������� ������ ���������� �������� �� ����" << endl;
			return NULL;
		}
		while (result->mm != mm)
		{
			if (!result->next)
			{
				cout << "������ � �������� ������ ���������� �������� �� ����" << endl;
				break;
			}
			result = result->next;
		}
		return result;
	}
};
void print(Person* per)
{
	if (per == NULL) return;
	else
	{
		print(per->next);
		cout << per->name << " " << per->surname << " " << per->zodiac << endl;
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HashTable newTable;
	string name, surname, zodiac, dd, mm, yy;
	int count;
	cout << "������ ������� ����� ";
	cin >> count;
	for (int i = 0; i < count; i++)
	{
		cout << "������ ��'� ";
		cin >> name;
		cout << "������ ������� ";
		cin >> surname;
		cout << "������ ���� ������ ";
		cin >> zodiac;
		cout << "������ ���� ���������� ";
		cin >> dd;
		cout << "������ ����� ���������� ";
		cin >> mm;
		cout << "������ �� ���������� ";
		cin >> yy;
		newTable.push(name, surname, zodiac, dd, mm, yy);
		cout << endl;
	}
	string searchItem;
	cout << "������  ����� ���������� ������ ��� �� �������� ������ :";
	cin >> searchItem;
	Person* search = newTable.findM(searchItem);
	if (search)
	{
		cout << "������ ������ ��������. �� ��� :";
		print(search);
	}
	else {
		cout << "������ ������ �� ��������" << endl;
	}
	return 0;
}