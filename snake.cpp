#include "csl.h"
#include <string>
#include <stdlib.h>
#include <time.h>

struct point{
    int x,y;
    int x0,y0;
};
point* snake = new point[10000];
point direction;
point bigFood;
point food;

bool checkTele = false;
bool Immortal = false;
bool Teleport = false;
bool ChangeSpeed = false;
bool checkFood = false;
bool endGame = false;
bool ATP = false;

char Name[15];
char mode[15];
char s[1000];
char X[10];
char Y[10];
char XF[10];
char YF[10];
char SL[10];
char moveSnake;

int Score = 0;
int color = 1;
int countFood = 0;
int speed = 75;
int MIHIG,MAHIG;
int MIWEG,MAWEG;
int snakeLength;
int numFood = 0;
const int DIRECTION = 1;


void drawSnake();
void circle(int x,int y);
void drawPoint(int x,int y);
void initGame(point& food);
void run();
void casual();
void changeDirection(int x);
void drawFood(point& food);
void drawFram();
void drawInfo();
void DrawbigFood(point& food);
void Nocursortype();
void Tele(point& food);
int EatFood(point &food);
int Length(int n);
int toString(char s[],int n);
char Autoplay(point food);


void initGame(){
    //Init Size Window
    setbgcolor(0);
    setcolor(11);
    resizecsl(60,60);
    DisableResizeWindow();
    DisableCtrButton(0,0,1);
    ShowScrollbar(0);
    Nocursortype(0,1);
    //SetTitle
    settitle("Snake");
    //Init Info Player
    strcpy(Name,"Thuan");
    //Init Mode
    strcpy(mode,"Normal");
    //Init Info Snake
    snakeLength = 3;
    int temp = 0;
    for (int i = snakeLength -1;i >= 0;i--)
    {
        snake[temp].x = i+1;snake[temp++].y = 1;
    }
    //Init moveSnake
    moveSnake = 77;
    //Init Direction
    direction.x = 1; direction.y = 0;
    //Init Frame
    MIWEG = 0;MAWEG = 45;
    MIHIG = 0;MAHIG = 45;
    //Init Food
    drawFood(food);
}

void drawPoint(int x,int y)
{
    circle(x,y);
}

void drawFram()
{
    cloneprint(MIWEG,MIHIG,MAWEG - MIWEG,'#',15);
    for (int i = MIHIG;i <= MAHIG;i++)
    {
    clprint(MIWEG,i,'#',15);
    clprint(MAWEG,i,'#',15);
    }
    cloneprint(MIWEG,MAHIG,MAWEG - MIWEG,'#',15);
}

