#include <string>
#define WALL 254
#define SIZE 40


        extern int maze [SIZE][SIZE] =
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

