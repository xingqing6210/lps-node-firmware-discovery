#include "wifi_function.h"
#include "wifi_config.h"
//#include "bsp_SysTick.h"
#include <string.h> 
#include <stdio.h>  
#include <stdbool.h>
#include  <stdlib.h>



/*
 * ��������ESP8266_Choose
 * ����  ��ʹ��/����WF-ESP8266ģ��
 * ����  ��enumChoose = ENABLE��ʹ��ģ��
 *         enumChoose = DISABLE������ģ��
 * ����  : ��
 * ����  �����ⲿ����
 */
void ESP8266_Choose (FunctionalState enumChoose)
{
 if (enumChoose == ENABLE)
	ESP8266_CH_HIGH_LEVEL()
 else
	ESP8266_CH_LOW_LEVEL()	
}


/*
 * ��������ESP8266_Rst
 * ����  ������WF-ESP8266ģ��
 * ����  ����
 * ����  : ��
 * ����  ����ESP8266_AT_Test����
 */
void ESP8266_Rst ( void )
{
	#if 0
	 ESP8266_Cmd ( "AT+RST", "OK", "ready", 2500 );   	
	
	#else
	 ESP8266_RST_LOW_LEVEL();
	 HAL_Delay( 500 ); 
	 ESP8266_RST_HIGH_LEVEL();
	 
	#endif

}


/*
 * ��������ESP8266_AT_Test
 * ����  ����WF-ESP8266ģ�����AT��������
 * ����  ����
 * ����  : ��
 * ����  �����ⲿ����
 */
void ESP8266_AT_Test ( void )
{
	ESP8266_RST_HIGH_LEVEL();
	
	HAL_Delay( 1500 ); 
	
	while ( ! ESP8266_Cmd ( "AT", "OK", NULL, 200 ) ) ESP8266_Rst ();  	

}


