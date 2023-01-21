#pragma once
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include<stdio.h>
#include<mmsystem.h>
#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib, "winmm.lib")
#pragma warning(disable:4996) 


#define WIDTH 640
#define HEIGHT 480
#define CELL 20
#define MAXSIZE (WIDTH/CELL)*(HEIGHT/CELL)
#define PI  3.14159265358979323846
#define SCOREFILE "历史最高成绩.txt"
#define BKCOL(x) HSLtoRGB((x*10)%360, 1, 0.5)
#define CHBOXWID 28

int map[WIDTH / CELL+1][HEIGHT / CELL+1] = { '\0' };
int speed = 1;
int vx = speed;
int vy = 0;
int foodx;
int foody;
int tailx;
int taily;
int maxscore;
bool bigfood;

typedef struct SNACK
{
	int x;
	int y;
}snack;

snack asnack[MAXSIZE];
int snacksize;
int score;
int gamebkcolor = RGB(216, 216, 216);
int sleeptime = 300;
int bksong = 1;

class GSCALE
{
public:
	GSCALE(int scale, int x, int y)
	{
		m_scale = scale;
		m_x = x;
		m_y = y;
	}

	int m_scale;
	int m_x;
	int m_y;
};

class BKMUSIC
{
public:
	BKMUSIC(int code, int x, int y)
	{
		m_code = code;
		m_x = x;
		m_y = y;
	}

	int m_code;
	int m_x;
	int m_y;
};

class BKCOLOR
{
public:
	BKCOLOR(int code, int x, int y)
	{
		m_code = code;
		m_x = x;
		m_y = y;
	}

	int m_code;
	int m_x;
	int m_y;
};


//设置按钮
//游戏难度
GSCALE SimpleGame(1, 49, 155);//简单模式
GSCALE MiddleGame(2, 218, 155);//中等
GSCALE DiffcultGame(3, 373, 155);//困难
GSCALE gamescale = SimpleGame;
//背景音乐
BKMUSIC Cloud9(1, 49, 274);
BKMUSIC CCDXT(2, 49, 334);
BKMUSIC bkgdmusic = Cloud9;
//背景颜色
BKCOLOR LightGray(1, 49, 454);
BKCOLOR LightGreen(2, 222, 454);
BKCOLOR LightBLue(3, 353, 454);
BKCOLOR LightPink(4, 497, 454);
BKCOLOR bkgdcolor = LightGray;

/***************************函数声明*******************************/

void seting();//设置游戏难度，背景音乐，背景颜色
//画线
void SetLine();
//画蛇
void PaintSnack();
//画墙
void PaintWall();
//开始游戏
void playgame();
//展示纪录
void showrecord();
//透明图片
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//登录界面
void InitLoadInterface();
//初始化游戏界面
void InitPlayInterface();
//刷新界面
void RefreshInterface();
//开始游戏
void StartGame();
//移动蛇
void MoveSnack();
//随机食物
void RandFood();
//打印食物
void PrintFood();
//判断是否碰到墙或者蛇身
bool JudgeFail();
//展示失败后的小窗口
void printfailbox();
//判断是否迟到食物
bool JudgeFood();
//纪录尾部位置信息
void RecordTail();
//获得点击位置
int getclick();
//实时打印分数
void printscore();
//保存最高成绩
void saverecord();
//初始化maxscore;
void initmaxscr();
//账号登录
int Loading();
//账号登录
int loaduser();
//注册账号
void registeruser();
//登录画面的框架
void loadingimg();
//起始画面
void Startinterface();
//登录成功界面
void loadsucimg();
//游戏选择界面
void chosinginterface();
//密码失败界面
void pwdfail();

/*****************************主程序*******************************/
int main(void)
{
	srand((unsigned int)time(NULL));//随机数种子

	initmaxscr();//初始化最高纪录
	initgraph(WIDTH + CELL * 2, HEIGHT + CELL * 3);//制定窗口
	BeginBatchDraw();//开始批量绘制

	int k = Loading();//登录账号
	if (k == 0)
	{
		closegraph();
		exit(0);
	}

	chosinginterface();

	EndBatchDraw();

	_getch();
	closegraph();
	return 0;
}

