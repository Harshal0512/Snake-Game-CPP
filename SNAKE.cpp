/******************************

           Snake Game
    Author: Harshal Kulkarni

******************************/

/************Header Files************/
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<time.h>
/************************************/

/************Definitions************/
#define SIZE 15
#define MAX 1000
#define STARTSIZE 4
#define STARTDELAY 250
#define SCOREINCREMENT 100

#define EMPTYSPACE 0
#define HEADCOORD 0
#define SPAWNEDFOOD 100
#define TOP 1
#define LEFT 2
#define BOTTOM 3
#define RIGHT 4
/***********************************/

/************Function Prototypes************/
void printBoard(int x[MAX], int y[MAX], int bodyDir[MAX]);
void increaseSize(int x[MAX], int y[MAX], int bodyDir[MAX], int temp1, int temp2, int temp3);
void food(int board[SIZE][SIZE]);
int isFoodEaten(int x[MAX], int y[MAX], int bodyDir[MAX], int temp1, int temp2, int temp3);
void initSnake(int x[MAX], int y[MAX], int bodyDir[MAX]);
/*******************************************/

/************Global Variables************/
int foodx, foody, foodflag, score, snakeSize, gameOver, win;
/****************************************/

void printBoard(int x[MAX], int y[MAX], int bodyDir[MAX]){
    clrscr();
    int i, j, board[SIZE][SIZE]={EMPTYSPACE}, temp=0;
    //Placing the snake on board
    for(i=0; i<snakeSize; i++){
        if(i==0){
            board[y[HEADCOORD]][x[HEADCOORD]]=bodyDir[HEADCOORD]+10; //head's direction values are plus 10 of body's values
        }else{
            board[ y[i] ][ x[i] ]=bodyDir[i];
        }
    }
    food(board);

    /**********Game Over Condition***********/
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            if(board[i][j] != EMPTYSPACE && board[i][j] != SPAWNEDFOOD)
                temp++;
        }
    }
    if(temp!=snakeSize){
        gameOver=1;
        board[ y[HEADCOORD] ][ x[HEADCOORD] ]=99;
    }
    /****************************************/

    //Printing the board
    cout<<"\n\n\tScore = "<<score<<"\n\tSnake Size = "<<snakeSize<<"\n";
    cout<<"\t\t   ._____________________________________________.\n";
    for(i=0; i<SIZE; i++){
        cout<<"\t\t   |";
        for(j=0; j<SIZE; j++){
            if(board[i][j]==TOP || board[i][j]==BOTTOM)
                cout<<"I";
            else if(board[i][j]==LEFT || board[i][j]==RIGHT)
                cout<<"-";
            else if(board[i][j]==TOP+10)
                cout<<"^";
            else if(board[i][j]==LEFT+10)
                cout<<"<";
            else if(board[i][j]==BOTTOM+10)
                cout<<"v";
            else if(board[i][j]==RIGHT+10)
                cout<<">";
            else if(board[i][j]==SPAWNEDFOOD)
                cout<<"O";
            else if(board[i][j]==99)
                cout<<"X";
            else if(board[i][j]==EMPTYSPACE)
                cout<<" ";

            cout<<"  ";
        }
        cout<<"|\n";
    }
    cout<<"\t\t   |_____________________________________________|";
}

void increaseSize(int x[MAX], int y[MAX], int bodyDir[MAX], int temp1, int temp2, int temp3){
    if(score%3==0){ //Size increases every 3rd food eaten
        x[snakeSize]=temp1;
        y[snakeSize]=temp2;
        bodyDir[snakeSize]=temp3;
        snakeSize++;
    }
}

void food(int board[SIZE][SIZE]){
    int i, j, temp=0;
    if(foodflag==0){
        board[foody][foodx]=SPAWNEDFOOD;
    }
    
    /********WIN CONDITION********/
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            if(board[i][j] != EMPTYSPACE && board[i][j] != SPAWNEDFOOD)
                temp++;
        }
    }                                                       //if all the blocks are covered by snake then win=1
    if(temp==SIZE*SIZE){
        gameOver=1;
        win=1;
    }
    /*****************************/
    while(foodflag==1){
        i=rand() % SIZE;
        j=rand() % SIZE;
        if(board[i][j]==EMPTYSPACE){ //To check if food isn't spawned on the coordinates of snake's body
            board[i][j]=SPAWNEDFOOD;
            foodx=j;
            foody=i;
            foodflag=0;
        }
    }
}

