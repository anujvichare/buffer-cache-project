
#include"buf.h"
#include<stdio.h>

extern BUF_H *bfreelist,*hashque[5];

/////////////////////////////////////////////
//
//   inhash() chakes for buffer in hash queue
//    if yes then return address of it else return 0
//
/////////////////////////////////////////////
BUF_H* inhash(int dev,int blkno)
{  BUF_H *tmp= hashque[dev];
    if(tmp==NULL)
		return 0;
for(tmp= hashque[dev] ; tmp->hash_next!=hashque[dev] ; tmp=tmp->hash_next)
	{if(tmp->blk_no==blkno && tmp->dev_no==dev)
		return tmp;
    }if(tmp->blk_no==blkno && tmp->dev_no==dev)
		return tmp;
     
	return 0;
}
BUF_H* getblk(int dev,int blkno)
	{
		BUF_H *bp=NULL;

		 while(1)
		 { bp=inhash(dev,blkno);
		   if(bp!=0)
			 {  if(bp->status == 1)
			   {
				    printf("buffer is busy");
					continue;
					//break;
			   } 
			     if(  bp->status==0)
					{ bp->status=1;
				   //code to break from free
				  bp->free_prev->free_next = bp->free_next;
				  bp->free_next->free_prev = bp->free_prev;

				  bp->free_next=bp;
				  bp->free_prev=bp;
				   printf("returning from hash que");
				    return(bp);
				 }
		     }
		     //else part means buffer is not in hash queue
		   {
		         bp=bfreelist;
				 
				  if(bfreelist==NULL)
					  {printf("empty free list");
				        continue;
				      }
				  if(bp->status==2)
				  {
				     printf("deayed write ");
					 continue;
				  }
		          
				   //procedure to return buffer

				  bp->status=1;
				  bp->dev_no=dev;
				  bp->blk_no=blkno;
				  display(bp);
				  //remove from free list
				  bp->free_prev->free_next = bp->free_next;
				  bp->free_next->free_prev = bp->free_prev;
				  
				  bp->free_next=bp;
				  bp->free_prev=bp;
				  
				  //from old hash to new hash

				  bp->hash_prev->hash_next = bp->hash_next;
				  bp->hash_next->hash_prev = bp->hash_prev;

				  if(hashque[dev]==NULL)
				  {
				    hashque[dev]=bp;
					bp->hash_next=hashque[dev];
				  bp->hash_prev= hashque[dev];
				  }
				  else{
				  bp->hash_next=hashque[dev];
				  bp->hash_prev= hashque[dev]->hash_prev;

				  hashque[dev]->hash_prev=bp;
				  bp=hashque[dev];

				  hashque[dev]=bp;
				  }
				  printf("returnig from freelist ");
				  return(bp);


		   }
	      }//while
     }