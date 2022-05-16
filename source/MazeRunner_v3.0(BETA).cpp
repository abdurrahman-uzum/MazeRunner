#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//Maze settings:
#define SIZE 20
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 18
#define FINISH_Y 18

#define BLOCK 'X'  //For marking dead-ends and loops.

#define FRAME_DELAY 10  //Decrement the value for less delay per step.




int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254,254,254,254, 0 ,254,254,254,254},
    {254,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254,254,254,254, 0 ,254,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254, 0 ,254,254,254,254,254, 0 ,254},
    {254,254,254, 0 , 0 ,254,254,254,254,254,254,254, 0 ,254,254,254,254,254, 0 ,254},
    {254,254,254, 0 ,254,254,254,254,254,254,254,254, 0 ,254,254,254,254,254, 0 ,254},
    {254,254,254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254,254,254,254, 0 ,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254,254,254,254,254,254, 0 ,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254,254,254,254,254,254, 0 ,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254,254,254,254,254,254, 0 ,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254,254},
    {254,254,254,254,254,254,254,254,254,254, 0 ,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254}
};





enum directions0
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



bool done = false;

int numberOfLoops = 0;


int breakPoints[50][2];

int decisions[50];
int directionBeforeDecision[50];
int forbiddenPaths[100][100];
int numberOfDecisions;

int y = 0;

int absoluteDirection;

int decision = 0;
int direction;





