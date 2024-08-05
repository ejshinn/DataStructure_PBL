#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { //��� Ÿ��
	char title[30];
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

//���� �Լ�
ListNode* delete_list(ListNode *head, char *x)
{
	if (head == NULL)
	{
		printf("\n������� ��ȭ ������\n");
		return NULL;
	}
	else
	{
		ListNode *removed;
		ListNode *pre = head;
		for (ListNode *p = head; p != NULL; p = p->link)
		{
			if (strcmp(p->title, x) == 0)
			{
				removed = p;
				if (p == head)
					head = removed->link;
				else
					pre->link = removed->link;
				free(removed);
				printf("\n�ٵ����� ���� �Ϸ��\n");
				return head;
			}
			else
				pre = p;
		}
	}
}

//�������� ��ȭ ���� �˻��ϴ� �Լ�
ListNode* search_title(ListNode *head, char *x)
{
	ListNode *p = head;
	while (p != NULL) {
		if (strcmp(p->title, x) == 0)
		{
			printf("\n��ȭ����: %s\n", p->title);
			printf("��ȭ�帣: %c\n", p->genre);
			printf("�����⵵: %d\n", p->year);
			return p;
		}
		p = p->link;
	}
	return NULL;
}

//�ֱ� ���� ��ȭ �˻� �Լ�
void search_recent(ListNode *head)
{
	if (head == NULL)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	ListNode *p = head;
	int recent = p->year;
	for (; p != NULL; p = p->link)
	{
		if (recent < p->year)
			recent = p->year;
	}

	for (p = head; p != NULL; p = p->link)
	{
		if (p->year == recent)
		{
			printf("\n��ȭ����: %s\n", p->title);
			printf("��ȭ�帣: %c\n", p->genre);
			printf("�����⵵: %d\n", p->year);
		}
	}
}

//�帣�� ��ȭ ���� �˻��ϴ� �Լ�
void search_genre(ListNode *head, char x)
{
	if (head == NULL)
	{
		printf("\n������� ��ȭ ������\n");
		return;
	}
	ListNode *p = head;
	while (p != NULL) {
		if (p->genre == x)
		{
			printf("\n��ȭ����: %s\n", p->title);
			printf("��ȭ�帣: %c\n", p->genre);
			printf("�����⵵: %d\n", p->year);
		}
		p = p->link;
	}
}

//���� ���(�Ϲ�) �Լ�
int list_length1(ListNode *head)
{
	int cnt = 0;
	for (ListNode *p = head; p != NULL; p = p->link)
		cnt++;
	return cnt;
}

//���� ���(��ȯ) �Լ�
int list_length2(ListNode *head)
{
	ListNode *p = head;
	if (p == NULL)
		return 0;
	else
		return 1 + list_length2(p->link);
}

//����Ʈ ���(�Ϲ�) �Լ�
void print_list1(ListNode *head)
{
	if (head == NULL)
		return;

	ListNode *p = head;
	for (; p != NULL; p = p->link)
	{
		printf("\n��ȭ����: %s\n", p->title);
		printf("�帣: %c\n", p->genre);
		printf("�����⵵: %d\n", p->year);
	}
	printf("NULL \n");
}

//����Ʈ ���(��ȯ)
void print_list2(ListNode *head)
{
	ListNode *p = head;
	if (p == NULL)
		printf("NULL");
	else
	{
		printf("\n��ȭ����: %s\n", p->title);
		printf("�帣: %c\n", p->genre);
		printf("�����⵵: %d\n", p->year);
		print_list2(p->link);
	}
}

//����Ʈ ���� ���(��ȯ)
void print_list3(ListNode *head)
{
	ListNode *p = head;
	if (p == NULL)
		printf("NULL");
	else
	{
		print_list3(p->link);
		printf("\n��ȭ����: %s\n", p->title);
		printf("�帣: %c\n", p->genre);
		printf("�����⵵: %d\n", p->year);
	}
}

int main(void)
{
	ListNode *head = NULL;
	char title[50], genre;
	int year, select = 0, i = 0;

	while (1)
	{
		if (i > 0)
			printf("\n");

		i = 1;
		printf("------- MUNU -------\n");
		printf("1. ��ȭ ���� �߰�\n");
		printf("2. ��ȭ ���� ���(�Ϲ�)\n");
		printf("3. ��ȭ ���� ���(��ȯ)\n");
		printf("4. ��ȭ ���� ���(���� ��ȯ)\n");
		printf("5. ����� ��ȭ ���� ���\n");
		printf("6. ��ȭ ���� �˻�\n");
		printf("7. �ֱ� ���� ��ȭ �˻�\n");
		printf("8. ��ȭ �帣 �˻�\n");
		printf("9. ��ȭ ���� ����\n");
		printf("0. ����\n");
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
		}
		else if (select == 2)
			print_list1(head);
		else if (select == 3)
			print_list2(head);
		else if(select == 4)
			print_list3(head);
		else if (select == 5)
		{
			printf("����� ��ȭ ����(�Ϲ�): %d\n", list_length1(head));
			printf("����� ��ȭ ����(��ȯ): %d\n", list_length2(head));
		}
		else if (select == 6)
		{
			printf("�˻��� ��ȭ ����: ");
			gets_s(title, sizeof(title)); rewind(stdin);
			if (search_title(head, title) != NULL)
				printf("\n�ٿ�ȭ ���� �˻� �Ϸ��\n");
			else
				printf("\n�ٿ�ȭ ���� ã�� ���С�\n");
		}
		else if(select == 7)
			search_recent(head);
		else if (select == 8)
		{
			printf("�˻��� ��ȭ �帣(A, C, F, R): "); genre = getchar();
			if (genre == 'A' || genre == 'C' || genre == 'F' || genre == 'R')
				search_genre(head, genre);
			else
				printf("\n���������� �ʴ� ��ȭ �帣�Դϴ١�\n");
		}
		else if (select == 9)
		{
			printf("������ ��ȭ ����: ");
			gets_s(title, sizeof(title)); rewind(stdin);

			if (search_title(head, title) != NULL)
				delete_list(head, title);
			else
				printf("\n���������� �ʴ� ��ȭ �����Դϴ١�\n");
		}
		else
			break;
	}
	return 0;
}