/*
 * ��������ESP8266_Cmd
 * ����  ����WF-ESP8266ģ�鷢��ATָ��
 * ����  ��cmd�������͵�ָ��
 *         reply1��reply2���ڴ�����Ӧ��ΪNULL��������Ӧ������Ϊ���߼���ϵ
 *         waittime���ȴ���Ӧ��ʱ��
 * ����  : 1��ָ��ͳɹ�
 *         0��ָ���ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_Cmd ( char * cmd, char * reply1, char * reply2, uint32_t waittime )
{    
	strEsp8266_Fram_Record.InfBit .FramLength = 0;               //���¿�ʼ�����µ����ݰ�

	ESP8266_Usart ( "%s\r\n", cmd );

	if ( ( reply1 == 0 ) && ( reply2 == 0 ) )                      //����Ҫ��������
		return true;
	
	HAL_Delay( waittime );                 //��ʱ
	
	HAL_Delay( 1000 ); 
	
	strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ]  = '\0';

	printf ( "%s", strEsp8266_Fram_Record.Data_RX_BUF );
  
	if ( ( reply1 != 0 ) && ( reply2 != 0 ) )
		return ( ( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, reply1 ) || 
						 ( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, reply2 ) ); 
 	
	else if ( reply1 != 0 )
		return ( ( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, reply1 ) );
	
	else
		return ( ( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, reply2 ) );
	
}


/*
 * ��������ESP8266_Net_Mode_Choose
 * ����  ��ѡ��WF-ESP8266ģ��Ĺ���ģʽ
 * ����  ��enumMode������ģʽ
 * ����  : 1��ѡ��ɹ�
 *         0��ѡ��ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_Net_Mode_Choose ( ENUM_Net_ModeTypeDef enumMode )
{
	switch ( enumMode )
	{
		case STA:
			return ESP8266_Cmd ( "AT+CWMODE=1", "OK", "no change", 2500 ); 
		
	  case AP:
		  return ESP8266_Cmd ( "AT+CWMODE=2", "OK", "no change", 2500 ); 
		
		case STA_AP:
		  return ESP8266_Cmd ( "AT+CWMODE=3", "OK", "no change", 2500 ); 
		
	  default:
		  return false;
  }
	
}


/*
 * ��������ESP8266_JoinAP
 * ����  ��WF-ESP8266ģ�������ⲿWiFi
 * ����  ��pSSID��WiFi�����ַ���
 *       ��pPassWord��WiFi�����ַ���
 * ����  : 1�����ӳɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_JoinAP ( char * pSSID, char * pPassWord )
{
	char cCmd [120];

	sprintf ( cCmd, "AT+CWJAP=\"%s\",\"%s\"", pSSID, pPassWord );
	
	return ESP8266_Cmd ( cCmd, "OK", NULL, 7000 );
	
}


/*
 * ��������ESP8266_BuildAP
 * ����  ��WF-ESP8266ģ�鴴��WiFi�ȵ�
 * ����  ��pSSID��WiFi�����ַ���
 *       ��pPassWord��WiFi�����ַ���
 *       ��enunPsdMode��WiFi���ܷ�ʽ�����ַ���
 * ����  : 1�������ɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_BuildAP ( char * pSSID, char * pPassWord, char * enunPsdMode )
{
	char cCmd [120];

	sprintf ( cCmd, "AT+CWSAP=\"%s\",\"%s\",1,%s", pSSID, pPassWord, enunPsdMode );
	
	return ESP8266_Cmd ( cCmd, "OK", 0, 1000 );
	
}


/*
 * ��������ESP8266_Enable_MultipleId
 * ����  ��WF-ESP8266ģ������������
 * ����  ��enumEnUnvarnishTx�������Ƿ������
 * ����  : 1�����óɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_Enable_MultipleId ( FunctionalState enumEnUnvarnishTx )
{
	char cStr [20];
	
	sprintf ( cStr, "AT+CIPMUX=%d", ( enumEnUnvarnishTx ? 1 : 0 ) );
	
	return ESP8266_Cmd ( cStr, "OK", 0, 500 );
	
}


/*
 * ��������ESP8266_Link_Server
 * ����  ��WF-ESP8266ģ�������ⲿ������
 * ����  ��enumE������Э��
 *       ��ip��������IP�ַ���
 *       ��ComNum���������˿��ַ���
 *       ��id��ģ�����ӷ�������ID
 * ����  : 1�����ӳɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_Link_Server ( ENUM_NetPro_TypeDef enumE, char * ip, char * ComNum, ENUM_ID_NO_TypeDef id)
{
	char cStr [100] = { 0 }, cCmd [120];

  switch (  enumE )
  {
		case enumTCP:
		  sprintf ( cStr, "\"%s\",\"%s\",%s", "TCP", ip, ComNum );
		  break;
		
		case enumUDP:
		  sprintf ( cStr, "\"%s\",\"%s\",%s", "UDP", ip, ComNum );
		  break;
		
		default:
			break;
  }

  if ( id < 5 )//������
    sprintf ( cCmd, "AT+CIPSTART=%d,%s", id, cStr);    ///AT+CIPSTART="TCP","ip","80"

  else
	  sprintf ( cCmd, "AT+CIPSTART=%s", cStr );//������

	return ESP8266_Cmd ( cCmd, "OK", "ALREAY CONNECT", 500 );
	
}

/*
 * ��������ESP8266_StartOrShutServer
 * ����  ��WF-ESP8266ģ�鿪����رշ�����ģʽ
 * ����  ��enumMode������/�ر�
 *       ��pPortNum���������˿ں��ַ���
 *       ��pTimeOver����������ʱʱ���ַ�������λ����
 * ����  : 1�������ɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_StartOrShutServer ( FunctionalState enumMode, char * pPortNum, char * pTimeOver )
{
	char cCmd1 [120], cCmd2 [120];

	if ( enumMode )
	{
		sprintf ( cCmd1, "AT+CIPSERVER=%d,%s", 1, pPortNum );
		
		sprintf ( cCmd2, "AT+CIPSTO=%s", pTimeOver );

		return ( ESP8266_Cmd ( cCmd1, "OK", 0, 500 ) &&
						 ESP8266_Cmd ( cCmd2, "OK", 0, 500 ) );
	}
	
	else
	{
		sprintf ( cCmd1, "AT+CIPSERVER=%d,%s", 0, pPortNum );

		return ESP8266_Cmd ( cCmd1, "OK", 0, 500 );
	}
	
}


/*
 * ��������ESP8266_UnvarnishSend
 * ����  ������WF-ESP8266ģ�����͸������
 * ����  ����
 * ����  : 1�����óɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_UnvarnishSend ( void )
{
	return (
	  ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 500 ) &&
	  ESP8266_Cmd ( "AT+CIPSEND", "\r\n", ">", 500 ) );
	
}


/*
 * ��������ESP8266_SendString
 * ����  ��WF-ESP8266ģ�鷢���ַ���
 * ����  ��enumEnUnvarnishTx�������Ƿ���ʹ����͸��ģʽ
 *       ��pStr��Ҫ���͵��ַ���
 *       ��ulStrLength��Ҫ���͵��ַ������ֽ���
 *       ��ucId���ĸ�ID���͵��ַ���
 * ����  : 1�����ͳɹ�
 *         0������ʧ��
 * ����  �����ⲿ����
 */