/********************************函数*************************************/
//使png图片透明函数  -- 基础函数
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //新版png
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/***********************游戏开始前登录账号************************/
//登录界面
int Loading()
{

	Startinterface();

	FlushBatchDraw();
	//获取点击信息
	flushmessage();
	ExMessage m;

	while (true)
	{
		m = getmessage(EX_MOUSE);

		if (m.message == WM_LBUTTONDOWN)
		{
			if (m.x >= 245 && m.x <= 415 && m.y >= 195 && m.y <= 245)//点击账号登录
			{
				int choice = loaduser();
				if (choice == 2)
				{
					return 0;
				}
				else if (choice == 1)
				{
					registeruser();
					flushmessage();
					Startinterface();
				}
				else if (choice == 3)
				{
					loadsucimg();
					return 1;
				}
				else if (choice == 0)
				{
					pwdfail();
					Startinterface();
				}
			}
			else if (m.x >= 245 && m.x <= 415 && m.y >= 260 && m.y <= 310)//点击注册账号
			{
				registeruser();
				flushmessage();
				Startinterface();
			}
			else if (m.x >= 285 && m.x <= 375 && m.y >= 325 && m.y <= 375)//点击退出
			{
				return 0;
			}
		}

	}

	return 0;
}
//登录画面的框架
void loadingimg()
{
	setbkcolor(RGB(136, 179, 139));
	cleardevice();
	setfillcolor(WHITE);
	solidrectangle(140, 110, 540, 410);

	settextcolor(WHITE);
	settextstyle(50, 0, "华文琥珀");
	outtextxy(140, 50, "简易贪吃蛇");

	IMAGE snkimg;
	loadimage(&snkimg, "images/卡通蛇2.png", 52, 50);
	transparentimage(NULL, 395, 50, &snkimg);

	settextcolor(RGB(136, 179, 139));
	settextstyle(40, 0, "华文琥珀");
	setbkmode(TRANSPARENT);
}
//起始画面
void Startinterface()
{
	loadingimg();
	setfillcolor(RGB(136, 179, 139));
	solidroundrect(245, 195, 415, 245, 5, 5);
	solidroundrect(245, 260, 415, 310, 5, 5);
	solidroundrect(285, 325, 375, 375, 5, 5);
	outtextxy(170, 130, "请点击你的选择:");

	settextcolor(WHITE);
	settextstyle(40, 0, "华文琥珀");
	setbkmode(TRANSPARENT);

	outtextxy(250, 200, "密码登录");
	outtextxy(250, 265, "注册账号");
	outtextxy(290, 330, "退出");
	FlushBatchDraw();
}
//账号登录
int loaduser()
{
	char name[11];
	InputBox(name, 11, "请输入你的昵称：", "昵称输入", NULL, 60, 20);
	char password[7];
	InputBox(password, 7, "请输入你的密码：\n(6个数字)", "密码输入", NULL, 60, 20);
	if (strlen(name) == 0 || strlen(password) == 0)
	{
		return 0;
	}
	//读取文件中的账号信息
	FILE* fp = fopen("pwd.ini", "r");
	char s[30] = { '\0' };
	char* p = fgets(s, 30, fp);
	if (p == NULL)
	{
		loadingimg();
		setfillcolor(RGB(136, 179, 139));
		solidroundrect(245, 255, 415, 305, 5, 5);
		solidroundrect(285, 325, 375, 375, 5, 5);
		settextcolor(RGB(62, 164, 100));
		settextstyle(40, 0, "simhei");
		outtextxy(220, 130, "没有账号信息");
		outtextxy(240, 180, "请注册账号");


		settextcolor(WHITE);
		settextstyle(40, 0, "华文琥珀");
		outtextxy(250, 260, "注册账号");
		outtextxy(290, 330, "退出");

		FlushBatchDraw();
		flushmessage();
		ExMessage m;//获取点击信息

		while (true)
		{
			m = getmessage(EX_MOUSE);

			if (m.message == WM_LBUTTONDOWN)
			{
				if (m.x >= 245 && m.x <= 415 && m.y >= 255 && m.y <= 305)//点击注册账号
				{
					return 1;
				}
				else if (m.x >= 285 && m.x <= 375 && m.y >= 325 && m.y <= 375)//点击退出
				{
					return 2;
				}
			}

		}

	}

	char userpwd[7] = { '\0' };
	char username[11] = { '\0' };
	int i = 0;
	for (; i < 6; i++)
	{
		userpwd[i] = s[i];
	}
	for (; i < strlen(s); i++)
	{
		username[i - 6] = s[i];
	}
	if (strstr(username, name) && (atoi(userpwd) == atoi(password)))
	{
		return 3;
	}

	while (!feof(fp))
	{
		memset(s, 0, sizeof(s));
		char* p = fgets(s, 11, fp);
		char userpwd[7] = { '\0' };
		char username[11] = { '\0' };
		int i = 0;
		for (; i < 6; i++)
		{
			userpwd[i] = s[i];
		}
		for (; i < strlen(s); i++)
		{
			username[i - 6] = s[i];
		}
		if (strstr(username, name) && (atoi(userpwd) == atoi(password)))
		{
			return 3;
		}

	}
	return 0;
}
//登录成功界面
void loadsucimg()
{
	loadingimg();
	settextstyle(40, 0, "华文琥珀");
	settextcolor(RGB(136, 179, 139));
	outtextxy(260, 240, "登录成功");

	settextstyle(20, 0, "华文琥珀");
	settextcolor(RGB(136, 179, 139));
	outtextxy(235, 300, "请等待3秒到达游戏界面");
	outtextxy(338, 330, "3");
	FlushBatchDraw();
	Sleep(1000);
	setfillcolor(WHITE);
	solidrectangle(334, 329, 346, 351);
	outtextxy(335, 330, "2");
	FlushBatchDraw();
	Sleep(1000);
	solidrectangle(334, 329, 346, 351);
	outtextxy(338, 330, "1");
	FlushBatchDraw();
	Sleep(1000);
}
//密码失败
void pwdfail()
{
	loadingimg();
	settextstyle(40, 0, "华文琥珀");
	settextcolor(RGB(136, 179, 139));
	outtextxy(260, 240, "登录失败");

	settextstyle(20, 0, "华文琥珀");
	settextcolor(RGB(136, 179, 139));
	outtextxy(235, 300, "请等待3秒返回初始界面");
	outtextxy(338, 330, "3");
	FlushBatchDraw();
	Sleep(1000);
	setfillcolor(WHITE);
	solidrectangle(334, 329, 346, 351);
	outtextxy(335, 330, "2");
	FlushBatchDraw();
	Sleep(1000);
	solidrectangle(334, 329, 346, 351);
	outtextxy(338, 330, "1");
	FlushBatchDraw();
	Sleep(1000);
	return;
}
//注册账号
void registeruser()
{
	char name[11] = { '\0' };
	InputBox(name, 11, "请输入你的昵称：", "昵称输入", NULL, 60, 20);
	char password[7] = { '\0' };
	InputBox(password, 7, "请输入你的密码：\n(6个数字)", "密码输入", NULL, 60, 20);

	FILE* fp = fopen("pwd.ini", "a");

	char s[20] = { '\0' };
	for (int i = 0; i < 6; i++)
	{
		fputc(password[i], fp);
	}

	for (int i = 0; i < strlen(name); i++)
	{
		fputc(name[i], fp);
	}
	fputc('\n', fp);
	fclose(fp);//关闭文件
	//绘制注册成功图片
	loadingimg();
	settextstyle(40, 0, "华文琥珀");
	settextcolor(RGB(136, 179, 139));
	outtextxy(260, 240, "注册成功");

	settextstyle(20, 0, "华文琥珀");
	settextcolor(RGB(136, 179, 139));
	outtextxy(235, 300, "请等待3秒返回登录界面");
	outtextxy(338, 330, "3");
	FlushBatchDraw();
	Sleep(1000);
	setfillcolor(WHITE);
	solidrectangle(334, 329, 346, 351);
	outtextxy(335, 330, "2");
	FlushBatchDraw();
	Sleep(1000);
	solidrectangle(334, 329, 346, 351);
	outtextxy(338, 330, "1");
	FlushBatchDraw();
	Sleep(1000);
	return;
}

