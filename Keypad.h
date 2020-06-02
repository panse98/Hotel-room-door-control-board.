#include "C:/Keil_v5/Labware/tm4c123gh6pm.h"
#include "GPIO_interface.h"
#define kpd_port GPIO_PORT_C
#define ROW_NB 4
#define COL_NB 4

uint32_t KeysNb[ROW_NB][COL_NB]={
		/*C0*/       /*C1*/      /*C2*/       /*C4*/
		{1,          2          ,3            ,4}, /*Row 0*/
		{5,          6,         7,              8}, /*row1*/
		{9,          10,        11,            12},/*row2*/
		{13,         14,        15,            16}/*row3*/

};

uint32_t Get_KPD_Value(void)
{
uint32_t key_num;
uint32_t Row_idx;
uint32_t Col_idx;
GPIO_Pin_Value pinVal = GPIO_HIGH;
for (Col_idx=0;Col_idx<COL_NB;Col_idx++)	
{ 
	GPIO_SetPinValue(kpd_port,Col_idx,GPIO_LOW);
for(Row_idx=0;Row_idx<	ROW_NB;Row_idx++)
{
pinVal=GPIO_GetPinValue(kpd_port,Row_idx+COL_NB);
// tol ma l key is down
	while(pinVal==GPIO_LOW)
	{
	key_num=KeysNb[Row_idx][Col_idx];
		pinVal=GPIO_GetPinValue(kpd_port,Row_idx+COL_NB);
	}
}
GPIO_SetPinValue(kpd_port,Col_idx,GPIO_HIGH);

}
return key_num;

}
	
	void GPIO_interrupt_handler()
{
	GPIO_PORTF_ICR_R = 0x10;// interrupt clear
	uint32_t keypadkey;
	//uint32_t userpass[4]={0000}; /* for test without tiva*/
uint32_t userpass[4];
	// for debug
		GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_LOW);

/*	for(int i=0;i<4;i++)
	{
	
	 keypadkey=Get_KPD_Value();
	
	userpass[i]=keypadkey;
		
	
	}*/
}
		

