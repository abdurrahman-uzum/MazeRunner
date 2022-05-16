#define WALL 32787
#define SIZE 10
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 8
#define FINISH_Y 8

extern int maze [SIZE][SIZE] =
{
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL},
    {WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL,  0 ,WALL},
    {WALL,  0 ,  0 ,WALL,  0 ,WALL,WALL,WALL,  0 ,WALL},
    {WALL,WALL,  0 ,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}
};
