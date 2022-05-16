#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20
#define FRAME_DELAY 50
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
/*
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
    {254, 0 , 0 , 0 , 0 ,254,254,254, 0 ,254},
    {254,254,254,254,254,254,254,254,254,254}

};*/


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
};


int mazeControl [SIZE][SIZE] =
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
};




struct Position
{
    int x = 1;
    int y = 1;

} pos, breakPoint;



//Checks every direction and randomly returns one possible way.
int check()
{
    int x = pos.x;
    int y = pos.y;

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;


    if ( maze[y-1][x] == 0 )       //UP
    {
        up = true;
    }
    if ( maze[y+1][x] == 0 )  //DOWN
    {
        down = true;
    }
    if ( maze[y][x+1] == 0 )  //RIGHT
    {
        right = true;
    }
    if ( maze[y][x-1] == 0 )  //LEFT
    {
        left = true;
    }


    srand ( time(0) );
    while (1)
    {
        switch( rand()%4 )
        {
        case UP:
            if (up) { return UP; }
            break;
        case DOWN:
            if (down) { return DOWN; }
            break;
        case RIGHT:
            if (right) { return RIGHT; }
            break;
        case LEFT:
            if (left) { return LEFT; }
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

    if ( maze[y-1][x] == 0 )       //UP
    {
        choices++;
    }
    if ( maze[y+1][x] == 0 )  //DOWN
    {
        choices++;
    }
    if ( maze[y][x+1] == 0 )  //RIGHT
    {
        choices++;
    }
    if ( maze[y][x-1] == 0 )  //LEFT
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
        if ( maze[y-1][x] == 0 ) { return true; }
        else { return false; }
        break;

    case DOWN:
        if ( maze[y+1][x] == 0 ) { return true; }
        else { return false; }
        break;

    case RIGHT:
        if ( maze[y][x+1] == 0 ) { return true; }
        else { return false; }
        break;
    case LEFT:
        if ( maze[y][x-1] == 0 ) { return true; }
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


void printMazeControl()
{
    printf("\n\n");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            printf("%3d", mazeControl[i][j]);
        }
        printf("\n");
    }
}


int mostVisited()
{
    int paths[4];

    if ( mazeControl[pos.y-1][pos.x] != 254 )
    {
        paths[UP] = mazeControl[pos.y-1][pos.x];
    }
    else
    {
        paths[UP] = 0;
    }

    if ( mazeControl[pos.y+1][pos.x] != 254 )
    {
        paths[DOWN] = mazeControl[pos.y+1][pos.x];
    }
    else
    {
        paths[DOWN] = 0;
    }


    if ( mazeControl[pos.y][pos.x+1] != 254 )
    {
        paths[RIGHT] = mazeControl[pos.y][pos.x+1];
    }
    else
    {
        paths[RIGHT] = 0;
    }

    if ( mazeControl[pos.y][pos.x-1] != 254 )
    {
        paths[LEFT] = mazeControl[pos.y][pos.x-1];
    }
    else
    {
        paths[LEFT] = 0;
    }

    int limiter;
    int hold;
    int pathsCopy[4];
    pathsCopy[0] = paths[0];
    pathsCopy[1] = paths[1];
    pathsCopy[2] = paths[2];
    pathsCopy[3] = paths[3];

    for (int i=0; limiter<4; i++)
    {
        i = i%3;

        if ( pathsCopy[i] > pathsCopy[i+1] ) {

                hold = pathsCopy[i+1];
                pathsCopy[i+1] = pathsCopy[i];
                pathsCopy[i] = hold;
                limiter = 0;
                continue;

        }
        limiter++;

    }

    if ( pathsCopy[3] == paths[UP] )
        return UP;
    if ( pathsCopy[3] == paths[DOWN] )
        return DOWN;
    if ( pathsCopy[3] == paths[RIGHT] )
        return RIGHT;
    if ( pathsCopy[3] == paths[LEFT] )
        return LEFT;
}








int main()
{
    //Setting a starting point.
    pos.x = INIT_X;
    pos.y = INIT_Y;

    int direction, prevDirection;
    bool done = false;

    printMaze();
    printMazeControl();
    system("pause");

    direction = check();

    while ( !done )
    {
        //While there are no choices other than moving forward:
        while ( numberOfChoices() <= 2 && checkHere(direction) )
        {
            //Block the path back if leads nowhere.
            if ( numberOfChoices() == 1 ) { maze[pos.y][pos.x] = 254; }

            mazeControl[pos.y][pos.x]++;

            moveto ( direction );
            printMaze();
            printMazeControl();

            if ( pos.x == FINISH_X && pos.y == FINISH_Y ) { done = true; break; }
        }


        if ( numberOfChoices() == 1 ) { maze[pos.y][pos.x] = 254; }

        //If encountered a position where more than one way is possible:
        if ( numberOfChoices() > 2 && !done)
        {
            //Saving the position and moving on.
            breakPoint = pos;
            direction = check();

            mazeControl[pos.y][pos.x]++;

            moveto(direction);
            printMaze();
            printMazeControl();
        }
        //If encountered an obstacle:
        else if ( !checkHere(direction) && !done )
        {
            //This hole if&switch section is responsible for trying not to return back if any other path exists.
            prevDirection = direction;
            direction = check();

            if ( direction == inverse(prevDirection) )
            {
                switch ( direction )
                {
                case UP:
                    if( checkHere(RIGHT) ) { direction = RIGHT; }
                    else if ( checkHere(LEFT) ) { direction = LEFT; }
                    else if ( checkHere(DOWN) ) { direction = DOWN; }
                    break;
                case DOWN:
                    if( checkHere(RIGHT) ) { direction = RIGHT; }
                    else if ( checkHere(LEFT) ) { direction = LEFT; }
                    else if ( checkHere(UP) ) { direction = DOWN; }
                    break;
                case RIGHT:
                    if( checkHere(UP) ) { direction = UP; }
                    else if ( checkHere(DOWN) ) { direction = DOWN; }
                    else if ( checkHere(LEFT) ) { direction = LEFT; }
                    break;
                case LEFT:
                    if( checkHere(UP) ) { direction = UP; }
                    else if ( checkHere(DOWN) ) { direction = DOWN; }
                    else if ( checkHere(RIGHT) ) { direction = RIGHT; }
                }

            }

            mazeControl[pos.y][pos.x]++;

            moveto(direction);
            printMaze();
            printMazeControl();
        }

        if ( pos.x == FINISH_X && pos.y == FINISH_Y ) { done = true; }
    }

    ///  END OF FIRST STAGE  ///

    printf("Maze mapping is done!\n");
    system("pause");

    done = false;

    for ( int i=0; i<SIZE; i++ )
    {
        for ( int j=0; j<SIZE; j++ )
        {
            if ( mazeControl[i][j] != 0 && mazeControl[i][j] != 254 )
            {
                maze[i][j] = 0;
            }
            else
            {
                maze[i][j] = mazeControl[i][j];
            }
        }

    }

    pos.x = INIT_X;
    pos.y = INIT_Y;

    while (!done)
    {
        direction = mostVisited();
        moveto ( direction );
        printMaze();

        if ( pos.x == FINISH_X && pos.y == FINISH_Y )
        {
            done = true;
        }
    }




































    return 0;
}























