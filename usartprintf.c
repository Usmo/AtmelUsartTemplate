
#include <usartprintf.h>

char command[MAX_COMMAND_LEN];
uint8_t index = 0;

FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE); //printf to usart examplesta




void printfInit()
{
stdout = &USART_stream;
}

static int USART3_printChar(char c, FILE *stream)
{
	USART3_sendChar(c);
	return 0;
}

void USART3_sendChar(char c)
{
	while (!(USART3.STATUS & USART_DREIF_bm))
	{
		;
	}
	USART3.TXDATAL = c;
}

void USART3_sendString(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		USART3_sendChar(str[i]);
	}
}

uint8_t checkUSARTCommand() {
	
	char c;
	if (USART_0_is_rx_ready()) {
		
		c = USART_0_read();
		if(c != '\n' && c != '\r')
		{
			command[index++] = c;
			if(index > MAX_COMMAND_LEN)
			{
				index = 0;
			}
		}
		if(c == '\n' || c == '\r')
		{
			command[index] = '\0\r\n';
			index = 0;
			return 1;
		}
	}
	
	return 0;
}

void clearUSARTCommand() {
	for(uint8_t i=0; i<MAX_COMMAND_LEN;i++) {
		command[i] = NULL;
	}
}