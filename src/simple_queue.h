/******************************************************************************
*
* Author: Andrey Opalev
*
******************************************************************************/
#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

#include <stdint.h>

typedef struct SimpleQ SimpleQ_t;

int32_t simpleq_init(SimpleQ_t *queue, int32_t elementSize, int32_t nComponents, uint8_t *buffer);
int32_t simpleq_dequeue(SimpleQ_t *queue, void *outElement);
int32_t simpleq_enqueue(SimpleQ_t *queue, void *inElement);
int32_t simpleq_size(SimpleQ_t *queue);
int32_t simpleq_capacity(SimpleQ_t *queue);
int32_t simpleq_count(SimpleQ_t *queue);

#endif //SIMPLE_QUEUE_H