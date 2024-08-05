#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct DListNode { //���߿��� ��� Ÿ��
	char title[30];
	char genre;
	int year;
	int time;
	struct DListNode *llink;
	struct DListNode *rlink;
}DListNode;

DListNode* current;

//���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

//���� ���� ����Ʈ�� ���
void print_dlist(DListNode* phead)
{
	if (phead->rlink == phead)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	else {
		DListNode* p;
		for (p = phead->rlink; p != phead; p = p->rlink) {
			printf("\n��ȭ����: %s\n", p->title);
			printf("�帣: %c\n", p->genre);
			printf("�����⵵: %d\n", p->year);
			printf("����ð�: %d\n", p->time);
		}
		printf("\n");
	}
}

//���ο� �����͸� ������� �����ʿ� �����ϴ� �Լ�
void dinsert(DListNode *head)
{
	DListNode *newnode = (DListNode *)malloc(sizeof(DListNode));
	printf("����: "); gets_s(newnode->title, sizeof(newnode->title));
	while (1)
	{
		printf("�帣(A, C, F, R): "); newnode->genre = getchar();
		if (newnode->genre == 'A' || newnode->genre == 'C' || newnode->genre == 'F' || newnode->genre == 'R')
			break;
		else
			rewind(stdin);
	}
	printf("�����⵵: "); scanf("%d", &newnode->year);
	printf("����ð�: "); scanf("%d", &newnode->time);
	
	newnode->llink = head;
	newnode->rlink = head->rlink;
	head->rlink->llink = newnode;
	head->rlink = newnode;

	current = head->rlink;
}

//���� �Լ�
void ddelete(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n������� ��ȭ ������\n");
		return;
	}
	else
	{
		int exist = 0;
		char x[30];
		printf("������ ��ȭ ����: "); gets_s(x, sizeof(x));

		DListNode *p;
		for (p = head->rlink; p != head; p = p->rlink)
		{
			if (strcmp(p->title, x) == 0)
			{
				exist = 1;
				p->llink->rlink = p->rlink;
				p->rlink->llink = p->llink;
				if (current == p)
					current = current->rlink;
				free(p);
				printf("\n�ٵ����� ���� �Ϸ��\n");
				return;
			}
		}
		if(exist == 0)
			printf("���������� �ʴ� ��ȭ�ӡ�\n");
	}
}

//�������� ��ȭ ���� �˻��ϴ� �Լ�
void search_title(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n������� ��ȭ ������\n");
		return;
	}
	else {
		int exist = 0;
		char x[30];
		printf("�˻��� ��ȭ ����: "); scanf("%s", x);
		DListNode *p;
		for (p = head->rlink; p != head; p = p->rlink) {
			if (strcmp(p->title, x) == 0)
			{
				exist = 1;
				printf("\n��ȭ����: %s\n", p->title);
				printf("��ȭ�帣: %c\n", p->genre);
				printf("�����⵵: %d\n", p->year);
				printf("����ð�: %d\n", p->time);
			}
		}
		if (exist == 0)
			printf("���������� ������\n");
	}
}

//�ֱ� ���� ��ȭ �˻� �Լ�
void search_recent(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n������� ��ȭ ������\n");
		return;
	}
	else {
		DListNode *p = head->rlink;
		int recent = p->year;
		for (; p != head; p = p->rlink)
		{
			if (recent < p->year)
				recent = p->year;
		}

		for (p = head->rlink; p != head; p = p->rlink)
		{
			if (p->year == recent)
			{
				printf("\n��ȭ����: %s\n", p->title);
				printf("��ȭ�帣: %c\n", p->genre);
				printf("�����⵵: %d\n", p->year);
				printf("����ð�: %d\n", p->time);
			}
		}
	}
}

//�帣�� ��ȭ ���� �˻��ϴ� �Լ�
void search_genre(DListNode *head)
{
	if (head->rlink == head) {
		printf("\n������� ��ȭ ������\n");
		return;
	}
	else {
		int exist = 0;
		char x;
		while (1)
		{
			printf("�帣(A, C, F, R): "); x = getchar();
			if (x == 'A' || x == 'C' || x == 'F' || x == 'R')
				break;
			else
				rewind(stdin);
		}
		DListNode *p;
		for (p = head->rlink; p != head; p = p->rlink) {
			if (p->genre == x)
			{
				exist = 1;
				printf("\n��ȭ����: %s\n", p->title);
				printf("��ȭ�帣: %c\n", p->genre);
				printf("�����⵵: %d\n", p->year);
				printf("����ð�: %d\n", p->time);
			}
		}
		if(exist == 0)
			printf("���������� ������\n");
	}
}

//���� �Լ�
int list_length(DListNode *head)
{
	int cnt = 0;
	for (DListNode *p = head->rlink; p != head; p = p->rlink)
		cnt++;
	return cnt;
}

void play(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}

	printf("< %s ��� ��... >\n", current->title);
	for (int i = current->time; i > 0; i--)
	{
		printf("%d ", i);
		Sleep(1000);
	}
	printf("\n");

	current = current->rlink;
	if (current == head)
		current = current->rlink;
}

void next(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	current = current->rlink;
	if (current == head)
		current = current->rlink;
	play(head);
}

void previous(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	current = current->llink;
	if (current == head)
		current = current->llink;
	play(head);
}

void first(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	current = head->rlink;
	play(head);
}

void last(DListNode* head)
{
	if (head->rlink == head)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	current = head->llink;
	play(head);
}

int main(void)
{
	DListNode* head = (DListNode *)malloc(sizeof(DListNode));
	init(head);
	char select;
	int i = 0;
	while (1)
	{
		if (i > 0)
			printf("\n");
		i++;

		printf("------- MUNU -------\n");
		printf("��ȭ ���� �߰�(1)\n");
		printf("��ȭ ���� ���(2)\n");
		printf("��ȭ ���� �˻�(3)\n");
		printf("��ȭ ���� ����(4)\n");
		printf("����� ��ȭ ���� ���(5)\n");
		printf("�ֱ� ���� ��ȭ �˻�(6)\n");
		printf("��ȭ �帣 �˻�(7)\n");
		printf("���� ��ȭ ���(P)\n");
		printf("���� ��ȭ ���(>)\n");
		printf("���� ��ȭ ���(<)\n");
		printf("ó�� ��ȭ ���(F/f)\n");
		printf("������ ��ȭ ���(L/l)\n");
		printf("����(0)\n");
		printf("--------------------\n");
		printf(">> ");
		scanf(" %c", &select);
		rewind(stdin);
	
		if (select == '1')
			dinsert(head);
		else if (select == '2')
			print_dlist(head);
		else if (select == '3')
			search_title(head);
		else if (select == '4')
			ddelete(head);
		else if (select == '5')
			printf("����� ��ȭ ����: %d\n", list_length(head));
		else if (select == '6')
			search_recent(head);
		else if (select == '7')
			search_genre(head);
		else if (select == 'P')
			play(head);
		else if (select == '>')
			next(head);
		else if (select == '<')
			previous(head);
		else if (select == 'F' || select == 'f')
			first(head);
		else if (select == 'L' || select == 'l')
			last(head);
		else
			break;
	}
	return 0;
}