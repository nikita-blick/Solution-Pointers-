﻿#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

int** Allocate(const int rows, const int cols);
void Clear(int**& arr, const int rows, const int cols = 0);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
void FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
void Print(int arr[], const int n);
void Print(int** arr, const int rows, const int cols);

int* push_back(int arr[], int& n, const int value);
int* push_front(int arr[], int& n, const int value);

int* pop_back(int arr[], int& n);
int* pop_front(int arr[], int& n);

int* insert(int arr[], int& n, const int value, const int index);
int* erase(int arr[], int& n, const int index);

int** push_row_back(int** arr, int& rows, const int cols);
int** push_row_front(int** arr, int& rows, const int cols);
int** pop_row_back(int** arr, int& rows);
int** pop_row_front(int** arr, int& rows);

void push_col_back(int** arr, const int rows, int& cols);
void push_col_front(int** arr, const int rows, int& cols);
void pop_col_back(int** arr, const int rows, int& cols);
void pop_col_front(int** arr, const int rows, int& cols);

int** insert_row(int** arr, int& rows, const int cols, const int index);
int** erase_row(int** arr, int& rows, const int index);

void insert_col(int** arr, const int rows, int& cols, const int index);
void erase_col(int** arr, const int rows, int& cols, const int index);


//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	int* arr = new int[n];	//Объявление динамического массива
	//short  - short
	//short* - Указатель на 'short';
	//int  - 'int';
	//int* - Указатель на 'int';
	//double  - 'double';
	//double* - Указатель на 'double';

	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	delete[] arr;
	//Memory leak - утечка памяти.  
#endif // DYNAMIC_MEMORY_1

	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	int** arr = Allocate(rows, cols);

	// Copy- функция не изменяет переданную в нее память, а возращает изменненую копию полученной памяти
	//Mutable - Функция изменяет полученный блок памяти;



	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	for (int i = 0; i < rows; i++)arr[i][cols - 1] = rand() % 1000;
	Print(arr, rows, cols);

	int index;
	cout << "Введите индекс добавляемого значения:"; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	Print(arr, rows, cols);


	Clear(arr, rows, cols);

	////////		удаление двумерного динамического массива		///////



}


int** Allocate(const int rows, const int cols)
{
	////////		Объявление двумерного динамического массива		///////

	//1) Содаем массив указателей:
	int** arr = new int* [rows];

	//2) выделяем память под строки:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	return arr;
}

void Clear(int**& arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) только теперь можно удалить массив указателей:
	delete[] arr;

}

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;	//через арифметику указателей и оператор разыменования
	}
}
void FillRand(int** arr, const int rows, const int cols, int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % (maxRand - minRand) + minRand;
		}
	}
}
void Print(int arr[], const int n)
{
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";		//через оператор индексирования (Subscript operator)
	}
	cout << endl;
}
void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
	cout << endl;
}

int* push_back(int arr[], int& n, const int value)
{
	//1) создаем буферный массив нужного размера:
	int* buffer = new int[n + 1];

	//2) копируем все элементы из исходного массива в буферный:
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}

	//3) удаляем исходный массив:
	delete[] arr;

	//4) подменяем адрес исходного массива адресом нового массива:
	arr = buffer;
	//buffer = nullptr;	//nullptr - это указатель на 0;

	//5) только после всего вышенаписанного в массиве 'arr' появляется элемент, в который можно сохранить добавляемое значени:
	arr[n] = value;

	//6) после добавления элемента в массив, количество его элементов увеличивается на 1:
	n++;

	//7) Mission complete - значение добавлено.
	return buffer;
}

int* push_front(int arr[], int& n, const int value)
{
	//1) 
	int* buffer = new int[n + 1];
	//2)
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	//3)
	delete[] arr;

	//4)
	buffer[0] = value;

	//5)
	n++;

	return buffer;
}

