#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct {
	char id[11];
	char password[7];
}User;

int searchID(User *users, char *targetID, int low, int high);
int checkPW(User *users, char *targetPW, int num);
int changePW(User *users, int num);

int main(void)
{
	User users[9] = {
		{"apple","111111"}, {"banana","222222"}, {"grape","333333"},
		{"lemon","444444"}, {"melon","555555"}, {"orange","666666"},
		{"pear","777777"}, {"pineapple","888888"}, {"strawberry","999999"}
	};

	char targetID[11];
	char targetPW[7];
	int resultID, resultPW;
	int sel = 0;

	while (1)
	{
		printf("1.�α���  2(1���� ��� ��).����: ");
		scanf("%d", &sel);

		if (sel == 1)
		{
			printf("\n���̵� �Է��ϼ���(10�� �̳�): ");
			scanf("%s", targetID);

			resultID = searchID(users, targetID, 0, 8);

			if (resultID == -1)
			{
				printf("�������� �ʴ� ���̵��Դϴ�.\n\n");
				continue;
			}

			else
			{
				printf("\n��й�ȣ�� 3ȸ �̳��� �˸°� �Է��ؾ� �մϴ�.\n");
				for (int i = 0; i < 3; i++)
				{
					if (i >= 1)
						printf("�ٽ� �Է��ϼ���.\n");

					printf("\n<%dȸ> ��й�ȣ�� �Է��ϼ���(6�� �̳�): ", i + 1);
					scanf("%s", targetPW);
					resultPW = checkPW(users, targetPW, resultID);

					if (resultPW == 1)
						break;
				}
				if (resultPW == -1)
					continue;
			}

			while (1)
			{
				printf("��й�ȣ�� �����ϰڽ��ϱ�?(1.�� 2.�ƴϿ�): ");
				scanf("%d", &sel); printf("\n");

				if (sel == 1)
				{
					if (changePW(users, resultID) == 1)
						break;
					else
						continue;
				}
				else
					break;
			}
		}
		else
			return 0;
	}
}

int searchID(User *users, char *targetID, int low, int high)
{
	int mid = 0;

	if (low > high)
		return -1;

	mid = (low + high) / 2;

	if (strcmp(users[mid].id, targetID) == 0)
		return mid;

	else if (strcmp(targetID, users[mid].id) < 0)
		return searchID(users, targetID, low, mid - 1);

	else
		return searchID(users, targetID, mid + 1, high);
}

int checkPW(User *users, char *targetPW, int num)
{
	if ((strcmp(users[num].password, targetPW) == 0))
	{
		printf("�α��� �Ǿ����ϴ�.\n\n");
		return 1;
	}

	else
	{
		printf("��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
		return -1;
	}
}

int changePW(User *users, int num)
{
	char newPW1[7];
	char newPW2[7];

	printf("������ ��й�ȣ �Է�(6�� �̳�): ");
	scanf("%s", newPW1);

	printf("������ ��й�ȣ ���Է�: ");
	scanf("%s", newPW2);

	if (strcmp(newPW1, newPW2) == 0)
	{
		printf("��й�ȣ�� ����Ǿ����ϴ�.\n\n");
		strcpy(users[num].password, newPW1);
		return 1;
	}

	else
	{
		printf("������ ��й�ȣ�� �ƴմϴ�.\n\n");
		return -1;
	}
}