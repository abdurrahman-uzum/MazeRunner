#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <StackArray.h>
#include <String.h>

#define WALL 32787
#define SIZE 20
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 18
#define FINISH_Y 18

int maze [SIZE][SIZE] =
{
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,  0 ,  0 ,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,  0 ,WALL},
    {WALL,WALL,WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL,WALL,WALL,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,  0 ,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL},
    {WALL,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,WALL},
    {WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL,WALL}
};

#define FRAME_DELAY 100  //Decrement the value for less delay per step.



//

boolean deathEnd=false;
boolean twoWayCheckLeft=false;
boolean twoWayCheckRight=false;

StackArray <String> stack;

//


//Direction-position managing:

enum directions
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

//////


//Global flags:

bool done = false;

int loopDetector = 0;
bool loop = false;

//////



//Global variables:

int absoluteDirection;

//////


//Function prototypes:

void printMaze(void);

bool checkHere(int);

void turn(int);
void proceed(void);

bool readForward(void);
bool readRight(void);
bool readLeft(void);


///////



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



bool checkHere ( int where )
{
    int x = pos.x;
    int y = pos.y;

    switch ( where )
    {
        case NORTH:
            if ( maze[y-1][x] != WALL ) { return true; }
            else { return false; }
            break;

        case SOUTH:
            if ( maze[y+1][x] != WALL ) { return true; }
            else { return false; }
            break;

        case EAST:
            if ( maze[y][x+1] != WALL ) { return true; }
            else { return false; }
            break;
        case WEST:
            if ( maze[y][x-1] != WALL ) { return true; }
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

    printMaze();
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

    if ( pos.x == FINISH_X && pos.y == FINISH_Y ) { done = true; }

    printMaze();
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



void removeDeathEnd(){

    while(true){ // poplanan move da possible way çýkana kadar dönecek
      String returnWay =  stack.pop();

      if(returnWay.length()<2){ // eðer poplanan move possible way içermiyorsa poplanan move u yap
        while( readForward() ){
            //düz git
            proceed();

            if( readForward() && readLeft() )
            {
              twoWayCheckLeft=true;
              break;
            }
            else if( readForward() && readRight() )
            {
              twoWayCheckRight=true;
              break;
            }

          }
          if(twoWayCheckLeft)
          {

            //düz gider
            proceed();

            stack.push("l");
            twoWayCheckLeft=false;
          }
          else if(twoWayCheckRight)
          {
            if(returnWay.charAt(0) == 'l')
            {
               //düz gider
               proceed();

               stack.push("r");
            }
            //else
            //{
            //}



            twoWayCheckRight=false;
          }
          else if(returnWay.charAt(0) == 'r'){ // poplanana göre tersine döner ve devam eder
            //sola dön
            turn(LEFT);
            }
          else if(returnWay.charAt(0) == 'l'){
            //saða dön
            turn(RIGHT);
            }

        }
      else{ // eðer possible way varsa
          if(returnWay.charAt(1)=='r'){ // saða döndüysem sol sensörü sürekli kontrol ediyorum
            while( !readLeft() ){
            //düz git
            proceed();

            }
            //sol tarafta yol var
            //junctiondayým stacki düzeltmem gerekiyor

            //sola dön
            turn(LEFT);

            returnWay.setCharAt(0,returnWay.charAt(1)); // possible way i alýnan yol olarak pushluyorum
            returnWay.setCharAt(1, '\0'); // possible wayi sildim (\0 null demek)
            stack.push(returnWay);

          }
          else if(returnWay.charAt(1)=='l'){ // üsttekinin tam ters yönü
            while( !readRight() ){
            //düz git
            }
            //junctiondayým stacki düzeltmem gerekiyor
            //saða dön
            returnWay.setCharAt(0,returnWay.charAt(1)); // possible way i alýnan yol olarak pushluyorum
            returnWay.setCharAt(1, '\0'); // possible wayi sildim
            stack.push(returnWay);

          }
        break; //bu else ten sonra possible wayin baþýna geldim
        // bu yola daha önce girmediðim için bu fonksiyondan çýkýp normal yol alma döngüsüne giriyorum

    }

  }
}

void checkPoints()
{

      //daha mantýklý sayýlar doubke a göre ayarla.
    if( readRight() && readLeft() )
    {
      if( /*rightSensor > leftSensor*/ 1 )
      {
        //saða dön
        turn(RIGHT);

        //ways[1] null eklemem gerekiyor mu ?
        stack.push("r");
      }
      else
      {
        //sola dön
        turn(LEFT);
        stack.push("l");
      }

    }
    else if ( readRight() )
    {
        //saða dön
        turn(RIGHT);

        stack.push("r");
    }
    else if( readLeft() )
    {
        //sola dön
        turn(LEFT);
        stack.push("l");
    }
    else if((!readForward()) && !readRight()  && !readLeft() )
    {
      //deathend ise
      //motor 180 döner.
      turn(BACK);

      deathEnd = true;

    }

}


// loop the main sketch.
void possibleWays(int rightSensor, int leftSensor)
{
  if( readRight() )
  {

    stack.push("fr");
  }
  else if( readLeft() )
  {

    stack.push("fl");
  }
  else if( readRight() && readLeft() )
  {

    stack.push("fr");


    stack.push("fl");
  }
}





int main()
{
    while ( !done )
    {
         if(!(deathEnd))
         {
            while( readForward() )
            {
            //motor düz çalýþtýr
            // right, left sensor bilgilerini al saniyede bir
              if( /*frontSensor>5*/ //? )
              {
                //checkPOintleri possibleways olarak atmasýn diye. //ama mantýken kontrol et.
                 possibleWays(rightSensor, leftSensor);
              }

            }
            checkPoints();

         }
         else
         {
            //motor düz, normale göre yavaþ çalýþsýn

            removeDeathEnd();
            deathEnd= false;

         }
    }
    printf("DONE!");


    return 0;
}























