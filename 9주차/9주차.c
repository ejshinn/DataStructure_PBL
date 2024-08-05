#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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

int check_matching(FILE *fp)
{
	StackType s;
	char ch, open_ch;
	init_stack(&s);         // ������ �ʱ�ȭ
	int sq = 0, dq = 0, an_pre = 0, an = 0, star_an = 0, star_an_pre = 0;
	FILE* fp2 = fopen("stack.out", "w");

	while ((ch = getc(fp)) != EOF) {
		//�ּ� or �Ϲ� ����
		if (ch == '/' && an_pre == 1)
			an = 1;
		else if (ch == '*' && an_pre == 1)
			star_an = 1;
		else
			an_pre = 0;

		//�� �ּ� ���� or �Ϲ� ����
		if (ch == '/' && star_an_pre == 1)
			star_an = 0;
		else
			star_an_pre = 0;

		//����
		if (ch == '\n')
			an = 0;

		//���� ����ǥ
		if (ch == '\''&& sq == 0)
			sq = 1;
		else if (ch == '\'')
			sq = 0;

		//ū ����ǥ
		if (ch == '"' && dq == 0)
			dq = 1;
		else if (ch == '"')
			dq = 0;

		//�ּ�
		if (ch == '/' && an_pre == 0)
			an_pre = 1;
		if (ch == '*' && star_an == 1)
			star_an_pre = 1;

		//��ȣ �˻�
		if (ch == '(' || ch == '[' || ch == '{')
		{
			if (sq == 0 && dq == 0 && an == 0 && star_an == 0)
			{
				push(&s, ch);
				printf("push %c\n", peek(&s));
				fprintf(fp2, "push %c\n", ch);
			}
		}

		else if (ch == ')' || ch == ']' || ch == '}')
		{
			if (sq == 0 && dq == 0 && an == 0 && star_an == 0)
			{
				if (is_empty(&s))  return 0;
				else {
					open_ch = pop(&s); 
					printf("pop %c\n", open_ch);
					fprintf(fp2, "pop %c\n", open_ch);
					if ((open_ch == '(' && ch != ')') ||
						(open_ch == '[' && ch != ']') ||
						(open_ch == '{' && ch != '}')) {
						return 0;
					}
				}
			}
		}
	}

	fclose(fp2);
	if (!is_empty(&s)) return 0; // ���ÿ� ���������� ����
	return 1;
}

int main(void)
{
	FILE* fp1 = fopen("stack.in", "r");
	if (fp1 == NULL) {
		printf("������ �� �� �����ϴ�.\n");
		exit(1);
	}

	int result = check_matching(fp1);

	FILE* fp2 = fopen("stack.out", "a");
	if (result == 1) {
		printf("��ȣ�˻� ����\n");
		fputs("��ȣ�˻� ����\n", fp2);
	}
	else {
		printf("��ȣ�˻� ����\n");
		fputs("��ȣ�˻� ����\n", fp2);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}