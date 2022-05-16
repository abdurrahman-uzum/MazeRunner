#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//#include "MAZE10_loop.h"
#include "MAZE20_simple.h"

#define FRAME_DELAY 350  //Decrement the value for less delay per step.


//Direction-position managing:

enum directions
{
    NORTH = 1,
    SOUTH = -1,
    EAST = 0,
    WEST = 2
};


int FORWARD = 0;
int RIGHT = -1;
int LEFT = 1;
int BACK = 2;


struct Position
{
    int x = 1;
    int y = 1;

} pos;

//////


//Global flags:

bool done = false;

int loopDetector = 0;
bool loop = false;

//////


//Control arrays:

int decisions[50];
int directionBeforeDecision[50];
int forbiddenPaths[100][100];

//////


//Global variables:

int absoluteDirection;

int y = 0;

int decision = 0;

int direction;

//////


//Function prototypes:

void printMaze(void);

int numberOfChoices(void);
bool checkHere(int);

void turn(int);
void proceed(void);

bool readForward(void);
bool readRight(void);
bool readLeft(void);

int decode(int);

void writeForbiddenPaths(void);
bool readForbiddenPaths(void);
void printForbiddenPaths(void);

void regularTurn ( void );
bool isloop ( void );

///////



void printMaze()
{
    int holder = maze[pos.y][pos.x];

    switch(absoluteDirection%4)
    {
    case 1: case -3:
        maze[pos.y][pos.x] = '^';//202;
        break;
    case 0:
        maze[pos.y][pos.x] = '>';//204;
        break;
    case 2: case -2:
        maze[pos.y][pos.x] = '<';//185;
        break;
    case -1: case 3:
        maze[pos.y][pos.x] = 'v';//203;
        break;
    }

    system("cls");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            printf(" %c", maze[i][j]==WALL ? 254 : maze[i][j] );
        }
        printf("\n");
    }

    //For debugging:

    printf("decision:%d   pos:(%d,%d)   loopDetector:%d\n" , decision, pos.x, pos.y, loopDetector );

    printf("decisions:");
    for ( i=0; i<=decision; i++ )
    {
        printf(" %d", decisions[i]);
    }
    printf("\n");

    Sleep(FRAME_DELAY);
    maze[pos.y][pos.x] = holder;
}





int numberOfChoices()
{
    int x = pos.x;
    int y = pos.y;

    int choices = 0;

    if ( maze[y-1][x] != WALL )  //UP
    {
        choices++;
    }
    if ( maze[y+1][x] != WALL )  //DOWN
    {
        choices++;
    }
    if ( maze[y][x+1] != WALL )  //RIGHT
    {
        choices++;
    }
    if ( maze[y][x-1] != WALL )  //LEFT
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
        case NORTH:
            if ( maze[y-1][x] != WALL ) { return true; }
            else { return false; }
            break;

        case SOUTH:
            if ( maze[y+1][x] != WALL ) { return true; }
            else { return false; }
            break;

        case EAST:
            if ( maze[y][x+1] != WALL ) { return true; }
            else { return false; }
            break;
        case WEST:
            if ( maze[y][x-1] != WALL ) { return true; }
            else { return false; }
            break;

        default:
            printf("\nIn function: checkHere(int where) FATAL ERROR!");
            exit(-1);
            break;
    }
}







void turn ( int where )
{
    int prevFORWARD = FORWARD;
    int prevRIGHT = RIGHT;
    int prevLEFT = LEFT;
    int prevBACK = BACK;


    if ( where == FORWARD )
    {

    }
    else if ( where == RIGHT )
    {
        absoluteDirection--;
        //loopDetector--;

        FORWARD = prevRIGHT;
        RIGHT = prevBACK;
        LEFT = prevFORWARD;
        BACK = prevLEFT;
    }

    else if ( where == LEFT )
    {
        absoluteDirection++;
        //loopDetector++;

        FORWARD = prevLEFT;
        RIGHT = prevFORWARD;
        LEFT = prevBACK;
        BACK = prevRIGHT;
    }

    else if ( where == BACK )
    {
        absoluteDirection += 2;

        FORWARD = prevBACK;
        RIGHT = prevLEFT;
        LEFT = prevRIGHT;
        BACK = prevFORWARD;
    }
    else
    {
        printf("\nIn function turn(int where) %d passed to function.  FATAL ERROR", where);
        exit(-1);
    }
}


