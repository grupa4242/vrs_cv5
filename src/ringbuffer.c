/*
 * ringbuffer.c
 *
 *  Created on: 25. 10. 2016
 *      Author: Lenka
 */


#include "ringbuffer.h"

#define CNTMSK (BUFFLEN - 1)

volatile char buff[BUFFLEN];
volatile uint16_t rp = 0;
volatile uint16_t wp = 0;

char getbuff()
{
	if (wp == rp)
		return 0;

	char tmp = buff[rp];
	rp++;
	rp&=CNTMSK;
	return tmp;
}

void putbuff(char c)
{
	if (((wp + 1) & CNTMSK) == rp)
		return;

	buff[wp]=c;
	wp++;
	wp&=CNTMSK;
}

uint16_t getfull()
{
	return (wp-rp)&CNTMSK;
}

uint16_t getfree()
{
	return ((rp-wp)&CNTMSK)-1;
}
