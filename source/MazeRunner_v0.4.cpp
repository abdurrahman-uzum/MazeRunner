#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define FRAME_DELAY 200
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 8
#define FINISH_Y 8


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
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254},
    {254, 0 ,254 ,0 ,254, 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254},
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
    {254, 0 , 0 , 0 , 0 ,254,254,254,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};

int mazeCopy [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254,254,254, 0 ,254, 0 ,254,254,254},
    {254,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254},
    {254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 ,254,254,254,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};

int mappedMaze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254,254,254, 0 ,254, 0 ,254,254,254},
    {254,254, 0 ,254, 0 ,254, 0 , 0 , 0 ,254},
    {254,254, 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 ,254,254,254,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};
/*////////
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254,254, 0 ,254,254,254,254,254},
    {254,254, 0 ,254, 0 ,254,254,254,254,254},
    {254,254, 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 , 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 ,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 ,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};

int mazeCopy [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254,254, 0 ,254,254,254,254,254},
    {254,254, 0 ,254, 0 ,254,254,254,254,254},
    {254,254, 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 , 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 ,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 ,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};

int mappedMaze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254,254,254,254, 0 ,254,254,254,254,254},
    {254,254, 0 ,254, 0 ,254,254,254,254,254},
    {254,254, 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 , 0 ,254, 0 ,254,254,254,254,254},
    {254, 0 ,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254,254,254, 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 , 0 ,'f',254},
    {254,254,254,254,254,254,254,254,254,254}

};*//////////////