void drawInfo()
{
    toString(X,snake[snakeLength-1].x);
    toString(Y,snake[snakeLength-1].y);
    toString(XF,food.x);
    toString(YF,food.y);
    toString(s,Score);
    toString(SL,snakeLength);
    scprint(MAWEG+1,MIHIG,"Score : ",11,0);
    scprint(MAWEG+9,MIHIG,s,11,0);
    cloneprint(MAWEG+9+Length(Score),MIHIG,Length(Score),' ',0);
    scprint(MAWEG+1,MIHIG+1,"Player Name : ",11,0);
    scprint(MAWEG+15,MIHIG+1,Name,11,0);
    scprint(MAWEG+1,MIHIG+2,"Mode : ",11,0);//Mode
    scprint(MAWEG+8,MIHIG+2,mode,11,0);
    scprint(MAWEG+1,MIHIG+10,"x :",11,0);//Head Snake.x
    scprint(MAWEG+4,MIHIG+10,X,11,0);
    cloneprint(MAWEG+4+Length(snake[snakeLength-1].x),MIHIG+10,Length(snake[snakeLength-1].x)+5,' ',0);
    scprint(MAWEG+1,MIHIG+11,"y :",11,0);//Head Snake.y
    scprint(MAWEG+4,MIHIG+11,Y,11,0);
    cloneprint(MAWEG+4+Length(snake[snakeLength-1].y),MIHIG+11,Length(snake[snakeLength-1].y)+5,' ',0);
    scprint(MAWEG+1,MIHIG+12,"xF :",11,0);//Food.x
    scprint(MAWEG+5,MIHIG+12,XF,11,0);
    cloneprint(MAWEG+5+Length(food.x),MIHIG+12,Length(food.x)+5,' ',0);
    scprint(MAWEG+1,MIHIG+13,"yF :",11,0);//Food.y
    scprint(MAWEG+5,MIHIG+13,YF,11,0);
    cloneprint(MAWEG+5+Length(food.y),MIHIG+13,Length(food.y)+5,' ',0);
    scprint(MAWEG+1,MIHIG+14,"Snake Length :",11,0);//Head Snake.y
    scprint(MAWEG+15,MIHIG+14,SL,11,0);
    cloneprint(MAWEG+15+Length(snakeLength),MIHIG+14,Length(snakeLength)+5,' ',0);

    if (!strcmp(mode,"Hack           ") || !strcmp(mode,"Auto and Hack    "))
    {
        scprint(MAWEG+1,MIHIG+3,"Skill : ",11,0);
        if (Immortal == false ) scprint(MAWEG+1,MIHIG+4,"1.Immortal : OFF",11,0);
        else if (Immortal == true ) scprint(MAWEG+1,MIHIG+4,"1.Immortal : ON ",11,0);
        if (Teleport == false ) scprint(MAWEG+1,MIHIG+5,"2.Teleport : OFF",11,0);
        else if (Teleport == true ) scprint(MAWEG+1,MIHIG+5,"2.Teleport : ON ",11,0);
        if (ChangeSpeed == false ) {
            scprint(MAWEG+1,MIHIG+6,"3.Change Speed : OFF",11,0);
            scprint(MAWEG+1,MIHIG+7,"         ",11,0);
        }
        else if (ChangeSpeed == true )
        {
            scprint(MAWEG+1,MIHIG+6,"3.Change Speed : ON ",11,0);
            scprint(MAWEG+1,MIHIG+7,"Speed: ",11,0);
            char sp[15];
            toString(sp,speed);
            scprint(MAWEG+7,MIHIG+7,sp,11,0);
            cloneprint(MAWEG+7+Length(speed),MIHIG+7,Length(speed)+5,' ',0);
        }
        if (ATP == false && !strcmp(mode,"Auto and Hack    ")) scprint(MAWEG+1,MIHIG+8,"4.AutoPlay : OFF  ",11,0);
        else if (ATP == true && !strcmp(mode,"Auto and Hack    ")) scprint(MAWEG+1,MIHIG+8,"4.AutoPlay : ON   ",11,0);
        else if (!strcmp(mode,"Hack           ")) scprint(MAWEG+1,MIHIG+8,"                    ",11,0);
    }
    else
    {
        scprint(MAWEG+1,MIHIG+3,"                    ",11,0);
        scprint(MAWEG+1,MIHIG+4,"                    ",11,0);
        scprint(MAWEG+1,MIHIG+5,"                    ",11,0);
        scprint(MAWEG+1,MIHIG+6,"                    ",11,0);
        scprint(MAWEG+1,MIHIG+7,"                    ",11,0);
        scprint(MAWEG+1,MIHIG+8,"                    ",11,0);
    }
}

void drawFood(point& food){
    srand(time(NULL));
    food.x = rand() % ((MAWEG - 1) - (MIWEG + 1) + 1) + MIWEG + 1;
    food.y = rand() % ((MAHIG - 1) - (MIHIG + 1) + 1) + MIHIG + 1;
    clprint(food.x,food.y,'o',3);
}

void DrawbigFood(point& food)
{
    srand(time(NULL));
    food.x = rand() % ((MAWEG - 1) - (MIWEG + 1) + 1) + MIWEG + 1;
    food.y = rand() % ((MAHIG - 1) - (MIHIG + 1) + 1) + MIHIG + 1;
}

void circle(int xC,int yC){
    clprint(xC,yC,'+',10);
}

void drawSnake (){
    int count = 0;
    for (int i = 0;count < snakeLength;i++){
            drawPoint(snake[i].x, snake[i].y);
            count++;
        }
    //delete point when snake move
    drawPoint(snake[snakeLength-1].x0,snake[snakeLength-1].y0);
    clprint (snake[snakeLength-1].x0,snake[snakeLength-1].y0,'o',0);
}

int EatFood(point& food,int value)
{
    if (snake[0].x == food.x && snake[0].y == food.y || checkTele == true)
    {
        snake[snakeLength].x = snake[snakeLength-1].x0; snake[snakeLength].y = snake[snakeLength-1].y0;
        if (checkTele == true ) Tele(food);
        checkTele = false;
        Score += value;
        snakeLength++;
        if (countFood == 4) return 0;
        return 2;
    }
    else return 1;
}

