#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType *s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}

// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType *s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// �����Լ�
element pop(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

// ��ũ�Լ�
element peek(StackType *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

int palindrome(char str[])
{
	StackType s;
	init_stack(&s);
	int i = 0;
	char ch, chs;
	int len = strlen(str);

	for (i = 0; i < len; i++)
	{
		ch = str[i];

		if (ispunct(ch) != 0 || ch == ' ')
			continue;

		ch = tolower(ch);
		push(&s, ch);
	}

	for (i = 0; i < len; i++)
	{
		ch = str[i];

		if (ispunct(ch) != 0 || ch == ' ')
			continue;

		ch = tolower(ch);
		chs = pop(&s);

		if (ch != chs)
			return 0;
	}

	return 1;
}

int main(void) {

	int check = 0;
	char str[MAX_STACK_SIZE];

	printf("���ڿ��� �Է��Ͻÿ�. : ");
	scanf("%[^\n]s", str);

	check = palindrome(str);

	if (check == 1)
		printf("%s��(��) ȸ���Դϴ�.\n", str);
	else
		printf("%s��(��) ȸ���� �ƴմϴ�.\n", str);

	return 0;
}