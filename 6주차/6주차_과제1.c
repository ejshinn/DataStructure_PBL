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

int check_matching(const char *in)
{
	StackType s1;
	StackType s2;
	char ch, open_ch;
	int i, n = strlen(in); // n= ���ڿ��� ����
	int cnt = 1;
	init_stack(&s1);         // ������ �ʱ�ȭ
	init_stack(&s2);

	for (i = 0; i < n; i++)
	{
		ch = in[i];      // ch = ���� ����
		switch (ch) {
		case '(':   case '[':    case '{':
			push(&s1, ch);
			push(&s2, cnt);
			printf("%d ", cnt);
			cnt++;
			break;
		case ')':   case ']':    case '}':
			if (is_empty(&s1) || is_empty(&s2))  return 0;
			else
			{
				open_ch = pop(&s1);
				if (open_ch == '(' && ch != ')' || open_ch == '[' && ch != ']' || open_ch == '{' && ch != '}')
					return 0;

				else
					printf("%d ", pop(&s2));

				break;
			}
		}
	}
	if (!is_empty(&s1) || !is_empty(&s2)) return 0; // ���ÿ� ���������� ����
	return 1;
}

int main(void)
{
	char str[MAX_STACK_SIZE];
	int sel = 0;
	while (1)
	{
		printf("����: ");  scanf("%s", str);

		if (check_matching(str) == 1)
			printf("\n��ȣ�˻� ����\n");
		else
			printf("\n��ȣ�˻� ����\n");

		printf("\n1.���  2.�ߴ�: "); scanf("%d", &sel);
		if (sel != 1)
			break;
	}
	return 0;
}