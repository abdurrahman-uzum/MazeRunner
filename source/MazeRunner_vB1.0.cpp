#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//Maze settings:
#define SIZE 40
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 38
#define FINISH_Y 38

#define FRAME_DELAY 50  //Decrement the value for less delay per step.



int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 , 0 ,254, 0 ,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254,254,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254, 0 ,254, 0 ,254,254,254,254,254,254,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254,254,254,254,254,254, 0 ,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254,254,254,254,254,254,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 , 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254, 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254,254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254,254,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254, 0 ,254,254,254, 0 ,254,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 ,254},
    {254, 0 ,254,254,254,254,254,254,254, 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254, 0 ,254,254,254, 0 ,254, 0 ,254,254, 0 ,254},
    {254, 0 ,254,254,254,254,254,254,254, 0 ,254,254,254,254,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 ,254, 0 ,254,254,254, 0 ,254, 0 , 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 ,254,254,254,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254,254,254,254,254, 0 ,254, 0 ,254,254,254, 0 ,254,254,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254,254,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 , 0 ,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254,254,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254,254, 0 ,254, 0 ,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254, 0 ,254, 0 ,254,254, 0 ,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254,254,254,254,254,254, 0 ,254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254,254, 0 , 0 ,254},
    {254, 0 ,254,254,254,254,254,254,254,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 ,254,254,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254, 0 ,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254, 0 ,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 , 0 , 0 ,254, 0 ,254,254,254,254,254,254,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 , 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254,254,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254,254, 0 ,254,254,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254,254,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254,254, 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254,254,254, 0 ,254,254,254, 0 , 0 , 0 ,254, 0 ,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
};



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
            printf(" %c", maze[i][j]);
        }
        printf("\n");
    }

    //For debugging:

    printf("decision:%d   pos:(%d,%d)\n" , decision, pos.x, pos.y );

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

    if ( maze[y-1][x] != 254 )  //UP
    {
        choices++;
    }
    if ( maze[y+1][x] != 254 )  //DOWN
    {
        choices++;
    }
    if ( maze[y][x+1] != 254 )  //RIGHT
    {
        choices++;
    }
    if ( maze[y][x-1] != 254 )  //LEFT
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
            if ( maze[y-1][x] != 254 ) { return true; }
            else { return false; }
            break;

        case SOUTH:
            if ( maze[y+1][x] != 254 ) { return true; }
            else { return false; }
            break;

        case EAST:
            if ( maze[y][x+1] != 254 ) { return true; }
            else { return false; }
            break;
        case WEST:
            if ( maze[y][x-1] != 254 ) { return true; }
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

        FORWARD = prevRIGHT;
        RIGHT = prevBACK;
        LEFT = prevFORWARD;
        BACK = prevLEFT;
    }

    else if ( where == LEFT )
    {
        absoluteDirection++;

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





int main()
{
    //Filling forbiddenPaths array with non-conflicting default value.
    for ( int i=0; i<100; i++ )
    {
        for ( int j=0; j<100; j++ )
        {
            forbiddenPaths[i][j] = -99;
        }
    }

    bool stillDeadEnd = false;
    decision = -1;

    srand ( time(NULL) );

    //Setting starting position
    pos.x = INIT_X;
    pos.y = INIT_Y;

    printMaze();
    system("pause");

    while ( !done )
    {
        /// Regular moving:

        while ( readForward() && !done )
        {
            proceed();

            if ( numberOfChoices() > 2 && readForward() )
            {
                directionBeforeDecision[++decision] = decode(absoluteDirection);
                decisions[decision] = decode(absoluteDirection);
            }

            printMaze();
        }
        ///


        /// Regular turning ( no decision ):

        if ( !readForward() && numberOfChoices() == 2 )
        {
            if ( readLeft() )
            {
                turn(LEFT);
                printMaze();
            }
            else if ( readRight() )
            {
                turn(RIGHT);
                printMaze();
            }
            else { printf("\nWTF"); }
        }
        ///


        /// Dead-end handling:

        if ( !readForward() && !readRight() && !readLeft() && !done )
        {
            stillDeadEnd = true;

            while ( stillDeadEnd && !done)
            {
                writeForbiddenPaths();  //Saving encountered dead-end to memory.

                turn(BACK);
                printMaze();

                while ( numberOfChoices()<=2 && !done)
                {
                    proceed();
                    printMaze();

                    if ( !readForward() && numberOfChoices() == 2 )
                    {
                        if ( readLeft() )
                        {
                            turn(LEFT);
                            printMaze();
                        }
                        else if ( readRight() )
                        {
                            turn(RIGHT);
                            printMaze();
                        }
                        else { printf("\nWTF"); }
                    }
                }

                turn(  decode( directionBeforeDecision[decision] ) );

                bool left = true;
                bool right = true;

                directionBeforeDecision[decision] = decode(absoluteDirection);

                if ( readRight() )  //Check right if path exist.
                {
                    decisions[decision] = RIGHT;
                    printMaze();

                    if ( !readForbiddenPaths() )
                    {
                        turn(RIGHT);
                    }
                    else
                    {
                        decisions[decision] = -99;
                        right = false;
                    }
                }
                if ( readLeft() && (!readRight() || !right) )  //Check left if path exist, where right path does not exist or unavailable
                {
                    decisions[decision] = LEFT;
                    printMaze();

                    if ( !readForbiddenPaths() )
                    {
                        turn(LEFT);
                    }
                    else
                    {
                        decisions[decision] = -99;
                        left = false;
                    }
                }


                if ( (!readRight() || !right) && (!readLeft() || !left) )
                {
                    turn(BACK);
                    proceed();

                    while ( numberOfChoices()<=2 && !done )
                    {
                        proceed();

                        if ( !readForward() && numberOfChoices() == 2 )
                        {
                            if ( readLeft() )
                            {
                                turn(LEFT);
                                printMaze();
                            }
                            else if ( readRight() )
                            {
                                turn(RIGHT);
                                printMaze();
                            }
                            else { printf("\nWTF"); }
                        }
                    }

                    decision--;
                }
                else
                {
                    stillDeadEnd = false;
                }
            }
        }
        ///

        /// Regular decisions

        if ( !readForward() && numberOfChoices() > 2 )
        {
            if ( readRight() )
            {
                directionBeforeDecision[++decision] = decode(absoluteDirection);

                turn(RIGHT);
                decisions[decision] = decode(absoluteDirection);
                printMaze();
            }
            else if ( readLeft() )
            {
                directionBeforeDecision[++decision] = decode(absoluteDirection);

                turn(LEFT);
                decisions[decision] = decode(absoluteDirection);
                printMaze();
            }
        }
        ///


    }

    printf("\nReached end of the maze. Correct path is:");
    for ( int i = 0; i<=decision; i++ )
    {
        printf(" %d", decisions[i]);
    }
    printf(" | 1:NORTH  -1:SOUTH  0:EAST  2:WEST\n");

    printf("\nForbidden paths are:\n");
    printForbiddenPaths();

    system("pause");

    pos.x = INIT_X;
    pos.y = INIT_Y;

    turn(EAST);
    done = false;
    decision = -1;

    printMaze();

    while ( !done )
    {
        while ( readForward() && !done )
        {
           if ( numberOfChoices() > 2 )
           {
               turn ( decode( decisions[++decision] ) );
           }
           proceed();
        }

        if ( readLeft() )
        {
           turn(LEFT);
           printMaze();
        }
        else if ( readRight() && numberOfChoices() == 2 && !done )
        {
           turn(RIGHT);
           printMaze();
        }



    }


    printMaze();
    system("pause");





    return 0;
}























