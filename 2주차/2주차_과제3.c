#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct complex {
	double real;
	double imag;
}Complex;

Complex add(Complex * arr)
{
	Complex result = { 0.0, 0.0 };

	for (int i = 0; i < 10; i++)
	{
		result.real += arr[i].real;
		result.imag += arr[i].imag;
	}
	return result;
}

int main(void) {

	Complex arr[10];

	printf("< ���� 3 > \n");
	printf("���Ҽ� 10�� �Է�(�Ǽ��� �����)\n");

	for (int i = 0; i < 10; i++)
	{
		printf("(%d) ", i + 1);
		scanf("%lf %lf", &arr[i].real, &arr[i].imag);
	}

	printf("\n���� ���: %g + %gi\n", add(arr).real, add(arr).imag);
	return 0;
}