void printMaze();
int numberOfChoices();
bool checkHere( int );




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
    /*
    printf("\nglobal direction:");
    switch(absoluteDirection%4)
    {
    case 1: case -3:
        printf("N %d   ", absoluteDirection);
        break;
    case 0:
        printf("E %d   ", absoluteDirection);
        break;
    case 2: case -2:
        printf("W %d   ", absoluteDirection);
        break;
    case -1: case 3:
        printf("S %d   ", absoluteDirection);
        break;
    default:
        printf("? %d   ", absoluteDirection);
        break;
    }*/
    printf("decision:%d   pos:(%d,%d)\n" , decision, pos.x, pos.y );

    printf("decisions:");
    for ( i=0; i<decision+1; i++ )
    {
        printf(" %d", decisions[i]);
    }
    printf("\n");

    printf("before:");
    for ( i=0; i<decision+1; i++ )
    {
        printf(" %d", directionBeforeDecision[i]);
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

    if ( maze[y-1][x] != 254 && maze[y-1][x] != BLOCK )  //UP
    {
        choices++;
    }
    if ( maze[y+1][x] != 254 && maze[y+1][x] != BLOCK )  //DOWN
    {
        choices++;
    }
    if ( maze[y][x+1] != 254 && maze[y][x+1] != BLOCK )  //RIGHT
    {
        choices++;
    }
    if ( maze[y][x-1] != 254 && maze[y][x-1] != BLOCK )  //LEFT
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
            if ( maze[y-1][x] != 254 && maze[y-1][x] != BLOCK ) { return true; }
            else { return false; }
            break;

        case SOUTH:
            if ( maze[y+1][x] != 254 && maze[y+1][x] != BLOCK ) { return true; }
            else { return false; }
            break;

        case EAST:
            if ( maze[y][x+1] != 254 && maze[y][x+1] != BLOCK ) { return true; }
            else { return false; }
            break;
        case WEST:
            if ( maze[y][x-1] != 254 && maze[y][x-1] != BLOCK ) { return true; }
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
    numberOfDecisions++;

    int prevFORWARD = FORWARD;
    int prevRIGHT = RIGHT;
    int prevLEFT = LEFT;
    int prevBACK = BACK;


    if ( where == FORWARD )
    {
        ;
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


/// NEEDS RE-CHECK FOR DIRECTIONS !!!
int convert ( int inputDirection )
{
    if ( inputDirection == FORWARD )
    {
        switch ( absoluteDirection%4 )
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
                printf("\nIn function convert(int inputDirection):int #1  FATAL ERROR!");
                exit(-1);
        }
    }
    else if ( inputDirection == RIGHT )
    {
        switch ( absoluteDirection%4 )
        {
            case 0:
                return SOUTH;
                break;
            case 1: case -3:
                return EAST;
                break;
            case 2: case -2:
                return NORTH;
                break;
            case 3: case -1:
                return WEST;
                break;
            default:
                printf("\nIn function convert(int inputDirection):int #2  FATAL ERROR!");
                exit(-1);
        }
    }
    else if ( inputDirection == LEFT )
    {
        switch ( absoluteDirection%4 )
        {
            case 0:
                return NORTH;
                break;
            case 1: case -3:
                return WEST;
                break;
            case 2: case -2:
                return SOUTH;
                break;
            case 3: case -1:
                return EAST;
                break;
            default:
                printf("\nIn function convert(int inputDirection):int #3  FATAL ERROR!");
                exit(-1);
        }
    }
    else
    {
        printf("\nIn function convert(int inputDirection):int #4  FATAL ERROR!");
        exit(-1);
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
    for ( int i=0; i<100; i++ )
    {
        for ( int j=0; j<100; j++ )
        {
            forbiddenPaths[i][j] = -99;
        }
    }

    srand ( time(NULL) );

    pos.x = INIT_X;
    pos.y = INIT_Y;

    bool decided = false;
    bool deadEnd = false;
    bool checkedOther = false;
    bool stillDeadEnd = false;
    int lastDirection;



    decision = -1;

    printMaze();
    system("pause");

    ///Problem in writing to or reading from forbiddenPaths.


    while ( !done )
    {
        /// Regular
        while ( readForward() && !done)
        {


            proceed();

            if ( numberOfChoices() > 2 && readForward() )
            {
                printf("\nGoing forward ");
                system("pause");
                directionBeforeDecision[++decision] = decode(absoluteDirection);
                decisions[decision] = decode(absoluteDirection);
            }



            printMaze();
        }

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

        /// Dead-end
        if ( !readForward() && !readRight() && !readLeft() && !done )
        {
            stillDeadEnd = true;

            while ( stillDeadEnd && !done)
            {

                writeForbiddenPaths();
                printForbiddenPaths();


                turn(BACK);
                printMaze();
                printf("\nTurned back #1.");
                system("pause");


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

                directionBeforeDecision[decision] = decode(absoluteDirection); ///

                if ( readRight() )  //Check right if path exist.
                {
                    decisions[decision] = RIGHT;
                    printMaze();

                    printf("\nChecking right...");
                    printForbiddenPaths();
                    if ( !readForbiddenPaths() )
                    {
                        turn(RIGHT);
                    }
                    else
                    {
                        printf("\nRight unavailable.");
                        system("pause");
                        decisions[decision] = -99;
                        right = false;
                    }
                }
                if ( readLeft() && (!readRight() || !right) )  //Check left if path exist, where right path does not exist or unavailable
                {
                    decisions[decision] = LEFT;
                    printMaze();
                    printf("\nChecking left...");
                    printForbiddenPaths();
                    if ( !readForbiddenPaths() )
                    {
                        turn(LEFT);
                    }
                    else
                    {
                        printf("\nLeft unavailable.");
                        system("pause");
                        decisions[decision] = -99;
                        left = false;
                    }
                }


                if ( (!readRight() || !right) && (!readLeft() || !left) )
                {
                    printf("\nHOLD ON! ");
                    system("pause");

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

        /// Decision

        if ( !readForward() && numberOfChoices() > 2 )
        {
            if ( readRight() )
            {
                printf("\nTurning right and printing into decisions array.");
                system("pause");

                directionBeforeDecision[++decision] = decode(absoluteDirection);

                turn(RIGHT);
                decisions[decision] = decode(absoluteDirection);
                printMaze();

                system("pause");
            }
            else if ( readLeft() )
            {
                printf("\nTurning left and printing into decisions array.");
                system("pause");

                directionBeforeDecision[++decision] = decode(absoluteDirection);

                turn(LEFT);
                decisions[decision] = decode(absoluteDirection);
                printMaze();

                system("pause");
            }
        }
        ///


    }

    printf("\nReached end of the maze. Correct path is:");
    for ( int i = 0; i<decision; i++ )
    {
        printf(" %d", decisions[i]);
    }
    printf(" | 1:NORTH  -1:SOUTH  0:EAST  2:WEST\n");

    system("pause");





    return 0;
}



/*
    forbidden paths array

    */





















