#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>

//#define SCREEN_WIDTH 90
//#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

#define T1POS 15
#define T2POS 30
#define T3POS 45
#define DISKS 5

using namespace std; 
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
 
int towers[3][DISKS];
int towerTop[3] = {DISKS-1,-1,-1};

int tries = 0; 
int score = 0; 

void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}
void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Tries: "<<tries<<endl;
}
void instructions(){
	
	system("cls");
	gotoxy(10,5); cout<<" -------------------------------------------------------------------------------------------------- "; 
	gotoxy(10,6); cout<<" |                                      Instructions                                              | "; 
	gotoxy(10,7); cout<<" --------------------------------------------------------------------------------------------------";
	gotoxy(10,10); cout<<"                             Shift Disks from Tower 1 to Tower 3. ";
	gotoxy(10,12); cout<<"                             You can not place large disk on small disk";
	gotoxy(10,14); cout<<"                             Towers are Numbered as 1,2 and 3";
	gotoxy(10,20); cout<<"                             Press any key to go back to menu...";
	getch();
}
void drawTile(int tower, int tileNo, int y){
	int x;
	if( tower == 1 ) x = T1POS;
	else if( tower == 2 ) x = T2POS;
	else if( tower == 3 ) x = T3POS;
	
	x -= tileNo;
	
	for(int j=0; j<((tileNo)*2)-1; j++){
		gotoxy(x,y);
		cout<<"*";
		x++;
	}
}
void drawTower(int tower){
	int x;
	int y = 9;
	
	gotoxy(10, 10); cout<<"=========";
	gotoxy(25, 10); cout<<"=========";
	gotoxy(40, 10); cout<<"=========";
	
	gotoxy(14, 11); cout<<"1";
	gotoxy(29, 11); cout<<"2";
	gotoxy(44, 11); cout<<"3";
	
	for(int i=0; i<5; i++){
		drawTile(tower, towers[tower-1][i], y);
		y--;
	}
}
int isEmpty(int towerNo){
	for(int i=0; i<DISKS; i++)
		if( towers[towerNo][i] != 0 )
			return 0;
	return 1;
}
int validate(int from, int to){
	if( !isEmpty(to) ){
		  
		if( towers[from][towerTop[from]] < towers[to][towerTop[to]] )
			return 1;
		else 
			return 0;
	}
	return 1;
}
int move(int from, int to){
	if( isEmpty(from) ) return 0; 
	if( validate(from, to) ){ 
		if( towers[from][towerTop[from]] != 0 ){
			towerTop[to]++;
			towers[to][towerTop[to]] = towers[from][towerTop[from]];
			towers[from][towerTop[from]] = 0;
			towerTop[from]--;
			return 1;
		}
	}
	return 0;
}
int win(){ 
	for(int i=0; i<DISKS; i++)
		if( towers[2][i] != DISKS-i )
			return 0;
	return 1;
}

void play(){
	int from, to;
	for(int i=0; i<DISKS; i++)
		towers[0][i] = DISKS-i;
	for(int i=0; i<DISKS; i++)
		towers[1][i] = 0;
	for(int i=0; i<DISKS; i++)
		towers[2][i] = 0;
	 
	do{
		system("cls"); 		  
		
		gotoxy(10,2); cout<<"================================================================================================="<<endl;
		gotoxy(10,3); cout<<"                                            TOWER OF HANOI                                                          "<<endl;
		gotoxy(10,4); cout<<"================================================================================================="<<endl<<endl;
		
		drawTower(1);
		drawTower(2);
		drawTower(3);
		
		if( win() ){
			system("cls");
			gotoxy(10,3); cout<<"============================================================"<<endl;
			gotoxy(10,4); cout<<"                           YOU WIN                          "<<endl;
			gotoxy(10,5); cout<<"============================================================"<<endl;
			cout<<endl<<endl<<endl;
			cout<<"Press any key to go back to menu...";
			getch();
			break;
		}
		
		gotoxy(65,8);
		cout<<"From (Values: 1,2,3): ";
		cin>>from;
		gotoxy(65,10);
		cout<<"To   (Values: 1,2,3): ";
		cin>>to;
		
		if( to < 1 || to > 3 ) continue;
		if( from < 1 || from > 3 ) continue;
		if( from == to ) continue;
		
		from--;
		to--;
		
		move(from, to);
		 
		if(kbhit()){
			char ch = getch();
			if( ch=='a' || ch=='A' ){ 
			}
			if( ch=='d' || ch=='D' ){ 
			} 
			if(ch==27){
				break;
			}
		} 
		  
	}while(1);
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	 
	do{
		system("cls");
		gotoxy(10,5); cout<<" -------------------------------------------------------------------------------------------------- "; 
		gotoxy(10,6); cout<<" |                                      Tower of Hanoi                                            | "; 
		gotoxy(10,7); cout<<" --------------------------------------------------------------------------------------------------";
		gotoxy(10,10); cout<<"                                       1. Start Game";
		gotoxy(10,12); cout<<"                                       2. How To Win";	 
		gotoxy(10,14); cout<<"                                       3. Quit";
		gotoxy(10,17); cout<<"                                       Select option: ";
		char op = getche();
		
		if( op=='1') play();
		else if( op=='2') instructions();
		else if( op=='3') exit(0);
	}while(1);
	
	return 0;
}
