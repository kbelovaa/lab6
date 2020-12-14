// spo6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

HANDLE hSemaphore;
const int n = 20;
LONG a[n];

int thread1()
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 500;
		Sleep(100);
		cout << a[i] << " ";
		ReleaseSemaphore(hSemaphore, 1, NULL);
	}
	return 0;
}

int thread2()
{
	int sum = 0;
	int k = 0;
	for (int i = 0; i < n; i++) {
		WaitForSingleObject(hSemaphore, INFINITE);
		if (i % 2 == 0)
		{
			sum += a[i];
			k++;
			cout << "(" << sum / k << ") ";
		}
	}
	return 0;
}

int main()
{
	hSemaphore = CreateSemaphore(NULL, 0, n, TEXT("MySemaphore"));
	if (hSemaphore == NULL) cout << "Create semaphore failed" << GetLastError() << endl;
	HANDLE hTh01 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread1, NULL, 0, NULL);
	if (hTh01 == NULL) return GetLastError();

	HANDLE hTh02 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread2, NULL, 0, NULL);
	if (hTh02 == NULL) return GetLastError();

	cin.get();
	CloseHandle(hSemaphore);
	CloseHandle(hTh01);
	CloseHandle(hTh02);
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