/****************游戏开始界面******************/
//游戏选择界面
void chosinginterface()
{
	InitLoadInterface();//显示登录界面
	ExMessage m;
	flushmessage();

	while (true)
	{
		//获取鼠标信息
		m = getmessage(EX_MOUSE);

		if (m.message == WM_LBUTTONDOWN)
		{
			if (m.x >= 250 && m.x <= 420 && m.y >= 162 && m.y <= 248)
			{
				flushmessage();
				playgame();
				break;
			}
			else if (m.x >= 190 && m.x <= 500 && m.y >= 387 && m.y <= 448)
			{
				flushmessage();
				showrecord();
				break;
			}
			else if (m.x >= 250 && m.x <= 420 && m.y >= 280 && m.y <= 360)
			{
				exit(0);
			}
			else if (m.x >= 542 && m.x <= 640 && m.y >= 464 && m.y <= 510)
			{
				seting();
				InitLoadInterface();//显示登录界面
				flushmessage();
			}
		}

	}
}
//登录界面
void InitLoadInterface()
{
	//设置背景颜色为白色
	setbkcolor(WHITE);
	cleardevice();

	IMAGE bkgroundimage;
	loadimage(&bkgroundimage, "images/游戏登录界面.png");
	putimage(0, 0, &bkgroundimage);

	FlushBatchDraw();

}

