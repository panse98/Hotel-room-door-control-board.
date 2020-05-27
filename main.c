#include "C:/Keil_v5/Labware/tm4c123gh6pm.h"
//#include "GPIOprog.c"
#include "GPIO_interface.h"
#include "UART.h"
#include "Keypad.h"

#define NULL 0

#define empty '0'
#define occupied '1'


/*modes*/
#define setup 0
#define checkin 1
#define cleaning 2
#define checkout 3

	// global variables for set up
	uint32_t rooms[10]; 
	char hotel_rooms[10];
	/*{1,2,3,4,5}*/
	uint32_t status[10]={empty,empty,empty,empty,empty,empty,empty,empty,empty,empty};
	char pass[10][4];
uint32_t password[10][4];/*={
	{0000},{5678},{1234},{2345},{3456},{8345},{7345},{6345},{3345},{4345}}; // room 1 has keypad and solenoid*/
	
	uint32_t userpass[4];
uint32_t favouriteroom=1;
	uint32_t room_nums;
	char room_numbers;
	char room_number;
	 uint32_t room_num;
	
//	uint32_t i=0; // counter 
	//uint32_t count =0;
  //uint32_t data[6];// roomnum, 

	
uint32_t UART_integer(char c)
		
	{
	if((c >='0') && (c<='9'))
	{
	int num = 0;


	num = c - '0';

	return num;
  }
	
	
}
	
	
	
	
int main()
{
	char mode;
		initPortC();
		initPortF();	
	  UART_init();
		// keypad on port C
GPIO_PORTC_DIR_R|=0x00;
	GPIO_PORTF_DIR_R|=0xFF;
	
// high ---->close solenoid
	GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_HIGH);

__enable_irq();

	while(1)
	{
		mode=UART_recieve();		// to choose mode
		switch (mode){
			case setup: // setup
		{
	    /************3chan at3amal anh rkm********/
		room_numbers=UART_recieve();// kda h5od 3adad l rooms l hysht8l 3liha
      room_nums=UART_integer(room_numbers);			
			for (int i=0;i<room_nums;i++)
			{
				hotel_rooms[i]=UART_recieve();
			rooms[i]=UART_integer(hotel_rooms[i]);
			  
			}
		}
		/**************************************************/
			case checkin:
		{
		room_number=UART_recieve();
			room_num=UART_integer(room_number);
		status[room_num-1]=UART_recieve();
			
		if (room_num==favouriteroom&& status[room_num-1]==empty) // empty= '0'
		{
					status[room_num-1]=occupied;
		/*set passsword*/
			for (int i=0;i<4;i++)
			{
			 pass[room_num-1][i]=UART_recieve();
				password[room_num-1][i]=UART_integer(pass[room_num-1][i]);
				
			
			}
			/****************interrupt***/

    while(GPIO_PORTC_DATA_R==NULL){};// 3awzah yfdl mstny anh yd5l password ,lsa ht2kd mnh
  
		for (int i=0;i<4;i++)
		{
		userpass[i]=Get_KPD_Value();
		}
		if (userpass==password[room_num-1])
			{
				
				// open solenoid
				GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_HIGH);
		
		  }
			
	}
		else if (status[room_num-1]!=empty)
		{
		// hfdl mstny yla2y room fadya
		}
  }
		/*********************************************************************/
			case cleaning:
		{
			room_num=UART_recieve();
		status[room_num-1]=UART_recieve();
			if (room_num==favouriteroom)
			{
		GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_LOW); // unlock
			}// hna mfrod aktr mn solenoid 3chan aft7 bta3 l room dih t7didn?
		}
		
		
			case checkout:
				{
					room_num=UART_recieve();
			
			if (room_num==favouriteroom)
			   {
			GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_HIGH); // lock tany
				status[room_num-1]=empty;
			
			    }
			}
		
		
		
	  }		
		
	}
	
}
		
	
