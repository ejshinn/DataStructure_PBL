#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100

typedef int element;
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

int eval(char exp[])
{
	int op1, op2, value, i = 0, cnt = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<')
		{
			value = ch - '0';
			push(&s, value); ++cnt;
			printf("push %d\n", peek(&s));
		}
		else
		{
			op2 = pop(&s); printf("pop %d\n", op2); --cnt;
			op1 = pop(&s); printf("pop %d\n", op1); --cnt;
			switch (ch) {
			case '+':
				push(&s, op1 + op2); ++cnt;  break;
			case '-':
				push(&s, op1 - op2); ++cnt;  break;
			case '*':
				push(&s, op1 * op2); ++cnt;  break;
			case '/':
				push(&s, op1 / op2); ++cnt;  break;
			case '%':
				push(&s, op1 % op2); ++cnt;  break;
			case '^':
				push(&s, (int)pow(op1, op2)); ++cnt; break;
			case '>':
				push(&s, op1 > op2);  ++cnt;  break;
			case '<':
				push(&s, op1 < op2); ++cnt;  break;
			}
			printf("%d %c %d ��� ��� push %d\n", op1, ch, op2, peek(&s));
		}

	}
	if (cnt != 1)
		return -1;

	return pop(&s);
}

/*
	712%+15*-    ���: 3
	4223^^+3-    ���: 257
	25+1-41*3^>  ���: 0

	�Է¿���
	2323+   ������ �� ����
	23+++   �ǿ����� �� ����
	2+3     ����ǥ��
*/

int main(void)
{
	int result = 0, sel = 0;
	char postfix[MAX_STACK_SIZE];

	while (1)
	{
		printf("����ǥ�� �Է�: ");  scanf("%s", postfix);

		result = eval(postfix);
		if (result == -1)
			printf("�ǿ����� �� > ������ ��");
		else
			printf("������ ���� %d\n", result);

		printf("\n1.���  2.����: "); scanf("%d", &sel);
		if (sel != 1)
			break;
	}

	return 0;
}