/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Code Related to the Buffer Initialization
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//header file inclusions
#include<stdio.h>
#include<malloc.h>
#include"buf.h"	//custom header file


BUF_H *bfreelist=NULL,*hashque[5]={NULL};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function Name			:	createPool
//	Function Parameters		:	address of head, total buffers 
//	Function Return			:	void	(Returns Nothing)
//	Function Description	:	Emulates the working of the binit
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void createPool(BUF_H **first, int size)
{
  register int i; 
  BUF_H *temp=NULL;

  for(i=0;i<size;i++)
  {  
	//creation of new buffer
	BUF_H *newBuf=NULL;
	newBuf=(BUF_H *)calloc(sizeof(BUF_H),1);
	if(newBuf==NULL)
	{
		printf("unable to create buffer pool");
		return;
	}
	newBuf->ptr_to_buf=(char *)malloc(sizeof(char)*10);
	newBuf->ptr_to_buf="data";
	newBuf->test=i;
   
	/*add new buffeer to free list and in hashque */
	if(*first==NULL)
	{ // printf("\n%d in if",i);
		*first=newBuf;
		temp=newBuf;

		newBuf->free_next=newBuf;
		newBuf->free_prev=newBuf;
		 
		newBuf->hash_next = newBuf;
		newBuf->hash_prev = newBuf;
	}
	else
	{
		temp->free_next=newBuf;
		newBuf->free_next = *first;
		newBuf->free_prev = temp;
		(*first)->free_prev = newBuf;

		temp->hash_next= newBuf;
		newBuf->hash_prev = temp;
		newBuf->hash_next=*first;
		(*first)->hash_prev= newBuf;

		temp=temp->free_next;
  
	}
 }//for
  //hashque[0]=bfreelist;
}// createPool


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function Name			:	display
//	Function Parameters		:	address of head 
//	Function Return			:	void	(Returns Nothing)
//	Function Description	:	Displays freelist
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display(BUF_H *first)
{
	BUF_H  *tmp=NULL;
	tmp=first;
	
	if(first==NULL)
	{
		printf("\n no free buffers \n");
		return;
	}

	while(tmp->free_next!= first)
	{
		printf("   %d",tmp->test);
		tmp=tmp->free_next;
	}
	printf("    %d \n",tmp->test);
	tmp=NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function Name			:	display1
//	Function Parameters		:	address of head 
//	Function Return			:	void	(Returns Nothing)
//	Function Description	:	Displays hashqueue
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void display1(BUF_H *first)
{
	BUF_H  *tmp=NULL;
	tmp=first;

	if(first==NULL)
	{
		printf("\nempty queue\n");
		return;
	}

	while(tmp->hash_next!= first)
	{
		printf("   %d",tmp->test);
		tmp=tmp->hash_next;
	}
	printf("    %d \n",tmp->test);
	tmp=NULL;
}