///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Emulating the code for the Emulating the getblk algorithm 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//header file inclusions
#include"buf.h"
#include<stdio.h>

extern BUF_H *bfreelist,*hashque[5];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name			:		inhash 
//	Function Description	:		Check if the required buffer is in hasqueue or not 
//	Function Parameters		:		int , int
//	Function Returns		:		address of it else return 0
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BUF_H* inhash(int dev,int blkno)
{  
	BUF_H *tmp= hashque[dev];
    if(tmp==NULL)
		return 0;
    for(tmp= hashque[dev] ; tmp->hash_next!=hashque[dev] ; tmp=tmp->hash_next)
	    {
			if(tmp->blk_no == blkno && tmp->dev_no == dev)
				return tmp;
        }
	if(tmp->blk_no == blkno && tmp->dev_no == dev)
		  return tmp;
     
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name			:		getblk 
//	Function Description	:		Request the buffer 
//	Function Parameters		:		int , int
//	Function Returns		:		buffer pointer of the available buffer	otherwise 0
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BUF_H* getblk(int dev,int blkno)
{    
	BUF_H *bp=NULL;

	 int oldhashq;
	 dev=(dev%4)+1;
	while(1)
	{
		bp=inhash(dev,blkno);
		if(bp!=0)//buffer is in hash queue else not
		{
			if(bp->status & B_BUSY)//buffer is lock 
			{
				printf("\n(%d,%d)buffer is busy",dev,blkno);
				//continue;
				break;
			} 
			else
			{ 
				bp->status = bp->status | B_BUSY;    // locking buffer
				//code to break from free
                if(bp->free_next==bp && bp->free_prev==bp)
				{
					bfreelist=NULL;
					printf("!!");
				}
				else
				{
					bp->free_prev->free_next = bp->free_next;
				    bp->free_next->free_prev = bp->free_prev;
				    bfreelist=bp->free_next;  //remove comment after brelese() coding
					       
				    bp->free_next=bp;
				    bp->free_prev=bp;
				}
				printf("\n(%d,%d)returning from hash que",dev,blkno);
				return(bp);
			}
		 }
		     //else part means buffer is not in hash queue
		 {
			bp=bfreelist;
			if(bfreelist==NULL)
			{
				printf("\nempty free list");
				//continue;
				return NULL;
			 }
			if(bp->status & B_DWRITE)
			{
				printf("\ndeayed write ");
				//continue;
				break;
			}
		          
			//procedure to return buffer
			
			oldhashq=bp->dev_no;

			bp->status |= B_BUSY;
			bp->dev_no=dev;
			bp->blk_no=blkno;
			
				//display(bp);
			//remove from free list
			if(bp->free_next==bp && bp->free_prev==bp)
			{
				bfreelist=NULL;
				printf("!");
			}
			else
			{
				bp->free_prev->free_next = bp->free_next;
				bp->free_next->free_prev = bp->free_prev;
					  
				bfreelist=bp->free_next;
							//    display(bp);
				bp->free_next=bp;
				bp->free_prev=bp;
			}
			//from old hash to new hash
			
			if(bp->hash_next==bp && bp->hash_prev==bp)
			{   
				  printf("\n -------    - - - %d",oldhashq);
				hashque[oldhashq]=NULL;      
			}
			
			else{
			bp->hash_prev->hash_next = bp->hash_next;
			bp->hash_next->hash_prev = bp->hash_prev;
			}
			
			if(hashque[dev] == NULL)
			{
				hashque[dev]=bp;
				bp->hash_next=bp;//hashque[dev];
				bp->hash_prev= bp; //hashque[dev];
			}

			else
			{
				bp->hash_next=hashque[dev];
				bp->hash_prev= hashque[dev]->hash_prev;

				hashque[dev]->hash_prev=bp;
				bp->hash_prev->hash_next = bp;

				hashque[dev]=bp;

				hashque[dev]=bp;
			}
			
			
			printf("\nreturnig from freelist ");
			return(bp);


		}
	  }//end of while
   }