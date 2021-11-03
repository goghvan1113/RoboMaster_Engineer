#ifndef __DATA_FIFO_H__
#define __DATA_FIFO_H__
#include "sys.h"

#define ASSERT(x) do {while(!(x));} while(0)

typedef struct
{
    uint8_t   *start_addr;                   //开始地址
    uint8_t   *end_addr;                     //结束地址
    uint32_t  free;                         //fifo剩余空间大小
    uint32_t  buf_size;                     //fifo大小
    uint32_t  used;                         //fifo已经使用字节数
    uint32_t   read_index;                   //读偏移量
    uint32_t   write_index;                  //写偏移量
} fifo_s_t;


fifo_s_t* fifo_s_create(uint32_t unit_cnt);
void     fifo_s_destory(fifo_s_t* pfifo);
int32_t fifo_s_put(fifo_s_t* pfifo, uint8_t element);
int32_t fifo_s_puts(fifo_s_t *pfifo, uint8_t *psource, uint32_t number);

uint8_t  fifo_s_get(fifo_s_t* pfifo);
uint16_t fifo_s_gets(fifo_s_t* pfifo, uint8_t* source, uint16_t len);

uint16_t fifo_s_Finds(fifo_s_t* pfifo, uint8_t* source, uint16_t len);
uint16_t fifo_s_FakeReads(fifo_s_t* pfifo, uint16_t len);

uint8_t  fifo_s_pre_read(fifo_s_t* pfifo, uint8_t offset);
uint8_t  fifo_is_empty(fifo_s_t* pfifo);
uint8_t  fifo_is_full(fifo_s_t* pfifo);
uint32_t fifo_used_count(fifo_s_t* pfifo);
uint32_t fifo_free_count(fifo_s_t* pfifo);
uint8_t  fifo_flush(fifo_s_t* pfifo);
int32_t fifo_s_init(fifo_s_t* pfifo, void* base_addr, uint32_t unit_cnt);


void clear_half_fifo(fifo_s_t* pfifo);


#endif












