/******************************************************************************
*
* Author: Andrey Opalev
*
******************************************************************************/

#include "simple_queue.h"
#include <string.h>

struct SimpleQ {
  int32_t size;
  int32_t count;
  int32_t begin;
  int32_t end;
  int32_t elementSize;
  uint8_t* buffer;

#ifdef QUEUE_STAT_ENABLED
  int32_t n_overflows;
  int32_t max_count;
#endif //QUEUE_STAT_ENABLED
};

int32_t simpleq_init(SimpleQ_t *queue, int32_t elementSize, int32_t nComponents, uint8_t *buffer)
{
  if (queue == NULL) {
    return -1;
  }

  queue->size = nComponents;
  queue->count = 0;
  queue->begin = 0;
  queue->end = 0;
  queue->buffer = buffer;
  queue->elementSize = elementSize; 

#ifdef QUEUE_STAT_ENABLED
  queue->n_overflows = 0;
  queue->max_count = 0;
#endif //QUEUE_STAT_ENABLED
}

int32_t simpleq_dequeue(SimpleQ_t *queue, void *outElement)
{
  if (queue->count == 0) {
    return -1;
  }

  int32_t buf_i = queue->begin * queue->elementSize;
  memcpy(outElement, &queue->buffer[buf_i], queue->elementSize);

  queue->begin++;
  if (queue->begin == queue->size) {
    queue->begin = 0;
  }

  queue->count--;
  return 0;
}

int32_t simpleq_enqueue(SimpleQ_t *queue, void *inElement)
{
  if (queue->count == queue->size) {
#ifdef QUEUE_STAT_ENABLED
    queue->n_overflows++;
#endif //QUEUE_STAT_ENABLED
    return -1;
  }

  int32_t buf_i = queue->end * queue->elementSize;
  memcpy(&queue->buffer[buf_i], inElement, queue->elementSize);

  queue->end++;
  if (queue->end == queue->size) {
    queue->end = 0;
  }

  queue->count++;
  return 0;
}

int32_t simpleq_size(SimpleQ_t *queue)
{
  return queue->size;
}

int32_t simpleq_capacity(SimpleQ_t *queue)
{
  return queue->size - queue->count;
}

int32_t simpleq_count(SimpleQ_t *queue)
{
  return queue->count;
}

#if defined(SELFTEST)
#include <assert.h>
#include <stdio.h>

int main()
{
  SimpleQ_t queue;
  struct Element {
    int32_t a;
    uint8_t b;
    int32_t c;
    uint8_t array[3];
  };
  const int32_t NElements = 10;
  uint8_t buffer[NElements * sizeof(struct Element)];

  simpleq_init(&queue, sizeof(struct Element), NElements, buffer);

  assert(simpleq_size(&queue) == NElements);
  assert(simpleq_capacity(&queue) == NElements);

  struct Element el1 = {1, 2, 3, {4, 5, 6}};
  struct Element el2;
  assert(simpleq_enqueue(&queue, &el1) == 0);
  assert(simpleq_capacity(&queue) == (NElements - 1));

  assert(simpleq_dequeue(&queue, &el2) == 0);
  assert(memcmp(&el1, &el2, sizeof(el1)) == 0);
  assert(simpleq_capacity(&queue) == NElements);

  // Enqueue 9 elemenets
  for (int i = 0; i < NElements - 1; ++i) {
    // printf("i = %d; count = %d; capacity = %d\n", i, simpleq_count(&queue), simpleq_capacity(&queue));
    assert(simpleq_enqueue(&queue, &el1) == 0);
    assert(simpleq_capacity(&queue) == (NElements - 1 - i));
  }

  // Enqueue 10th element
  assert(simpleq_enqueue(&queue, &el1) == 0);
  // Faield to enqueue one more
  assert(simpleq_enqueue(&queue, &el1) != 0);

  // Dequeue 9 elements
  for (int i = 0; i < NElements - 1; ++i) {
    assert(simpleq_dequeue(&queue, &el2) == 0);
    assert(memcmp(&el1, &el2, sizeof(el1)) == 0);
    assert(simpleq_capacity(&queue) == (i + 1));
  }

  // Dequeue 10th element
  assert(simpleq_dequeue(&queue, &el2) == 0);
  assert(memcmp(&el1, &el2, sizeof(el1)) == 0);

  // Faield to dequeue one more
  assert(simpleq_dequeue(&queue, &el2) != 0);
}

#endif //SELFTEST