bool ESP8266_SendString ( FunctionalState enumEnUnvarnishTx, char * pStr, uint32_t ulStrLength, ENUM_ID_NO_TypeDef ucId )
{
	char cStr [20];
	bool bRet = false;
		
	if ( enumEnUnvarnishTx )
	{
		ESP8266_Usart ( "%s", pStr );
	}
	
	else
	{
		if ( ucId < 5 )
			sprintf ( cStr, "AT+CIPSEND=%d,%ld", ucId, ulStrLength + 2 );

		else
			sprintf ( cStr, "AT+CIPSEND=%ld", ulStrLength + 2 );
		
		ESP8266_Cmd ( cStr, "> ", 0, 1000 );

		bRet = ESP8266_Cmd ( pStr, "SEND OK", 0, 1000 );
  }
	
	return bRet;

}


/*
 * ��������ESP8266_ReceiveString
 * ����  ��WF-ESP8266ģ������ַ���
 * ����  ��enumEnUnvarnishTx�������Ƿ���ʹ����͸��ģʽ
 * ����  : ���յ����ַ����׵�ַ
 * ����  �����ⲿ����
 */
char * ESP8266_ReceiveString ( FunctionalState enumEnUnvarnishTx )
{
	char * pRecStr = 0;
	
	strEsp8266_Fram_Record.InfBit .FramLength = 0;
	strEsp8266_Fram_Record.InfBit .FramFinishFlag = 0;
	while ( ! strEsp8266_Fram_Record.InfBit .FramFinishFlag );
	strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ] = '\0';
	
	if ( enumEnUnvarnishTx )
	{
		if ( strstr ( strEsp8266_Fram_Record.Data_RX_BUF, ">" ) )
			pRecStr = strEsp8266_Fram_Record.Data_RX_BUF;

	}
	
	else 
	{
		if ( strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "+IPD" ) )
			pRecStr = strEsp8266_Fram_Record.Data_RX_BUF;

	}

	return pRecStr;
	
}


/*
 * ��������ESP8266_WebFetch_Test
 * ����  ��WF-ESP8266ģ�����ץȡ��ҳ����
 * ����  ����
 * ����  : ��
 * ����  �����ⲿ����
 */
