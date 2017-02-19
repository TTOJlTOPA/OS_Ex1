#include <iostream>
#include <Windows.h>
using namespace std;

DWORD WINAPI Calculate(LPVOID lpParameters)
{
	int* pol = (int*)lpParameters;
	int result = 0;

	cout << "Deg: " << pol[1] << "\n";
	for (int i = 2; i < pol[1] + 3; i++) {
		result += pol[i] * pow(pol[0], i - 2);
		cout << pol[i] << " ";
		Sleep(17);
	}
	cout << "\n";
	cout << "p(" << pol[0] << ") = " << result << "\n";

	return result;
}