/********************开玩**********************/
//游戏
void playgame()
{
	flushmessage();
	if (bksong == 1)
	{
		mciSendString("open Cloud9.mp3", NULL, 0, NULL);
		mciSendString("play Cloud9.mp3", NULL, 0, NULL);
	}
	else
	{
		mciSendString("open 纯纯的夏天.mp3", NULL, 0, NULL);
		mciSendString("play 纯纯的夏天.mp3", NULL, 0, NULL);
	}

	InitPlayInterface();

	StartGame();
	if (bksong == 1)
	{
		mciSendString("close Cloud9.mp3", NULL, 0, NULL);
	}
	else
	{
		mciSendString("close 纯纯的夏天.mp3", NULL, 0, NULL);
	}

	saverecord();

	printfailbox();

}

//初始化游戏
void InitPlayInterface()
{
	setbkcolor(gamebkcolor);
	cleardevice();
	PaintWall();
	score = 0;

	vx = speed;
	vy = 0;

	printscore();
	//初始化地图
	snacksize = 4;
	//初始化蛇
	for (int i = 0; i < snacksize; i++)
	{
		asnack[i].x = 12 - i;
		asnack[i].y = 12;
		map[asnack[i].x][asnack[i].y] = 1;
	}
	RecordTail();
	//画蛇
	PaintSnack();
	//初始化食物
	RandFood();
	//画线
	SetLine();
	FlushBatchDraw();
	Sleep(sleeptime);
}

//正式开始游戏
void StartGame()
{
	flushmessage();
	while (true)
	{
		setbkcolor(gamebkcolor);//设置背景颜色
		cleardevice();//清空画面
		PaintWall();//打印墙
		PrintFood();//打印食物
		printscore();//显示分数
		//获取键盘输入
		int flag = 1;//判断这次是否由键盘输入
		flushmessage();
		if (GetAsyncKeyState(VK_UP) && (vx != 0))
		{
			vx = 0;
			vy = -speed;
			flag = 0;

		}
		if (GetAsyncKeyState(VK_DOWN) && (vx != 0))
		{
			vx = 0;
			vy = speed;
			flag = 0;
		}
		if (GetAsyncKeyState(VK_LEFT) && (vy != 0))
		{
			vy = 0;
			vx = -speed;
			flag = 0;
		}
		if (GetAsyncKeyState(VK_RIGHT) && (vy != 0))
		{
			vy = 0;
			vx = speed;
			flag = 0;
		}

		MoveSnack();//移动蛇

		if (JudgeFail())//判断是否失败
		{
			break;
		}

		RecordTail();//记录尾部的位置
		PaintSnack();//打印蛇
		SetLine();//画线

		FlushBatchDraw();

		if (JudgeFood())
			RandFood();//判断是否吃到食物

		//判断是否要加速
		if (((GetAsyncKeyState(VK_RIGHT) && vx == speed) ||
			(GetAsyncKeyState(VK_LEFT) && vx == -speed) ||
			(GetAsyncKeyState(VK_UP) && vy == -speed) ||
			(GetAsyncKeyState(VK_DOWN) && vy == speed)) && flag == 1)
			Sleep(100 - snacksize / 8);
		else
			Sleep(sleeptime - snacksize / 3);
	}

}