void ESP8266_init( void )
{
	char cStrInput [100] = { 0 }, * pStrDelimiter [2], * pBuf, * pStr;
	uint8_t uc = 0;

	ESP8266_Choose ( ENABLE );	


	ESP8266_AT_Test ();
	

	ESP8266_Net_Mode_Choose ( STA );
  

	ESP8266_Cmd ( "AT+CWLAP", "OK", 0, 5000 );


  do
	{
		printf ( "\r\n�����������ӵ�Internet��WiFi���ƺ���Կ�������ʽΪ�������ַ�+Ӣ�Ķ���+��Կ�ַ�+�ո񣬵������\r\n" );

		//1810,4001001111 
		scanf ( "%s", cStrInput );

		printf ( "\r\n�Ե�Ƭ�� ����\r\n" );

		pBuf = cStrInput;
		uc = 0;
		while ( ( pStr = strtok ( pBuf, "," ) ) != NULL )
		{
			pStrDelimiter [ uc ++ ] = pStr;
			pBuf = NULL;
		} 
		
  } while ( ! ESP8266_JoinAP ( pStrDelimiter [0], pStrDelimiter [1] ) );
//	ESP8266_Cmd ( "AT+CIPMUX=0", "OK", 0, 500 );            //������ 
//  do
//	{
//		printf ( "\r\n���ӵ�WiFi\r\n" );

//  } while ( ! ESP8266_JoinAP ( "LieBao", "12345678") );

}
/*****************************************************************************************************/
/*�ӷ�������������*/
void Web_To_ESP(void)
{ 	
	uint16_t i;
	bool state;
//	ESP8266_Cmd ( "AT", "OK", NULL, 200 );
	ESP8266_Cmd ( "AT+CIPMUX=0", "OK", 0, 500 );            //������ 
	HAL_Delay(1000);
	do
	{
		strEsp8266_Fram_Record.InfBit .FramLength = 0;               //���¿�ʼ�����µ����ݰ�
		for(i=0;i<2048;i++)
			strEsp8266_Fram_Record.Data_RX_BUF[i]=0;                //�������	
		ESP8266_Usart ( "%s\r\n", "AT+CIPSTART=\"TCP\",\"192.168.1.103\",9000" );//ע��������Ҫ���룺������IP��ַ�Ͷ˿ں�	
		HAL_Delay( 1000);                 //��ʱ	
		strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ]  = '\0';
		printf ( "%s", strEsp8266_Fram_Record.Data_RX_BUF );
      state= (( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "OK" )|( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "ALREAY CONNECT" ));
		if(( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "ERROR" ))
			state=false; 		
	}
	while(state==false);
  
	ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 500 );            //0,��͸����1��͸��
	ESP8266_Cmd ( "AT+CIPSEND", "\r\n", ">", 500 );
	ESP8266_SendString ( ENABLE, "GET /LibrarySeatServer/seatInfo?room=1 HTTP/1.1\r\n",     0, Single_ID );
	ESP8266_SendString ( ENABLE, "Host: 192.168.1.103:9000\r\n",                            0, Single_ID );
	ESP8266_SendString ( ENABLE, "User-Agent: abc\r\n",                                     0, Single_ID );
	ESP8266_SendString ( ENABLE, "Connection: close\r\n",                                   0, Single_ID );
	ESP8266_SendString ( ENABLE, "\r\n",                                                    0, Single_ID );
	strEsp8266_Fram_Record.InfBit .FramLength = 0;
	HAL_Delay(1200);
	strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ] = '\0';
	printf ("%s",strEsp8266_Fram_Record.Data_RX_BUF);
}	
///***************************************************************************************/
////��½�����ߺ�������һ��ˢ��½���ڶ���ˢ����
////������usr_Id             ��1,2,3,4,5,.......
void login(uint8_t usr_Id)
{
	char cStr[100]={0};
	uint16_t i;
	bool state;
	switch(usr_Id)
	{
		case 1:
			sprintf ( cStr, "GET /LibrarySeatServer/usrInfo?%s HTTP/1.1\r\n", "usr=june&password=19920211&req_type=SWIPE" );//�û�june
			break;
		case 2:
			sprintf ( cStr, "GET /LibrarySeatServer/usrInfo?%s HTTP/1.1\r\n", "usr=solar&password=19920211&req_type=SWIPE" );//�û�solar
			break;
		default:
			break;
	}
	
	ESP8266_Cmd ( "AT+CIPMUX=0", "OK", 0, 500 );//������
	HAL_Delay(500);
	do
	{
		strEsp8266_Fram_Record.InfBit .FramLength = 0;               //���¿�ʼ�����µ����ݰ�
		for(i=0;i<1024;i++)
			strEsp8266_Fram_Record.Data_RX_BUF[i]=0;                //�������
		ESP8266_Usart ( "%s\r\n", "AT+CIPSTART=\"TCP\",\"192.168.191.3\",8080");		
		HAL_Delay( 1000);                 //��ʱ	
		strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ]  = '\0';
		printf ( "%s", strEsp8266_Fram_Record.Data_RX_BUF );
      state= ( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "OK" )||( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "ALREAY CONNECT" );
		if(( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "ERROR" ))
			state=false; 
	
	}
	while(state==false);
    ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 500 );            //0,��͸����1��͸��
	ESP8266_Cmd ( "AT+CIPSEND", "\r\n", ">", 500 );
	ESP8266_SendString ( ENABLE, cStr,                                0, Single_ID );//������
	ESP8266_SendString ( ENABLE, "Host: 192.168.191.3:8080\r\n",      0, Single_ID );//����Ϊ����ͷ
	ESP8266_SendString ( ENABLE, "User-Agent: abc\r\n",               0, Single_ID );
	ESP8266_SendString ( ENABLE, "Content-Length: 38\r\n",            0, Single_ID );
	ESP8266_SendString ( ENABLE, "Connection: close\r\n",             0, Single_ID );
	ESP8266_SendString ( ENABLE, "\r\n",                              0, Single_ID );
	strEsp8266_Fram_Record.InfBit .FramLength = 0;
	HAL_Delay(3000);
	strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ] = '\0';
	printf ("%s",strEsp8266_Fram_Record.Data_RX_BUF);
	printf ("\r\n");
	if((strstr(strEsp8266_Fram_Record.Data_RX_BUF,"OK"))!=NULL)
		printf ("log in successfully\r\n");
}	

