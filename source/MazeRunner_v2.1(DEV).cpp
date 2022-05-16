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

#define FRAME_DELAY 200  //Decrement the value for less delay per step.








int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 48, 48, 48, 48, 48,254,254, 48,254, 48, 48, 48, 48, 48, 48,254,254,254,254},
    {254,254,254,254,254, 48,254,254, 48,254,254,254,254, 48,254,254,254,254,254,254},
    {254, 48,254, 48,254, 48, 48, 48, 48, 48, 48,254,254, 48, 48, 48,254,254,254,254},
    {254, 48,254, 48, 48, 48,254,254, 48,254, 48, 48,254, 48,254,254,254,254,254,254},
    {254, 48,254, 48,254, 48,254,254,254,254,254, 48, 48, 48, 48, 48,254,254,254,254},
    {254, 48,254, 48,254, 48, 48, 48, 48,254,254, 48,254,254,254, 48,254,254,254,254},
    {254, 48,254,254,254, 48,254,254, 48,254,254, 48, 48, 48,254, 48,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48,254,254, 48,254,254,254, 48,254,254,254,254},
    {254, 48,254,254,254,254,254,254,254,254, 48, 48, 48, 48,254, 48,254,254,254,254},
    {254, 48,254,254,254,254,254,254,254,254,254, 48,254, 48,254, 48,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48, 48, 48, 48,254, 48, 48, 48,254,254,254,254},
    {254,254,254, 48,254,254, 48,254, 48,254,254, 48,254,254,254, 48,254,254,254,254},
    {254, 48,254, 48,254,254, 48, 48, 48,254, 48, 48,254, 48, 48, 48,254,254,254,254},
    {254, 48,254, 48, 48, 48,254,254, 48,254, 48,254,254, 48,254,254,254,254,254,254},
    {254, 48,254, 48,254, 48,254,254,254,254, 48,254,254, 48,254, 48,254,254,254,254},
    {254, 48,254, 48,254, 48, 48, 48, 48,254, 48,254,254, 48,254,254,254,254,254,254},
    {254, 48,254,254,254, 48,254,254, 48,254, 48,254, 48, 48, 48, 48,254,254,254,254},
    {254, 48, 48, 48, 48, 48, 48,254, 48, 48, 48,254,254,254,254, 48, 48, 48, 48,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254}

};


int blankMaze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254,254},
    {254,254,254,254,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254,254,254,254,254,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 ,254,254,254,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 , 0 ,254, 0 ,254,254,254,254,254,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 ,254,254,254,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254,254, 0 ,254,254,254,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 ,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254,254,254, 0 ,254,254,254,254},
    {254, 0 ,254,254,254,254,254,254,254,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254,254,254},
    {254, 0 ,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254, 0 ,254,254,254,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254,254,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254,254,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254,254,254,254,254,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254, 0 , 0 , 0 , 0 ,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254}

};





enum directions
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};



struct Position
{
    int x = 1;
    int y = 1;

} pos, prevPos;



bool done = false;

int numberOfLoops = 0;


int breakPoints[50][2];

int decision = 0;
int direction;

void printMaze( void );
void printBlankMaze( void );
int check( void );
int numberOfChoices();
bool checkHere( int );
void moveto( int );
int whatsThere( int );
int findReverseDirection ( struct Position, struct Position );
void follow( int );
int followTrace( int );




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
    printf("\ndirection:%d   number of choices:%d   pos:(%d,%d)   prevPos:(%d,%d)   last breakpoint:(%d,%d)   Loops:%d\n", direction, numberOfChoices(), pos.x, pos.y, prevPos.x, prevPos.y, breakPoints[decision][0], breakPoints[decision][1], numberOfLoops );

    Sleep(FRAME_DELAY);
    maze[pos.y][pos.x] = holder;
}


void printBlankMaze()
{
    int holder = blankMaze[pos.y][pos.x];
    blankMaze[pos.y][pos.x] = 'o';

    system("cls");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            printf(" %c", blankMaze[i][j]);
        }
        printf("\n");
    }

    Sleep(FRAME_DELAY);
    blankMaze[pos.y][pos.x] = holder;
}



