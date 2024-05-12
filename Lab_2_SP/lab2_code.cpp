#include<iostream>
using namespace std;

// Вычислить (2 * c + 5 - b) / (2 * b / a - 60)
int main()
{
	int a = 0, b = 0, c = 0, result_c = 0, result_asm = 0, of = 0, zf = 0;
	cin >> a >> b >> c;

	// считаем только если делители не равны 0
	if (a != 0 && (2 * b / a - 60) != 0)
		result_c = (2 * c + 5 - b) / (2 * b / a - 60);

	__asm
	{
		mov eax, b; <eax> = b
		mov ebx, a; <ebx> = a

		; сначала считаем вторую скобку

		; обработка деления на 0
		cmp ebx, 0; сравниваем а с 0, если числа равны = > ZF = 1
		jz zero_flag; ошибка делитель = 0

		cdq; eax ==> edx:eax
		idiv ebx; <eax> = b / a

		imul eax, 2; <eax> = 2 * b / a
		jo overflow; ошибка переполнения

		sub eax, 60; <eax> = 2 * b / a - 60
		jo overflow; ошибка переполнения

		push eax; в стеке 2 * b / a - 60

		; считаем первую скобку

		mov eax, c; <eax> = c
		imul eax, 2; <eax> = 2 * c
		jo overflow; ошибка переполнения

		add eax, 5; <eax> = 2 * c + 5
		jo overflow; ошибка переполнения

		mov ebx, b; <ebx> = b
		sub eax, ebx; <eax> = 2 * c + 5 - b
		jo overflow; ошибка переполнения

		pop ebx; <ebx> = 2 * b / a - 60
		; обработка деления на 0
		cmp ebx, 0; сравниваем вторую скобку с 0, если числа равны = > ZF = 1
		jz zero_flag; ошибка делитель = 0
		
		cdq; eax ==> <edx:eax> = 2 * c + 5 - b
		idiv ebx; <edx:eax> = (2 * c + 5 - b) / (2 * b / a - 60)

		mov result_asm, eax; сохраняем результат в переменную result_asm
		jmp end_programm

		zero_flag:
			mov zf, 1
			jmp end_programm

		overflow:
			mov of, 1
			jmp end_programm

		end_programm:

	}

	if (zf == 1)
	{
		cout << "\nError, division by zero!" << endl;
		return -1;
	}
	else if (of == 1)
	{
		cout << "\nError, overflow!" << endl;
		return -1;
	}
	else
	{
		cout << "\nResult C++: " << result_c << endl;
		cout << "Result asm: " << result_asm << endl;
		return 0;
	}

}