///*************************************************************************************************************/
////reqType���������ͣ�1ֱ������ĳ��������λ��Ϣ��2����ռ������
////desk������ID
////room����ID 
////seat����λID
////actionType���������ͣ�ֱ�ӵ���occupy��
////usr���û�ID
//void occupy(char desk_ID,char room_ID,char seat_ID,char usr_ID)
//{
//	char cStr[100]={0};
//	uint16_t i;
//	bool state;
//	sprintf ( cStr, "GET /LibraryDeskServer/deskInfo?reqType=2&desk=%d&room=%d&seat=%d&actionType=occupy&usr=%d HTTP/1.1\r\n",desk_ID,room_ID,seat_ID,usr_ID);			
//	ESP8266_Cmd ( "AT+CIPMUX=0", "OK", 0, 500 );//������
//	HAL_Delay(500);
//	do
//	{
//		strEsp8266_Fram_Record.InfBit .FramLength = 0;               //���¿�ʼ�����µ����ݰ�
//		for(i=0;i<1024;i++)
//			strEsp8266_Fram_Record.Data_RX_BUF[i]=0;                //�������
//		sprintf(array,"AT+CIPSTART=\"TCP\",\"%s\",8080",IP);
//		ESP8266_Usart ( "%s\r\n", array );		
//		HAL_Delay( 1000);                 //��ʱ	
//		strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ]  = '\0';
//		printf ( "%s", strEsp8266_Fram_Record.Data_RX_BUF );
//      state= ( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "OK" )||( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "ALREAY CONNECT" );
//		if(( bool ) strstr ( strEsp8266_Fram_Record.Data_RX_BUF, "ERROR" ))
//			state=false; 
//	
//	}
//	while(state==false);
//	sprintf(array,"Host: %s:8080\r\n",IP);
//    ESP8266_Cmd ( "AT+CIPMODE=1", "OK", 0, 500 );            //0,��͸����1��͸��
//	ESP8266_Cmd ( "AT+CIPSEND", "\r\n", ">", 500 );
//	ESP8266_SendString ( ENABLE, cStr,                                NULL, Single_ID );//������
//  ESP8266_SendString ( ENABLE, array,                               NULL, Single_ID );//����Ϊ����ͷ
//	ESP8266_SendString ( ENABLE, "User-Agent: abc\r\n",               NULL, Single_ID );
//	ESP8266_SendString ( ENABLE, "Content-Length: 38\r\n",            NULL, Single_ID );
//	ESP8266_SendString ( ENABLE, "Connection: close\r\n",             NULL, Single_ID );
//	ESP8266_SendString ( ENABLE, "\r\n",                              NULL, Single_ID );
//	strEsp8266_Fram_Record.InfBit .FramLength = 0;
//	HAL_Delay(1500);
//	strEsp8266_Fram_Record.Data_RX_BUF [ strEsp8266_Fram_Record.InfBit .FramLength ] = '\0';
//	if((strstr(strEsp8266_Fram_Record.Data_RX_BUF,"[{"))!=NULL)
//		printf ("occupy successfully\r\n");
//	else 
//		printf ("failed\r\n");


//}




