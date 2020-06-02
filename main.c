#include "C:/Keil_v5/Labware/tm4c123gh6pm.h"
//#include "GPIOprog.c"
#include "GPIO_interface.h"
#include "UART.h"
//#include "Keypad.h"

#define NULL 0

#define empty '0'
#define occupied '1'


/*modes*/
#define setup   '0'
#define checkin  '1'
#define cleaning  '2'
#define checkout  '3'

	// global variables for set up
	uint32_t rooms[10]={0,1,2,3,4,5,6,7,8,9}; 
	char hotel_rooms[10];
	/*{1,2,3,4,5}*/
	uint32_t status[10]={empty,empty,empty,empty,empty,empty,empty,empty,empty,empty};
	char pass[10][4];
uint32_t password[10][4]={
	{0000},{5678},{1234},{2345},{3456},{8345},{7345},{6345},{3345},{4345}}; // room 1 has keypad and solenoid*/
	
	uint32_t userpass[4];
uint32_t favouriteroom=1;
	uint32_t room_nums;
	char room_numbers;
	char room_number;
	 uint32_t room_num;
	uint32_t keypadkey; 
	
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
	/****function to compare a whole string*****/
uint32_t string_compare(uint32_t c [4],uint32_t v [4])
{
	uint32_t counter =0;
for(int i=0;i<4;i++)
	{
	if (c[i]==v[i])
	{
	counter++;
	}
	}
if (counter==4)
{
return (1);
}
else {
return 0;
}

}
	
	
int main()
{
	char mode;


	initPortC();
		initPortF();	
	  UART_init();
	GPIO_interrupt_init();
		// keypad on port C
GPIO_PORTC_DIR_R|=0x0;
	//GPIO_PORTF_DIR_R|=0xFF;
	//GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_1,GPIO_HIGH);// output
	GPIO_PORTF_DIR_R|=0x04;//pin2 output rest pins are inputs 3chan l interrupt
	
// high ---->close solenoid
	GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_HIGH);

__enable_irq();

	while(1)
	{
		//mode = checkin;


		mode=UART_recieve();			// to choose mode
	UART_send(mode);
	switch (mode){
			case setup: // setup
		{
	    /************3chan at3amal anh rkm********/
		room_numbers=UART_recieve();// kda h5od 3adad l rooms l hysht8l 3liha
			UART_send(room_numbers);
      room_nums=UART_integer(room_numbers);			
		for (int i=0;i<room_nums;i++)
			
			{
				hotel_rooms[i]=UART_recieve();
				UART_send(hotel_rooms[i]);
			rooms[i]=UART_integer(hotel_rooms[i]);
			
				
			}
		}
		mode=UART_recieve();			// to choose mode
	UART_send(mode);
		/**************************************************/
			case checkin:
		{
			
		room_number=UART_recieve();
			UART_send(room_number);
			room_num=UART_integer(room_number);
		status[room_num-1]=UART_recieve();	
			UART_send(status[room_num-1]);
			
		if (room_num==favouriteroom&& status[room_num-1]==empty) // empty= '0'
		{
					status[room_num-1]=occupied;
	if (status[room_num-1]==occupied)

{
	/*set passsword*/
			for (int i=0;i<4;i++)
			{
			 pass[room_num-1][i]=UART_recieve();
				password[room_num-1][i]=UART_integer(pass[room_num-1][i]);
				
			
			}	
	GPIO_interrupt_handler();
	
	
	}
	
			/****************interrupt***/

/*    while(GPIO_PORTC_DATA_R==NULL){};// 3awzah yfdl mstny anh yd5l password ,lsa ht2kd mnh
  
		for (int i=0;i<4;i++)
		{
		userpass[i]=Get_KPD_Value();
		}*/
	
		
	//	if (userpass[i]==password[room_num-1][i])
			if (string_compare(userpass,password[room_num-1])==1)
			{
				
				// open solenoid
				GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_LOW);
		
		  
			
		}
		}
		else if (status[room_num-1]!=empty) // mch sure mnha 
		{
UART_send('0');
		}
  }
		/*********************************************************************/
			case cleaning:
		{
			// 7wlih 
			room_number=UART_recieve();
			UART_send(room_number);
			room_num=UART_integer(room_number);
		
			status[room_num-1]=UART_recieve();
			UART_send(status[room_num-1]);
			if (room_num==favouriteroom) // 3chan hia l room l leha keypad w solenoid
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
		
	
