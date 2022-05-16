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

#define FRAME_DELAY 1000  //Decrement the value for less delay per step.




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

char decisions[50];
int numberOfDecisions;

int globalDirection;

int decision = 0;
int direction;





void printMaze();
void printBlankMaze();
int check();
int numberOfChoices();
bool checkHere( int where );
void moveto( int where );
int whatsThere( int where );
int findReverseDirection ( struct Position firstPos, struct Position secPos );
void follow( int where );
int followTrace( int globalDirection );




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

    //For debugging:

    printf("\nglobal direction:");
    switch(globalDirection%4)
    {
    case NORTH: case -3:
        printf("N %d   ", globalDirection);
        break;
    case EAST:
        printf("E %d   ", globalDirection);
        break;
    case WEST: case -2:
        printf("W %d   ", globalDirection);
        break;
    case SOUTH: case 3:
        printf("S %d   ", globalDirection);
        break;
    default:
        printf("? %d   ", globalDirection);
        break;
    }
    printf("number of choices:%d   decisions:%d   pos:(%d,%d)\n" , numberOfChoices(), decision, pos.x, pos.y );

    printf("decisions:");
    for ( i=0; i<decision; i++ )
    {
        printf(" %c", decisions[i]);
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









/*
void transformDirections ( int MOVE )
{
    switch ( MOVE )
    {

    case FORWARD:
        decisions[numberOfDecisions] = FORWARD;
        break;

    case RIGHT:
        for ( int i=0; i<numberOfDecisions; i++ )
        {
            switch ( decisions[numberOfDecisions] )
            {
            case FORWARD:
                decisions[numberOfDecisions] = LEFT;
                break;

            case RIGHT:
                decisions[numberOfDecisions] = FORWARD;
                break;

            case LEFT:
                decisions[numberOfDecisions] = BACK;
                break;

            case BACK:
                decisions[numberOfDecisions] = RIGHT;
                break;
            }
        }
        break;

    case LEFT:
        for ( int i=0; i<numberOfDecisions; i++ )
        {
            switch ( decisions[numberOfDecisions] )
            {
            case FORWARD:
                decisions[numberOfDecisions] = LEFT;
                break;

            case RIGHT:
                decisions[numberOfDecisions] = FORWARD;
                break;

            case LEFT:
                decisions[numberOfDecisions] = BACK;
                break;

            case BACK:
                decisions[numberOfDecisions] = RIGHT;
                break;
            }
        }
        break;
    }
}*/


void turn ( int where )
{
    numberOfDecisions++;

    int prevFORWARD = FORWARD;
    int prevRIGHT = RIGHT;
    int prevLEFT = LEFT;
    int prevBACK = BACK;



    if ( where == RIGHT )
    {
        globalDirection--;

        FORWARD = prevRIGHT;
        RIGHT = prevBACK;
        LEFT = prevFORWARD;
        BACK = prevLEFT;
    }

    else if ( where == LEFT )
    {
        globalDirection++;

        FORWARD = prevLEFT;
        RIGHT = prevFORWARD;
        LEFT = prevBACK;
        BACK = prevRIGHT;
    }

    else if ( where == BACK )
    {
        globalDirection += 2;

        FORWARD = prevBACK;
        RIGHT = prevLEFT;
        LEFT = prevRIGHT;
        BACK = prevFORWARD;
    }
    else
    {
        printf("\nIn function turn(int where)  FATAL ERROR!");
        exit(-1);
    }
}











void proceed ()
{
    switch ( globalDirection%4 )
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
}














bool readForward()
{
    switch ( globalDirection%4 )
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
    switch ( globalDirection%4 )
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
    switch ( globalDirection%4 )
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











int main()
{
    srand ( time(NULL) );

    pos.x = INIT_X;
    pos.y = INIT_Y;

    bool decided = false;
    bool deadEnd = false;
    bool checkedOther = false;
    int lastDirection;

    printMaze();
    system("pause");


    while ( !done )
    {
        if ( deadEnd || ( !readForward() && !readRight() && !readLeft() ) )
        {
            printf("\nDead-end detected!");
            system("pause");

            turn(BACK);
            printMaze(); printf("\nTurned back#1."); system("pause");


            while ( numberOfChoices() <= 2 ) { proceed(); }

            if ( decisions[decision-1] == 'F' ) { turn(BACK); printMaze(); printf("\nTurned back#2."); system("pause"); }
            else if ( decisions[decision-1] == 'R' ) { turn(RIGHT); printMaze(); printf("\nTurned right."); system("pause"); }
            else if ( decisions[decision-1] == 'L' ) { turn(LEFT); printMaze(); printf("\nTurned left."); system("pause");}
            else { printf("\nSomething shitty happened."); }

            system("pause");

            decision--;

            decided = false;
            while ( !decided )
            {
                if ( readRight() &&  decisions[decision] != 'R' )
                {

                    decisions[decision++] = 'R';
                    turn(RIGHT);

                    printf("\nTurned right#2."); system("pause");

                    proceed();
                    decided = true;
                }



                else if ( readLeft() && decisions[decision] != 'L' )
                {

                    decisions[decision++] = 'L';
                    turn(LEFT);

                    printf("\nTurned left#2."); system("pause");

                    proceed();
                    decided = true;
                }

                else
                {
                    turn(BACK);
                    //decision--;
                    printf("\nTurned back#3."); system("pause");
                    proceed();
                    decided = true;
                }

            }


            deadEnd = false;
        }

        while ( readForward() && !deadEnd )
        {
            if ( numberOfChoices() > 2 )
            {
                decisions[decision++] = 'F';
            }

            proceed();

            if ( !readForward() && numberOfChoices() <= 2 )
            {
                if ( readRight() )
                {
                    turn(RIGHT);
                }
                else if ( readLeft() )
                {
                    turn(LEFT);
                }
                else
                {
                    deadEnd = true;
                }
            }

        }

        if ( !readForward() && ( readRight() || readLeft() )  )
        {
            switch ( rand()%2 )
                {
                case 0:
                    if ( readRight() &&  decisions[decision] != 'R' )
                    {
                        turn(RIGHT);
                        decisions[decision++] = 'R';
                        proceed();
                        decided = true;
                    }
                    break;

                case 1:
                    if ( readLeft() && decisions[decision] != 'L' )
                    {
                        turn(LEFT);
                        decisions[decision++] = 'L';
                        proceed();
                        decided = true;
                    }
                    break;
                }
        }










    }







    return 0;
}



/*
    forbidden paths array

    */

/*
    it doesn't know it's directions. After changing 'X' to XXXXXX after first right turn it thinks its right is its forward or whatever.
*/



















