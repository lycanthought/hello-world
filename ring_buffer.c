/* START OF FILE -------------------------------------------------------------*/

/******************************************************************************/
/* ring_buffer.h                                                              */
/* © Dan Perrett 2018                                                         */
/* Author: Dan Perrett                                                        */
/******************************************************************************/

/* Defines: ------------------------------------------------------------------*/
#define RING_BUFFER_SIZE 256

/* Data Structures: ----------------------------------------------------------*/
struct ringBuffer{
  uint32_t writeAddress;
  uint32_t readAddress;
  uint8_t bufferArray[RING_BUFFER_SIZE];
};

/* Function Prototypes: ------------------------------------------------------*/
 uint32_t RINGBUF_getCurrentSize(struct ringBuffer *buffer);
 uint8_t  RINGBUF_mostRecentByte(struct ringBuffer *buffer);
 uint8_t  RINGBUF_writeToBuffer (struct ringBuffer *buffer, uint8_t character);
 uint8_t  RINGBUF_readFromBuffer(struct ringBuffer *buffer);

/*----------------------------------------------------------------------------*/


/*--------------------------------------------------------------- END OF FILE */


//ring_buffer.c

#include "main.h"
uint32_t RINGBUF_getCurrentSize(struct ringBuffer *buffer)
{
  if( buffer->readAddress > buffer->writeAddress )
  {
  	return ( RING_BUFFER_SIZE - (buffer->readAddress - buffer->writeAddress) );
  }
  else if( buffer->readAddress < buffer->writeAddress )
  {
    return ( buffer->writeAddress - buffer->readAddress );
  }
  else
  {
    return 0;
  }
}

uint8_t  RINGBUF_mostRecentByte(struct ringBuffer *buffer)
{
	uint32t address = buffer->readAddress;
	if( address == buffer->writeAddress )
	{
		return 0;
	}
	else
	{
		return buffer[address];
	}
}

uint8_t  RINGBUF_writeToBuffer (struct ringBuffer *buffer, uint8_t character)
{
	uint32t address = (((buffer->writeAddress)+1) % RING_BUFFER_SIZE);
	if( address == buffer->readAddress)
	{
		return 0;
	}
	else
	{
		buffer[(buffer->writeAddress)] = character;
		buffer->writeAddress = address;
		return character;
	}
}

uint8_t  RINGBUF_readFromBuffer(struct ringBuffer *buffer)
{
  	uint32t address = buffer->readAddress;
	if( buffer->readAddress == buffer->writeAddress )
	{
		return 0;
	}
	else
	{
		buffer->readAddress = ((buffer->readAddress+1) % RING_BUFFER_SIZE);
		return buffer[address];
	}
}




