#ifndef __MALLOC_H
#define __MALLOC_H
//#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>
  
#ifndef NULL
#define NULL 0
#endif

#define MEM_BLOCK_SIZE			  32  	  					          //内存块大小为32字节
#define MEM_MAX_SIZE			        2*1024  						        //最大管理内存 2K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE //内存表大小
		 
//内存管理控制器
struct _m_mallco_dev
{
	void (*init)(void);					//初始化
	uint8_t   (*perused)(void);		  	    	//内存使用率
	uint8_t 	  *membase;					//内存池
	uint16_t   *memmap; 					//内存管理状态表
	uint8_t     memrdy; 						//内存管理是否就绪
};

extern struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义

void memSet(void *s,uint8_t c,uint32_t count);	 //设置内存
void memCpy(void *des,void *src,uint32_t n);//复制内存 

void memInit(void);					 //内存管理初始化函数
uint32_t memMalloc(uint32_t size);		 //内存分配
uint8_t memFree(uint32_t offset);		 //内存释放
uint8_t memPerused(void);				 //获得内存使用率 
////////////////////////////////////////////////////////////////////////////////
//用户调用函数
void cJsonFree(void *ptr);  			//内存释放
void *cJsonMalloc(uint32_t size);			//内存分配
void *cJsonRealloc(void *ptr,uint32_t size);//重新分配内存
#endif














