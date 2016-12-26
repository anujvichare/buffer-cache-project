/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		Custom Header-file
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Global structure of the buffer
typedef struct buf_samp
{
  char dev_no;
  int blk_no;
  int status;
  char *ptr_to_buf;
  struct buf_samp *free_next;
  struct buf_samp *free_prev;
  struct buf_samp *hash_next;
  struct buf_samp *hash_prev;

  int test;
}BUF_H;


//MACRO

//status signals
#define B_BUSY 1
#define B_DWRITE 2
#define B_OLD 4



//buffer status
/*
 BUF_H *bfreelist=NULL,*hashque[5]={NULL,NULL,NULL,NULL,NULL};

#ifdef BUF_H *bfreelist
     extern BUF_H *bfreelist=NULL,*hashque[5]={NULL,NULL,NULL,NULL,NULL};
#endif
	 */

//function Prototype
void createPool(BUF_H **,int);
void display(BUF_H *);
void display1(BUF_H *);

BUF_H* getblk(int,int);
void brelese(BUF_H *);