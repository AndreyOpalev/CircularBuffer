#ifndef CIRCULAR_BUF_H
#define CIRCULAR_BUF_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint32_t size;
	uint32_t count;
	uint32_t head;
	uint32_t tail;
  uint32_t n_overflows;
  uint32_t max_count;
	uint8_t* ptrBuffer;
} CircBuf;

bool      circbuf_init(CircBuf *circbuf, uint8_t *buffer, uint32_t size);
uint32_t  circbuf_getSize(CircBuf *circbuf);
bool      circbuf_push(CircBuf *circbuf, uint8_t data);
uint8_t   circbuf_pull(CircBuf *circbuf);
uint32_t  circbuf_getCount(CircBuf *circbuf);

#endif //CIRCULAR_BUF_H