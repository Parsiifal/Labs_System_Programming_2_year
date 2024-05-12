#include<iostream>
using namespace std;

// Вычислить систему X = a^(b) + 5, если a > b; или -15b, если a = b; или (ab - 20) / b, если a < b
int main()
{
	int a = 0, b = 0, result_c = 0, result_asm = 0, of = 0, zf = 0, neg_degree = 0;
	cout << "Input a, b:" << endl;
	cin >> a >> b;
	
	if (a > b)
		result_c = pow(a, b) + 5;
	else if (a < b && b != 0)
		result_c = (a * b - 20) / b;
	else
		result_c = -15 * b;
	
	__asm
	{
		mov eax, a; <eax> = a
		mov ebx, b; <ebx> = b
		cmp eax, ebx; сравнение a и b
		jg l_bigger; переход если a > b
		jl l_smaller; переход если a < b

		imul ebx, -15; <ebx> = -15 * b
		jo overflow; ошибка переполнения

		mov result_asm, ebx; сохраняем результат
		jmp end_programm; переход на конец программы

		l_bigger:
			cmp ebx, 0; сравниваем степень с 0
			jl negative_degree; переход если степень отрицательная (b < 0)
			jne non_zero_degree; переход если степень ненулевая (b != 0)
			mov eax, 1; <eax> = 1
			jmp loop_end; пропускаем цикл возведения в степень

		; возведение в степень b
		non_zero_degree:
			mov edx, eax; для цикла
			mov ecx, 1; <ecx> = 1 - начальное значение степени

		exponentiation_loop:
			cmp ecx, ebx; сравниваем текущую степень с числом b
			jge loop_end; если степень a >= b, выходим из цикла

			imul eax, edx; <eax> = a^(ecx)
			jo overflow; ошибка переполнения

			add ecx, 1; <ecx> += 1
			jo overflow; ошибка переполнения

			jmp exponentiation_loop; следующая итерация

		loop_end:
			add eax, 5; <eax> = a^(b) + 5
			jo overflow; ошибка переполнения
			mov result_asm, eax; сохраняем результат
			jmp end_programm; переход на конец программы
				
		l_smaller:
			; обработка деления на 0
			cmp ebx, 0; сравниваем b с 0, если числа равны = > ZF = 1
			jz zero_flag; ошибка делитель = 0

			imul eax, ebx; <eax> = a * b
			jo overflow; ошибка переполнения

			sub eax, 20; <eax> = a * b - 20
			jo overflow; ошибка переполнения

			cdq; eax ==> <edx:eax> = a * b - 20
			idiv ebx; <edx:eax> = (a * b - 20) / b

			mov result_asm, eax; сохраняем результат
			jmp end_programm; переход на конец программы

		negative_degree:
			mov neg_degree, 1
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
	else if (neg_degree == 1)
	{
		cout << "\nError, negative degree!" << endl;
		return -1;
	}
	else
	{
		cout << "\nResult C++: " << result_c << endl;
		cout << "Result asm: " << result_asm << endl;
		return 0;
	}

}