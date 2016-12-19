#include<stdio.h>
//#include<string.h>
#include"buf.h"

 BUF_H *bfreelist=NULL,*hashque[5]={NULL,NULL,NULL,NULL,NULL};
//////////////////////////////////////////////////////////////////////
//
//
//  name: createPool
//
//  input: address of head, total buffers 
//
/// return: void
//
//
///////////////////////////////////////////////////////////////////////

void createPool(BUF_H **first, int size)
{
  int i; BUF_H *temp=NULL;
  for(i=0;i<size;i++)
 {  //creation of new buffer
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
  hashque[0]=bfreelist;
}// createPool


void display(BUF_H *first)
{
 BUF_H  *tmp=NULL;
 tmp=first;

 if(first==NULL)
   {
     printf("\n no bufferpool created \n");
    return;
   }

  while(tmp->free_next!= first)
  {
    printf("\n %d",tmp->test);
    tmp=tmp->free_next;
   }
  printf("\n %d",tmp->test);
}




