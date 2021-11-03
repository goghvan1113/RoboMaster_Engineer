#include "data_fifo.h"
#include "stdlib.h"
#include "stdio.h"


//给定地址、空间和大小，将其初始化为一个fifo
int32_t fifo_s_init(fifo_s_t* pfifo, void* base_addr, uint32_t unit_cnt)
{
    //! 检查输入形参
    ASSERT(NULL != pfifo);
    ASSERT(NULL != base_addr);
    ASSERT(0 != unit_cnt);

    //! 初始化fifo
    pfifo->start_addr = (uint8_t*)base_addr;
    pfifo->end_addr = (uint8_t*)base_addr + unit_cnt - 1;
    pfifo->buf_size = unit_cnt;
    pfifo->free = unit_cnt;
    pfifo->used = 0;
    pfifo->read_index = 0;
    pfifo->write_index = 0;

    return 0;

}
/*
* 创建一个fifo，形参是fifo的深度，fifo宽度是固定的8位
* 返回值是一个创建好的fifo结构体地址
*/

fifo_s_t* fifo_s_create(uint32_t unit_cnt)
{
    fifo_s_t *pfifo = NULL;
    uint8_t  *base_addr = NULL;

    //输入不能是0
    ASSERT(0 != unit_cnt);

    //申请地址，如果不是stm32芯片内部的存储空间，需自己再实现malloc
    pfifo = (fifo_s_t*)malloc(sizeof(fifo_s_t));
    if (NULL == pfifo)
    {
        //申请出错，退出
        return (NULL);
    }

    //申请fifo空间
    base_addr = malloc(unit_cnt);
    if (NULL == base_addr)
    {
				free(pfifo);
        //出错
        return (NULL);
    }

    fifo_s_init(pfifo, base_addr, unit_cnt);

    return (pfifo);
}

/*
* 释放一块fifo的空间
*/
void fifo_s_destory(fifo_s_t* pfifo)
{
    //输入不能是0
    ASSERT(NULL != pfifo);
    ASSERT(NULL != pfifo->start_addr);

    //释放fifo空间
    free(pfifo->start_addr);


    //释放fifo控制结构体
    free(pfifo);

    return;
}

/*
* 向fifo里面放1个字节数据
* 返回值-1表示FIFO满了
*/
int32_t fifo_s_put(fifo_s_t* pfifo, uint8_t element)
{
    //检查输入
    ASSERT(NULL != pfifo);

    if (0 >= pfifo->free)
    {
        //出错，fifo满了，返回-1
        return -1;
    }

    pfifo->start_addr[pfifo->write_index++] = element;
    pfifo->write_index %= pfifo->buf_size;
    pfifo->free--;
    pfifo->used++;

    return 0;
}

/*
* 向fifo里面放number个字节数据
* 返回值表示实际放进去了多少个
*/
int32_t fifo_s_puts(fifo_s_t *pfifo, uint8_t *psource, uint32_t number)
{
    int puts_num = 0;
	uint32_t i = 0;

    //输入不能是空
    ASSERT(NULL != pfifo);

    if (psource == NULL)
        return -1;

    for(; (i < number) && (pfifo->free > 0); i++)
    {
        pfifo->start_addr[pfifo->write_index++] = psource[i];
        pfifo->write_index %= pfifo->buf_size;
        pfifo->free--;
        pfifo->used++;
        puts_num++;
    }
    return puts_num;
}

/*
* 从fifo里面读1个字节数据
* 返回值表示读到的数据
*/
uint8_t fifo_s_get(fifo_s_t* pfifo)
{
    uint8_t   retval = 0;

    //检查输入
    ASSERT(NULL != pfifo);

    retval = pfifo->start_addr[pfifo->read_index++];
    pfifo->read_index %= pfifo->buf_size;
    pfifo->free++;
    pfifo->used--;

    return retval;
}

/*
* 从fifo里面读len个字节数据
* 返回值表示实际读了多少个
*/
uint16_t fifo_s_gets(fifo_s_t* pfifo, uint8_t* source, uint16_t len)
{
    uint16_t retval = 0;
	uint16_t i = 0;

    //检查输入
    ASSERT(NULL != pfifo);

    for(; (i < len) && (pfifo->used > 0); i++)
    {
        source[i] = pfifo->start_addr[pfifo->read_index++];
        pfifo->read_index %= pfifo->buf_size;
        pfifo->free++;
        pfifo->used--;
        retval++;
    }

    return retval;
}

