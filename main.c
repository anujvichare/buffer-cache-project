#include<stdio.h>
#include<conio.h>
#include"buf.h"

extern BUF_H *bfreelist,*hashque[5];
//////////////////////////////
//
//  main function
//
/////////////////////////////
int main()
{

int no;
BUF_H *test;
printf("enter no of buffers u want \t");
scanf("%d",&no);
 createPool(&bfreelist,no);
  display(bfreelist);
 test=getblk(2,10);

 printf("\t\t output   %d %d\n",test->blk_no,test->test);
 
 test=getblk(3,10);
 printf("output   %d %d\n",test->blk_no,test->test);
 //test->status=0;
 test=getblk(2,10);
 printf("output   %d %d\n",test->blk_no,test->test);

 display(bfreelist);

 getch();
return 0;
}