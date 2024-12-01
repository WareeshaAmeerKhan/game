#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;void gotoxy(int x,int y);
char getCharAtxy(short int x, short int y);

void printMaze();
void displayHeader();
void displayMenu();
void InstructionMenu();
void exit();
void clearScreen();
void printBonus();

int score=0;
bool bonus=false;

char enemy1[4][21] = {
                        {' ',' ',' ',' ',' ','\\','\\',' ',' ',' ','/','/'},
                        {'/','o','=','=','=','=','=','=','=','\\','.','.','.','.','.','.','.','.','.','.','.'},
                        {'\\','o','=','=','=','=','=','=','=','/','.','.','.','.','.','.','.','.','.','.','.'},
                        {' ',' ',' ',' ',' ','/','/',' ',' ',' ','\\','\\'}
                     };

char enemy2[3][14] = {
                        {'.',' ',' ',' ','.'},
                        {' ','\\',' ','/',' ',' ','_','_','_','_'},
                        {' ','(','@',')','_','(','(','(',')',')',')','>','>','>'}
                     }; 

char enemy3[3][14] = {
                        {' ',' ','_','_','_','_','@','.','@','_','_','_','_'},
                        {' ',' ','|',' ','|',' ','|',' ','|',' ','|',' ','|'},
                        {' ','/',' ','/',' ','/',' ',' ',' ','\\',' ','\\',' ','\\'}
                     };

char player[5][6] = {
                        {' ','_','_'},
                        {'(',' ',';','>'},
                        {' ','|','|','=','=','>'},
                        {' ','(',')'},
                        {' ','|','_','\\','_'}
                    };
int px=6,py=8;
int ex1=145,ey1=8;
int ex2=145,ey2=19;
int ex3=145,ey3=30;

int bulletX[5000];
int bulletY[5000];
bool isBulletActive[5000]={false};
int bulletCount=0;

void printplayer();
void eraseplayer();
void movePlayer();

void playerdown();
void playerleft();
void playerright();
void playerup();

void FireBullet();
void MoveBullete();
void printBullet(int x, int y);
void eraseBullete(int x, int y);
void makeBulletInActive(int index);

void printenemy1();
void eraseenemy1();
void MoveEnemy1(int enemyIndex, int& enemyX, int& enemyY);

void printenemy2();
void eraseenemy2();
void MoveEnemy2(int enemyIndex, int& enemyX, int& enemyY);

void printenemy3();
void eraseenemy3();
void MoveEnemy3(int enemyIndex, int& enemyX, int& enemyY);

int enemyBulletX[5000];
int enemyBulletY[5000];
bool isEnemyBulletActive[5000] = {false};
int enemyBulletCount = 0;
const int maxEnemyBullets = 5000; 
const int bulletsPerBurst = 5;  
bool isEnemyPaused[3] = {false, false, false}; 
int pauseCounter[3] = {0, 0, 0};               
int pauseThreshold = 50;                      
int enemyMoveDirection[3] = {1, 1, 1};        

void ShootEnemyBullets(int enemyIndex, int enemyX, int enemyY);
void MoveEnemyBullets();
void printBulletEnemy(int x, int y);
void eraseBulletEnemy(int x, int y);

main()
{
	system("cls");
    displayHeader();
    displayMenu();
}

void displayMenu()
{
    int option;
    cout<<"Choose option: "<<endl;
    cout<<"1) Instructions"<<endl;
    cout<<"2) Start Game"<<endl;
    cout<<"0) Exit"<<endl;
    cout<<"Your Option: ";
    cin>>option;
    cout<<endl<<"Loading..."<<endl;
    clearScreen();
    if(option==0)
    {
        exit();
    }
    else if(option==1)
    {
        InstructionMenu();
    }
    else if(option==2)
    {
        system("cls");
        printMaze();
        printBonus();
        printplayer();
        printenemy1();
        printenemy2();
        printenemy3();
        gotoxy(180,10);
        cout<<"--------------------------"<<endl;
        gotoxy(180,11);
        cout<<"   Score: "<<score<<endl;
        gotoxy(180,12);
        cout<<"--------------------------"<<endl;
        gotoxy(180,13);
        cout<<"Press ctrl key to go back to menu!";
    	while(true)
	    {
            if(GetAsyncKeyState(VK_CONTROL))
            {
                clearScreen();
                displayMenu();
                break;
            }
		    if(GetAsyncKeyState(VK_RIGHT))
	        {
		        playerright();
	        }
	        if(GetAsyncKeyState(VK_UP))
	        {   
		        playerup();
	        }
	        if(GetAsyncKeyState(VK_LEFT))
	        {
		        playerleft();
	        }
	        if(GetAsyncKeyState(VK_DOWN))
	        {
		        playerdown();
	        }
            if(GetAsyncKeyState(VK_SPACE))
	        {
		        FireBullet();
	        }
            if(!bonus && px<=100 && px+6>=100 && py<=25 && py+5>=25)
	        {
		        score+=1;
		        bonus=true;
                gotoxy(180,11);
		        cout<<"   Score: "<<score;
        	}

            MoveBullete();
            MoveEnemy1(0, ex1, ey1);
            ShootEnemyBullets(0, ex1, ey1); 

            MoveEnemy2(1, ex2, ey2); 
            ShootEnemyBullets(1, ex2, ey2); 

            MoveEnemy3(2, ex3, ey3);
            ShootEnemyBullets(2, ex3, ey3); 

            MoveEnemyBullets();

            Sleep(20); 

        }
    }
}

