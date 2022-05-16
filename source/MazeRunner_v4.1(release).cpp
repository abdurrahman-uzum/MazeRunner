/*
    ABOUT ALGORITHM

    This algorithm is designed for an autonomous vehicle moving in a maze, therefore it's much less efficient compare to an algorithm designed for software only.
    An entity is created in order to replicate a physical vehicle, and needs to move in the maze like a vehicle to map the maze, rather than scanning.

    Position of this entity is held by a struct, as x and y coordinates.

    Every time it moves, it checks the four blocks around of it, to simulate sensorial input, and constructs the maze in it's "head". This is done by the
    function < plotMaze >, and this function itself is often called by the function < moveto >.

    At the beginning, 2d array named < mappedMaze > only consists of zeros, meaning that everywhere is possible to go.

    By the first call for function < plotMaze >, first four blocks around starting point are constructed.

    Walls of the maze and entity itself is represented by an arbitrary big constant integer. ( reason will be explained. [note #1] )

    Unvisited paths are represented by zero. As entity moves in the maze, value of passed paths are incremented by 1, that is, if a square is visited once,
    value for it will be 1, if twice, 2, so on.

    Every time entity reaches a breakpoint, i.e. two or more paths are possible to go ( other than turning back ), this position is saved to < breakpoints > array. Also, when
    this occurs, value of visited paths are incremented by a relatively big number (I chose 5). As a result, paths which are connected to starting point with lesser number
    of breakpoints will have greater value at the end.[note #2]. For big mazes, values of paths can reach hundreds, interfering with ASCII codes of maze elements. This is why
    at note #1, values of constant maze elements must be big enough.

    When entity reaches a dead-end, i.e. only possible path is returning back, that position is marked as BLOCK, and entity moves one square back.
    Notice that at this point, entity still has only one way to go, the same situation continues, ( assume this dead end is multiple squares long. )
    so, this process repeats until a breakpoint is reached ( meaning that more than one paths are possible ). This breakpoint can be either previous breakpoint, or a new one.
    At this point, that path to dead-end will be covered, and will be treated as a wall.
    If it's the previous one it will be ignored at breakpoints array from now on.
    If it's a new breakpoint, this position is also written at breakpoints array.
    Program is always concerned about only the last breakpoint saved at breakpoints array. As said above, if that breakpoint leads to a dead-end, when that dead-end is
    handled, new last breakpoint will become one before that.

    When entity reaches a previously visited path at where there are more than one paths to go, this means a loop is encountered.
    ( "more than one path to go" part is for distinguish loops from dead-ends, because entity will move to previously visited path while returning from a breakpoint
    as well, but will only have one way to go. )
    In that case, entity will mark it's current position as BLOCK and will move to path with smaller value. Notice at that point, situation will not be different than a
    dead-end. So rest will be handled by dead-end handling part.
    Reason why a path with smaller value was chosen is to leave the path which is more directly connected to starting point open. This the reason of note #2. Also this
    prevents the entity from blocking connection of starting point with rest of the maze.

    When the end is reached, at array mappedMaze, a path to end will be constructed during the process. Second part of the algorithm starts from beginning and follows that path.

    NOTE:
    This algorithm does not, and cannot without wasting so much time, find the shortest path. But it should be possible to find the shorter path around the loops.
    More upgrades is to come about that.


    /14.12.2019/
*/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>


//Maze settings:

#define SIZE 40
#define FRAME_DELAY 20
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 38
#define FINISH_Y 38

//To prevent interfering with path values, give these symbolic constants biggest possible values.
#define WALL 32787
#define BLOCK 32766
#define CHARACTER 32765

//Visualization constants. Assign ASCII characters only.
#define charWALL 254
#define charBLOCK 'X'
#define charCHARACTER 'o'



//Representation of physical maze.
int maze [SIZE][SIZE] =
{
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,WALL},
    {WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,WALL},
    {WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL},
    {WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,  0 ,  0 ,  0 ,WALL,  0 ,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
};



