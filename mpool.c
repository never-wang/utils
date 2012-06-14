/****************************************************************************
 *       Filename:  mpool.c
 *
 *    Description: special memory pool for client
 *
 *        Version:  1.0
 *        Created:  04/11/2012 01:45:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wang Wencan 
 *	    Email:  never.wencan@gmail.com
 *        Company:  HPC Tsinghua
 ***************************************************************************/
#include "mpool.h"

static int size_to_bit(size_t size)
{
    size_t cur_size = 2;
    int i;

    for(i = 1; i <= MAX_BITS; i++)
    {
	if(cur_size >= size)
	{
	    break;
	}
	cur_size = cur_size << 1;
    }

    return i;
}

static int split_block(mpool_t *mp_p, void *free_addr, const size_t size)
{
    mpool_block_t *block_p;

    block_p = (mpool_block_t *)((char *)free_addr - sizeof(mpool_block_t));

    if(block_p->magic != BLOCK_MAGIC || blcok_p->magic2 != BLOCK_MAGIC)
    {
	return - MPOOL_ERROR_POOL_OVER;
    }
}

static void *get_space(mpool_t *mp_p, const size_t space_size, int *error_p)
{
    size_t size;
    void *free_addr = NULL;

    size = space_size;

    for(i = size_to_bit(; i <= MAX_BITS; i ++)
    {
	if(
    }
    
}

static void *alloc_mem(mpool_t *mp_p, const size_t size, int *error_p)
{
    void *addr;

    addr = get_sapce(mp_p, size + FENCE_SIZE, error_p);

    if(NULL == addr)
    {
	return NULL;
    }

    *((char *)addr + size) = FENCE_MAGIC;

    SET_ERROR(error_p, MPOOL_ERROR_NONE);
}

int mpool_open(const size_t page_size, const size_t pool_size, mpool_t **mpool)
{
    mpool_t mpool;

    memset(&mpool, 0, sizeof(mpool_t));

    mp.magic = MPOOL_MAGIC;
    mp.alloc_c = 0;
    mp.user_allloc = 0;
    mp.max_alloc_c = 0;
    mp.mp_page_c = 0;
    mp.first_p = NULL;
    mp.last_p = NULL;
    mp.magic2 = MPOOL_MAGIC;

    if(page_size > 0)
    {
	if(page_size % getpagesize() != 0)
	{
	    return - MPOOL_ERROR_ARG_INVAILD;
	}
	mp.page_size = page_size;
    }else
    {
	mp.page_size = getpagesize() * DEFAULT_PAGE_MULT;
    }

    page_n = PAGES_OF_SIZE(&mp, sizeof(mpool_t));
    mp_p = alloc_pages(&mp, page_n);
    
    memcpy(mpool_p, &mpool, sizeof(mpool_t));

    return MPOOL_SUCCESS;
}
int mpool_close(mpool_t *mpool);
void *mpool_malloc(mpool_t *mp_p, const size_t size)
{
    void addr;

    if(NULL = mp_p)
    {
	addr = malloc(size);
	if(NULL == addr)
	{
	    return NULL;
	}
	return addr;
    }

    if(mp_p->magic != MPOOL_MAGIC)
    {
	return NULL;
    }

    if(mp_p->magic2 != MPOOL_MAGIC)
    {
	return NULL;
    }

    if(0 == size)
    {
	return NULL;
    }

    addr = alloc_mem(mp_p, size);

    return addr;
}
int mpool_calloc(mpool_t *mpool, const size_t num, const size_t size);
int mpool_realloc(mpoo_t *mpool, void *addr, const size_t size);
int mpool_free(mpool_t *mpool, void *addr);
