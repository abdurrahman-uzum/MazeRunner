#include <bits/stdc++.h>
//#include <String.h>
#include <iostream>
#include <string>

#define WALL 32787
#define SIZE 20
#define INIT_X 1
#define INIT_Y 1
#define FINISH_X 18
#define FINISH_Y 18
#define FRAME_DELAY 100  //Decrement the value for less delay per step.

using namespace std;

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

int absoluteDirection = 0;
int done = false;




double rightSensor;
double leftSensor;
double frontSensor;
bool deathEnd = false;

stack <string> stc;

string ways;



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




void printMaze()
{
    int holder = maze[pos.y][pos.x];
    maze[pos.y][pos.x] = 'o';

    system("cls");
    for (int i=0; i<SIZE; i++)
    {
        for (int j=0; j<SIZE; j++)
        {
            printf(" ");
            switch(maze[i][j])
            {
                case WALL:
                    printf("■");
                break;

                case 'o':
                    printf("o");
                break;

                default:
                    printf(" ");
                    break;
            }
        }
        printf("\n");
    }

    //Sleep(FRAME_DELAY);
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











void removeDeathEnd()
{
      //motor 180 döner
      turn(BACK);

      while (true)
      {
           // poplanan move da possible way çıkana kadar dönecek
            string returnWay;
            returnWay = stc.pop();

            if (returnWay.length() < 2)
            {
                  // eğer poplanan move possible way içermiyorsa poplanan move u yap

                  if (returnWay.charAt(0) == 'r')
                  {
                      // poplanana göre tersine döner ve devam eder
                      while( !readLeft() )
                      {
                        //düz git
                        proceed();
                      }
                      //sola dön
                      turn(LEFT);
                  }
                  else if (returnWay.charAt(0) == 'l')
                  {
                      while( !readRight() )
                      {
                         //düz git
                         proceed();
                      }
                      //sağa dönüş
                      turn(RIGHT);
                  }
            }

            // eğer possible way varsa
            else
            {

                  if ( returnWay.charAt(0) == 'f' )
                  {
                        if (returnWay.charAt(1) == 'r') // sağa döndüysem sol sensörü sürekli kontrol ediyorum
                        {
                              while ( !readLeft() )
                              {
                                  //düz git
                                  proceed();
                              }
                              //sol tarafta yol var, sola dön


                              //junctiondayım stci düzeltmem gerekiyor
                              returnWay.setCharAt(0, returnWay.charAt(1)); // possible way i alınan yol olarak pushluyorum
                              returnWay.setCharAt(1, '\0'); // possible wayi sildim
                              stc.push(returnWay);

                              //sola dönüş
                              turn(LEFT);
                        }
                        else if (returnWay.charAt(1) == 'l') // üsttekinin tam ters yönü
                        {
                              while ( !readRight() )
                              {
                                //düz git
                                proceed();
                              }
                              //sağa dönücem
                              turn(RIGHT);

                              //junctiondayım stci düzeltmem gerekiyor
                              returnWay.setCharAt(0, returnWay.charAt(1)); // possible way i alınan yol olarak pushluyorum
                              returnWay.setCharAt(1, '\0'); // possible wayi sildim
                              stc.push(returnWay);
                        }
                  }
                  else
                  {
                      if(returnWay.charAt(0) == 'r')
                      {
                           while ( !readLeft() )
                           {
                               //düz git
                               proceed();
                           }
                          returnWay.setCharAt(0, returnWay.charAt(1)); // possible way i alınan yol olarak pushluyorum
                          returnWay.setCharAt(1, '\0'); // possible wayi sildim
                          stc.push(returnWay);
                      }

                      else if(returnWay.charAt(0) == 'l')
                      {
                           while ( !readRight() )
                           {
                              //düz git
                              proceed();
                           }
                           //returnWay right olarak pushladım.
                          returnWay.setCharAt(0, returnWay.charAt(1)); // possible way i alınan yol olarak pushluyorum
                          returnWay.setCharAt(1, '\0'); // possible wayi sildim
                          stc.push(returnWay);
                      }

                      break; //bu else ten sonra possible wayin başına geldim
                      // bu yola daha önce girmediğim için bu fonksiyondan çıkıp normal yol alma döngüsüne giriyorum
                  }
            }
        }
}
void checkPoints()
{

      //daha mantıklı sayılar doubke a göre ayarla. tmm.
      if ( readRight() && readLeft() )
      {
            switch ( rand()%2 )
            {
                case 0:
                    //ways[1] null eklemem gerekiyor mu ? bilmem.
                    stc.push("rl");
                    //sağa dön
                    turn(RIGHT);
                break;

                case 1:

                    stc.push("lr");
                    //sola dön
                    turn(LEFT);
                break;
            }

      }
      else if ( readRight() )
      {
            stc.push("r");
            //sağa dön
            turn(RIGHT);
      }
      else if ( readLeft() )
      {
            stc.push("l");
            //sola dön
            turn(LEFT);
      }
      else if ( !readForward() && readRight()  && !readLeft() )
      {
            //deathend ise
            deathEnd = true;
      }
}



void possibleWays()
{
      if ( readRight() && readLeft() )
      {
          stc.push("fr");
          stc.push("fl");
      }
      else if ( readRight() )
      {
          stc.push("fr");
      }
      else if ( readLeft() )
      {
          stc.push("fl");
      }

}








int main()
{
    printMaze();
    deathEnd = false;
    int i = 0;

    while ( !done )
    {

          if ( !(deathEnd) )
          {
                while ( readForward() )
                {

                      //Serial.print("repeats: ");
                      //Serial.println(i++);

                      //motor düz çalıştır
                      proceed();

                      // right, left sensor bilgilerini al saniyede bir
                      possibleWays();
                }
                checkPoints();

          }
          else
          {
                //while: bir possible wayde daha fazla ilerleyemiyorsan diğer possible a bak. varsa diğerine gerek yok.
                //possiblewaysleri ziyaret etmesi için
                //deathendler karışıyor.DENEEEĞĞĞĞĞĞĞ


                //motor düz, normale göre yavaş çalışsın
                proceed(); ///!!!!!!///

                // checkPoints(); // deathEnd true ise checkPoints yapmaya gerek yok
                removeDeathEnd();
                deathEnd = false;
          }


    }
    Serial.println("DONE !");
    return 0;

}
