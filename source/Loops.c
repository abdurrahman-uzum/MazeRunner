#include<stdio.h>
#include<conio.h>

int mul(int, int);
int mul(int a, int b) {
    return a*b;
}

void main() {
     int x, y, z;
     //clrscr();
     x=10;
     y=20;
     z=mul(x,y);
     printf("%d", mul(x,y));
     mul(x,y);
     system("PAUSE");
}