//画线
void SetLine()
{
	setlinecolor(RGB(141, 141, 141));
	for (int x = CELL * 2; x <= WIDTH; x = x + 20)
	{
		line(x, 0, x, HEIGHT + CELL);
	}
	for (int x = CELL * 2; x <= HEIGHT; x = x + 20)
	{
		line(0, x, WIDTH + CELL, x);
	}
}

//画蛇
void PaintSnack()
{
	setorigin(CELL, CELL);
	setfillcolor(BKCOL(0));
	double startangle, endangle;
	if (vx == speed)
	{
		startangle = PI / 6;
		endangle = 11 * PI / 6;
	}
	else if (vx == -speed)
	{
		startangle = 7 * PI / 6;
		endangle = 2 * PI + 5 * PI / 6;
	}
	else if (vy == speed)
	{
		startangle = 10 * PI / 6;
		endangle = 3 * PI + 2 * PI / 6;
	}
	else if (vy == -speed)
	{
		startangle = 4 * PI / 6;
		endangle = 2 * PI + 2 * PI / 6;
	}
	solidpie((asnack[0].x) * 20, (asnack[0].y) * 20, (asnack[0].x + 1) * 20, (asnack[0].y + 1) * 20, startangle, endangle);
	for (int i = 1; i < snacksize; i++)
	{
		setfillcolor(BKCOL(i));
		solidcircle((asnack[i].x + 0.5) * 20, (asnack[i].y + 0.5) * 20, CELL / 2);
	}
	setorigin(0, 0);
}
//画墙
void PaintWall()
{
	IMAGE img;
	loadimage(&img, "images\\墙.png");

	for (int i = 0; i <= WIDTH + CELL; i = i + 20)
	{
		putimage(i, 0, &img);
		putimage(i, HEIGHT + CELL, &img);
	}

	for (int i = 0; i <= HEIGHT + CELL; i = i + 20)
	{
		putimage(0, i, &img);
		putimage(WIDTH + CELL, i, &img);
	}
}

//纪录尾部位置信息
void RecordTail()
{
	tailx = asnack[snacksize - 1].x;
	taily = asnack[snacksize - 1].y;
}

//实时打印分数
void printscore()
{
	settextcolor(RGB(255, 26, 26));
	settextstyle(20, 0, _T("等线"));
	char s[15] = "得分为:";
	int i = strlen(s);
	int temp = score, n = score;
	int k = 0;
	if (snacksize == 4)
	{
		s[i] = '0';
	}
	while (temp)
	{
		temp /= 10;
		k++;
	}

	while (n)
	{
		s[i + k - 1] = n % 10 + '0';
		n /= 10;
		k--;
	}

	outtextxy(WIDTH / 2 + CELL - 70, HEIGHT + CELL * 2, s);
}

//初始化maxscore;
void initmaxscr()
{
	FILE* fp = fopen(SCOREFILE, "r");

	char ch;
	ch = fgetc(fp);
	if (ch == -1)
	{
		maxscore = -1;
		return;
	}

	int scr = ch - '0';

	while ((ch = fgetc(fp)) != EOF)
	{
		scr *= 10;
		scr += ch - '0';
	}

	maxscore = scr;
	fclose(fp);
}

