#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { //��� Ÿ��
	char title[50];
	char genre;
	int year;
	struct ListNode *link;
}ListNode;

//���� ó�� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//���� �Լ�
ListNode* insert_node(ListNode *head, char *title, char genre, int year)
{
	ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));

	strcpy(newNode->title, title);
	newNode->genre = genre;
	newNode->year = year;

	if (head == NULL) //�� ����� ��� ���� �տ� ����
	{
		head = newNode;
		newNode->link = NULL;
		return head;
	}

	ListNode *pre = head;
	for (ListNode *p = head; p; p = p->link) {
		if (strcmp(p->title, newNode->title) > 0) { //������ ��ȭ������ ���� ��
			if (p == head) {
				newNode->link = head;
				head = newNode;
				return head;
			}
			else {
				newNode->link = pre->link;
				pre->link = newNode;
				return head;
			}
		}
		else {
			pre = p;
		}
	}

	pre->link = newNode; //�� ���� ����
	newNode->link = NULL;
	return head;
}
/*
ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

//pre�� ����Ű�� ����� ���� ��带 �����Ѵ�.
ListNode* delete(ListNode *head, ListNode *pre)
{
	ListNode *removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}
*/
int list_length(ListNode *head)
{
	int cnt = 0;
	for (ListNode *p = head; p != NULL; p = p->link)
		cnt++;
	return cnt;
}

void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->link)
	{
		printf("\n��ȭ����: %s\n", p->title);
		printf("�帣: %c\n", p->genre);
		printf("�����⵵: %d\n", p->year);
	}
	printf("NULL \n");
}

int main(void)
{
	ListNode *head = NULL;
	char title[50], genre;
	int year, select = 0, i =0;

	while (1)
	{
		if (i > 0)
			printf("\n");

		i = 1;
		printf("------- MUNU -------\n");
		printf("1. ��ȭ ���� �߰�\n");
		printf("2. ��ȭ ���� ���\n");
		printf("3. ����\n");
		printf("--------------------\n");
		printf("��ȣ ����: "); scanf("%d", &select);
		rewind(stdin);

		if (select == 1)
		{
			printf("\n��ȭ����: ");
			gets_s(title, sizeof(title)); rewind(stdin);
			
			while (1)
			{
				printf("�帣(A, C, F, R): "); genre = getchar();
				if (genre == 'A' || genre == 'C' || genre == 'F' || genre == 'R')
					break;
				else
					rewind(stdin);
			}

			printf("�����⵵: "); scanf("%d", &year);

			head = insert_node(head, title, genre, year);
			printf("�ٵ����� ���� �Ϸ��\n");
			printf("--------------------\n");
			printf("\n����� ��ȭ�� ����: %d\n", list_length(head));
			print_list(head);
		}
		else if (select == 2)
		{
			printf("\n����� ��ȭ�� ����: %d\n", list_length(head));
			print_list(head);
		}
		else
			break;
	}

	return 0;
}