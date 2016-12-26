/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	All Code Related for emulating the working of the brelease Algorithm
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//header file inclution
#include"buf.h"
#include<stdio.h>

extern BUF_H *bfreelist,*hashque[5];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function Name			:	insert
//	Function Parameters		:	adress of the BUF_H structure 
//	Function Return			:	void	(Returns Nothing)
//	Function Description	:	Adding buffer to the free list 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert(BUF_H *bp)
{ 
	if(bfreelist==NULL)
	   bfreelist=bp;
    
	else
	{
	  bp->free_next=bfreelist;
	  bfreelist->free_prev->free_next=bp;
	  bp->free_prev=bfreelist->free_prev;
	  bfreelist->free_prev=bp;

	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Function Name			:	brelese
//	Function Parameters		:	adress of the BUF_H structure 
//	Function Return			:	void	(Returns Nothing)
//	Function Description	:	Emulates the actual working of the brelease of the algorithm. 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void brelese(BUF_H *bp)
{    
	if(bp==NULL)
		return;
	/*
     printf("\n waking up all the process.....");
	 printf("\n waking up all the process waiting for this buffer....");

	 printf("\n incresing cpu execution level to disk int");
	 */

	 if(bp->status & B_DWRITE)
	 {
		printf("\n --  insert at end");
		insert(bp);
	 }
	 else if(bp->status & B_OLD)
	 {
		printf("\n --  insert at start");
		insert(bp);
		bfreelist=bp; //insertion at the first
	 }

	 bp->status &= ~(B_BUSY | B_DWRITE | B_OLD);
}