#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(void) {

	char str[MAX_STACK_SIZE];

	printf("���ڿ��� �Է��Ͻÿ�. : ");
	scanf_s("%s", str, sizeof(str));

	StackType s1, s2;
	init_stack(&s1);
	init_stack(&s2);
	int i = 0, count = 0;

	while (str[i] != 0)
	{
		count = 1;
		char ch = str[i++];

		while (ch == str[i] || ch + ('A' - 'a') == str[i] || ch - ('A' - 'a') == str[i])
		{
			count++;
			i++;
		}

		push(&s1, count + '0');

		if ('a' <= ch && ch <= 'z')
			push(&s1, ch);
		else
			push(&s1, ch - ('A' - 'a'));
	}

	while (!is_empty(&s1))
	{
		push(&s2, peek(&s1));
		pop(&s1);
	}

	printf("����� ���ڿ� : ");
	while (!is_empty(&s2))
	{
		printf("%c", pop(&s2));
	}
	return 0;
}