//移动蛇
void MoveSnack()
{
	for (int i = snacksize - 1; i > 0; i--)
	{
		map[asnack[i].x][asnack[i].y] = 0;
		asnack[i].x = asnack[i - 1].x;
		asnack[i].y = asnack[i - 1].y;
		map[asnack[i].x][asnack[i].y] = 1;
	}
	asnack[0].x = asnack[0].x + vx;
	asnack[0].y = asnack[0].y + vy;
	map[asnack[0].x][asnack[0].y] = 1;

}

//随机食物
void RandFood()
{
	int randnum = rand() % 8;
	if (randnum == 4)
	{
		bigfood = true;
		foodx = rand() % (WIDTH / CELL - 1);
		foody = rand() % (HEIGHT / CELL - 1);
		while (map[foodx][foody] == 1)
		{
			foodx = rand() % (WIDTH / CELL - 1);
			foody = rand() % (HEIGHT / CELL - 1);
		}
	}
	else
	{
		bigfood = false;
		foodx = rand() % (WIDTH / CELL);
		foody = rand() % (HEIGHT / CELL);
		while (map[foodx][foody] == 1)
		{
			foodx = rand() % (WIDTH / CELL);
			foody = rand() % (HEIGHT / CELL);
		}
	}

}

//打印食物
void PrintFood()
{
	setfillcolor(HSLtoRGB((0 + snacksize * 10) % 360, 1, 0.5));
	if (bigfood)
	{
		solidcircle((foodx + 2) * CELL, (foody + 2) * CELL, CELL);
	}
	else
	{
		solidcircle((foodx + 1) * CELL + CELL / 2, (foody + 1) * CELL + CELL / 2, CELL / 2);
	}
}

//判断是否碰到墙或者蛇身
bool JudgeFail()
{

	for (int i = 0;i < snacksize; i++)
	{
		if (asnack[0].x < 0 || asnack[0].x>31 ||
			asnack[0].y < 0 || asnack[0].y >23)
		{
			return true;
		}
	}

	for (int i = 1; i < snacksize; i++)
	{
		if (asnack[0].x == asnack[i].x && asnack[0].y == asnack[i].y)
		{
			return true;
		}
	}
	return false;
}

//判断是否吃到食物
bool JudgeFood()
{
	if (bigfood)
	{
		if (map[foodx][foody] == 1 || map[foodx + 1][foody] == 1 || map[foodx][foody + 1] == 1 || map[foodx + 1][foody + 1] == 1)
		{
			int vxtail = asnack[snacksize - 2].x - asnack[snacksize - 1].x;
			int vytail = asnack[snacksize - 2].y - asnack[snacksize - 1].y;

			for (int i = 0; i < 4; i++)
			{
				asnack[snacksize + i].x = tailx + vxtail * i;
				asnack[snacksize + i].y = taily + vytail * i;
			}
			snacksize += 4;
			score += 40;
			return true;
		}
	}
	else if (map[foodx][foody] == 1)
	{
		snacksize++;
		asnack[snacksize - 1].x = tailx;
		asnack[snacksize - 1].x = tailx;
		score += 10;
		return true;
	}
	return false;
}

/***********失败************/
//保存最高成绩
void saverecord()
{
	if (score <= maxscore)
	{
		return;
	}

	maxscore = score;

	FILE* fp = fopen(SCOREFILE, "w");
	//将目前的成绩转化为字符串
	char s[10] = { '\0' };
	int i = 0;
	int temp = score, n = score;
	int k = 0;
	if (snacksize == 4)
	{
		s[i] = '0';
	}
	while (temp)
	{
		temp /= 10;
		k++;
	}
	while (n)
	{
		s[i + k - 1] = n % 10 + '0';
		n /= 10;
		k--;
	}

	fputs(s, fp);
	fclose(fp);

}

