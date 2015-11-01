//�~ �������������ķ���

# include <stdio.h>
# include <stdlib.h>
# include <windows.h>
# include <time.h>
# include <conio.h>


# define INIT_LENGTH 4		//�߳�ʼ���ĳ���
# define DEBUG 0


char direction = 'd';		//��¼���ƶ��ķ���a������w�����ϣ�d�����ң�s������
int length = 0;		//��¼�ߵĳ���

/* ���ڱ�ʾ�������ĵ�Ľṹ�� */
typedef struct body
{
	int x;
	int y;
}body_t, * pBody_t;

body_t snake[300];		//���ڴ������������
body_t randPoint = { 0, 0 };		//����������ֵĵ�


void init_game(void);
void print_snake(void); 
void gotoxy(int x, int y);
void rand_point(void);
void move_snake(void);


int main(void)
{
	int speed = 0;
	char tmpDirection = 0;
	body_t tmpBody = { 0, 0 };

	
	system("mode con cols=40 lines=20");
	while (1)
	{
		printf("��ѡ����Ϸ����1~9,9���Ѷ���ߣ���");
		scanf("%d", &speed);
		if (speed <= 9 && speed >= 1)
			break;
	}
	
	speed = 1000 - speed * 100;

	init_game();	//��ʼ����Ϸ

	/* ��Ϸ����Ҫ���� */
	while (1)
	{

		/* ��������ʱ��ʾ���������� */
#if DEBUG
		gotoxy(1, 1);
		printf("%d,%d", randPoint.x, randPoint.y);
#endif

		Sleep(speed);		//���ڿ������ƶ����ٶ�

		/* ���̲ٿط��� */
		if (kbhit())
		{
		
			tmpDirection = getch();

			/* �����ж��Ƿ񰴼�Ϊw��a��s��d�����߲����ͷ */
			if (('w' == tmpDirection || 's' == tmpDirection || 'a' == tmpDirection || 'd' == tmpDirection) && 'w' + 's' != tmpDirection + direction && 'a' + 'd' != tmpDirection + direction)
			{
				direction = tmpDirection;
			}

		}


		/* ��ͷ��������غ� */
		if (randPoint.x == snake[1].x && randPoint.y == snake[1].y)
		{
			tmpBody = snake[length];
			system("cls");
			move_snake();

			snake[length + 1] = tmpBody;
			gotoxy(snake[length + 1].x, snake[length + 1].y);
			printf("�~");
			length++;

			rand_point();
		}
		else
		{
			system("cls");
			move_snake();
		}

	}
	
	
	getchar();
	return 0;
}



void init_game(void)
{
	int i = 0;
	
	/* ����һ������Ϊ4��С�� */
	for(i = 1; i <= 4; i++)
	{
		snake[i].x = 21 - i * 2;
		snake[i].y = 10;
	}
	length = INIT_LENGTH;
	print_snake();
	
	/* �������һ���� */ 
	rand_point();
}

/* ����gotoxy������ӡ���� */
void print_snake(void)
{
	int i = 0;
	
	for(i = 1; i <= length; i++)
	{
		gotoxy(snake[i].x, snake[i].y);
		printf("�~");
	}
}

/* ֱ�Ӵӱ����Ƕ��������ˣ�������~~~~(>_<)~~~~ */
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


/* ��������㣬 �������Ϊ ��ǰʱ�� x 189 */
void rand_point(void)
{
	int i = 0;

	srand((int)time(0) * 182);

	/* �ж�������ɵĵ��Ƿ��������غϣ����غϣ����������� */
	while (1)
	{
		randPoint.x = (int)(20 * rand() / RAND_MAX) * 2 + 1;
		randPoint.y = (int)(20 * rand() / RAND_MAX) + 1;

		for (i = 1; i <= length; i++)
		{
			if (snake[i].x == randPoint.x && snake[i].y == randPoint.y)
				break;
		}

		if (i > length)
			break;
	}

	gotoxy(randPoint.x, randPoint.y);
	printf("�~");

}

/* �ƶ�������������Ҫ�Ĳ��� */
void move_snake(void)
{
	int i = 0;

	/* ��������ÿ�����ֵ������һ���� */
	for (i = length; i >= 2; i--)
	{
		snake[i] = snake[i - 1];
	}

	/* ��ͷ��ǰ�����ƶ�һ�� */
	switch (direction)
	{
	case 'w':snake[1].y -= 1; break;		//��
	case 's':snake[1].y += 1; break;	//��
	case 'a':snake[1].x -= 2; break;		//��
	case 'd':snake[1].x += 2; break;	//��
	}

	/* �ж��Ƿ�ײ��ǽ */
	if (-1 == snake[1].x || 41 == snake[1].x || 0 == snake[1].y || 21 == snake[1].y)
	{
		system("cls");
		gotoxy(15, 10);
		printf("GAME OVER!\n");
		getch();
		getch();
		exit(-1);
	}

	/* �ж��Ƿ�ҧ���Լ� */
	for (i = 5; i <= length; i++)
	{
		if (snake[i].x == snake[1].x && snake[i].y == snake[1].y)
		{
			system("cls");
			gotoxy(15, 10);
			printf("GAME OVER!\n");
			getchar();
			exit(-1);
		}
	}

	print_snake();
	gotoxy(randPoint.x, randPoint.y);
	printf("�~");
}
