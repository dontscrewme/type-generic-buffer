#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

static bool index_is_empty(buffer_t* me, uint16_t index);

struct buffer_t
{
	uint16_t space;
	uint16_t buffer_length;
	uint8_t item_size;
	uint8_t data[];
};

buffer_t* newBuffer(size_t buffer_length, size_t item_size)
{
  buffer_t* me = malloc(sizeof(buffer_t) + buffer_length*item_size);
	if (!me)
	{
		return NULL;
	}

	me->space = buffer_length;
	me->buffer_length = buffer_length;
  me->item_size = item_size;
	memset(me->data, 0, item_size*buffer_length);

	return me;
}

bool put(buffer_t* me, const void* item)
{
  if ((!me) || (bufferIsFull(me)))
	{
		return false;
	}

  uint16_t index = me->buffer_length - me->space;
  memcpy(&me->data[index*me->item_size], item, me->item_size);
  --me->space;
  return true;
}

bool item_in_buffer(buffer_t* me, const void* item)
{
  if ((!me) || (me->buffer_length == me->space))
	{
		return false;
	}

  uint16_t total_item = me->buffer_length - me->space;

  uint16_t index = 0;
  for (; index < total_item; index++)
  {
    if(!index_is_empty(me, index))
    {
      if(!memcmp(&me->data[index*me->item_size], item, me->item_size))
      {
        return true;
      }
    }
  }

  return false;
}

bool bufferIsFull(buffer_t* me)
{
  if (0 == me->space)
  {
    return true;
  }

  return false;
}

void deleteBuffer(buffer_t* me)
{
  free(me);
}

static bool index_is_empty(buffer_t* me, uint16_t index)
{
  // char* zero = calloc(1, sizeof(me->item_size));
  // bool ret = memcmp(zero, &me->data[index*me->item_size], me->item_size);
  // free(zero);
  // return ret;

  static const char zero[128] = {0};
  return !memcmp(zero, &me->data[index*me->item_size], me->item_size>128? 128: me->item_size);
}

void print_buffer(buffer_t* me)
{
  printf("*****buffer message*****\n");
  printf("space: %d\n", me->space);
  printf("buffer_length: %d\n", me->buffer_length);
  printf("item_size: %d\n", me->item_size);

  uint16_t total_item = me->buffer_length - me->space;
  for (uint16_t i = 0; i<total_item; i++)
  {
    printf("item[%d]: %s\n", i, (char*)&me->data[i*me->item_size]);
  }
}