void proceed ()
{
    switch ( absoluteDirection%4 )
    {
        case 0:
            pos.x++;
            break;


        case 1: case -3:
            pos.y--;
            break;


        case 2: case -2:
            pos.x--;
            break;


        case 3: case -1:
            pos.y++;
            break;
    }
    printMaze();

    if ( pos.x == FINISH_X && pos.y == FINISH_Y ) { done = true; }
}




bool readForward()
{
    switch ( absoluteDirection%4 )
    {
        case 0:
            return checkHere(EAST);
            break;

        case 1: case -3:
            return checkHere(NORTH);
            break;

        case 2: case -2:
            return checkHere(WEST);
            break;

        case 3: case -1:
            return checkHere(SOUTH);
            break;
    }
}

bool readRight()
{
    switch ( absoluteDirection%4 )
    {
        case 0:
            return checkHere(SOUTH);
            break;

        case 1: case -3:
            return checkHere(EAST);
            break;

        case 2: case -2:
            return checkHere(NORTH);
            break;

        case 3: case -1:
            return checkHere(WEST);
            break;
    }
}

bool readLeft()
{
    switch ( absoluteDirection%4 )
    {
        case 0:
            return checkHere(NORTH);
            break;

        case 1: case -3:
            return checkHere(WEST);
            break;

        case 2: case -2:
            return checkHere(SOUTH);
            break;

        case 3: case -1:
            return checkHere(EAST);
            break;
    }
}




int decode ( int inputDirection )
{
    switch ( inputDirection%4 )
    {
    case 0:
        return EAST;
        break;

    case 1: case -3:
        return NORTH;
        break;

    case 2: case -2:
        return WEST;
        break;

    case 3: case -1:
        return SOUTH;
        break;

    default:
        printf("\nIn function decode(input direction):int  FATAL ERROR!");
        exit(-1);
        break;
    }
}



void writeForbiddenPaths()
{
    for ( int x=0; x<=decision; x++ )
    {
        forbiddenPaths[y][x] = decisions[x];
    }
    y++;
}



bool readForbiddenPaths()  //If any matches found function will return true.
{
    bool match = false;

    for ( int y1=0; y1<y; y1++ )
    {
        for ( int x=0; x<=decision; x++ )
        {
            if ( decisions[x] != forbiddenPaths[y1][x] ) { match = false; break; }
            match = true;
        }
        if ( match ) { return true; }
    }
    return match;
}



void printForbiddenPaths()
{
    printf("\n\n");
    for ( int y1=0; y1<y; y1++ )
    {
        for ( int x=0; x<=decision; x++ )
        {
            printf(" %d", forbiddenPaths[y1][x] );
        }
        printf("\n");
    }
    system("pause");
}



void regularTurn()
{
    bool found = false;
    while ( !found )
    {
        switch ( rand()%2 )
        {
            case 0:

                if ( readLeft() )
                {
                    turn(LEFT);
                    printMaze();
                    if ( isloop() )
                    {
                        writeForbiddenPaths();
                        loop = true;

                        printf("\nLoop? #1");
                        system("pause");

                        break;
                    }
                    found = true;
                }
                break;

            case 1:

                if ( readRight() )
                {
                    turn(RIGHT);
                    printMaze();

                    if ( isloop() )
                    {
                        writeForbiddenPaths();
                        loop = true;

                        printf("\nLoop? #1");
                        system("pause");

                        break;
                    }

                    found = true;
                }
                break;
        }
    }
}



bool isloop()
{

    int prevd;
    bool control = false;
    loopDetector = 0;

    for ( int i=1; i<=decision; i++ )
    {
        prevd = decisions[i-1];

        switch ( prevd )
        {
        case NORTH:
            if ( decisions[i] == WEST ) { loopDetector++; control = true; }
            else if ( decisions[i] == EAST ) { loopDetector--; control = true; }
            break;

        case SOUTH:
            if ( decisions[i] == WEST ) { loopDetector--; control = true; }
            else if ( decisions[i] == EAST ) { loopDetector++; control = true; }
            break;

        case EAST:
            if ( decisions[i] == NORTH ) { loopDetector++; control = true; }
            else if ( decisions[i] == SOUTH ) { loopDetector--; control = true; }
            break;

        case WEST:
            if ( decisions[i] == NORTH ) { loopDetector--; control = true; }
            else if ( decisions[i] == SOUTH ) { loopDetector++; control = true; }
            break;
        }

    }

    if ( abs(loopDetector)%4 == 0 && control ) { return true; }
    return false;

}






int main()
{
    decisions[0] = 0;
    decisions[1] = 0;
    decisions[2] = -1;
    decision = 2;

    printf("%d", isloop() );


    return 0;
}























