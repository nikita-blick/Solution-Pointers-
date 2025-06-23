#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>T** Allocate(const int rows, const int cols);
template<typename T>void Clear(T**& arr, const int rows, const int cols = 0);

int* FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);
double* FillRand(double arr[], const int n, int minRand = 0, int maxRand = 100);
int** FillRand(int** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);
double** FillRand(double** arr, const int rows, const int cols, int minRand = 0, int maxRand = 100);

template<typename T> void Print(T arr[], const int n);
template<typename T> void Print(T** arr, const int rows, const int cols);

template<typename T>T* push_back(T arr[], int& n, const T value);
template<typename T>T* push_front(T arr[], int& n, const T value);
template<typename T>T* insert(T arr[], int& n, const T value, const int index);

template<typename T>T* pop_back(T arr[], int& n);
template<typename T>T* pop_front(T arr[], int& n);

template<typename T>T** push_row_back(T** arr, int& rows, const int cols);
template<typename T>T** push_row_front(T** arr, int& rows, const int cols);

template<typename T>T** insert_row(T** arr, int& rows, const int cols, const int index);

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols);
template<typename T>T** pop_row_front(T** arr, int& rows, const int cols);


template<typename T>void push_col_back(T** arr, const int rows, int& cols);


//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

#define DATATYPE double
typedef double DataType;

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1
	int n;
	cout << "Введите размер массива: "; cin >> n;
	DataType* arr = new DataType[n];	// объявление динамического массива

	FillRand(arr, n);
	Print(arr, n);

	DataType value;
	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_back(arr, n, value);
	Print(arr, n);

	cout << "Введите добавляемое значение: "; cin >> value;
	arr = push_front(arr, n, value);
	Print(arr, n);

	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	//arr = insert(arr, n, value, index);
	//Print(arr, n);
	Print(arr = insert(arr, n, value, index), n);

	arr = pop_back(arr, n);
	Print(arr, n);

	arr = pop_front(arr, n);
	Print(arr, n);

	delete[] arr;
	//Memory leak - утечка памяти.  
#endif // DYNAMIC_MEMORY_1

#ifdef DYNAMIC_MEMORY_2
	int rows;
	int cols;
	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество элементов строки: "; cin >> cols;

	DataType** arr = Allocate<DataType>(rows, cols);

	//Copy	  - функция НЕ изменяет переданную в нее память, а возвращает измененную копию полученной памяти.
	//Mutable - Функция изменяет полученный блок памяти;

	///	///////////////////////////////////////////////////////////////	///

	//FillRand(arr, rows, cols);
	//Print(arr, rows, cols);
	Print(FillRand(arr, rows, cols), rows, cols);

	arr = push_row_back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 1000);
	Print(arr, rows, cols);

	/*
	Print(FillRand(arr = push_row_back(arr, rows, cols))[rows - 1], cols), rows, cols);
	Print(arr, rows, cols);*/


	arr = push_row_front(arr, rows, cols);
	Print(arr, rows, cols);

	push_col_back(arr, rows, cols);
	for (int i = 0; i < rows; i++)arr[i][cols - 1] = rand() % 1000;
	Print(arr, rows, cols);

	int index;
	cout << "Введите индекс добавляемой строки: "; cin >> index;
	arr = insert_row(arr, rows, cols, index);
	Print(arr, rows, cols);

	arr = pop_row_back(arr, rows, cols);
	Print(arr, rows, cols);

	Print(arr = pop_row_back(arr, rows, cols), rows, cols);
	Print(arr = pop_row_front(arr, rows, cols), rows, cols);








	///	///////////////////////////////////////////////////////////////	///

	Clear(arr, rows, cols);
#endif // DYNAMIC_MEMORY_2




}