//The 2D array in which the constructed map will be plotted.
int mappedMaze[SIZE][SIZE];


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

int breakpoints[50][2];
int decision = 0;
int direction;



//Function prototypes
void printMaze( void );
void printBlankMaze( void );
int check( void );
int numberOfChoices( void );
bool checkHere( int );
void moveto( int );
int whatsThere( int );
int whatsThere1( int );
void plotMaze( void );
void highlight( void );
void follow( int );
int followTrace( int );




//Overly complicated looking function just to print everything on the screen. Has no contribution to the algorithm.
void printMaze()
{
    int holder = mappedMaze[pos.y][pos.x];

    mappedMaze[pos.y][pos.x] = CHARACTER;
    maze[pos.y][pos.x] = CHARACTER;

    system("cls");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            if ( mappedMaze[i][j] == WALL || mappedMaze[i][j] == BLOCK || mappedMaze[i][j] == CHARACTER )
            {
                switch ( mappedMaze[i][j] )
                {
                    case WALL:
                        printf(" %c ", charWALL);
                    break;

                    case BLOCK:
                        printf(" %c ", charBLOCK);
                        break;

                    case CHARACTER:
                        printf(" %c ", charCHARACTER);
                        break;
                }
            }
            else if ( mappedMaze[i][j] > 99 )
            {
                printf("%d", mappedMaze[i][j]);
            }
            else if ( mappedMaze[i][j] > 9 )
            {
                printf(" %d", mappedMaze[i][j]);
            }
            else if ( mappedMaze[i][j] > 0 )
            {
                printf(" %d ", mappedMaze[i][j]);
            }
            else
            {
                printf("   ");
            }
        }

        printf(" | ");

        for (int j=0; j<SIZE; j++)
        {
            switch ( maze[i][j] )
            {
                case WALL:
                    printf(" %c", charWALL);
                break;

                case BLOCK:
                    printf(" %c", charBLOCK);
                    break;

                case CHARACTER:
                    printf(" %c", charCHARACTER);
                    break;

                default:
                    printf(" %c", maze[i][j]);
                    break;
            }
        }

        printf("\n");
    }

    //For debugging:
    printf("\ndirection:%d   decisions:%d   pos:(%d,%d)   last breakpoint:(%d,%d)\n", direction, decision, pos.x, pos.y, breakpoints[decision][0], breakpoints[decision][1]);

    Sleep(FRAME_DELAY);

    mappedMaze[pos.y][pos.x] = holder;
    maze[pos.y][pos.x] = NULL;
}



void printBlankMaze()
{
    int holder = maze[pos.y][pos.x];
    maze[pos.y][pos.x] = 'o';

    system("cls");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            switch ( maze[i][j] )
            {
                case WALL:
                    printf(" %c", charWALL);
                break;

                case BLOCK:
                    printf(" %c", charBLOCK);
                    break;

                case CHARACTER:
                    printf(" %c", charCHARACTER);
                    break;

                default:
                    printf(" %c", maze[i][j]);
                    break;
            }
        }
        printf("\n");
    }

    Sleep(FRAME_DELAY);
    maze[pos.y][pos.x] = holder;
}




