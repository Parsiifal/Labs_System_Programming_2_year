#include<iostream>
using namespace std;

int main()
{
	int N = 956;

	__asm
	{
		mov eax, N
		mov ecx, 10

		; Извлекаем единицы
		xor edx, edx
		div ecx
		mov ebx, edx

		; Извлекаем десятки
		imul ebx, 10
		xor edx, edx
		div ecx
		add ebx, edx

		; Извлекаем сотни
		imul ebx, 10
		add ebx, eax

		mov N, ebx

	}

	cout << "Result: " << N << endl;
	return 0;

}