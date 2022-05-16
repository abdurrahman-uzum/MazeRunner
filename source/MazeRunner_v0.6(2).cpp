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

int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 49, 48, 48, 48, 48, 48,254, 48,254, 48, 48, 48, 48, 48,254,254,254,254,254},
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

int blankMaze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254,254,254,254,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254,254,254,254,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 , 0 ,254, 0 ,254,254,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254,254, 0 ,254,254, 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254,254,254,254,254,254, 0 ,254, 0 ,254,254},
    {254, 0 ,254,254,254,254,254,254,254,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 , 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254,254, 0 , 0 ,254},
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

} pos;


bool done = false;


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

void printBlankMaze()
{
    int holder = blankMaze[pos.y][pos.x];
    blankMaze[pos.y][pos.x] = 'o';

    //system("cls");
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



//Checks every direction and randomly returns one possible way.
int check()
{
    int x = pos.x;
    int y = pos.y;

    int up = (int)maze[y-1][x];
    int down = (int)maze[y+1][x];
    int right = (int)maze[y][x+1];
    int left = (int)maze[y][x-1];



    while ( 1 )
    {

                if ( up<=down && up<=right && up<=left )
                {
                    return UP;
                }

                if ( left<=up && left<=down && left<=right )
                {
                    return LEFT;
                }


                if ( right<=up && right<=down && right<=left )
                {
                    return RIGHT;
                }

                if ( down<=up && down<=right && down<=left )
                {
                    return DOWN;
                }


    }
}


//Returns how many possible paths there are.
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

void follow( int where )
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
    if ( pos.x == FINISH_X && pos.y == FINISH_Y )
    {
        blankMaze[pos.y][pos.x] = '1';
        done = true;
    }
}




int followTrace( int currentDirection )
{
    int x = pos.x;
    int y = pos.y;

    int up = (int)maze[y-1][x] != 254 ? (int)maze[y-1][x] : 48;

    int down = (int)maze[y+1][x] != 254 ? (int)maze[y+1][x] : 48;

    int right = (int)maze[y][x+1] != 254 ? (int)maze[y][x+1] : 48;

    int left = (int)maze[y][x-1] != 254 ? (int)maze[y][x-1] : 48;

    bool allChecked = false;

    while ( 1 )
    {
        if ( up!=48 && ( currentDirection!=DOWN || allChecked ) )
        {
            return UP;
        }
        if ( down!=48 && ( currentDirection!=UP || allChecked ) )
        {
            return DOWN;
        }
        if ( right!=48 && ( currentDirection!=LEFT || allChecked ) )
        {
            return RIGHT;
        }
        if ( left!=48 && ( currentDirection!=RIGHT || allChecked ) )
        {
            return LEFT;
        }

        allChecked = true;
    }
}





int main()
{
    //Setting a starting point.
    pos.x = INIT_X;
    pos.y = INIT_Y;

    int direction;
    int decision = 0;

    int breakPoints[15][2];

    breakPoints[0][0] = pos.x;
    breakPoints[0][1] = pos.y;

    direction = check();

    printMaze();
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
            breakPoints[decision][0] = pos.x;
            breakPoints[decision][1] = pos.y;

            decision++;
            direction = check();
        }

        while ( decision > 0 && !done )
        {
            if ( !checkHere(direction) )
            {
                if ( numberOfChoices() == 1 )
                {
                    while ( !(pos.x == breakPoints[decision][0] && pos.y == breakPoints[decision][1]) && numberOfChoices() <= 1 )
                    {
                        maze[pos.y][pos.x] = 254;

                        direction = check();
                        moveto ( direction );
                        printMaze();
                    }
                    decision--;
                    direction = check();
                }
                else
                {
                    direction = check();
                }
            }
            else
            {
                moveto(direction);
                printMaze();

                if ( numberOfChoices() > 2 )
                {
                    decision++;
                    breakPoints[decision][0] = pos.x;
                    breakPoints[decision][1] = pos.y;

                    direction = check();
                }
            }
        }
    }

    printf("\nMapping is finished.");
    system("pause");

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
        printf("\t\t");
        printMaze();

        if ( pos.x == FINISH_X && pos.y == FINISH_Y ) { done = true; }
    }






    return 0;
}



















