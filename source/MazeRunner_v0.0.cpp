#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define SIZE 10
#define FRAME_DELAY 500


enum direction
{
    CURRENT,
    UP,
    DOWN,
    RIGHT,
    LEFT
};






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

int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    { 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254, 0 ,254,254,254, 0 ,254,254,254},
    {254,254, 0 ,254,254,254, 0 , 0 , 0 ,254},
    {254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 },
    {254,254,254,254,254,254,254,254,254,254}

};




struct Position
{
    int x = 0;
    int y = 1;

} pos, prevPos, targetPos, breakPoint;

int check();
void printMaze();





int check()
{
    int x = pos.x;
    int y = pos.y;

    if ( maze[y][x+1] == 0 )
    {
        return RIGHT;
    }
    else if ( maze[y+1][x] == 0 )
    {
        return DOWN;
    }
    else if ( maze[y-1][x] == 0 )
    {
        return UP;
    }
    else if ( maze[y][x-1] == 0 )
    {
        return LEFT;
    }
}

bool checkDirection ( int where )
{
    int x = pos.x;
    int y = pos.y;

    switch ( where )
    {
    case RIGHT:
        if ( maze[y][x+1] == 0 ) { return true; }
        break;
    case LEFT:
        if ( maze[y][x-1] == 0 ) { return true; }
        break;
    case DOWN:
        if ( maze[y+1][x] == 0 ) { return true; }
        break;
    case UP:
        if ( maze[y-1][x] == 0 ) { return true; }
        break;
    default:
        return false;
        break;
    }

    return false;
}

bool checkExcept ( int where )
{
    if ( where == RIGHT )
    {
        if ( checkDirection(LEFT) || checkDirection(UP) || checkDirection(DOWN) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if ( where == LEFT )
    {
        if ( checkDirection(RIGHT) || checkDirection(UP) || checkDirection(DOWN) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if ( where == UP )
    {
        if ( checkDirection(LEFT) || checkDirection(RIGHT) || checkDirection(DOWN) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if ( where == DOWN )
    {
        if ( checkDirection(LEFT) || checkDirection(UP) || checkDirection(RIGHT) )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}









Position setTarget ( int where )
{
    Position tempPosHolder;

    tempPosHolder.x = pos.x;
    tempPosHolder.y = pos.y;

    switch ( where )
    {
        case RIGHT:
            tempPosHolder.x++;
            break;
        case UP:
            tempPosHolder.y--;
            break;
        case DOWN:
            tempPosHolder.y++;
            break;
        case LEFT:
            tempPosHolder.x--;
            break;

    }

    return tempPosHolder;

}

int rvrs ( int inputDirection )
{
    switch ( inputDirection )
    {
    case RIGHT:
        return LEFT;
        break;
    case LEFT:
        return RIGHT;
        break;
    case UP:
        return DOWN;
        break;
    case DOWN:
        return UP;
        break;
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

    bool done = false;
    int direction = -1;  //I gave the same name to this with an enum and for whatever reason i did not get an error. You better change this.


    printMaze();

    while ( !done )
    {

        if ( !checkDirection ( direction ) )
        {
            direction = check();

            breakPoint.x = pos.x;
            breakPoint.y = pos.y;

        }
        targetPos = setTarget ( direction );

        if ( targetPos.x == prevPos.x && targetPos.y == prevPos.y )
        {
            maze[pos.y][pos.x] = 254;
            while ( pos.x != breakPoint.x && pos.y != breakPoint.y )
            {


            }

        }

        prevPos.x = pos.x;
        prevPos.y = pos.y;

        pos.x = targetPos.x;
        pos.y = targetPos.y;

        printMaze();

        if ( pos.x == 9 && pos.y == 8 ) { done = true; }

    }

    printf("\nDONE!!!");




    return 0;
}



