int isFoodEaten(int x[MAX], int y[MAX], int bodyDir[MAX], int temp1, int temp2, int temp3){
    if(x[HEADCOORD]==foodx && y[HEADCOORD]==foody){
        score+=SCOREINCREMENT;
        increaseSize(x, y, bodyDir, temp1, temp2, temp3);
        return 1;
    }
    else
        return 0;
}

void initSnake(int x[MAX], int y[MAX], int bodyDir[MAX]){
    int temp1, temp2;
    temp1=temp2=SIZE/2-1;
    while(snakeSize<STARTSIZE){
        if(snakeSize==0){
            x[snakeSize]=temp1;
            y[snakeSize]=temp2;
            bodyDir[snakeSize]=2;
        }else{
            x[snakeSize]=temp1;
            y[snakeSize]=temp2;
            bodyDir[snakeSize]=2;
        }
        temp1++;
        snakeSize++;
    }
}

void main(){
    restartLabel:
    foodflag=1, score=0, snakeSize=0, gameOver=0, win=0;
    srand(time(NULL));
    int x[MAX], y[MAX], bodyDir[MAX];
    char dir='A';
    initSnake(x, y, bodyDir);
    /*
        1/w-top
        2/a-left
        3/s-bottom
        4/d-right
        x-horizontal direction
        y-vertical direction
    */
    printBoard(x, y, bodyDir);
    cout<<"\n\n\t\tPress Any Key to Start the Game";
    getch();
    clrscr();
    while(1){
        clrscr();
        if(kbhit()){    //if key pressed
            char input;
            input=getch();
            if( (int(input)=='W' || int(input)=='w') && dir!='S'){
                dir='W';
            }
            if( (int(input)=='S' || int(input)=='s') && dir!='W'){
                dir='S';
            }
            if( (int(input)=='A' || int(input)=='a') && dir!='D'){
                dir='A';
            }
            if( (int(input)=='D' || int(input)=='d') && dir!='A'){
                dir='D';
            }
            if(int(input)=='Q' || int(input)=='q'){
                exit(0);
            }
        }
        //if key is not pressed..
        int x1, y1, b1, temp1=x[HEADCOORD], temp2=y[HEADCOORD], temp3=bodyDir[HEADCOORD];
        for(int i=1; i<snakeSize; i++){
            x1=x[i];
            y1=y[i];
            b1=bodyDir[i];
            x[i]=temp1;
            y[i]=temp2;
            bodyDir[i]=temp3;
            temp1=x1;
            temp2=y1;
            temp3=b1;
        }
        switch(dir){
            case 'W':
                if(y[HEADCOORD]==0)
                    y[HEADCOORD]=SIZE-1;
                else
                    y[HEADCOORD]--;
                bodyDir[HEADCOORD]=1;
                break;
            case 'S':
                if(y[HEADCOORD]==SIZE-1)
                    y[HEADCOORD]=0;
                else
                    y[HEADCOORD]++;
                bodyDir[HEADCOORD]=3;
                break;
            case 'A':
                if(x[HEADCOORD]==0)
                    x[HEADCOORD]=SIZE-1;
                else
                    x[HEADCOORD]--;
                bodyDir[HEADCOORD]=2;
                break;
            case 'D':
                if(x[HEADCOORD]==SIZE-1)
                    x[HEADCOORD]=0;
                else
                    x[HEADCOORD]++;
                bodyDir[HEADCOORD]=4;
                break;
        }
        foodflag=isFoodEaten(x, y, bodyDir, temp1, temp2, temp3);
        printBoard(x, y, bodyDir);
        int delaycalc=STARTDELAY-(score/20);
        if(delaycalc<100)
            delay(100);
        else
            delay(delaycalc);
        if(gameOver==1 && win==1){
            cout<<"\n\n\t\tCongratulation!!! You won...";
            cout<<"\n\t\tPress Y or y to try again";
            cout<<"\n\t\tCHOICE: ";
            char c;
            cin>>c;
            if(c=='Y' || c=='y')
                goto restartLabel;
            else{
                exit(0);
            }
        }else if(gameOver==1 && win==0){
            cout<<"\n\n\t\tOops You Crashed...";
            cout<<"\n\t\tPress Y or y to try again";
            cout<<"\n\t\tCHOICE: ";
            char c;
            cin>>c;
            if(c=='Y' || c=='y')
                goto restartLabel;
            else{
                exit(0);
            }
        }
    }
}