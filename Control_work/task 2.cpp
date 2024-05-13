#include<iostream>
using namespace std;

int main()
{
	short X = 1, Y = 5, Z = 7, W = 0;

	__asm
	{
		mov ax, 9
		mov cx, Z
		xor dx, dx
		idiv cx
		mov cx, dx; посчитали выражение с Z

		mov bx, Y
		sub bx, 2; посчитали выражение с Y

		mov ax, X
		imul ax, 10; посчитали выражение с X

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