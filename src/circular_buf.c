#include <stddef.h>
#include "circular_buf.h"

/**
 * @brief Initialize circbuf
 * @param CircBuf   CircBuf pointer
 * @param buffer    Buffer pointer
 * @param size      Size of the buffer
 * @return true (or 1) if it's initialized properly, false (or 0) - otherwise
 */
bool circbuf_init(CircBuf *circbuf, uint8_t *buffer, uint32_t size)
{
    if (circbuf == NULL) {
		return false;
	}
	if (buffer == NULL) {
		return false;
	}
	if (size == 0) {
		return false;
	}

	circbuf->size = size;
	circbuf->ptrBuffer = buffer;
	circbuf->count = 0;
	circbuf->head = 0;
	circbuf->tail = 0;
    circbuf->n_overflows = 0;
    circbuf->max_count = 0;

    return true;
}

/**
 * @brief Put the new data into circbuf
 * @param circbuf  CircBuf pointer
 * @param data  New data
 * @return true (or 1) if it's okay, false (or 0) if't the circbuf was already full
 */
bool circbuf_push(CircBuf *circbuf, uint8_t data)
{
    if (circbuf == NULL) {
        return false;
    }

    // circbuf is full
    if (circbuf->count == circbuf->size) {
        circbuf->n_overflows++;
        return false;
    }

    circbuf->ptrBuffer[circbuf->head] = data;
    if (circbuf->head < (circbuf->size - 1)) {
        circbuf->head++;
    } else {
        circbuf->head = 0;
    }

    circbuf->count++;
    if (circbuf->count > circbuf->max_count) {
        circbuf->max_count = circbuf->count;
    }


    return true;
}

/**
 * @brief Pull the first element out
 *
 * Before reading it's better to check count by circbuf_getCount() to be sure that any values exist.
 *
 * @param circbuf CircBuf pointer
 * @return Data. If the circbuf is empty it return also a zero value
 */
uint8_t circbuf_pull(CircBuf *circbuf)
{
    if (circbuf == NULL || circbuf->ptrBuffer == NULL) {
        return 0;
    }

    if (circbuf->count == 0) {
        return 0;
    }

    uint8_t dataToPull = circbuf->ptrBuffer[circbuf->tail];
    if (circbuf->tail < (circbuf->size - 1)) {
        circbuf->tail++;
    } else {
        circbuf->tail = 0;
    }
    circbuf->count--;
    return dataToPull;
}

/**
 * @brief Return size of the circbuf buffer
 * @param circbuf  CircBuf pointer
 * @return  Size
 */
uint32_t circbuf_getSize(CircBuf *circbuf)
{
    if (circbuf == NULL) {
        return 0;
    }

    return circbuf->size;
}

/**
 * @brief Return current count of the data at the circbuf
 * @param circbuf  CircBuf pointer
 * @return  Count of the data
 */
uint32_t circbuf_getCount(CircBuf *circbuf)
{
    if (circbuf == NULL) {
        return  0;
    } else {
        return  circbuf->count;
    }
}
