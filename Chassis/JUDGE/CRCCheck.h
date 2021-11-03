#ifndef __CRCCHECK_H__
#define __CRCCHECK_H__

#include "stm32f4xx.h"
#include "stdlib.h"

#define CRC8_INIT_NUM	0xff
#define CRC16_INIT_NUM  0xffff


uint8_t get_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength, uint8_t ucCRC8);
uint8_t verify_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength);
void append_crc8_check_sum(uint8_t* pchMessage, uint16_t dwLength);

uint16_t get_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength, uint16_t wCRC);
uint8_t verify_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength);
void append_crc16_check_sum(uint8_t* pchMessage, uint32_t dwLength);





#endif











