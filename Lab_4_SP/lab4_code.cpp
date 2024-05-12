#include<iostream>
using namespace std;

// Найти сумму кубов всех положительных элементов массива
int main()
{
	int siz, result_c = 0, result_asm = 0, of = 0;
	cout << "Enter array size: ";
	cin >> siz;
	int* mas;
	if(siz > 0)
	{
		mas = new int[siz];
		cout << "Enter elements: \n";
		for (int i = 0; i < siz; i++)
		{
			cin >> mas[i];
			if (mas[i] > 0)
			{
				result_c += pow(mas[i], 3);
			}
		}
	}
	else
	{
		cout << "\nError!" << endl;
		return -1;
	}
	
	__asm
	{
		xor esi, esi; подготовим регистр индекса в массиве
		mov ebx, mas; ebx указывает на начало массива
		mov ecx, siz; счётчик цикла по всем элементам массива
		jecxz end_programm; завершить если длина массива 0

		begin_loop:
			mov eax, [ebx + esi * 4]; определяем текущий элемент
			cmp eax, 0; сравнение a[i] и 0
			jl end_loop; если меньше, то завершаем цикл

			mov edx, eax; помещаем текущий элемент для возведения в куб

			imul eax, eax; сначала возводим в квадрат
			jo overflow; ошибка переполнения

			imul eax, edx; далее возводим в куб
			jo overflow; ошибка переполнения

			add result_asm, eax; записываем в сумму кубов
			jo overflow; ошибка переполнения

		end_loop:
			add esi, 1; переходим к следующему элементу
			jo overflow; ошибка переполнения
			loop begin_loop; повторяем цикл для всех элементов массива
			jmp end_programm

		overflow:
			mov of, 1
			jmp end_programm

		end_programm:

	}

	if (of == 1)
	{
		cout << "\nError, overflow!" << endl;
		return -1;
	}
	else
	{
		cout << "\nArray: [ ";
		for (int i = 0; i < siz - 1; i++)
		{
			cout << mas[i] << ", ";
		}
		cout << mas[siz - 1] << " ]\n";
		cout << "Result C++: " << result_c << endl;
		cout << "Result asm: " << result_asm << endl;
		return 0;
	}

}