#include<iostream>
using namespace std;

int main()
{
	int T = 0;
	char H = 20, M = 13, S = 49;

	__asm
	{
		movzx eax, H
		imul eax, 3600

		movzx ebx, M
		imul ebx, 60

		movzx ecx, S

		add eax, ebx
		add eax, ecx
		mov T, eax
	}

	cout << "Result: " << T << endl;
	return 0;

}