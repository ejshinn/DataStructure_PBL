#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef struct point {
	int xpos;
	int ypos;
}Point;

double function1(Point p);
Point function2(Point *p);

int main(void) {

	Point pos1;
	Point pos2[5];

	printf("< ���� 3-1 > \n");
	printf("x��ǥ y��ǥ �Է�: ");
	scanf("%d %d", &pos1.xpos, &pos1.ypos);

	printf("�������κ����� �Ÿ�: %g \n\n", function1(pos1));

	printf("< ���� 3-2 > \n");

	printf("��ǥ 5�� �Է�\n");
	for (int i = 0; i < 5; i++)
	{
		printf("%d��° x��ǥ y��ǥ �Է�: ", i + 1);
		scanf("%d %d", &pos2[i].xpos, &pos2[i].ypos);
	}

	printf("�������κ��� ���� �� ��ǥ: (%d, %d) \n\n", function2(pos2).xpos, function2(pos2).ypos);
	return 0;
}

double function1(Point p)
{
	double distance = 0.0;
	distance = sqrt((double)((p.xpos * p.xpos) + (p.ypos * p.ypos)));
	return distance;
}

Point function2(Point *p)
{
	double distance[5];
	double farDistance = 0.0;
	int farPoint = 0;

	for (int i = 0; i < 5; i++)
	{
		distance[i] = function1(p[i]);
	}

	farDistance = distance[0];

	for (int i = 1; i < 5; i++)
	{
		if (distance[i] > farDistance)
		{
			farDistance = distance[i];
			farPoint = i;
		}
	}

	return p[farPoint];
}