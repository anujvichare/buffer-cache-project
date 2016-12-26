///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//header fille inclusions
#include<stdio.h>
#include"buf.h"

extern BUF_H *bfreelist,*hashque[5];
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name			:		main 
//	Function Description	:		Entry point function 
//	Function Parameters		:		int , char *
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int no;
	BUF_H *test,*test1,*test2,*test3,*test4;
	printf("enter no of buffers u want \t");
	scanf("%d",&no);
	createPool(&bfreelist,no);
	printf("displaying free buffers"); 
	display(bfreelist);
 /*display1(hashque[0]);


 test=getblk(2,10);
 printf("\n first getblk(2,10)\n");
 printf("hashqqueue[2] :");
 display1(hashque[2]);
 printf("\t\t output   %d %d\n",test->blk_no,test->test);
 //test->status=0; //changing status to not busy
 brelese(test);

 test=getblk(3,10);
  printf("\n first getblk(3,10)\n");
 printf("hashqqueue[3] :");
 display1(hashque[3]);
 printf("\noutput   %d %d\n",test->blk_no,test->test);

 
 test1=getblk(2,10);

 test=getblk(2,11);

 test=getblk(2,10);

 
 test=getblk(2,11);
 display1(hashque[2]);
 test=getblk(2,2);
 test=getblk(2,4);
 test1->status=2;
 test=getblk(0,5);
// printf("\nlast %d",test->test);
// test->status=2;
 brelese(test1);
 //test=getblk(1,5);
// printf("\n..last %d",test->test);
//test->status=4;
brelese(test);*/


	test=getblk(4,12); 
	display(bfreelist);

	test1=getblk(3,12);
	display(bfreelist);
 
	test2=getblk(4,45);
	test2->status |= B_DWRITE;
	display(bfreelist);

	test4=getblk(2,5);
	brelese(test2);
	display(bfreelist);
 
	test3=getblk(4,45);
	display(bfreelist);

	test1->status=4;
	brelese(test1);

	printf("\n\nhash ques :\n");
	display1(hashque[0]);
	display1(hashque[1]);
	display1(hashque[2]);
	display1(hashque[3]);
	display1(hashque[4]);
	display(bfreelist);

	test=getblk(1,14);

	test=getblk(4,50);
	test=getblk(1,50);
	test=getblk(1,40);
	printf("\n\n--------\n\nhash ques :\n");
	display1(hashque[0]);
	display1(hashque[1]);
	display1(hashque[2]);
	display1(hashque[3]);
	display1(hashque[4]);

	printf("\n\n buffers in free list are: \n");
	display(bfreelist);

	return 0;
}
