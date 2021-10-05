#include <stdio.h>
#include <avr/io.h>


//#define F_CPU 3333333
#define MAX_COMMAND_LEN 64

void prinfInit();
static int USART3_printChar(char character, FILE *stream);
void USART3_sendChar(char c);
void USART3_sendString(char *str);
uint8_t checkUSARTCommand();
void clearUSARTCommand();