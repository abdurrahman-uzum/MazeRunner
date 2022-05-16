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
char turns[200];


//////


//Global variables:

int absoluteDirection;

int y = 0;

int decision = 0;

int direction;

int numberOfTurns = -1;

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

    printf("turns:");
    for ( i=0; i<=numberOfTurns; i++ )
    {
        printf(" %c", turns[i]);
    }
    printf("\n");

    //

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
        turns[++numberOfTurns] = 'R';

        FORWARD = prevRIGHT;
        RIGHT = prevBACK;
        LEFT = prevFORWARD;
        BACK = prevLEFT;
    }

    else if ( where == LEFT )
    {
        absoluteDirection++;
        turns[++numberOfTurns] = 'L';

        FORWARD = prevLEFT;
        RIGHT = prevFORWARD;
        LEFT = prevBACK;
        BACK = prevRIGHT;
    }

    else if ( where == BACK )
    {
        absoluteDirection += 2;

        //turns[numberOfTurns] = turns[numberOfTurns]== 'R' ? 'L' : 'R';

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


///Integrate with proceed()
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




void eraseTurns()
{
    for ( int i=0; i<=numberOfTurns; i++ )
    {
        turns[i] = NULL;
    }
    numberOfTurns = -1;

}




bool isloop()
{
    loopDetector = 0;
    for ( int i=0; i<=numberOfTurns; i++ )
    {
        if ( turns[i] == 'L' ) { loopDetector++; }
        else if ( turns[i] == 'R' ) { loopDetector--; }
    }

    if ( abs(loopDetector) == 4 )
    {
        //eraseTurns();
        return true;
    }
    return false;

}








int main()
{
    /// STEP #0: PREPARATION ///

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

    ///===///


    /// STEP #1: SOLVING ///

    while ( !done )
    {
        /// Regular moving:
        while ( readForward() && !done && !loop )
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
        if ( !readForward() && numberOfChoices() == 2 && !loop )
        {
            regularTurn();
        }
        ///






/*

        /// Loop handling:

        if ( loop )
        {
            decisions[decision--] = -99;
            writeForbiddenPaths();

            turn( turns[numberOfTurns]=='R'? LEFT : RIGHT );
            printMaze();
            system("pause");


        }*/

        /// Dead-end handling:

        if ( ( !readForward() && !readRight() && !readLeft() && !done ) || loop )
        {
            stillDeadEnd = true;

            while ( stillDeadEnd && !done)
            {
                writeForbiddenPaths();

                turn(BACK);

                //if ( loop ) { eraseTurns(); }

                printMaze();

                while ( ( numberOfChoices()<=2 /*|| loop*/ ) && !done)
                {
                    //loop = false;

                    proceed();
                    printMaze();

                    if ( !readForward() && numberOfChoices() == 2 )
                    {
                        regularTurn();
                    }
                }


                //turn(  decode( directionBeforeDecision[decision] ) );

                bool left = true;
                bool right = true;
                bool fward = true;

                //directionBeforeDecision[decision] = decode(absoluteDirection);

                if ( readForward() )
                {
                    decisions[decision] = FORWARD;
                    printMaze();

                    if ( !readForbiddenPaths() )
                    {
                        proceed();
                    }
                    else
                    {
                        decisions[decision] = -99;
                        fward = false;
                    }
                }

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

                if ( readLeft() &&  (!readRight() || !right) )  //Check left if path exist, where right path does not exist or unavailable
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
                            regularTurn();
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
            directionBeforeDecision[++decision] = decode(absoluteDirection);
            printMaze();

            if ( readRight() )
            {
                turn(RIGHT);

                decisions[decision] = decode(absoluteDirection);
                printMaze();

                if ( isloop() )
                {
                    printf("\nLoop? #2");
                    system("pause");
                    loop = true;
                }


            }
            else if ( readLeft() )
            {
                turn(LEFT);

                decisions[decision] = decode(absoluteDirection);
                printMaze();

                if ( isloop() )
                {
                    printf("\nLoop? #2");
                    system("pause");
                    loop = true;
                }


            }
        }
        ///


    }

    ///===///

    /// STEP #2: FOLLOWING ///

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























