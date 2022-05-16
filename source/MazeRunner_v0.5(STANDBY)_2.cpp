#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define FRAME_DELAY 200
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 18
#define FINISH_Y 18


enum directions
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};


/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48,254},
    {254,254,254, 48,254,254, 48,254, 48,254},
    {254, 48,254, 48,254,254, 48, 48, 48,254},
    {254, 48,254, 48, 48, 48,254,254, 48,254},
    {254, 48,254, 48,254, 48,254,254,254,254},
    {254, 48,254 ,0 ,254, 48, 48, 48, 48,254},
    {254, 48,254,254,254, 48,254,254, 48,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48,254},
    {254,254,254,254,254,254,254,254,254,254}
};*/

/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    { 48, 48, 48, 48, 48, 48, 48,254,254,254},
    {254,254,254,254,254,254, 48,254,254,254},
    {254,254,254,254,254,254, 48, 48, 48,254},
    {254,254,254,254,254,254,254,254, 48,254},
    {254,254,254,254,254,254,254,254, 48,254},
    {254,254,254,254,254,254,254,254, 48,254},
    {254,254,254,254,254,254,254,254, 48,254},
    {254,254,254,254,254,254,254,254, 48, 48},
    {254,254,254,254,254,254,254,254,254,254}
};*/
/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254,254,254},
    {254,254, 48,254,254,254, 48,254,254,254},
    {254,254, 48,254,254,254, 48, 48, 48,254},
    {254,254, 48,254, 48,254, 48,254, 48,254},
    {254, 48, 48,254, 48,254, 48,254, 48,254},
    {254, 48,254,254, 48,254, 48,254, 48,254},
    {254, 48,254,254, 48,254, 48,254, 48,254},
    {254, 48, 48, 48, 48,254,254, 48, 48,254},
    {254,254,254,254,254,254,254,254,254,254}

};*/
/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254,254,254},
    {254,254,254,254, 48,254, 48,254,254,254},
    {254,254, 48,254, 48,254, 48, 48, 48,254},
    {254,254, 48,254, 48,254, 48,254, 48,254},
    {254, 48, 48,254, 48,254, 48,254, 48,254},
    {254, 48,254,254, 48,254, 48,254, 48,254},
    {254, 48,254,254, 48,254, 48,254, 48,254},
    {254, 48, 48, 48, 48,254,254,254,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};
*/



int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48,254, 48, 48, 48, 48, 48,254,254,254,254,254},
    {254,254,254, 48,254,254, 48,254, 48,254,254,254,254, 48,254,254,254,254,254,254},
    {254, 48,254, 48,254,254, 48, 48, 48, 48, 48,254,254, 48, 48, 48, 48, 48, 48,254},
    {254, 48,254, 48, 48, 48,254,254, 48,254, 48, 48,254, 48,254,254,254,254, 48,254},
    {254, 48,254, 48,254, 48,254,254,254,254,254, 48, 48, 48, 48, 48,254,254, 48,254},
    {254, 48,254, 48,254, 48, 48, 48, 48,254,254, 48,254,254,254, 48,254,254, 48,254},
    {254, 48,254,254,254, 48,254,254, 48,254,254, 48, 48, 48,254, 48,254, 48, 48,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48,254,254,254,254,254,254, 48,254, 48,254,254},
    {254, 48,254,254,254,254,254,254,254,254, 48, 48, 48, 48,254, 48,254, 48,254,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254, 48,254, 48,254, 48,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48,254, 48, 48,254, 48, 48, 48,254, 48,254,254},
    {254,254,254, 48,254,254, 48,254, 48,254,254, 48,254,254,254,254, 48, 48, 48,254},
    {254, 48,254, 48,254,254, 48, 48, 48,254, 48, 48,254, 48, 48, 48, 48,254, 48,254},
    {254, 48,254, 48, 48, 48,254,254, 48,254, 48,254,254, 48,254,254,254,254, 48,254},
    {254, 48,254, 48,254, 48,254,254,254,254, 48,254,254, 48,254, 48, 48, 48, 48,254},
    {254, 48,254, 48,254, 48, 48, 48, 48,254, 48,254,254, 48,254,254,254,254, 48,254},
    {254, 48,254,254,254, 48,254,254, 48,254, 48,254, 48, 48, 48, 48, 48, 48,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48, 48, 48,254,254,254,254,254,254, 48, 48,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254}
};
/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254,254,254},
    {254,254,254,254, 48,254, 48,254,254,254},
    {254,254,254,254, 48,254, 48, 48, 48,254},
    {254,254,254,254, 48,254, 48,254, 48,254},
    {254, 48, 48,254, 48,254, 48,254, 48,254},
    {254, 48,254,254, 48,254, 48,254, 48,254},
    {254, 48,254,254, 48,254, 48,254, 48,254},
    {254, 48, 48,254, 48,254,254,254, 48,254},
    {254,254,254,254,254,254,254,254,254,254}

};*/


void printMaze();
int inverse( int inputDirection );

struct Position
{
    int x = 1;
    int y = 1;

} pos, breakPoint;

bool done = false;