//Returns random possible direction. ( prioritises unvisited - low value paths ).
int check()
{
    int x = pos.x;
    int y = pos.y;

    int up = (int)mappedMaze[y-1][x];
    int down = (int)mappedMaze[y+1][x];
    int right = (int)mappedMaze[y][x+1];
    int left = (int)mappedMaze[y][x-1];

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



//Returns number of available directions.
int numberOfChoices()
{
    int x = pos.x;
    int y = pos.y;

    int choices = 0;

    if ( mappedMaze[y-1][x] != WALL && mappedMaze[y-1][x] != BLOCK )  //UP
    {
        choices++;
    }
    if ( mappedMaze[y+1][x] != WALL && mappedMaze[y+1][x] != BLOCK )  //DOWN
    {
        choices++;
    }
    if ( mappedMaze[y][x+1] != WALL && mappedMaze[y][x+1] != BLOCK )  //RIGHT
    {
        choices++;
    }
    if ( mappedMaze[y][x-1] != WALL && mappedMaze[y][x-1] != BLOCK )  //LEFT
    {
        choices++;
    }

    return choices;
}



//Returns whether the given direction is available.
bool checkHere ( int where )
{
    int x = pos.x;
    int y = pos.y;

    switch ( where )
    {
        case UP:
            if ( mappedMaze[y-1][x] != WALL && mappedMaze[y-1][x] != BLOCK ) { return true; }
            else { return false; }
            break;

        case DOWN:
            if ( mappedMaze[y+1][x] != WALL && mappedMaze[y+1][x] != BLOCK ) { return true; }
            else { return false; }
            break;

        case RIGHT:
            if ( mappedMaze[y][x+1] != WALL && mappedMaze[y][x+1] != BLOCK ) { return true; }
            else { return false; }
            break;
        case LEFT:
            if ( mappedMaze[y][x-1] != WALL && mappedMaze[y][x-1] != BLOCK ) { return true; }
            else { return false; }
            break;

        default:
            printf("\nIn function: checkHere FATAL ERROR!");
            exit(-1);
            break;
    }
}



//Moves entity to given direction, increments value of visited squares, checks whether end of the maze is reached and calls plotMaze function to map the maze.
void moveto( int where )
{
    if ( whatsThere1(where) == WALL || whatsThere1(where) == BLOCK )
    {
        printf("\nI cannot walk on walls!\n");
        exit(-1);
    }

    (int)mappedMaze[pos.y][pos.x]++;

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
            printf("\nIn function: moveto  FATAL ERROR!\n");
            exit(-1);
    }

    plotMaze();

    if ( pos.x == FINISH_X && pos.y == FINISH_Y )
    {
        mappedMaze[pos.y][pos.x] = 999;
        done = true;
    }
}



//Returns value of square at given direction (from sensors).
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
            printf("\nIn function: whatsThere  FATAL ERROR!");
            exit(-1);
    }

    return (int)maze[temp.y][temp.x];
}




//Returns value of square at given direction (from mapped maze).
int whatsThere1( int where )
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
            printf("\nIn function: whatsThere1(int where)  FATAL ERROR!");
            exit(-1);
    }

    return (int)mappedMaze[temp.y][temp.x];
}




//Constitutes the maze with the information taken from sensors. ( well, replicates that at this stage. )
void plotMaze()
{
    if ( whatsThere(UP) == WALL || whatsThere(UP) == BLOCK ) { mappedMaze[pos.y-1][pos.x] = WALL; }

    if ( whatsThere(DOWN) == WALL || whatsThere(DOWN) == BLOCK ) { mappedMaze[pos.y+1][pos.x] = WALL; }

    if ( whatsThere(RIGHT) == WALL || whatsThere(RIGHT) == BLOCK ) { mappedMaze[pos.y][pos.x+1] = WALL; }

    if ( whatsThere(LEFT) == WALL || whatsThere(LEFT) == BLOCK ) { mappedMaze[pos.y][pos.x-1] = WALL; }
}




//Increments the value of previously marked paths, thus prioritising them.
//(Paths which are connected to the start point with lesser breakpoints will have greater values.)
void highlight ()
{
    for ( int i=0; i<SIZE; i++ )
    {
        for ( int j=0; j<SIZE; j++ )
        {
            if ( mappedMaze[i][j]!=0 && mappedMaze[i][j]!=WALL && mappedMaze[i][j]!=BLOCK && mappedMaze[i][j]!=CHARACTER )
            {
                mappedMaze[i][j] = (int)mappedMaze[i][j] + 5;
            }
        }
    }
}



