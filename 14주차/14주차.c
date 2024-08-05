#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>
#include <math.h>
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

#define MAX_QUEUE_SIZE 100
typedef TreeNode * element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode *ptr)
{
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf(" [%d] ", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

int nodes_level(TreeNode *ptr, int level)
{
	if (ptr == NULL)
		return 0;
	if (level == 1)
		return 1;
	return nodes_level(ptr->left, level - 1) + nodes_level(ptr->right, level - 1);
}

int get_height(TreeNode *node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + MAX(get_height(node->left), get_height(node->right));
	return height;
}

int balance(TreeNode *node)
{
	int lh;
	int rh;

	if (node == NULL)
		return true;

	lh = get_height(node->left);
	rh = get_height(node->right);

	if (abs(lh - rh) <= 1 && balance(node->left) && balance(node->right))
		return true;

	return false;
}

bool symmetry(TreeNode *node)
{
	if (node == NULL) return false;
	else {
		symmetry(node->left);
		symmetry(node->right);
		TreeNode * tmp = node->left;
		node->left = node->right;
		node->right = tmp;
	}
	return true;
}

//            15
//       4         20
//    1         16    25
//  5   2     3          7

TreeNode n1 = { 5, NULL, NULL };
TreeNode n2 = { 2, NULL, NULL };
TreeNode n3 = { 1, &n1, &n2 };
TreeNode n4 = { 4, &n3, NULL };
TreeNode n5 = { 3, NULL, NULL };
TreeNode n6 = { 16, &n5, NULL };
TreeNode n7 = { 7, NULL, NULL };
TreeNode n8 = { 25, NULL, &n7 };
TreeNode n9 = { 20, &n6, &n8 };
TreeNode n10 = { 15, &n4, &n9 };
TreeNode *root = &n10;


//             6
//         1       2
//      4     5       3
//    9     8       7   10
/*
TreeNode n1 = { 9, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 8, NULL, NULL };
TreeNode n4 = { 5, &n3, NULL };
TreeNode n5 = { 1, &n2, &n4 };
TreeNode n6 = { 7, NULL, NULL };
TreeNode n7 = { 10, NULL, NULL };
TreeNode n8 = { 3, &n6, &n7 };
TreeNode n9 = { 2, NULL, &n8 };
TreeNode n10 = { 6, &n5, &n9 };
TreeNode *root = &n10;
*/

//            18
//        1         5
//    15     8    9   2
//  7   3 11
/*
TreeNode n1 = { 7, NULL, NULL };
TreeNode n2 = { 3, NULL, NULL };
TreeNode n3 = { 11, NULL, NULL };
TreeNode n4 = { 15, &n1, &n2 };
TreeNode n5 = { 8, &n3, NULL };
TreeNode n6 = { 1, &n4, &n5 };
TreeNode n7 = { 9, NULL, NULL };
TreeNode n8 = { 2, NULL, NULL };
TreeNode n9 = { 5, &n7, &n8 };
TreeNode n10 = { 18, &n6, &n9 };
TreeNode *root = &n10;
*/

int main(void)
{
	int stop = 1, menu = 0, x= 0;
	while (stop)
	{
		printf("1. ���� ��ȸ ���  2. ���� ��� ����  3. ���� Ʈ�� Ȯ��  4. Ʈ�� �¿��Ī  5. ����  >> ");
		scanf("%d", &menu);
		switch (menu) {
		case 1:
			printf("\n���� ��ȸ:");
			level_order(root);
			printf("\n\n\n");
			break;
		case 2:
			printf("\n���� �Է�: "); scanf("%d", &x);
			if (x < 1 || get_height(root) < x)
			{
				printf("������ �߸� �Է��߽��ϴ�.\n\n\n");
				break;
			}
			printf("���� %d�� ��� ����: %d��\n\n\n", x, nodes_level(root, x));
			break;
		case 3:
			if (balance(root))
				printf("\n����Ʈ���Դϴ�.\n\n\n");
			else
				printf("\n����Ʈ���� �ƴմϴ�.\n\n\n");
			break;
		case 4:
			printf("\n[Before]\n"); level_order(root);
			if (symmetry(root))
			{
				printf("\n[After]\n"); level_order(root);
				printf("\n\n\n");
			}
			else
				printf("����\n\n");
			break;
		default:
			stop = 0;
			break;
		}
	}	
	return 0;
}