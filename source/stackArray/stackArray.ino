#include <StackArray.h>
//kütüphaneyi indir

// declare a string message.
double rightSensor;
double leftSensor;
double frontSensor;
boolean deathEnd=false;

// create a stack of characters.
StackArray <String[2]> stack;

// startup point entry (runs once).
void setup () {
  // start serial communication.
  Serial.begin (9600);

  // set the printer of the stack.
  stack.setPrinter (Serial);
}


boolean reverse(String stack.peek(), String sensor)
{
  if(stack.peek().equals(sensor))
  {
    return false; 
  }
  else
  {
    return true;
  }
}


void checkPoints(int rightSensor, int leftSensor)
{
  if(deathEnd == false)
  {
      //daha mantıklı sayılar doubke a göre ayarla.
    if(rightSensor >2 && leftSensor > 2)
    {
      if(rightSensor> leftSensor)
      {
        // daha çok yol katetmesi için
        ways[0] = "right";
        //ways[1] null eklemem gerekiyor mu ?
        stack.push(ways);
      }
      else
      {
        ways[0] =  "left";
        stack.push(ways);
      }
      
    }
    else if (rightSensor > 2 )
    {
        ways[0] =  "right";
        stack.push(ways);
    }
    else if( leftSensor > 2)
    {
        ways[0] =  "left";
        stack.push(ways);
    }
    else if((frontSensor == 2) && rightSensor ==2  && leftSensor ==2)
    {
      //deathend ise 
      //motor 180 döner
      deathEnd = true;   
      
      
    }
  }
  else
  {
    //deathend ise 
     if(frontSensor >2 && leftSensor > 2)
    {

        if(reverse(stack.peek(),leftSensor))
        {
          stack.pop();
          //motor forward gitsin
           ways[0] = "left";
          stack.push("left");
         
          
        }
        else
        {
          stack.pop();
          //motor forward ya da left dönsün
        }
    }
    else if(frontSensor > 2 && rightSensor > 2 )
    {
      if(reverse(stack.peek(),rightSensor))
        {
          stack.pop();
          //motor forward gitsin
          ways[0] = "right";
          stack.push("right");
         
          
        }
        else
        {
          stack.pop();
          //motor forward ya da right dönsün
          //eklemeyi unutma stack' e
        }
    }
    else if (rightSensor > 2 )
    {
      //else durumu olur muydu kontrol et
      //motor sağa dönsün
       if(reverse(stack.peek(),rightSensor))
       stack.pop();
    }
    else if( leftSensor > 2)
    {
      //else durumu check
      //motor sola dönsün
       if(reverse(stack.peek(),leftSensor))
       stack.pop();
    }
    //deathend durumu olmalı mı kontrol et
  }
  
}


// loop the main sketch.
void possibleWays(int rightSensor, int leftSensor)
{
  if(rightSensor >2)
  {
    ways[0]= "Forward";
    ways[1]= "right";
    stack.push(ways);
  }
  else if(leftSensor > 2)
  {
    ways[0]= "Forward";
    ways[1]= "left";
    stack.push(ways);
  }
  else if(rightSensor >2 && leftSensor > 2 )
  {
    ways[0]= "Forward";
    ways[1]= "right";
    stack.push(ways);

    ways[0]= "Forward";
    ways[1]= "right";
    stack.push(ways);
  }
}
void loop () {
 String ways[2];
 if(!(deathEnd))
 {
    while(frontSensor >10)
    {
    //motor düz çalıştır
    // right, left sensor bilgilerini al saniyede bir
      possibleWays(rightSensor, leftSensor);
    }
    checkPoints();
  
 }
 else
 {
  //while: bir possible wayde daha fazla ilerleyemiyorsan diğer possible a bak. varsa diğerine gerek yok.
  //possiblewaysleri ziyaret etmesi için
  //deathendler karışıyor.DENEEEĞĞĞĞĞĞĞ
    
    
    
    checkPoints();
    //motor düz, normale göre yavaş çalışsın
    
    deathEnd = false;
    if(stack.peek().contains("Forward")
    {
        //ilk possible way gelene kadar popla(another idea)
      //possiblewaylere baktığı kısım
      if(rightSensor > 2 )
      {
        stack.pop(); // F / R 'i silmek için
        //dön sağa sağ eklemem gerekirdi ama başladığı yerden dönüormuşçasına 
        ways[0] = "left";
        stack.push(ways);
      }
      else if(leftSensor>2)
      {
        stack.pop(); // F/L 'i silmek için
        //dön sola
        ways[0] = "right";
        stack.push(ways);
      }

    }
    else
    {
      if(rightSensor >2)
      {
        if(reverse(stack.peek(),rightSensor)
        {
          stack.pop();
          //sola dön
        }
        else
        {
          stack.pop();
          //sağa dön
        }
      }
    }  
 }
}