//Same with the function moveto, but just moves the entity around and marks the followed path, visualization purposes.
void follow( int where )
{
    switch ( where )
    {
        case UP:
            maze[pos.y][pos.x] = '|';
            pos.y--;
            break;

        case DOWN:
            maze[pos.y][pos.x] = '|';
            pos.y++;
            break;

        case RIGHT:
            maze[pos.y][pos.x] = 196;
            pos.x++;
            break;

        case LEFT:
            maze[pos.y][pos.x] = 196;
            pos.x--;
            break;

        default:
            printf("\nIn function: follow  FATAL ERROR!");
            exit(-1);
    }
    if ( pos.x == FINISH_X && pos.y == FINISH_Y )
    {
        done = true;
    }
}



//Returns the direction to the square with greatest value. ( except if that means returning back. )
int followTrace( int currentDirection )
{
    int x = pos.x;
    int y = pos.y;


    int up = (int)mappedMaze[y-1][x] != WALL ? (int)mappedMaze[y-1][x] :0;

    int down = (int)mappedMaze[y+1][x] != WALL ? (int)mappedMaze[y+1][x] :0;

    int right = (int)mappedMaze[y][x+1] != WALL ? (int)mappedMaze[y][x+1] :0;

    int left = (int)mappedMaze[y][x-1] != WALL ? (int)mappedMaze[y][x-1] :0;

    bool allChecked = false;


    while ( 1 )
    {

        if ( ( up!=0 && up!=BLOCK ) && ( currentDirection!=DOWN || allChecked ) )
        {
            return UP;
        }
        if ( ( down!=0 && down!=BLOCK ) && ( currentDirection!=UP || allChecked ) )
        {
            return DOWN;
        }
        if ( ( right!=0 && right!=BLOCK ) && ( currentDirection!=LEFT || allChecked ) )
        {
            return RIGHT;
        }
        if ( ( left!=0 && left!=BLOCK ) && ( currentDirection!=RIGHT || allChecked ) )
        {
            return LEFT;
        }

        allChecked = true;

    }
}




int main()
{
    /// STEP #0 : Setting up. ///

    //Constructing blank map.
    for ( int i=0; i<SIZE; i++ )
    {
        for ( int j=0; j<SIZE; j++ )
        {
            mappedMaze[i][j] = 0;
        }
    }

    //Setting start position
    pos.x = INIT_X;
    pos.y = INIT_Y;

    breakpoints[0][0] = pos.x;
    breakpoints[0][1] = pos.y;

    printBlankMaze();
    system("pause");

    plotMaze();


    /// STEP #1 : Solving the maze. ///

    while ( !done )
    {

        /// Loop handling:

        if ( whatsThere1(direction) > 0 && whatsThere(direction)!=WALL && whatsThere1(direction)!=BLOCK && numberOfChoices() == 2 )
        {
            mappedMaze[pos.y][pos.x] = BLOCK-1;  // -1 is because this will be incremented by moveto function as well, as a side effect.

            direction = check();
            moveto(direction);
            printMaze();

            direction = check();
        }
        ///


        ///Dead-end handling:

        if ( numberOfChoices() == 1 )
        {
            while ( !(pos.x == breakpoints[decision][0] && pos.y == breakpoints[decision][1]) && numberOfChoices() <= 1 )
            {
                mappedMaze[pos.y][pos.x] = BLOCK -1;

                direction = check();
                moveto ( direction );

                printMaze();
            }

            if ( pos.x == breakpoints[decision][0] && pos.y == breakpoints[decision][1] )
            {
                decision--;
            }
        }
        ///


        ///Moving if there is nothing to worry:

        direction = check();

        if ( whatsThere1(direction) == 0 )
        {
            moveto(direction);
            printMaze();

            if ( numberOfChoices() > 2 )
            {
                decision++;

                breakpoints[decision][0] = pos.x;
                breakpoints[decision][1] = pos.y;

                highlight();

                direction = check();
            }
        }
        ///

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


