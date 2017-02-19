#include <iostream>
#include <Windows.h>
using namespace std;

DWORD WINAPI Calculate(LPVOID lpParameters);

DWORD WINAPI Input(LPVOID lpParameters)
{
	HANDLE polynom1;
	HANDLE polynom2;
	DWORD IDPolynom1;
	DWORD IDPolynom2;
	DWORD retVal;

	int argument;
	int deg1;
	int deg2;
	int num;
	int denom;
	double div;
	int* pol1;
	int* pol2;

	cout << "Enter deg of numerator: ";
	cin >> deg1;
	pol1 = new int[deg1 + 3];
	pol1[1] = deg1;
	cout << "Enter coefs of numerator: ";
	for (int i = 2; i < deg1 + 3; i++) {
		cin >> pol1[i];
	}
	cout << "Enter deg of denominator: ";
	cin >> deg2;
	pol2 = new int[deg2 + 3];
	pol2[1] = deg2;
	cout << "Enter coefs of denominator: ";
	for (int i = 2; i < deg2 + 3; i++) {
		cin >> pol2[i];
	}
	cout << "Enter the argument: ";
	cin >> argument;
	pol1[0] = argument;
	pol2[0] = argument;

	polynom1 = CreateThread(NULL, 0, Calculate, (void*)pol1, 0, &IDPolynom1);
	polynom2 = CreateThread(NULL, 0, Calculate, (void*)pol2, 0, &IDPolynom2);
	if (polynom1 == NULL || polynom2 == NULL) {
		return GetLastError();
	}

	HANDLE arr[2] = { polynom1, polynom2 };
	WaitForMultipleObjects(2, arr, TRUE, INFINITE);
	GetExitCodeThread(polynom1, &retVal);
	num = (int)retVal;
	GetExitCodeThread(polynom2, &retVal);
	denom = (int)retVal;
	CloseHandle(polynom1);
	CloseHandle(polynom2);

	div = (double)num / (double)denom;
	cout << "f(" << argument << ") = " << div << "\n";

	delete[] pol1;
	delete[] pol2;

	return 0;
}