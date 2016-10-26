/*
 * ringbuffer.h
 *
 *  Created on: 25. 10. 2016
 *      Author: Lenka
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#define BUFFLEN 64
#include <stdint.h>

char getbuff();
void putbuff(char c);

uint16_t getfull();
uint16_t getfree();



#endif /* RINGBUFFER_H_ */