int* pop_back(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
int* pop_front(int arr[], int& n)
{
	int* buffer = new int[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

int* insert(int arr[], int& n, const int value, const int index)
{
	int* buffer = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		if (i < index)buffer[i] = arr[i];
		else if (i == index)buffer[i] = value;
		else buffer[i] = arr[i - 1];
	}
	delete[] arr;
	n++;
	return buffer;
	
}
int* erase(int arr[], int& n, const int index)
{
	int* buffer = new int[n - 1];
	for (int i = 0; i < n - 1; i++)
	{
		if (i < index) buffer[i] = arr[i];
		else buffer[i] = arr[i + 1];
	}
	delete[] arr;
	n--;
	return buffer;
	
}

int** push_row_back(int** arr, int& rows, const int cols)
{
	//1) Создаём буфферный массив указателей нужного размера: 
	int** buffer = new int* [rows + 1];

	//2) Копируем адреса строк в новый массив: 
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}

	//3) Удаляем исходный массив указателей:
	delete[] arr;

	//4) Добавляем добавляемую строку:
	buffer[rows] = new int[cols] {};

	//5) После добавления строки, количество строк увеличивается на 1:
	rows++;

	//6) Возвращаем новый массив:
	return buffer;
}
int** push_row_front(int** arr, int& rows, const int cols)
{
	int** buffer = new int* [rows + 1];
	buffer[0] = new int[cols] {};
	for (int i = 0; i < rows; i++)buffer[i + 1] = arr[i];
	delete[] arr;
	rows++;
	return buffer;
}
int** pop_row_back(int** arr, int& rows)
{
	delete[] arr[rows - 1];
	int** buffer = new int* [--rows];
	for (int i = 0; i < rows; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
int** pop_row_front(int** arr, int& rows)
{
	delete[] arr[0];
	int** buffer = new int* [--rows];
	for (int i = 0; i < rows; i++) buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

void push_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		//1) Создаём буферную строку нужного размера: 
		int* buffer = new int[cols + 1] {};

		//2) копируем элементы из исходной строки в буферную:
		for (int j = 0; j < cols; j++)buffer[j] = arr[i][j];

		//3) Удаляем сходную строку:
		delete[] arr[i];

		//4) Подменяем адрес исходной строки адресом новой строки:
		arr[i] = buffer;
	}
	cols++;
}
void push_col_front(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < cols; j++)buffer[j + 1] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}
void pop_col_back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1];
		for (int j = 0; j < cols - 1; j++)buffer[j] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols--;
}
void pop_col_front(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1];
		for (int j = 0; j < cols - 1; j++)buffer[j] = arr[i][j + 1];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols--;
}

int** insert_row(int** arr, int& rows, const int cols, const int index)
{
	if (index < 0 || index>rows)
	{
		cout << "Error: Out of range exception" << endl;
		return arr;
	}
	int** buffer = new int* [rows + 1];
	for (int i = 0; i < rows + 1; i++)
	{
		buffer[i] = (i < index ? arr[i] : (i == index) ? new int[cols] {} : arr[i - 1]);
	}

	delete[] arr;
	rows++;
	return buffer;
}

int** erase_row(int** arr, int& rows, const int index)
{
	delete[] arr[index];
	int** buffer = new int* [--rows];
	for (int i = 0; i < index; i++)
	{
		buffer[i] = arr[i];
	}
	for (int i = index; i < rows; i++)
	{
		buffer[i] = arr[i + 1];
	}

	delete[] arr;
	return buffer;
}

void insert_col(int** arr, const int rows, int& cols, const int index)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < index; j++) buffer[j] = arr[i][j];
		buffer[index] = 0;
		for (int j = index; j < cols + 1; j++) buffer[j + 1] = arr[i][j];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols++;
}
void erase_col(int** arr, const int rows, int& cols, const int index)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1];
		for (int j = 0; j < index; j++)buffer[j] = arr[i][j];
		for (int j = index; j < cols - 1; j++)buffer[j] = arr[i][j + 1];
		delete[] arr[i];
		arr[i] = buffer;
	}
	cols--;
}