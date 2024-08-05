#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ListNode { //��� Ÿ��
	int coef;
	int expon;
	struct ListNode *link;
}ListNode;

//���� ����Ʈ ���
typedef struct ListType {
	int size;
	ListNode *head;
	ListNode *tail;
}ListType;

//���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//����Ʈ ��� ���� �Լ�
ListType* create()
{
	ListType *plist = (ListType *)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

//plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���, expon�� ����
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp = (ListNode *)malloc(sizeof(ListNode));
	if (temp == NULL) error("�޸� �Ҵ� ����");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void poly_print(ListType* plist)
{
	int i = 0;
	ListNode* p = plist->head;
	printf("f(x) = ");
	for (; p != NULL; p = p->link) {
		if (i > 0 && p->coef >= 0)
			printf("+ ");
		printf("%dx^%d ", p->coef, p->expon);
		i++;
	}
	printf("\n");
}

int calculation(ListType* plist, int x)
{
	int result = 0;
	ListNode* tmp = plist->head;
	while (tmp != NULL)
	{
		result += (tmp->coef * (int)pow((double)x, (double)tmp->expon));
		tmp = tmp->link;
	}
	return result;
}

int main(void)
{
	ListType *list;
	int coef = 0, expon = 0, x = 0, sel1 = 0, sel2 = 0;
	list = create();

	while (1)
	{
		printf("1. ��� �߰�  2. STOP  >> "); scanf("%d", &sel1);
		if (sel1 == 1)
		{
			printf("��� �Է�: "); scanf("%d", &coef);
			printf("���� �Է�: "); scanf("%d", &expon);
			insert_last(list, coef, expon);
			printf("\n");
		}
		else
		{
			printf("\n");
			break;
		}
	}
	poly_print(list);

	while (1)
	{
		printf("x �Է�: "); scanf("%d", &x);
		printf("���: %d\n", calculation(list, x));

		printf("\n1. x�� �ٽ� �Է�  2. ����  >> "); scanf("%d", &sel2);
		if (sel2 != 1)
			break;
	}

	free(list);
}