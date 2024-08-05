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
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init_stack(&s);
	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '%' && ch != '^' && ch != '>' && ch != '<' && ch != '&' && ch != '|')
		{
			value = ch - '0';
			push(&s, value);
			printf("push %d\n", peek(&s));
		}
		else
		{
			op2 = pop(&s); printf("pop %d\n", op2);
			op1 = pop(&s); printf("pop %d\n", op1);
			switch (ch) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			case '%': push(&s, op1 % op2); break;
			case '^': push(&s, (int)pow(op1, op2)); break;
			case '<': push(&s, op1 < op2); break;
			case '>': push(&s, op1 > op2); break;
			case '&': push(&s, op1 && op2); break;
			case '|': push(&s, op1 || op2); break;
			}
			printf("%d %c %d ��� ��� push %d\n", op1, ch, op2, peek(&s));
		}
	}
	return pop(&s);
}

int num = 5;

int prec(char op)
{
	switch (op) {
	case '(': case ')': return 0;
	case '&': return 1;
	case '|': return 2;
	case '>': case '<': return 3;
	case '+': case '-': return 4;
	case '*': case '/': case '%': return 5;
	case '^': return ++num;
	}
	return -1;
}

void infix_to_postfix(char *pf, char exp[])
{
	int i = 0;
	char ch, top_op;
	int len = strlen(exp);
	StackType s;

	init_stack(&s);

	for (i = 0; i < len; i++)
	{
		ch = exp[i];
		switch (ch) {
		case '+': case '-': case '*': case '/': case '%': case '^': case '<': case '>': case '&': case '|':
			//���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ���
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
			{
				if (ch == '^' && (prec(ch) < prec(peek(&s))))
					break;
				printf("pop %c\n", peek(&s));
				*pf++ = pop(&s);
			}
			push(&s, ch);
			printf("push %c\n", peek(&s));
			break;
		case '(':
			push(&s, ch);
			printf("push %c\n", peek(&s));
			break;
		case ')':
			printf("pop %c\n", peek(&s));
			top_op = pop(&s);
			//���� ��ȣ�� ���� ������ ���
			while (top_op != '(')
			{
				printf("pop %c\n", peek(&s));
				*pf++ = top_op;
				top_op = pop(&s);
			}
			break;
		default: //�ǿ�����
			*pf++ = ch;
			break;
		}
	}
	while (!is_empty(&s)) //���ÿ� ����� �����ڵ� ���
	{
		printf("pop %c\n", peek(&s));
		*pf++ = pop(&s);
	}
	*pf = '\0';
}

printf("test (((( } ")
/* ((( }} */
// (((]]]

int main(void)
{
	int result = 0, sel = 0;
	char infix[MAX_STACK_SIZE];
	char * postfix = (char *)malloc(sizeof(char) * 100);

	while (1)
	{
		printf("����ǥ�����: ");  scanf("%s", infix);

		infix_to_postfix(postfix, infix);
		printf("����ǥ�����: %s\n\n", postfix);

		result = eval(postfix);
		printf("�����: %d\n", result);

		printf("\n1.���  2.����: "); scanf("%d", &sel);
		if (sel != 1)
			break;
	}

	free(postfix);
	return 0;
}