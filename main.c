#include "C:/Keil_v5/Labware/tm4c123gh6pm.h"
#include "GPIO_interface.h"
#include "UART.h"



  
#define empty '0'     /*room status*/           
#define occupied '1'



#define setup   '0'  /*modes*/
#define checkin  '1'
#define cleaning  '2'
#define checkout  '3'

	// global variables for set up
	uint32_t rooms[10];
	char hotel_rooms[10];
	uint32_t status[10]={empty,empty,empty,empty,empty,empty,empty,empty,empty,empty}; // receptionest can overwrite 
	char pass[10][4];                                                                  //these intialization values  
uint32_t password[10][4]={{0000},{0000},{0000},{0000},{0000},{0000},{0000},{0000},{0000},{0000}};
	uint32_t userpass[4];
uint32_t favouriteroom=1;
	uint32_t room_nums;
	char room_numbers;
	char room_number;
	 uint32_t room_num;
	uint32_t keypadkey; 
	
	/* to convert char recieved form UART into integer*/
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

initPortB();
	initPortC();
		initPortF();	
	  UART_init();
	GPIO_interrupt_init();
		// keypad on port b&c
GPIO_PORTC_DIR_R|=0x0;
//GPIO_PORTB_DIR_R|=0x0;
	
	//GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_1,GPIO_HIGH);// output
	GPIO_PORTF_DIR_R|=0x04;//pin2 output rest pins are inputs for l interrupt
	
// high ---->close solenoid
	GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_HIGH);

__enable_irq();

	while(1)
	{
send_string("choose mode");

		mode=UART_recieve();			// to choose mode
	UART_send(mode);
	switch (mode){
			case setup: // setup
		{
			send_string("setup mode");
	   send_string("Enter total number of rooms");
		room_numbers=UART_recieve();// kda h5od 3adad l rooms l hysht8l 3liha
			UART_send(room_numbers);
			room_nums=UART_integer(room_numbers);		
      send_string("Enter numbers & status of rooms");			
		for (int i=0;i<room_nums;i++)
			
			{
				hotel_rooms[i]=UART_recieve();
				UART_send(hotel_rooms[i]);
		rooms[i]=UART_integer(hotel_rooms[i]);
			/* status*/
				status[i]=UART_recieve();
				
			}
		}
		break;
	//	mode=UART_recieve();			// to choose mode
	//UART_send(mode);
		/**************************************************/
			case checkin:
		{
			send_string("Checkin mode");
			send_string("Enter room number");
			
		room_number=UART_recieve();
			UART_send(room_number);
			room_num=UART_integer(room_number);
		//status[room_num-1]=UART_recieve();	
			//UART_send(status[room_num-1]);
			
		if (status[room_num-1]==empty) // empty= '0'
		{
					status[room_num-1]=occupied;
	if (status[room_num-1]==occupied)
send_string("Set a password to room"); 
{
	/*set passsword*/
			for (int i=0;i<4;i++)
			{
			 pass[room_num-1][i]=UART_recieve();
				password[room_num-1][i]=UART_integer(pass[room_num-1][i]);
				
			
			}	
	GPIO_interrupt_handler();
	
	
	}

		
			if (string_compare(userpass,password[room_num-1])==1)
			{
				
				// open solenoid
				GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_LOW);
		
		  send_string("room has been reserved successfully");
			
		}
		}
		else if (status[room_num-1]!=empty) // mch sure mnha 
		{
        send_string("room unavailable");
		}
  }
		break;
		/*********************************************************************/
			case cleaning:
		{
		send_string("cleaning mode");
			send_string("Enter room number");
			room_number=UART_recieve();
			UART_send(room_number);
			room_num=UART_integer(room_number);
		
			//status[room_num-1]=UART_recieve();
			//UART_send(status[room_num-1]);
			if (room_num==favouriteroom) // room with keypad and solenoid
			{
		GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_LOW); // unlock
			}// hna mfrod aktr mn solenoid 3chan aft7 bta3 l room dih t7didn?
			else {
		
/* open another rooms solenoid */		
		}
		}
		
		break;
		
			case checkout:
				{
					send_string("Checkout mode");
					send_string("Enter room number");
					room_number=UART_recieve();
					send_string("room number is");
					UART_send(room_number);
					UART_send('\n');
					room_num=UART_integer(room_number);
			
			if (room_num==favouriteroom&& status[room_num-1]==occupied)
			   {
			GPIO_SetPinValue(GPIO_PORT_F,GPIO_PIN_2,GPIO_HIGH); // lock tany
				status[room_num-1]=empty;
			send_string("checkout is done succesfully");
			    }
			}
				break;
		
		
		
	  }		
		
	}
	
}
		
	