void InstructionMenu()
{
    cout<<"INSTRUCTIONS"<<endl;
    cout<<"<~~~~~~~~~~>"<<endl;
    cout<<"Follow these instructions while playing the game: "<<endl;
    cout<<"--------------------------------------------------"<<endl;
    cout<<"1) Press right arrow to move forward"<<endl;
    cout<<"2) Press left arrow to move backward"<<endl;
    cout<<"3) Press up arrow to move upward"<<endl;
    cout<<"4) Press down to move downward"<<endl;
    cout<<"5) Press space to shoot fire"<<endl;

    cout << "Press any key to go back! ";
    _getch();
    cout << endl;
    cout << "Loading..." << endl;
    clearScreen();
    displayMenu();
}

void clearScreen() 
{
    Sleep(1000);   
    system("cls"); 
    displayHeader();
}

void printBonus()
{
	gotoxy(100,25);
	cout<<"($)";
}

void exit()
{
    int option;

    cout<<"Are you sure to exit app? ";
    cout<<"\n\t 1)Yes \t 2)No \n"<<endl;
    cout<<"Choose option: ";
    cin>>option;
    cout<<"Loading...";
    if(option==1)
    {
        clearScreen();
        cout<<"Exiting App...";
        Sleep(2000);
        system("cls");
        exit(0);
    }
    else if(option==2)
    {
        clearScreen();
        displayMenu();
        cout<<"Loading..."<<endl;
    }
    else
    {
        cout<<"\nInvalid Option! Try again.\n";
        clearScreen();
        exit();
    }
}

void displayHeader()
{
cout<<"    #####     ######     #####      ######          ##  ##     ######     ##       ##       ######     #####   "<<endl;
cout<<"    ##  ##    ##        ##            ##            ## ##        ##       ##       ##       ##         ##  ##  "<<endl; 
cout<<"    #####     #####      ####         ##            ####         ##       ##       ##       #####      #####   "<<endl;
cout<<"    ##        ##            ##        ##            ## ##        ##       ##       ##       ##         ## ##   "<<endl;
cout<<"    ##        ######    #####         ##            ##  ##     ######     ######   ######   ######     ##  ##  "<<endl<<endl<<endl;
}

void printMaze()
{
cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"#                                                                                                                                                                         #"<<endl;
cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #"<<endl;
}

void gotoxy(int x,int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
	CHAR_INFO ci;
	COORD xy={0,0};
	SMALL_RECT rect={x,y,x,y};
	COORD coordBufSize;
	coordBufSize.X=1;
	coordBufSize.Y=1;
	return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar: ' ';
}

void printenemy1()
{
	for (int i = 0; i < 4; i++)
    {
        gotoxy(ex1,ey1+i);
        for (int j = 0; j < 21; j++)
        {
            cout<<enemy1[i][j];
        }
    }
}

void eraseenemy1()
{
	for (int i = 0; i < 4; i++)
    {
        gotoxy(ex1,ey1+i);
        for (int j = 0; j < 21; j++)
        {
            cout<<" ";
        }
    }
}

void MoveEnemy1(int enemyIndex, int& enemyX, int& enemyY)
{
    if (!isEnemyPaused[enemyIndex]) 
    {
        eraseenemy1(); 
        enemyY += enemyMoveDirection[enemyIndex]; 

        if (enemyY <= 1 || enemyY >= 11)
        {
            enemyMoveDirection[enemyIndex] = -enemyMoveDirection[enemyIndex];
        }

        printenemy1(); 

        if (enemyY % 3 == 0)
        {
            isEnemyPaused[enemyIndex] = true;
        }
    }
}

void printenemy2()
{
    for (int i = 0; i < 3; i++)
    {
        gotoxy(ex2,ey2+i);
        for (int j = 0; j < 14; j++)
        {
            cout<<enemy2[i][j];
        }
    }
}

void eraseenemy2()
{
	for (int i = 0; i < 3; i++)
    {
        gotoxy(ex2,ey2+i);
        for (int j = 0; j < 14; j++)
        {
            cout<<" ";
        }
    }
}

void MoveEnemy2(int enemyIndex, int& enemyX, int& enemyY)
{
    if (!isEnemyPaused[enemyIndex]) 
    {
        eraseenemy2(); 
        enemyY += enemyMoveDirection[enemyIndex]; 

        if (enemyY <= 12 || enemyY >= 22)
        {
            enemyMoveDirection[enemyIndex] = -enemyMoveDirection[enemyIndex];
        }

        printenemy2(); 

        if (enemyY % 3 == 0)
        {
            isEnemyPaused[enemyIndex] = true;
        }
    }
}

