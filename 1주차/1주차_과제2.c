#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int function1(char str[]);
int function2(char *p);
int function3(char *p);

int main(void) {

	char str[100];

	printf("���ڿ� �Է�: ");
	scanf("%[^\n]s", str);

	printf("\n< ���� 2-1 > \n");
	printf("�Է��� ���ڿ��� ����: %d \n\n", function1(str));

	printf("< ���� 2-2 > \n");
	printf("�Է��� ���ڿ��� ����: %d \n\n", function2(str));

	printf("< ���� 2-3 > \n");
	printf("�Է��� ���ڿ��� ����: %d \n\n", function3(str));

	return 0;
}

int function1(char str[])
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return len;
}

int function2(char *p)
{
	int i = 0;
	while (*(p + i) != '\0')
		i++;
	return i;
}

int function3(char *p) {
	if (*p == '\0') return 0;
	else return (1 + function3(p + 1));
}