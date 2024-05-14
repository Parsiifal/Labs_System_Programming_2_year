#include<iostream>
using namespace std;

int main()
{
	short X = 1, Y = 8, Z = 6, W = 0;

	__asm
	{
		mov ax, 9
		mov cx, Z

		cmp cx, 0
		jz end_programm

		cwd
		idiv cx
		mov cx, dx; посчитали выражение с Z

		mov bx, Y
		sub bx, 2; посчитали выражение с Y
		jo end_programm

		mov ax, X
		imul ax, 10; посчитали выражение с X
		jo end_programm

		cmp bx, cx
		jle y_less
		jg z_less

		z_less:
			cmp ax, cx
			jle x_less
			mov W, cx
			jmp end_programm

		y_less:
			cmp ax, bx
			jle x_less
			mov W, bx
			jmp end_programm

		x_less:
			mov W, ax

		end_programm:

	}

	cout << "Result: " << (int)W << endl;
	return 0;

}