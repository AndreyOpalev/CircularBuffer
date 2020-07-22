#ifndef FIFO_H
#define FIFO_H

#include <stdint.h>
#include <stdbool.h>

/// Fifo structure
typedef struct {
	uint8_t  *ptrBuffer;
	uint32_t size;
	uint32_t count;
	uint32_t head;
	uint32_t tail;
    uint32_t n_overflows;
    uint32_t max_count;
} Fifo;

bool fifo_init(Fifo *fifo, uint8_t *buffer, uint32_t size);
uint32_t fifo_getSize(Fifo *fifo);
bool fifo_push(Fifo *fifo, uint8_t data);
uint8_t fifo_pull(Fifo *fifo);
uint32_t fifo_getCount(Fifo *fifo);

#endif //FIFO_H
