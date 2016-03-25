#ifndef __MALLOC_H
#define __MALLOC_H
//#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>
  
#ifndef NULL
#define NULL 0
#endif

#define MEM_BLOCK_SIZE			  32  	  					          //�ڴ���СΪ32�ֽ�
#define MEM_MAX_SIZE			        2*1024  						        //�������ڴ� 2K
#define MEM_ALLOC_TABLE_SIZE	MEM_MAX_SIZE/MEM_BLOCK_SIZE //�ڴ���С
		 
//�ڴ���������
struct _m_mallco_dev
{
	void (*init)(void);					//��ʼ��
	uint8_t   (*perused)(void);		  	    	//�ڴ�ʹ����
	uint8_t 	  *membase;					//�ڴ��
	uint16_t   *memmap; 					//�ڴ����״̬��
	uint8_t     memrdy; 						//�ڴ�����Ƿ����
};

extern struct _m_mallco_dev mallco_dev;	 //��mallco.c���涨��

void memSet(void *s,uint8_t c,uint32_t count);	 //�����ڴ�
void memCpy(void *des,void *src,uint32_t n);//�����ڴ� 

void memInit(void);					 //�ڴ�����ʼ������
uint32_t memMalloc(uint32_t size);		 //�ڴ����
uint8_t memFree(uint32_t offset);		 //�ڴ��ͷ�
uint8_t memPerused(void);				 //����ڴ�ʹ���� 
////////////////////////////////////////////////////////////////////////////////
//�û����ú���
void cJsonFree(void *ptr);  			//�ڴ��ͷ�
void *cJsonMalloc(uint32_t size);			//�ڴ����
void *cJsonRealloc(void *ptr,uint32_t size);//���·����ڴ�
#endif