//获取鼠标信息
int getclick()
{
	FlushBatchDraw();
	flushmessage();
	ExMessage m;

	while (true)
	{
		m = getmessage(EX_MOUSE);

		if (m.message == WM_LBUTTONDOWN)
		{
			if (m.x >= 306 && m.x <= 611 && m.y >= 162 && m.y <= 255)//点击重新开始
			{
				return 1;
			}
			else if (m.x >= 305 && m.x <= 627 && m.y >= 390 && m.y <= 445)//点击查看历史纪录
			{
				return 2;
			}
			else if (m.x >= 308 && m.x <= 485 && m.y >= 277 && m.y <= 354)//点击退出
			{
				return 0;
			}
		}

	}
}

//打印失败界面
void printfailbox()
{
	setbkcolor(WHITE);
	cleardevice();

	IMAGE failbkimg, snackimg;
	loadimage(&snackimg, "images\\卡通蛇.png");
	loadimage(&failbkimg, "images/游戏失败.png");

	putimage(0, 0, &failbkimg);
	transparentimage(NULL, 40, 180, &snackimg);
	
	flushmessage();
	int choice;
	choice = getclick();
	if (choice == 1)//重新开始
	{
		playgame();
		flushmessage();
	}
	else if (choice == 2)
	{
		showrecord();
	}
}

