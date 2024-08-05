#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_SIZE 50

//������ ����
typedef struct {
	char word[MAX_WORD_SIZE];
	int count;
} element;

//����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

//���� e1 < e2�̸� -1 ��ȯ
//���� e1 == e2�̸� 0 ��ȯ
//���� e1 > e2 �̸� 1 ��ȯ
int compare(char e1[], char e2[])
{
	return strcmp(e1, e2);
}

TreeNode * new_node(char word[])
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	strcpy(temp->key.word, word);
	temp->key.count = 1;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode * insert_node(TreeNode * node, char word[])
{
	//Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�.
	if (node == NULL) return new_node(word);

	//�׷��� ������ ��ȯ������ Ʈ���� ��������.
	if (compare(word, node->key.word) < 0)
		node->left = insert_node(node->left, word);
	else if (compare(word, node->key.word) > 0)
		node->right = insert_node(node->right, word);
	else
		node->key.count++;

	//��Ʈ �����͸� ��ȯ�Ѵ�.
	return node;
}

//���� ��ȸ
void inorder(TreeNode * root, FILE* fp)
{
	if (root) {
		inorder(root->left, fp);                                     //���ʼ���Ʈ�� ��ȸ
		printf("%s: %d��\n", root->key.word, root->key.count);       //��� �湮
		fprintf(fp, "%s: %d��\n", root->key.word, root->key.count);
		inorder(root->right, fp);                                    //�����ʼ���Ʈ�� ��ȸ
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
		return (max > root->key.count ? max : root->key.count);
	}
}

void max_node(TreeNode * root, int max, FILE* fp)
{
	if (root) {
		max_node(root->left, max, fp);
		if (max == root->key.count)
		{
			printf("���� ���� ������ �����(�󵵼�): %s(%d��)\n", root->key.word, root->key.count);
			fprintf(fp, "���� ���� ������ �����(�󵵼�): %s(%d��)\n", root->key.word, root->key.count);
		}
		max_node(root->right, max, fp);
	}
}

int main(void)
{
	TreeNode * root = NULL;
	char rw[MAX_WORD_SIZE];
	char temp[MAX_WORD_SIZE];
	int c;
	char *rwords[] = { "break", "case", "char", "do", "else", "for", "if", "int", "return", "switch", "typedef", "void", "while" };

	FILE* fp1 = fopen("bst_in.txt", "r");
	if (fp1 == NULL) {
		printf("������ �� �� �����ϴ�.\n");
		exit(1);
	}
	
	do {
		c = fscanf(fp1, "%s", rw);
		if (c != EOF)
		{
			for (int i = 0; i < 13; i++)
			{
				strcpy(temp, "("); strcat(temp, rwords[i]);
				if (compare(rw, rwords[i]) == 0 || strstr(rw, temp) != NULL)
					root = insert_node(root, rwords[i]);
			}
		}
	} while (c != EOF);
	fclose(fp1);

	FILE* fp2 = fopen("bst_out.txt", "w");
	inorder(root, fp2);
	int max = FindMax(root);
	max_node(root, max, fp2);
	fclose(fp2);

	return 0;
}