//Checks every direction and randomly returns one possible way.
int check( int currentDirection )
{
    int x = pos.x;
    int y = pos.y;

    int up = (int)maze[y-1][x];
    int down = (int)maze[y+1][x];
    int right = (int)maze[y][x+1];
    int left = (int)maze[y][x-1];

    //bool allChecked = false;
    //(currentDirection != DOWN || allChecked)

    while ( 1 )
    {
        if ( up<=down && up<=right && up<=left )
        {
            return UP;
        }
        if ( down<=up && down<=right && down<=left )
        {
            return DOWN;
        }
        if ( right<=up && right<=down && right<=left )
        {
            return RIGHT;
        }
        if ( left<=up && left<=down && left<=right )
        {
            return LEFT;
        }
    }
}


//Returns how many possible paths there are.
int numberOfChoices()
{
    int x = pos.x;
    int y = pos.y;

    int choices = 0;

    if ( maze[y-1][x] != 254 )       //UP
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



//Checks whether a specific path is available.
bool checkHere ( int where )
{
    int x = pos.x;
    int y = pos.y;

    switch ( where )
    {
        case UP:
            if ( maze[y-1][x] != 254 ) { return true; }
            else { return false; }
            break;

        case DOWN:
            if ( maze[y+1][x] != 254 ) { return true; }
            else { return false; }
            break;

        case RIGHT:
            if ( maze[y][x+1] != 254 ) { return true; }
            else { return false; }
            break;
        case LEFT:
            if ( maze[y][x-1] != 254 ) { return true; }
            else { return false; }
            break;

        default:
            printf("\nIn function: checkHere(int where) FATAL ERROR!");
            exit(-1);
            break;
    }
}






//Moves the entity to a direction (not position).
void moveto( int where )
{
    if ( maze[pos.y][pos.x] != 254 && !(pos.x == INIT_X && pos.y == INIT_Y)  )
    {
        (int)maze[pos.y][pos.x]++;
    }
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
    if ( pos.x == FINISH_X && pos.y == FINISH_Y )
    {
        maze[pos.y][pos.x] = '1';
        done = true;
    }
}


//Inverses the direction.
int inverse( int inputDirection )
{
    int returnDirection;
    switch ( inputDirection )
    {
        case UP:
            returnDirection = DOWN;
            break;
        case DOWN:
            returnDirection = UP;
            break;
        case RIGHT:
            returnDirection = LEFT;
            break;
        case LEFT:
            returnDirection = RIGHT;
            break;
    }
    return returnDirection;
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
    //Setting a starting point.
    pos.x = INIT_X;
    pos.y = INIT_Y;

    int direction, prevDirection;

    printMaze();
    system("pause");

    int breakPoints[15][2];
    breakPoints[0][0] = pos.x;
    breakPoints[0][1] = pos.y;

    direction = 2;//check();

    int decision = 0;

    while ( !done )
    {
        while (  numberOfChoices() <= 2 && checkHere(direction) && !done )
        {
            if ( checkHere(inverse(direction)) )
            {
                moveto ( direction );
                printMaze();
            }
            else
            {
                direction = check(direction);
                moveto ( direction );
                printMaze();
            }
        }

        if ( !checkHere(direction) && !done )
        {
            direction = check(direction);
        }

        if ( numberOfChoices() > 2 ) /// !
        {
            breakPoints[decision][0] = pos.x;
            breakPoints[decision][1] = pos.y;

            decision++;
            direction = check(direction);

            //printf("\n#1 Decision checkpoint. Decision = %d", decision);
            //system("pause");
        }
        while ( decision > 0 && !done )
        {
            if ( !checkHere(direction) )
            {
                if ( numberOfChoices() == 1 )
                {
                    direction = inverse(direction);
                    while ( !(pos.x == breakPoints[decision][0] && pos.y == breakPoints[decision][1]) && numberOfChoices() <= 1 )
                    {
                        if ( maze[pos.y][pos.x] < 52 )
                        {
                            maze[pos.y][pos.x] = 254;
                        }

                        direction = check(direction);
                        moveto ( direction );
                        printMaze();

                    }
                    decision--;
                    direction = check(direction); /// !!! ///
                    //printf("\nReturned last breakpoint. Decision = %d", decision);
                    //system("pause");

                }
                else
                {
                    direction = check(direction);
                }
            }
            else
            {
                //direction=check(direction); MAY BE IMPORTANT LATER!
                moveto(direction);
                printMaze();

                if ( numberOfChoices() > 2 )
                {
                    decision++;
                    breakPoints[decision][0] = pos.x;
                    breakPoints[decision][1] = pos.y;

                    direction = check(direction);

                    //printf("\n#2 Decision checkpoint. Decision = %d", decision);
                    //system("pause");
                }
            }
        }
    }

    printf("\nDONE!");


    return 0;
}


/*
Note to self:
At last, i implemented the ability to hold more than one breakpoint.
Holding part works, yet the algorithm which was written for only one  breakpoint doesn't.
Might need to rewrite the entire algorithm.
*/



/*
    SOLVED
    It does not follow the smallest number path on checkpoint #2
    okay, not necessarily due to #2 checkpoint...
    problem occurs after blocking the path behind.
*/

/*
    Looks like the final problem (:
    Problem after filling the path behind after second breakpoint.

*/



