/*
* 从fifo里面查找下面几个字节的数据，但不读出
* 返回值表示实际查找了多少个
*/

uint16_t fifo_s_Finds(fifo_s_t* pfifo, uint8_t* source, uint16_t len)
{
  uint16_t retval = 0;
	uint16_t i = 0;
	uint16_t ReadIndex_Temp = 0;
	uint16_t Used_Temp = 0;
	
    //检查输入
    ASSERT(NULL != pfifo);
	
	Used_Temp = pfifo->used;
	ReadIndex_Temp = pfifo->read_index;

    for(; (i < len) && (Used_Temp > 0); i++)
    {
        source[i] = pfifo->start_addr[ReadIndex_Temp++];
		ReadIndex_Temp %= pfifo->buf_size;
        Used_Temp--;
        retval++;
    }

    return retval;
}

/*
* 从fifo里面查找下面几个字节的数据，但不读出后，发现查找的数据是需要读的，直接设置读出即可。虚假读
* 返回值表示实际查找了多少个
*/

uint16_t fifo_s_FakeReads(fifo_s_t* pfifo, uint16_t len)
{

    //检查输入
    ASSERT(NULL != pfifo);
	
	if(len > pfifo->used)
		len = pfifo->used;
	
	pfifo->read_index += len;
	pfifo->read_index %= pfifo->buf_size;
	pfifo->free += len;
	pfifo->used -= len;

    return len;
}


/******************************************************************************************
//
//! \brief  准备从fifo里读一个元素
//!
//! \param  [in]  pfifo是fifo指针
//! \param  [in]  offset是fifo中要读的偏移地址
//!
//! \retval 读出的内容
//
******************************************************************************************/
uint8_t fifo_s_pre_read(fifo_s_t* pfifo, uint8_t offset)
{
    uint32_t index;

    //检查输入
    ASSERT(NULL != pfifo);

    if (offset > pfifo->used)
    {
        return 0x00;
    }
    else
    {
        index = ((pfifo->read_index + offset) % pfifo->buf_size);
        //把读指针移到对应地址
        return pfifo->start_addr[index];
    }
}


/******************************************************************************************
//!
//! \retval 返回非0表示空
//!         返回0表示非空
//
******************************************************************************************/
uint8_t fifo_is_empty(fifo_s_t* pfifo)
{
    ASSERT(NULL != pfifo);

    return (0 == pfifo->used);
}

/*****************************************************************************************
//!
//! \retval 返回非0表示满了
//!         返回0表示没满
//
*****************************************************************************************/
uint8_t fifo_is_full(fifo_s_t* pfifo)
{
    //检查输入
    ASSERT(NULL != pfifo);

    return (0 == pfifo->free);
}

/******************************************************************************************
//!
//! \retval fifo中已经放了多少字节
//
******************************************************************************************/
uint32_t fifo_used_count(fifo_s_t* pfifo)
{
    //检查输入
    ASSERT(NULL != pfifo);

    return (pfifo->used);
}

/******************************************************************************************
//!
//! \retval fifo中还剩多少字节
//
******************************************************************************************/
uint32_t fifo_free_count(fifo_s_t* pfifo)
{
    //检查输入
    ASSERT(NULL != pfifo);

    return (pfifo->free);
}


/******************************************************************************************
//
//! \brief  清空fifo
//!
//! \param  输入要清空的fifo指针
//!
//! \retval 0是成功清除，-1是出错
//
******************************************************************************************/
uint8_t fifo_flush(fifo_s_t* pfifo)
{
    //检查输出
    ASSERT(NULL != pfifo);

    //初始化fifo
    pfifo->free = pfifo->buf_size;
    pfifo->used = 0;
    pfifo->read_index = 0;
    pfifo->write_index = 0;

    return 0;
}

void clear_half_fifo(fifo_s_t* pfifo){
    //检查输入  
    uint8_t num;;
	
	ASSERT(NULL != pfifo);
	
	num = pfifo->buf_size /2;
	
    if(num >= pfifo->used)
		return;
    pfifo->read_index += num;
    pfifo->read_index %= pfifo->buf_size;
    pfifo->used -= num;
    pfifo->free += num;
}