//展示最高成绩
void showrecord()
{
	setbkcolor(WHITE);
	cleardevice();
	//显示返回按钮
	IMAGE bk;
	loadimage(&bk, "images/查看历史.png");
	putimage(0, 0, &bk);
	
	settextstyle(50, 0, "汉仪小麦体简");
	settextcolor(RGB(146, 214, 163));

	char norecordtxt[] = "没有历史纪录";

	char recordtxt[30] = "历史最高纪录为:";
	RECT r = { 0,0,WIDTH + CELL * 2, HEIGHT + CELL * 3 };

	if (maxscore == -1)
	{
		drawtext(norecordtxt, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (maxscore >= 0)
	{
		int i = strlen(recordtxt);
		int temp = maxscore, n = maxscore;
		int k = 0;

		while (temp)
		{
			temp /= 10;
			k++;
		}

		while (n)
		{
			recordtxt[i + k - 1] = n % 10 + '0';
			n /= 10;
			k--;
		}

		drawtext(recordtxt, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		FlushBatchDraw();
	}
	flushmessage();

	ExMessage m;
	while (1)
	{
		m = getmessage(EX_MOUSE);
		if (m.message == WM_LBUTTONDOWN)
		{
			if (m.x >= 177 && m.x <= 489 && m.y >= 457 && m.y <= 513)
			{
				chosinginterface();
				break;
			}
		}
	}

}

//设置显示
void seting()//设置游戏难度，背景音乐，背景颜色
{
	IMAGE bkimg, rightimg;
	loadimage(&bkimg, "images/设置背景图片.png");
	putimage(0, 0, &bkimg);

	setfillcolor(RGB(146, 214, 163));
	solidrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + 32, gamescale.m_y + 32);
	solidrectangle(bkgdmusic.m_x, bkgdmusic.m_y, bkgdmusic.m_x + 32, bkgdmusic.m_y + 32);
	solidrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + 32, bkgdcolor.m_y + 32);
	settextcolor(RGB(146, 214, 163));
	settextstyle(15, 0, "汉仪小麦体简");
	RECT r = { 0, 0, 679, 539 };
	drawtext("Made By Caroline", &r, DT_BOTTOM | DT_SINGLELINE | DT_CENTER);


	FlushBatchDraw();
	ExMessage m;
	flushmessage();
	while (true)
	{
		m = getmessage(EX_MOUSE);

		if (m.message == WM_LBUTTONDOWN)
		{
			if (gamescale.m_scale != 1 && m.x >= SimpleGame.m_x && m.x <= SimpleGame.m_x + CHBOXWID && m.y >= SimpleGame.m_y && m.y <= SimpleGame.m_y + CHBOXWID)
			{
				clearrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + CHBOXWID, gamescale.m_y + CHBOXWID);
				gamescale = SimpleGame;
				sleeptime = 300;
				solidrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + CHBOXWID, gamescale.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (gamescale.m_scale != 2 && m.x >= MiddleGame.m_x && m.x <= MiddleGame.m_x + CHBOXWID && m.y >= MiddleGame.m_y && m.y <= MiddleGame.m_y + CHBOXWID)
			{
				clearrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + CHBOXWID, gamescale.m_y + CHBOXWID);
				gamescale = MiddleGame;
				sleeptime = 250;
				solidrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + CHBOXWID, gamescale.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (gamescale.m_scale != 3 && m.x >= DiffcultGame.m_x && m.x <= DiffcultGame.m_x + CHBOXWID && m.y >= DiffcultGame.m_y && m.y <= DiffcultGame.m_y + CHBOXWID)
			{
				clearrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + CHBOXWID, gamescale.m_y + CHBOXWID);
				gamescale = DiffcultGame;
				sleeptime = 200;
				solidrectangle(gamescale.m_x, gamescale.m_y, gamescale.m_x + CHBOXWID, gamescale.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (bkgdmusic.m_code != 1 && m.x >= Cloud9.m_x && m.x <= Cloud9.m_x + CHBOXWID && m.y >= Cloud9.m_y && m.y <= Cloud9.m_y + CHBOXWID)
			{
				clearrectangle(bkgdmusic.m_x, bkgdmusic.m_y, bkgdmusic.m_x + CHBOXWID, bkgdmusic.m_y + CHBOXWID);
				bkgdmusic = Cloud9;
				bksong = 1;
				solidrectangle(bkgdmusic.m_x, bkgdmusic.m_y, bkgdmusic.m_x + CHBOXWID, bkgdmusic.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (bkgdmusic.m_code != 2 && m.x >= CCDXT.m_x && m.x <= CCDXT.m_x + CHBOXWID && m.y >= CCDXT.m_y && m.y <= CCDXT.m_y + CHBOXWID)
			{
				clearrectangle(bkgdmusic.m_x, bkgdmusic.m_y, bkgdmusic.m_x + CHBOXWID, bkgdmusic.m_y + CHBOXWID);
				bkgdmusic = CCDXT;
				bksong = 2;
				solidrectangle(bkgdmusic.m_x, bkgdmusic.m_y, bkgdmusic.m_x + CHBOXWID, bkgdmusic.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (bkgdcolor.m_code != 1 && m.x >= LightGray.m_x && m.x <= LightGray.m_x + CHBOXWID && m.y >= LightGray.m_y && m.y <= LightGray.m_y + CHBOXWID)
			{
				clearrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				bkgdcolor = LightGray;
				gamebkcolor = RGB(216, 216, 216);
				solidrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (bkgdcolor.m_code != 2 && m.x >= LightGreen.m_x && m.x <= LightGreen.m_x + CHBOXWID && m.y >= LightGreen.m_y && m.y <= LightGreen.m_y + CHBOXWID)
			{
				clearrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				bkgdcolor = LightGreen;
				gamebkcolor = RGB(172, 217, 181);
				solidrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (bkgdcolor.m_code != 3 && m.x >= LightBLue.m_x && m.x <= LightBLue.m_x + CHBOXWID && m.y >= LightBLue.m_y && m.y <= LightBLue.m_y + CHBOXWID)
			{
				clearrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID + 1, bkgdcolor.m_y + CHBOXWID);
				bkgdcolor = LightBLue;
				gamebkcolor = RGB(192, 232, 237);
				solidrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (bkgdcolor.m_code != 4 && m.x >= LightPink.m_x && m.x <= LightPink.m_x + CHBOXWID && m.y >= LightPink.m_y && m.y <= LightPink.m_y + CHBOXWID)
			{
				clearrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				bkgdcolor = LightPink;
				gamebkcolor = RGB(230, 208, 225);
				solidrectangle(bkgdcolor.m_x, bkgdcolor.m_y, bkgdcolor.m_x + CHBOXWID, bkgdcolor.m_y + CHBOXWID);
				FlushBatchDraw();
			}
			else if (m.x >= 564 && m.x <= 633 && m.y >= 200 && m.y <= 335)
			{
				return;
			}
		}
	}

}
