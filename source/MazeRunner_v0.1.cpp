#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#define SIZE 10
#define FRAME_DELAY 500
#define INIT_X 1
#define INIT_Y 1


enum directions
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

const int random = -999;


bool decision;






/*int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {0,0,0,0,0,0,0,254,0,254},
    {254,254,254,0,254,254,0,254,0,254},
    {254,0,254,0,254,254,0,0,0,254},
    {254,0,254,0,0,0,254,254,0,254},
    {254,0,254,0,254,0,254,254,254,254},
    {254,0,254,0,254,0,0,0,0,254},
    {254,0,254,254,254,0,254,254,0,254},
    {254,0,0,0,0,0,0,254,0,0},
    {254,254,254,254,254,254,254,254,254,254}
};*/

/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254,254,254,254,254, 0 ,254,254,254},
    {254,254,254,254,254,254, 0 , 0 , 0 ,254},
    {254,254,254,254,254,254,254,254, 0 ,254},
    {254,254,254,254,254,254,254,254, 0 ,254},
    {254,254,254,254,254,254,254,254, 0 ,254},
    {254,254,254,254,254,254,254,254, 0 ,254},
    {254,254,254,254,254,254,254,254, 0 , 0 },
    {254,254,254,254,254,254,254,254,254,254}
};*/
/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254, 0 ,254,254,254, 0 ,254,254,254},
    {254,254, 0 ,254,254,254, 0 , 0 , 0 ,254},
    {254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 ,254,254, 0 , 0 ,254},
    {254,254,254,254,254,254,254,254,254,254}

};*/

int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254,254,254, 0 ,254, 0 ,254,254,254},
    {254,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254},
    {254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 ,254,254,254, 0 ,254},
    {254,254,254,254,254,254,254,254,254,254}

};




struct Position
{
    int x = 1;
    int y = 1;

} pos, prevPos, targetPos, breakPoint;




int check()
{
    int x = pos.x;
    int y = pos.y;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;


    if ( maze[y-1][x] == 0 )       //UP
    {
        up = true;
    }
    if ( maze[y+1][x] == 0 )  //DOWN
    {
        down = true;
    }
    if ( maze[y][x+1] == 0 )  //RIGHT
    {
        right = true;
    }
    if ( maze[y][x-1] == 0 )  //LEFT
    {
        left = true;
    }
    /*else
    {
        printf("\nI guess I messed up?");
        exit(1);
    }*/

    if (up) { return UP; }
    if (down) { return DOWN; }
    if (right) { return RIGHT; }
    if (left) { return LEFT; }

}

int numberOfChoices()
{
    int x = pos.x;
    int y = pos.y;

    int choices = 0;

    if ( maze[y-1][x] == 0 )       //UP
    {
        choices++;
    }
    if ( maze[y+1][x] == 0 )  //DOWN
    {
        choices++;
    }
    if ( maze[y][x+1] == 0 )  //RIGHT
    {
        choices++;
    }
    if ( maze[y][x-1] == 0 )  //LEFT
    {
        choices++;
    }

    return choices;
}




bool checkHere ( int where )
{
    int x = pos.x;
    int y = pos.y;

    switch ( where )
    {
    case UP:
        if ( maze[y-1][x] == 0 ) { return true; }
        else { return false; }
        break;

    case DOWN:
        if ( maze[y+1][x] == 0 ) { return true; }
        else { return false; }
        break;

    case RIGHT:
        if ( maze[y][x+1] == 0 ) { return true; }
        else { return false; }
        break;
    case LEFT:
        if ( maze[y][x-1] == 0 ) { return true; }
        else { return false; }
        break;

    default:
        printf("\nIn function: checkHere(int where) FATAL ERROR!");
        exit(-1);
        break;
    }
}




void moveto( int where )
{
    switch ( where )
    {
    case UP:
        pos.y--;
        break;

    case DOWN:
        pos.y++;
        break;

    case RIGHT:
        pos.x++;
        break;

    case LEFT:
        pos.x--;
        break;

    default:
        printf("\nIn function: moveto(int where)  FATAL ERROR!");
        exit(-1);
    }
}



void printMaze()
{
    int holder = maze[pos.y][pos.x];
    maze[pos.y][pos.x] = 'o';

    system("cls");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            printf(" %c", maze[i][j]);
        }
        printf("\n");
    }

    Sleep(FRAME_DELAY);
    maze[pos.y][pos.x] = holder;

}






int main()
{
    pos.x = INIT_X;
    pos.y = INIT_Y;


    int direction;
    bool done = false;

    printMaze();
    printf("\nPress any key to start.");
    getchar();

    direction = check();

    while ( !done )
    {
        //if ( numberOfChoices <= 2 )
        {
        while ( numberOfChoices() <= 2 && checkHere(direction) )
        {
            moveto ( direction );
            printMaze();
            printf("\nMaze printed");
        }

        printf("\nI have a choice here.");
        system("pause");

        breakPoint.x = pos.x;
        breakPoint.y = pos.y;
        printf("\nBreak point saved.");


        direction = check();
        moveto(direction);
        printMaze();



        if ( pos.x == 8 && pos.y == 8 ) { done = true; }
    }









    return 0;
}





