void changeDirection(int x){
    switch(x){
                case 72:
                    if (direction.y != DIRECTION) {
                        direction.y = -DIRECTION; direction.x = 0;
                    }
                    break;
                case 80:
                    if (direction.y != -DIRECTION) {
                        direction.y = DIRECTION; direction.x = 0;
                    }
                   break;
                case 77:
                    if (direction.x != -DIRECTION) {
                        direction.x = DIRECTION; direction.y = 0;
                    }
                    break;
                case 75:
                    if (direction.x != DIRECTION) {
                        direction.x = -DIRECTION; direction.y = 0;
                    }
                    break;
                case 45:
                    if (ChangeSpeed == true)
                    if (speed >= 1) speed--;
                    break;
                case 61:
                    if (ChangeSpeed == true)
                    if (speed < 1000) speed++;
                    break;
                case 104:
                    strcpy(mode,"Hack           ");
                    break;
                case 105:
                    if (!strcmp(mode,"Hack           ") || !strcmp(mode,"Auto and Hack    "))
                    Immortal = !Immortal;
                    if (strcmp(mode,"Auto and Hack    ")) ATP = false;
                    break;
                case 115:
                    if (!strcmp(mode,"Hack           ") || !strcmp(mode,"Auto and Hack    "))
                    ChangeSpeed = !ChangeSpeed;
                    if (strcmp(mode,"Auto and Hack    ")) ATP = false;
                    break;
                case 116:
                    if (!strcmp(mode,"Hack           ") || !strcmp(mode,"Auto and Hack    "))
                    Teleport = !Teleport;
                    if (strcmp(mode,"Auto and Hack    ")) ATP = false;
                    break;
                case 110:
                    strcpy(mode,"Normal          ");
                    if (strcmp(mode,"Auto and Hack    ")) ATP = false;
                    break;
                case 108:
                    if (Teleport == true)
                    checkTele = !checkTele;
                    if (strcmp(mode,"Auto and Hack    ")) ATP = false;
                    break;
                case 97:
                    strcpy(mode,"Auto Play    ");
                    break;
                case 114:
                    strcpy(mode,"Auto and Hack    ");
                    break;
                case 112:
                    if (!strcmp(mode,"Auto and Hack    "))
                    ATP = !ATP;
                    break;
            }
}


void casual()
{
   for (int i = 0;i < snakeLength;i++){
        // Head
        if (i == 0){
            snake[0].x0 = snake[0].x;  snake[0].y0 = snake[0].y;
            snake[0].x += direction.x; snake[0].y += direction.y;
        }
        //Body
        else {
            snake[i].x0 = snake[i].x;snake[i].y0 = snake[i].y;
            snake[i].x = snake[i-1].x0;snake[i].y = snake[i-1].y0;
        }
        //endgame
        if (i != 0 && (snake[0].x == snake[i].x && snake[0].y == snake[i].y) && Immortal == false) endGame = true;
        if (snake[i].x <= MIWEG) snake[i].x = MAWEG-i - 1;
        if (snake[i].x >= MAWEG) snake[i].x = MIWEG + i + 1;
        if (snake[i].y <= MIHIG) snake[i].y = MAHIG-i - 1;
        if (snake[i].y >= MAHIG) snake[i].y = MIHIG + i + 1;
    }
    //Eat Food
    if (EatFood(food,5) == 2 && checkFood == false)
    {
        countFood++;
        checkFood = false;
        if (countFood == 4)
        {
            checkFood = true;
            DrawbigFood(bigFood);
        }
        else drawFood(food);
    }
    else if (checkFood == true)
    {
        countFood = 0;
        if (EatFood(bigFood,10) != 1)
        {
            checkFood = false;
            drawFood(food);
        }
    }
}

char Autoplay(point food)
{
    if (snake[0].x == food.x)
    {
        if (snake[0].y > food.y) return 72;
        else if (snake[0].y < food.y) return 80;
    }
    if (snake[0].y == food.y)
    {
        if (snake[0].x > food.x) return 75;
        else if (snake[0].x < food.x) return 77;
    }
}

void Tele(point& food)
{
    snake[0].x = food.x; snake[0].y = food.y;
    if (checkFood == false ) drawFood(food);
    else DrawbigFood(food);
}

int Length(int n)
{
	int length = 0;
	if (n == 0) return 1;
	while (n > 0)
	{
		n /= 10;
		length++;
	}
	return length;
}

int toString(char s[],int n)
{
	int length = Length(n);
	for (int i = length - 1 ;i >= 0 ;i--)
	{
		s[i] = n % 10 + 48;
		n /= 10;
	}
}

void LoopGame()
{
    Sleep(speed);
    if (checkFood == true) clprint(bigFood.x,bigFood.y,'O',color++);
    if (color >= 15) color = 1;
    casual();
    drawSnake();
    if (ATP == true || !strcmp(mode,"Auto Play    "))  if (checkFood == false) moveSnake = Autoplay(food);
    else moveSnake = Autoplay(bigFood);
    drawInfo();
    drawFram();
    char oldmove = moveSnake;
    if (kbhit()){//Kiem tra xem chuyen dong cua ran co thay doi khong
    moveSnake = getch();
    while (moveSnake == -32){
                moveSnake = getch();
        }
    }
    changeDirection(moveSnake);
    if (moveSnake == 105 || moveSnake == 115 || moveSnake == 116 || moveSnake == 45 || moveSnake == 61 || moveSnake == 108 || moveSnake == 112) moveSnake = oldmove;
}

void run()
{
    initGame();
    while(!endGame){
        LoopGame();
    }
    if (endGame == true){
        scprint(snake[snakeLength-1].x,snake[snakeLength-1].y,"YOU LOSE",10,0);
    }
}


int main()
{
    run();
}
