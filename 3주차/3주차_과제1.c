#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_DEGREE 101

typedef struct {
	int degree;
	int coef[MAX_DEGREE];
}polynomial;

polynomial input_poly()
{
	polynomial p;

	while (1)
	{
		printf("���׽��� �ְ�����: ");
		scanf("%d", &p.degree);
		if (p.degree >= 0)
			break;
		else
			printf("0�̻��� ���� �ٽ� �Է��ϼ���.\n\n");
	}

	for (int i = 0; i <= p.degree; i++)
	{
		printf("x^%d�� ���: ", p.degree - i);
		scanf("%d", &p.coef[i]);
	}

	return p;
}

void print_poly(polynomial p)
{
	printf("\nA(x) = ");
	for (int i = p.degree; i > 0; i--)
	{
		if (p.coef[p.degree - i] != 0)
			printf("%dx^%d + ", p.coef[p.degree - i], i);
	}

	printf("%d\n", p.coef[p.degree]);
}

int calculation(polynomial p, int x)
{
	int k = 0, result = 0, tmp = 0;

	if (p.degree == 0)
		return p.coef[0];

	else
	{
		for (int i = p.degree; i >= 0; i--)
		{
			tmp = 1;

			for (int j = p.degree; j > p.degree - i; j--)
			{
				tmp *= x;
			}

			result += (p.coef[k++] * tmp);
		}
		return result;
	}
}

int main(void) {

	polynomial a;
	int x, num1, num2;

	while (1)
	{
		num2 = 0;
		a = input_poly();
		print_poly(a);

		while (1)
		{
			x = 0, num1 = 0;

			printf("x��: ");
			scanf("%d", &x);

			printf("A(%d) = %d\n", x, calculation(a, x));

			printf("\n�ٸ� x���� �����Ϸ��� �ƹ� ����(0 ����)��, �׸��Ϸ��� 0�� �Է��ϼ���: ");
			scanf("%d", &num1);

			if (num1 == 0)
				break;
		}

		printf("\n�ٸ� ���׽��� �Է��Ϸ��� �ƹ� ����(0 ����)��, �׸��Ϸ��� 0�� �Է��ϼ���: ");
		scanf("%d", &num2);

		if (num2 == 0)
			break;
	}
	return 0;
}