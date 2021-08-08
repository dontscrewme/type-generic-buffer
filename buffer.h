#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

typedef struct buffer_t buffer_t;

buffer_t* newBuffer(size_t buffer_length, size_t item_size);
bool put(buffer_t* me, const void* item);
bool item_in_buffer(buffer_t* me, const void* item);
bool bufferIsFull(buffer_t* me);
void deleteBuffer(buffer_t* me);

void print_buffer(buffer_t* me);

#endif