/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 ,254,254,254,254,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254,254,254,254,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 , 0 , 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 , 0 ,254, 0 ,254,254,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254,254, 0 , 0 , 0 , 0 , 0 ,254,254, 0 ,254},
    {254, 0 ,254 ,0 ,254, 0 , 0 , 0 , 0 ,254,254, 0 ,254,254,254, 0 ,254,254, 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254,254,254,254,254,254, 0 ,254, 0 ,254,254},
    {254, 0 ,254,254,254,254,254,254,254,254, 0 , 0 , 0 , 0 ,254, 0 ,254, 0 ,254,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254, 0 ,254, 0 ,254, 0 ,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 ,254, 0 , 0 ,254, 0 , 0 , 0 ,254, 0 ,254,254},
    {254,254,254, 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 , 0 , 0 ,254},
    {254, 0 ,254, 0 ,254,254, 0 , 0 , 0 ,254, 0 , 0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254},
    {254, 0 ,254, 0 , 0 , 0 ,254,254, 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254},
    {254, 0 ,254, 0 ,254, 0 ,254,254,254,254, 0 ,254,254, 0 ,254, 0 , 0 , 0 , 0 ,254},
    {254, 0 ,254 ,0 ,254, 0 , 0 , 0 , 0 ,254, 0 ,254,254, 0 ,254,254,254,254, 0 ,254},
    {254, 0 ,254,254,254, 0 ,254,254, 0 ,254, 0 ,254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254, 0 , 0 , 0 ,254,254,254,254,254,254, 0 , 0 ,254},
    {254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254}
};*/
/*
int maze [SIZE][SIZE] =
{
    {254,254,254,254,254,254,254,254,254,254},
    {254, 0 , 0 , 0 , 0 , 0 , 0 ,254,254,254},
    {254,254,254,254, 0 ,254, 0 ,254,254,254},
    {254,254,254,254, 0 ,254, 0 , 0 , 0 ,254},
    {254,254,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 ,254,254, 0 ,254, 0 ,254, 0 ,254},
    {254, 0 , 0 ,254, 0 ,254,254,254, 0 ,254},
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

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;


    if ( maze[y-1][x] != 254 )   //UP
    {
        up = true;
    }
    if ( maze[y+1][x] != 254 )  //DOWN
    {
        down = true;
    }
    if ( maze[y][x+1] != 254 )  //RIGHT
    {
        right = true;
    }
    if ( maze[y][x-1] != 254 )  //LEFT
    {
        left = true;
    }

    srand ( time(0) );
    while (1)
    {
        switch( rand()%4 )
        {
        case UP:
            if ( currentDirection == DOWN )
            {
                if ( down ) { return DOWN; }
                else if ( right ) { return RIGHT; }
                else if ( left ) { return LEFT; }
                else if ( up ) { return UP; }
            }
            else if ( up ) { return UP; }
            break;

        case DOWN:
            if ( currentDirection == UP )
            {
                if ( up ) { return UP; }
                else if ( right ) { return RIGHT; }
                else if ( left ) { return LEFT; }
                else if ( down ) { return DOWN; }
            }
            else if ( down ) { return DOWN; }
            break;

        case RIGHT:
            if ( currentDirection == LEFT )
            {
                if ( left ) { return LEFT; }
                else if ( up ) { return UP; }
                else if ( down ) { return DOWN; }
                else if ( right ) { return RIGHT; }
            }
            else if ( right ) { return RIGHT; }
            break;

        case LEFT:
            if ( currentDirection == RIGHT )
            {
                if ( right ) { return RIGHT; }
                else if ( up ) { return UP; }
                else if ( down ) { return DOWN; }
                else if ( left ) { return LEFT; }
            }
            else if ( left ) { return LEFT; }
            break;
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


int checkForPath( int currentDirection )
{
    int x = pos.x;
    int y = pos.y;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;


    if ( mappedMaze[y-1][x] == '1' )   //UP
    {
        up = true;
    }
    if ( mappedMaze[y+1][x] == '1' )  //DOWN
    {
        down = true;
    }
    if ( mappedMaze[y][x+1] == '1' )  //RIGHT
    {
        right = true;
    }
    if ( mappedMaze[y][x-1] == '1' )  //LEFT
    {
        left = true;
    }

    srand ( time(0) );
    while (1)
    {
        switch( rand()%4 )
        {
        case UP:
            if ( currentDirection == DOWN )
            {
                if ( down ) { return DOWN; }
                else if ( right ) { return RIGHT; }
                else if ( left ) { return LEFT; }
                else if ( up ) { return UP; }
            }
            else if ( up ) { return UP; }
            break;

        case DOWN:
            if ( currentDirection == UP )
            {
                if ( up ) { return UP; }
                else if ( right ) { return RIGHT; }
                else if ( left ) { return LEFT; }
                else if ( down ) { return DOWN; }
            }
            else if ( down ) { return DOWN; }
            break;

        case RIGHT:
            if ( currentDirection == LEFT )
            {
                if ( left ) { return LEFT; }
                else if ( up ) { return UP; }
                else if ( down ) { return DOWN; }
                else if ( right ) { return RIGHT; }
            }
            else if ( right ) { return RIGHT; }
            break;

        case LEFT:
            if ( currentDirection == RIGHT )
            {
                if ( right ) { return RIGHT; }
                else if ( up ) { return UP; }
                else if ( down ) { return DOWN; }
                else if ( left ) { return LEFT; }
            }
            else if ( left ) { return LEFT; }
            break;
        }
    }




}



//Moves the entity to a direction (not position).
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
    if ( pos.x == FINISH_X && pos.y == FINISH_Y )
    {
        /*printMaze();
        printf("\nDONE!");
        exit(1);*/

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

    breakPoint = pos;

    direction = 2;//check();

    bool decision = false;

    while ( !done )
    {
        while (  numberOfChoices() <= 2 && checkHere(direction) && !done )
        {
            maze[pos.y][pos.x] = '1';
            moveto ( direction );
            printMaze();
        }

        if ( !checkHere(direction) && !done )
        {
            direction = check(direction);
        }

        if ( numberOfChoices() > 2 )
        {
            breakPoint = pos;
            decision = true;
            direction = check(direction);
        }
        while ( decision && !done)
        {
            if ( !checkHere(direction) )
            {
                if ( numberOfChoices() == 1 )
                {
                    direction = inverse(direction);
                    while ( !(pos.x == breakPoint.x && pos.y == breakPoint.y) && numberOfChoices() <= 1 )
                    {
                        if ( maze[pos.y][pos.x] != '1' )
                        {
                            maze[pos.y][pos.x] = 254;
                        }
                        if ( checkHere(direction) )
                        {
                            moveto ( direction );
                            printMaze();
                        }
                        else
                        {
                            direction = check(direction);
                        }
                    }
                    decision = false;
                }
                else
                {
                    direction = check(direction);
                }
            }
            else
            {
                moveto(direction);
                printMaze();
            }
        }
    }

    printf("Maze mapping is finished.");
    system("pause");

    done = false;
    pos.x = INIT_X;
    pos.y = INIT_Y;

    for ( int i=0; i<SIZE; i++ )
    {
        for ( int j=0; j<SIZE; j++ )
        {
            mappedMaze[i][j] = maze[i][j];
        }
    }

    for ( int i=0; i<SIZE; i++ )
    {
        for ( int j=0; j<SIZE; j++ )
        {
            maze[i][j] = mazeCopy[i][j];
        }
    }


    printMaze();


    while ( !done )
    {
        direction = checkForPath(direction);
        moveto(direction);
        printMaze();
        if ( pos.x == FINISH_X && pos.y == FINISH_Y  ) { done = true; }
    }
    printf("\nDONE!");
    system("pause");











    return 0;
}





















