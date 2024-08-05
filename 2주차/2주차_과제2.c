#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int function1(int arr[], int low, int high, int key)
{
	int mid = 0;

	while (low <= high)
	{
		mid = (low + high) / 2;
		printf("Ž�� ����: [%d - %d]\n", low, high);
		printf("���� arr[%d]��(��) �� ��\n\n", mid);

		if (key == arr[mid])
			return mid;
		else if (key > arr[mid])
			low = mid + 1;
		else
			high = mid - 1;
	}

	return -1;
}

int function2(int arr[], int low, int high, int key)
{
	int mid = 0;

	if (low > high)
		return -1;

	mid = (low + high) / 2;
	printf("Ž�� ����: [%d - %d]\n", low, high);
	printf("���� arr[%d]��(��) �� ��\n\n", mid);

	if (arr[mid] == key)
		return mid;
	else if (key < arr[mid])
		return function2(arr, low, mid - 1, key);
	else
		return function2(arr, mid + 1, high, key);
}

int main(void) {

	int size = 0, key = 0, least = 0, tmp = 0, result = 0;

	printf("�Է��� ���� ����: ");
	scanf("%d", &size);

	int * arr = (int*)malloc(size * sizeof(int));

	printf("\n���� %d���� �Է��ϼ���\n", size);
	for (int i = 0; i < size; i++)
	{
		printf("%d��°: ", i + 1);
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < size - 1; i++) {
		least = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[least])
				least = j;
		}
		tmp = arr[i];
		arr[i] = arr[least];
		arr[least] = tmp;
	}

	printf("\n���� ��: ");
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\nã�� ��: ");
	scanf("%d", &key);

	printf("\n\n< ���� 2-1 > \n");
	result = function1(arr, 0, size - 1, key);

	if (result == -1)
		printf("%d��(��) �������� ����\n", key);
	else
		printf("%d��(��) arr[%d]�� ������\n", key, result);

	printf("\n\n< ���� 2-2 > \n");
	result = function2(arr, 0, size - 1, key);

	if (result == -1)
		printf("%d��(��) �������� ����\n", key);
	else
		printf("%d��(��) arr[%d]�� ������\n", key, result);

	free(arr);

	return 0;
}