template<typename T>T** Allocate(const int rows, const int cols)
{
	
	////////		объявление двумерного динамического массива		///////
	

	//1) содаем массив указателей:
	T** arr = new T * [rows];

	//2) выделяем память под строки:
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new T[cols];
	}

	return arr;
}
template<typename T>void Clear(T**& arr, const int rows, const int cols)
{
	
	////////		удаление двумерного динамического массива		///////
	

	//1) сначала удаляются строки двумерного массива:
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}

	//2) только теперь можно удалить массив указателей:
	delete[] arr;

	//3) зануляем указатель на массив
	arr = nullptr;
}

int* FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;	// через арифметику указателей и оператор разыменования
	}
	return arr;
}
double* FillRand(double arr[], const int n, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = rand() % (maxRand - minRand) + minRand;	// через арифметику указателей и оператор разыменования
		arr[i] /= 100;
	}
	return arr;
}
int** FillRand(int** arr, const int rows, const int cols, int minRand, int maxRand)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % (maxRand - minRand) + minRand;
		}
	}
	return arr;
}
double** FillRand(double** arr, const int rows, const int cols, int minRand, int maxRand)
{
	minRand *= 100;
	maxRand *= 100;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = double(rand() % (maxRand - minRand) + minRand) / 100;
		}
	}
	return arr; 
}

template<typename T>void Print(T arr[], const int n)
{
	cout << arr << endl;
	cout << *arr << endl;
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";		// через оператор индексирования (Subscript operator)
	}
	cout << endl;
}
template<typename T>void Print(T** arr, const int rows, const int cols)
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

template<typename T>T* push_back(T arr[], int& n, const T value)
{
	//1) создаем буферный массив нужного размера:
	T* buffer = new T[n + 1];

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
	return arr;
}

template<typename T>T* push_front(T arr[], int& n, const T value)
{
	T* buffer = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[] arr;
	buffer[0] = value;
	n++;
	return arr;
}

template<typename T>T* insert(T arr[], int& n, const T value, const int index)
{
	T* buffer = new T[n + 1]{};
	for (int i = 0; i < n; i++)buffer[i < index ? i : i + 1] = arr[i];
	delete[] arr;
	buffer[index] = value;
	n++;
	return buffer;
}

template<typename T>T* pop_back(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	return buffer;
}
template<typename T>T* pop_front(T arr[], int& n)
{
	T* buffer = new T[--n];
	for (int i = 0; i < n; i++)buffer[i] = arr[i + 1];
	delete[] arr;
	return buffer;
}

template<typename T>T** push_row_back(T** arr, int& rows, const int cols)
{
	/*//1) создаем буферный массив указателей нужного размера:
	T** buffer = new T * [rows + 1];
	//2) копируем адреса строк в новый массив:
	for (int i = 0; i < rows; i++)
	{
		buffer[i] = arr[i];
	}
	//3) удаляем исходный массив указателейЖ
	delete[] arr;
	//4) добавляем добавляемую строку:
	buffer[rows] = new T[cols]{};
	//5) после добавления строки, количество строк увеличивается на 1:
	rows++;
	//6) возвращаем новый массив:
	return buffer;*/

	return push_back(arr, rows, new T[cols]);
	// повторное использование кода (Reusable code)
	// DRY - Don`t Repeat Yourself
}
template<typename T>T** push_row_front(T** arr, int& rows, const int cols)
{
	return push_front(arr, rows, new T[cols]{});
}

template<typename T>T** insert_row(T** arr, int& rows, const int cols, const int index)
{
	if (index<0 || index>rows)
	{
		cout << "Error: Out of range exception" << endl;
		return arr;
	}
	return insert(arr, rows, new T[cols]{}, index);
}

template<typename T>T** pop_row_back(T** arr, int& rows, const int cols)
{
	delete[] arr[rows - 1];
	return pop_back(arr, rows);

}
template<typename T>T** pop_row_front(T** arr, int& rows, const int cols)
{
	delete[] arr[0];
	return pop_front(arr, rows);
}

template<typename T>void push_col_back(T** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		arr[i] = push_back(arr[i], cols, T());   //T() - значение по умолчанию для шаблонного типа.
		cols--;
	}
	cols++;
}