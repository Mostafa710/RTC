#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "keypad.h"
#include "timer 2.h"
#include "std_macros.h"
#include "seven segment.h"

volatile unsigned char seconds_counter;

int main(void)
{
	unsigned char minutes_counter=0,hours_counter=0;
	unsigned char val,first_digit,second_digit;
	LCD_init();
	keypad_init('D');
	seven_segment_init('B');
	timer2_overflow_init_interrupt();
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,5);
	LCD_send_string("Press 1 to");
	LCD_move_cursor(2,1);
	LCD_send_string("set clock");
    while(1)
    {
		val=keypad_read('D');
		if(val != NOT_PRESSED)
		{
			if(val == '1')
			{
				_delay_ms(250);
				LCD_clear_screen();
				LCD_send_string("Hours=--");
				LCD_move_cursor(1,7);
				do 
				{
					second_digit=keypad_read('D');
				} while (second_digit == NOT_PRESSED);
				LCD_send_char(second_digit);
				_delay_ms(250);
				do
				{
					first_digit=keypad_read('D');
				} while (first_digit == NOT_PRESSED);
				LCD_send_char(first_digit);
				_delay_ms(250);
				hours_counter=(second_digit-48)*10+(first_digit-48);
				LCD_clear_screen();
				LCD_send_string("Minutes=--");
				LCD_move_cursor(1,9);
				do
				{
					second_digit=keypad_read('D');
				} while (second_digit == NOT_PRESSED);
				LCD_send_char(second_digit);
				_delay_ms(250);
				do
				{
					first_digit=keypad_read('D');
				} while (first_digit == NOT_PRESSED);
				LCD_send_char(first_digit);
				_delay_ms(250);
				minutes_counter=(second_digit-48)*10+(first_digit-48);
				LCD_clear_screen();
				LCD_send_string("Seconds=--");
				LCD_move_cursor(1,9);
				do
				{
					second_digit=keypad_read('D');
				} while (second_digit == NOT_PRESSED);
				LCD_send_char(second_digit);
				_delay_ms(250);
				do
				{
					first_digit=keypad_read('D');
				} while (first_digit == NOT_PRESSED);
				LCD_send_char(first_digit);
				_delay_ms(250);
				seconds_counter=(second_digit-48)*10+(first_digit-48);
				LCD_clear_screen();
				LCD_send_string("Press 1");
				LCD_move_cursor(2,1);
				LCD_send_string("to set time");
			}
			else
			{
				LCD_clear_screen();
				LCD_send_string("Wrong Choice");
				_delay_ms(1000);
				LCD_clear_screen();
				LCD_send_string("Press 1");
				LCD_move_cursor(2,1);
				LCD_send_string("to set time");
			}
		}
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,0);
		seven_segment_write('B',seconds_counter%10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,1);
		seven_segment_write('B',seconds_counter/10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,2);
		seven_segment_write('B',minutes_counter%10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,3);
		seven_segment_write('B',minutes_counter/10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,4);
		seven_segment_write('B',hours_counter%10);
		_delay_ms(5);
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		CLR_BIT(PORTC,5);
		seven_segment_write('B',hours_counter/10);
		_delay_ms(5);
		if(seconds_counter == 60)
		{
			seconds_counter=0;
			minutes_counter++;
		}
		if(minutes_counter == 60)
		{
			minutes_counter=0;
			hours_counter++;
		}
		if(hours_counter == 24)
		{
			hours_counter=0;
		}
    }
}
ISR(TIMER2_OVF_vect)
{
	seconds_counter++;
}