void printenemy3()
{
	for (int i = 0; i < 3; i++)
    {
        gotoxy(ex3,ey3+i);
        for (int j = 0; j < 14; j++)
        {
            cout<<enemy3[i][j];
        }
    }
}

void eraseenemy3()
{
	for (int i = 0; i < 3; i++)
    {
        gotoxy(ex3,ey3+i);
        for (int j = 0; j < 14; j++)
        {
            cout<<" ";
        }
    }
}

void MoveEnemy3(int enemyIndex, int& enemyX, int& enemyY)
{
    if (!isEnemyPaused[enemyIndex]) 
    {
        eraseenemy3(); 
        enemyY += enemyMoveDirection[enemyIndex]; 

        if (enemyY <= 23 || enemyY >= 33)
        {
            enemyMoveDirection[enemyIndex] = -enemyMoveDirection[enemyIndex];
        }

        printenemy3(); 

        if (enemyY % 3 == 0)
        {
            isEnemyPaused[enemyIndex] = true;
        }
    }
}

void printplayer()
{
    for (int i = 0; i < 5; i++)
    {
        gotoxy(px,py+i);
        for (int j = 0; j < 6; j++)
        {
            cout<<player[i][j];
        }
    }
}

void eraseplayer()
{
	for (int i = 0; i < 5; i++)
    {
        gotoxy(px,py+i);
        for (int j = 0; j < 6; j++)
        {
            cout<<" ";
        }
    }
}

void playerright()
{
   if(getCharAtxy(px+6,py)!='#')
   {
	Sleep(10);
	eraseplayer();
	px=px+2;
	printplayer();
   }
}

void playerup()
{
   if(getCharAtxy(px,py-2)!='#')
   {
	Sleep(10);
	eraseplayer();
	py=py-1;
	printplayer();
   }
}

void playerdown()
{
   if(getCharAtxy(px,py+5)!='#')
   {
	Sleep(10);
	eraseplayer();
	py=py+1;
	printplayer();
   }
}

void playerleft()
{
   if(getCharAtxy(px-2,py)!='#')
   {
	Sleep(10);
	eraseplayer();
	px=px-2;
	printplayer();
   }
}

void FireBullet()
{
    bulletX[bulletCount]=px+7;
    bulletY[bulletCount]=py+2;
    isBulletActive[bulletCount]=true;
    gotoxy(px+7,py+2);
    cout<<"~";
    bulletCount++;
}

void MoveBullete()
{
    for(int x=0; x<bulletCount; x++)
    {
        char next=getCharAtxy(bulletX[x]+1,bulletY[x]);
        if(next!=' ')
        {
            eraseBullete(bulletX[x],bulletY[x]);
            makeBulletInActive(x);
        }
        else
        {
            eraseBullete(bulletX[x],bulletY[x]);
            bulletX[x]=bulletX[x]+2;
            printBullet(bulletX[x],bulletY[x]);
        }
    }
}

void printBullet(int x, int y)
{
    gotoxy(x,y);
    cout<<"~";
}

void eraseBullete(int x, int y)
{
    gotoxy(x,y);
    cout<<" ";
}

void makeBulletInActive(int index)
{
    isBulletActive[index]=false;
}

void ShootEnemyBullets(int enemyIndex, int enemyX, int enemyY)
{
    if (isEnemyPaused[enemyIndex]) 
    {
        pauseCounter[enemyIndex]++;

        if (pauseCounter[enemyIndex] == 1) 
        {
            for (int i = 0; i < 5; i++) 
            {
                if (enemyBulletCount < maxEnemyBullets)
                {
                    enemyBulletX[enemyBulletCount] = enemyX - 5 + i;  
                    enemyBulletY[enemyBulletCount] = enemyY+1; 
                    isEnemyBulletActive[enemyBulletCount] = true;

                    gotoxy(enemyBulletX[enemyBulletCount], enemyBulletY[enemyBulletCount]);
                    cout << "."; 
                    enemyBulletCount++;
                }
            }
        }

        if (pauseCounter[enemyIndex] >= pauseThreshold)
        {
            isEnemyPaused[enemyIndex] = false; 
            pauseCounter[enemyIndex] = 0;     
        }
    }
}

void MoveEnemyBullets()
{
    for (int i = 0; i < enemyBulletCount; i++)
    {
        if (isEnemyBulletActive[i])
        {
            char next = getCharAtxy(enemyBulletX[i] - 1, enemyBulletY[i]); 
            
            if (next != ' ')
            {
                eraseBulletEnemy(enemyBulletX[i], enemyBulletY[i]);
                isEnemyBulletActive[i] = false;
            }
            else
            {
                eraseBulletEnemy(enemyBulletX[i], enemyBulletY[i]);
                enemyBulletX[i]--; 
                printBulletEnemy(enemyBulletX[i], enemyBulletY[i]);
            }
        }
    }
}

void printBulletEnemy(int x, int y)
{
    gotoxy(x,y);
    cout<<".";
}

void eraseBulletEnemy(int x, int y)
{
    gotoxy(x,y);
    cout<<" ";
}

