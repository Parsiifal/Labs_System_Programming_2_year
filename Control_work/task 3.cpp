#include<iostream>
using namespace std;

int main()
{
	short N = 157;

	__asm
	{
		mov ax, N
		mov cx, 10

		; Извлекаем единицы
		xor dx, dx
		div cx
		mov bx, dx

		; Извлекаем десятки
		imul bx, 10
		xor dx, dx
		div cx
		add bx, dx

		; Извлекаем сотни
		imul bx, 10
		add bx, ax

		mov N, bx

	}

	cout << "Result: " << (int)N << endl;
	return 0;

}