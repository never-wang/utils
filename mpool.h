/****************************************************************************
 *       Filename:  mpool.h
 *
 *    Description:  special memory pool for client
 *
 *        Version:  1.0
 *        Created:  04/11/2012 11:06:43 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wang Wencan 
 *	    Email:  never.wencan@gmail.com
 *        Company:  HPC Tsinghua
 ***************************************************************************/
#ifndef _MPOOL_H
#define _MPOOL_H

#include "stdint.h"

#define MPOOL_ERROR_NONE    0    /* no error */

#define MPOOL_MAGIC 0xABCDABCD
#define BLOCK_MAGIC 0x12341234

#define FENCE_SIZE 1
#define FENCE_MAGIC 0xEF

#define PAGES_OF_SIZE(mpool_p, size)	(((size) + sizeof(mpool_block_t) + \
					(mpool_p)->page_size - 1) / \
					(mpool_p)->page_size)
#define SIZE_OF_PAGES(mpool_p, page_c) ((page_c) * (mpool_p)->page_size)

#define SET_ERROR(error_p, val)	\
	do { \
	    if(NULL != (error_p)) { \
		(*(error_p)) = (val); \
	    }} while(0)

typedef struct 
{
    unsigned int    magic;	/* magic number fo struct */
    unsigned long   alloc_c;
    unsigned long   user_alloc;
    unsigned long   max_alloc_c;
    unsigned long   page_c;
    unsigned int    max_page_c;
    size_t	    page_size;
    mpool_block_t   *first_p;
    mpool_block_t   *last_p;
    mpool_block_t   *free[MAX_BITS + 1];
    unsigned int    magic2;	/* upper magic */
} mpool_t;

typdef struct
{
    unsigned int    magic;
    void	    *bound_p;
    mpool_block_t   *next_p;
    unsigned int    magic2;
} mpool_block_t;
/**
 * @brief: allocate a new memory pool
 *
 * @param page_size: Set the memory page size, this must be a multiple of the 
 *	getpagesize() value.
 * @param pool_size: the memory pool's init space size , this must be a multiple of 
 *	page_size
 * @param mpool: pointer to the  allocated memory pool
 *
 * @return: MPOOL_SUCCESS if success
 */
int mpool_open(const size_t page_size, const size_t pool_size, mpool_t **mpool);

/**
 * @brief: free a memory pool
 *
 * @param mpool: pointer to the memory pool
 *
 * @return: MPOOL_SUCCESS if success
 */
int mpool_close(mpool_t *mpool);

/**
 * @brief: allocte space in a memory pool
 *
 * @param mpool: pointer to the memory pool
 * @param size: number of bytes to allocte
 *
 * @return: error code, MPOOL_SUCCESS if success
 */
int mpool_malloc(mpool_t *mpool, const size_t size);

/**
 * @brief: allocate a block of memory for an array of num elements int the memory pool 
 *	, each of them size bytes long and zero the space
 *
 * @param mpool: pointer to the memory pool
 * @param num: number of elments to allocate
 * @param size: size of each elements
 *
 * @return: error code, MPOOL_SUCCESS if sucess
 */
int mpool_calloc(mpool_t *mpool, const size_t num, const size_t size);

/**
 * @brief: the size of the memory block pointed to by the addr is changed to the size 
 *	bytes
 *
 * @param mpool: pointer to the memory pool
 * @param addr: pointer to the resize memroy block, if addr is NULL, a new block is 
 *	allocated
 * @param size: new size for the memory block
 *
 * @return: error code, MPOOL_SUCCESS if success 
 */
int mpool_realloc(mpoo_t *mpool, void *addr, const size_t size);
/**
 * @brief: free a memory block
 *
 * @param mpool: pointer to the memory pool
 * @param addr: the memory block to free
 *
 * @return: error code, MPOOL_SUCCESS if success
 */
int mpool_free(mpool_t *mpool, void *addr);
#endif