int check()
{
    int x = pos.x;
    int y = pos.y;

    int up = (int)maze[y-1][x];
    int down = (int)maze[y+1][x];
    int right = (int)maze[y][x+1];
    int left = (int)maze[y][x-1];

    srand ( time(NULL) );

    while ( 1 )
    {
        switch ( rand()%4 )
        {
            case UP:
                if ( up<=down && up<=right && up<=left )
                {
                    return UP;
                }
            break;

            case DOWN:
                if ( left<=up && left<=down && left<=right )
                {
                    return LEFT;
                }
            break;

            case RIGHT:
                if ( right<=up && right<=down && right<=left )
                {
                    return RIGHT;
                }
            break;

            case LEFT:
                if ( down<=up && down<=right && down<=left )
                {
                    return DOWN;
                }
            break;
        }
    }
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
        case UP:
            if ( maze[y-1][x] != 254 && maze[y-1][x] != BLOCK ) { return true; }
            else { return false; }
            break;

        case DOWN:
            if ( maze[y+1][x] != 254 && maze[y+1][x] != BLOCK ) { return true; }
            else { return false; }
            break;

        case RIGHT:
            if ( maze[y][x+1] != 254 && maze[y][x+1] != BLOCK ) { return true; }
            else { return false; }
            break;
        case LEFT:
            if ( maze[y][x-1] != 254 && maze[y][x-1] != BLOCK ) { return true; }
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
    prevPos = pos;

    (int)maze[pos.y][pos.x]++;

    bool weirdSituation = false;

    if ( whatsThere(where) == 254 || whatsThere(where) == 'X' )
    {
        printf("\nA problem occurred.");
        system("pause");

        switch ( where )
        {
            case UP:
                maze[pos.y-1][pos.x] = 0;
                break;

            case DOWN:
                maze[pos.y+1][pos.x] = 0;
                break;

            case RIGHT:
                maze[pos.y][pos.x+1] = 0;
                break;

            case LEFT:
                maze[pos.y][pos.x-1] = 0;
                break;

            default:
                printf("\nIn function: moveto(int where)  FATAL ERROR!");
                exit(-1);
        }

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




int whatsThere( int where )
{
    struct Position temp;
    temp = pos;

    switch ( where )
    {
        case UP:
            temp.y--;
            break;

        case DOWN:
            temp.y++;
            break;

        case RIGHT:
            temp.x++;
            break;

        case LEFT:
            temp.x--;
            break;

        default:
            printf("\nIn function: whatsThere(int where)  FATAL ERROR!");
            exit(-1);
    }

    return (int)maze[temp.y][temp.x];
}




void follow( int where )
{
    switch ( where )
    {
        case UP:
            blankMaze[pos.y][pos.x] = '|';
            pos.y--;
            break;

        case DOWN:
            blankMaze[pos.y][pos.x] = '|';
            pos.y++;
            break;

        case RIGHT:
            blankMaze[pos.y][pos.x] = 196;
            pos.x++;
            break;

        case LEFT:
            blankMaze[pos.y][pos.x] = 196;
            pos.x--;
            break;

        default:
            printf("\nIn function: follow(int where)  FATAL ERROR!");
            exit(-1);
    }
    if ( pos.x == FINISH_X && pos.y == FINISH_Y )
    {
        done = true;
    }
}



int followTrace( int currentDirection )
{
    int x = pos.x;
    int y = pos.y;


    int up = (int)maze[y-1][x] != 254 ? (int)maze[y-1][x] :48;

    int down = (int)maze[y+1][x] != 254 ? (int)maze[y+1][x] :48;

    int right = (int)maze[y][x+1] != 254 ? (int)maze[y][x+1] :48;

    int left = (int)maze[y][x-1] != 254 ? (int)maze[y][x-1] :48;

    bool allChecked = false;


    while ( 1 )
    {

        if ( ( up!=48 && up!=BLOCK ) && ( currentDirection!=DOWN || allChecked ) )
        {
            return UP;
        }
        if ( ( down!=48 && down!=BLOCK ) && ( currentDirection!=UP || allChecked ) )
        {
            return DOWN;
        }
        if ( ( right!=48 && right!=BLOCK ) && ( currentDirection!=LEFT || allChecked ) )
        {
            return RIGHT;
        }
        if ( ( left!=48 && left!=BLOCK ) && ( currentDirection!=RIGHT || allChecked ) )
        {
            return LEFT;
        }

        allChecked = true;

    }
}



int findReverseDirection ( struct Position firstPos, struct Position secPos )
{
    if ( secPos.y == firstPos.y - 1 )
    {
        return DOWN;
    }

    if ( secPos.y == firstPos.y + 1 )
    {
        return UP;
    }

    if ( secPos.x == firstPos.x + 1 )
    {
        return LEFT;
    }

    if ( secPos.x == firstPos.x - 1 )
    {
        return RIGHT;
    }

    printf("\nIn function: findReverseDirection  FATAL ERROR!\n");
    exit(-1);
}



int findDirection ( struct Position firstPos, struct Position secPos )
{
    if ( secPos.y == firstPos.y - 1 )
    {
        return UP;
    }

    if ( secPos.y == firstPos.y + 1 )
    {
        return DOWN;
    }

    if ( secPos.x == firstPos.x + 1 )
    {
        return RIGHT;
    }

    if ( secPos.x == firstPos.x - 1 )
    {
        return LEFT;
    }

    printf("\nIn function: findDirection  FATAL ERROR!\n");
    exit(-1);
}






int main()
{
    /// STEP #1 : Solving the maze. ///

    pos.x = INIT_X;
    pos.y = INIT_Y;

    breakPoints[0][0] = pos.x;
    breakPoints[0][1] = pos.y;

    direction = check();

    printBlankMaze();
    system("pause");


    while ( !done )
    {
        while (  numberOfChoices() <= 2  && !done )
        {
            direction = check();
            moveto ( direction );
            printMaze();
        }


        if ( numberOfChoices() > 2 )
        {
            decision++;

            breakPoints[decision][0] = pos.x;
            breakPoints[decision][1] = pos.y;

            direction = check();
        }


        while ( decision > 0 && !done )
        {

            /// Loop handling:

            if ( whatsThere( findDirection(prevPos,pos) ) > 48 && whatsThere( findDirection(prevPos,pos) ) != 254 && whatsThere( findDirection(prevPos,pos) )!= BLOCK )
            {
                ///
                if ( whatsThere(findReverseDirection(prevPos,pos)) == BLOCK )
                {
                    printf("\nHmmmm...");
                    system("pause");

                    maze[pos.y][pos.x] = BLOCK-1;
                    moveto(direction);
                    direction = check();
                    moveto(direction);
                    printMaze();
                }
                ///

                else
                {
                    numberOfLoops++;
                    printf("\nLoop detected.  ");
                    system("pause");

                    maze[pos.y][pos.x] = BLOCK-1;

                    direction = findReverseDirection(prevPos, pos);

                    moveto(direction);
                    printMaze();

                    direction = followTrace(direction);
                }

            }

            ///


            /// Dead-end handling:

            if ( numberOfChoices() == 1 )
            {

                while ( !(pos.x == breakPoints[decision][0] && pos.y == breakPoints[decision][1]) && numberOfChoices() <= 1 )
                {
                    maze[pos.y][pos.x] = BLOCK -1;

                    direction = check();
                    moveto ( direction );

                    printMaze();
                }


                if ( pos.x == breakPoints[decision][0] && pos.y == breakPoints[decision][1] )
                {
                    if ( numberOfChoices() == 1 ) { maze[pos.y][pos.x] = BLOCK -1; }

                    decision--;
                }
                direction = check();
            }
            else
            {
                direction = check();
            }

            ///


            /// Moving if there is nothing to worry:

            if ( numberOfChoices() <= 2 )
            {
                moveto(direction);
                printMaze();
            }
            if ( numberOfChoices() > 2 )
            {
                if ( whatsThere( findDirection(prevPos,pos) ) > 48 && whatsThere( findDirection(prevPos,pos) ) != 254 && whatsThere( findDirection(prevPos,pos) )!= BLOCK && whatsThere( findReverseDirection(prevPos,pos) ) == BLOCK )
                {
                }
                else
                {
                    decision++;

                    breakPoints[decision][0] = pos.x;
                    breakPoints[decision][1] = pos.y;

                    direction = check();
                    moveto(direction);
                    printMaze();
                }
            }

            ///
        }
    }



    printf("\nMapping is finished.");
    system("pause");



    /// STEP #2 : Starting at the beginning again and following the correct path. ///

    done = false;

    pos.x = INIT_X;
    pos.y = INIT_Y;

    printBlankMaze();
    system("pause");

    while ( !done )
    {
        direction = followTrace( direction );
        follow ( direction );
        printBlankMaze();

        if ( pos.x == FINISH_X && pos.y == FINISH_Y ) { done = true; }
    }

    printf("\nMAZE COMPLETED!");






    return 0;
}

/*
    Every now and then, usually recently after handling a loop, it does not fill the square behind of it where supposed to do so.
    That causes it to think it's in another loop, whereas it's in a dead-end.

    **When enters a loop, marks that position and returns back, if there is another way just a square away, other than where it came, problem occurs there.
      Traps itself in this situation.
*/

/*
    Try to:
    Save all the coordinates related to entrance of loops.
    After mapping, check for both sides of the loop, and mark shortest path with a big number, which will cause it to prefer that path afterwards.
*/

















