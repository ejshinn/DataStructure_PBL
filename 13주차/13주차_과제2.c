#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

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

//���� ��ȸ
void inorder(TreeNode *root)
{
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data); //��� �湮
		inorder(root->right);
	}
}

//���� ��ȸ
void preorder(TreeNode *root)
{
	if (root != NULL) {
		printf("[%d] ", root->data); //��� �湮
		preorder(root->left);
		preorder(root->right);
	}
}

//���� ��ȸ
void postorder(TreeNode *root)
{
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data); //��� �湮
	}
}

void preorder_plus(TreeNode *root)
{
	if (root != NULL) {
		root->data++;
		preorder_plus(root->left);
		preorder_plus(root->right);
	}
}

int sum(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else {
		int tmp = sum(root->left) + sum(root->right);
		return tmp + root->data;
	}
}

int FindMax(TreeNode *root)
{
	if (root == NULL)
		return 0;
	else {
		int left = FindMax(root->left);
		int right = FindMax(root->right);
		int max = left > right ? left : right;
		return (max > root->data ? max : root->data);
	}
}

void MinValue(TreeNode *root, int x) {
	if (root != NULL) {
		MinValue(root->left, x);
		if (root->data < x) {
			printf("[%d] ", root->data);
		}
		MinValue(root->right, x);
	}
}

int main(void)
{
	int x = 0;

	printf("���� ��ȸ: ");
	inorder(root);
	printf("\n");

	printf("���� ��ȸ: ");
	preorder(root);
	printf("\n");

	printf("���� ��ȸ: ");
	postorder(root);
	printf("\n");

	printf("\n���� ��ȸ 1 ����: ");
	preorder_plus(root);
	preorder(root);
	printf("\n");

	printf("���� ��ȸ ����: ");
	printf("%d\n", sum(root));

	printf("���� ��ȸ �ִ�: ");
	printf("%d\n", FindMax(root));
	printf("\n");

	printf("x�� �Է�: "); scanf("%d", &x);
	printf("%d���� ���� ��: ", x);
	MinValue(root, x);
	printf("\n");

	return 0;
}