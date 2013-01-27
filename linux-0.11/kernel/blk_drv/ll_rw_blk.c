/*
 *  linux/kernel/blk_dev/ll_rw.c
 *
 * (C) 1991 Linus Torvalds
 */

/*
 * This handles all read/write requests to block devices
 */
#include <errno.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <asm/system.h>

#include "blk.h"

/*
 * The request-struct contains all necessary data
 * to load a nr of sectors into memory
 */
struct request request[NR_REQUEST];

/*
 * used to wait on when there are no free requests
 */
struct task_struct * wait_for_request = NULL;

/* blk_dev_struct is:
 *	do_request-address
 *	next-request
 */
struct blk_dev_struct blk_dev[NR_BLK_DEV] = {
	{ NULL, NULL },		/* no_dev */
	{ NULL, NULL },		/* dev mem */
	{ NULL, NULL },		/* dev fd */
	{ NULL, NULL },		/* dev hd */
	{ NULL, NULL },		/* dev ttyx */
	{ NULL, NULL },		/* dev tty */
	{ NULL, NULL }		/* dev lp */
};

static inline void lock_buffer(struct buffer_head * bh)
{
	cli();
	while (bh->b_lock)
		sleep_on(&bh->b_wait);
	bh->b_lock=1;
	sti();
}

static inline void unlock_buffer(struct buffer_head * bh)
{
	if (!bh->b_lock)
		printk("ll_rw_block.c: buffer not locked\n\r");
	bh->b_lock = 0;
	wake_up(&bh->b_wait);
}

/*
 * add-request adds a request to the linked list.
 * It disables interrupts so that it can muck with the
 * request-lists in peace.
 */
static void add_request(struct blk_dev_struct * dev, struct request * req)
{
	struct request * tmp;

	req->next = NULL;
	cli();
	if (req->bh)
		req->bh->b_dirt = 0;
	if (!(tmp = dev->current_request)) {
		dev->current_request = req;
		sti();
		(dev->request_fn)();
		return;
	}
	for ( ; tmp->next ; tmp=tmp->next)
		if ((IN_ORDER(tmp,req) || 
		    !IN_ORDER(tmp,tmp->next)) &&
		    IN_ORDER(req,tmp->next))
			break;
	req->next=tmp->next;
	tmp->next=req;
	sti();
}

static void make_request(int major,int rw, struct buffer_head * bh)
{
	struct request * req;
	int rw_ahead;

/* WRITEA/READA is special case - it is not really needed, so if the */
/* buffer is locked, we just forget about it, else it's a normal read */
	if ((rw_ahead = (rw == READA || rw == WRITEA))) {
		if (bh->b_lock)
			return;
		if (rw == READA)
			rw = READ;
		else
			rw = WRITE;
	}
	if (rw!=READ && rw!=WRITE)
		panic("Bad block dev command, must be R/W/RA/WA");
	lock_buffer(bh);
	if ((rw == WRITE && !bh->b_dirt) || (rw == READ && bh->b_uptodate)) {
		unlock_buffer(bh);
		return;
	}
repeat:
/* we don't allow the write-requests to fill up the queue completely:
 * we want some room for reads: they take precedence. The last third
 * of the requests are only for reads.
 */
	if (rw == READ)
		req = request+NR_REQUEST;
	else
		req = request+((NR_REQUEST*2)/3);
/* find an empty request */
	while (--req >= request)
		if (req->dev<0)
			break;
/* if none found, sleep on new requests: check for rw_ahead */
	if (req < request) {
		if (rw_ahead) {
			unlock_buffer(bh);
			return;
		}
		sleep_on(&wait_for_request);
		goto repeat;
	}
/* fill up the request-info, and add it to the queue */
	req->dev = bh->b_dev;
	req->cmd = rw;
	req->errors=0;
	req->sector = bh->b_blocknr<<1;
	req->nr_sectors = 2;
	req->buffer = bh->b_data;
	req->waiting = NULL;
	req->bh = bh;
	req->next = NULL;
	add_request(major+blk_dev,req);
}

//
// Make request to block device. 
// No not execuate read/write operation directly!
//
void ll_rw_block(int rw, struct buffer_head * bh)
{
	unsigned int major;

	if ((major=MAJOR(bh->b_dev)) >= NR_BLK_DEV ||
	!(blk_dev[major].request_fn)) {
		printk("Trying to read nonexistent block-device\n\r");
		return;
	}
	make_request(major,rw,bh);
}
/**********************************************************************************
  Introduction to MINIX file system
  MINIX file system is same as standard Unix file system. It consist of six parts:
  
			logical block bitmap(corresponding data block)
				  |		  inode
     super block  |	   _____|_____
		  |		  |   |			  |	        
  ---------------------------------------------------------------------------------
  |	0	| 1	| 2	| 3	| 4	| 5	| 6	| 7	| 8	| 9	| 10 |11 | 12 | 13 |....|	|	|	|  |
  ---------------------------------------------------------------------------------
     |		  |						  |___________________________________________|
	 |		  |												|	
bootloader inode bitmap(corresponding inode)						data block

 super block : contain information of file system on block device
 logical block: is a common scheme used for	specifying the location of blocks of data
				LBA address can be mapped to CHS tuples with the following formula:
				C = LBA/(SPT*HPC)
				H = (LBA/SPT) % HPC
				S = (LBA%SPT) + 1 
				HPC : maximum number of heads per cylinder
				SPT : maximum number of sectors per track
				In MINIX file system , a logical block == 2* section(1K)
				In linux kernel, a logical block = 1 section (512 bytes)

 inode bitmap : To Zhiming the inodes which have been used
 logical block bitmap : To Zhuming the logical blocks that have been used.
 inode block: contain the inodes.

 What is the virtual file system?
 How to manage the buffer cache  in memory?


Q1: How to map inode to LBA?							|15--12|11---|8-------------0|
		|--short i_mode : file type and attribute(rwx)  | type |???? | file attribute|
		|--short i_uid  : user id
		|--long i_size	: file size
 inode--|--long i_mtime : time to be modified
		|--char i_gid	: group id
		|--char i_nlinks: link number	
		|--short i_zone[9] : data blocl occupied by this file.
							 i_zone[0]~i_zone[6] are direct zones
							 i_zone[7] is once indirect zone
							 i_zone[8] is twice indirect zone
							 (zone is an alias for block)
 
 ***********************************************************************************/

void blk_dev_init(void)
{
	int i;
	for (i=0 ; i<NR_REQUEST ; i++) {
		request[i].dev = -1;
		request[i].next = NULL;
	}
}





