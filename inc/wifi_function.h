#ifndef __WIFI_FUNCTION_H
#define	__WIFI_FUNCTION_H 

#include <stdint.h>
#ifdef STM32F103xB
#include <stm32f1xx_hal.h>
#else
#include <stm32f0xx_hal.h>
#endif
#include "wifi_config.h"
#include <stdbool.h>
#include "usart.h"


#define     ESP8266_Usart( fmt, ... )           USART2_printf (fmt, ##__VA_ARGS__ ) 


//#define     ESP8266_CH_HIGH_LEVEL()             GPIO_SetBits( GPIOC, GPIO_Pin_0 )
#define     ESP8266_CH_HIGH_LEVEL()		HAL_GPIO_WritePin(GPIOC, 0, GPIO_PIN_SET);
//#define     ESP8266_CH_LOW_LEVEL()              GPIO_ResetBits( GPIOC, GPIO_Pin_0 )
#define     ESP8266_CH_LOW_LEVEL()              HAL_GPIO_WritePin(GPIOC, 0, GPIO_PIN_RESET);

//#define     ESP8266_RST_HIGH_LEVEL()            GPIO_SetBits( GPIOC, GPIO_Pin_1 )
#define     ESP8266_RST_HIGH_LEVEL()            HAL_GPIO_WritePin(GPIOC, 1, GPIO_PIN_SET);
//#define     ESP8266_RST_LOW_LEVEL()             GPIO_ResetBits( GPIOC, GPIO_Pin_1 )
#define     ESP8266_RST_LOW_LEVEL()            HAL_GPIO_WritePin(GPIOC, 1, GPIO_PIN_RESET);

//#define     ESP8266_GPIO0_HIGH_LEVEL()            GPIO_SetBits( GPIOC, GPIO_Pin_2 )
#define     ESP8266_GPIO0_HIGH_LEVEL()            HAL_GPIO_WritePin(GPIOC, 2, GPIO_PIN_SET);
//#define     ESP8266_GPIO0_LOW_LEVEL()             GPIO_ResetBits( GPIOC, GPIO_Pin_2 )
#define     ESP8266_GPIO0_LOW_LEVEL()            HAL_GPIO_WritePin(GPIOC, 2, GPIO_PIN_RESET);

void        ESP8266_Choose                      ( FunctionalState enumChoose );
void        ESP8266_Rst                         ( void );
void        ESP8266_AT_Test                     ( void );
bool        ESP8266_Cmd                         ( char * cmd, char * reply1, char * reply2, uint32_t waittime );
bool        ESP8266_Net_Mode_Choose             ( ENUM_Net_ModeTypeDef enumMode );
bool        ESP8266_JoinAP                      ( char * pSSID, char * pPassWord );
bool        ESP8266_BuildAP                     ( char * pSSID, char * pPassWord, char * enunPsdMode );
bool        ESP8266_Enable_MultipleId           ( FunctionalState enumEnUnvarnishTx );
bool        ESP8266_Link_Server                 ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id);
bool        ESP8266_Cmd_link                    ( char * cmd, char * reply1, char * reply2,char *reply3, uint32_t waittime );
bool        ESP8266_UnLink_Server               (void);
bool        ESP8266_StartOrShutServer           ( FunctionalState enumMode, char * pPortNum, char * pTimeOver );
bool        ESP8266_UnvarnishSend               ( void );
bool        ESP8266_SendString                  ( FunctionalState enumEnUnvarnishTx, char * pStr, uint32_t ulStrLength, ENUM_ID_NO_TypeDef ucId );
char *      ESP8266_ReceiveString               ( FunctionalState enumEnUnvarnishTx );

void        ESP8266_init                       ( void );
void        Web_To_ESP                          (void);
void        login                                (uint8_t);
void        logout                               (uint8_t);


#endif    /* __WIFI_FUNCTION_H */





