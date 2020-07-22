#include <stddef.h>
#include "fifo.h"

/**
 * @brief Initialize fifo
 * @param fifo      Fifo pointer
 * @param buffer    Buffer pointer
 * @param size      Size of the buffer
 * @return true (or 1) if it's initialized properly, false (or 0) - otherwise
 */
bool fifo_init(Fifo *fifo, uint8_t *buffer, uint32_t size)
{
    if (fifo == NULL) {
		return false;
	}
	if (buffer == NULL) {
		return false;
	}
	if (size == 0) {
		return false;
	}

	fifo->size = size;
	fifo->ptrBuffer = buffer;
	fifo->count = 0;
	fifo->head = 0;
	fifo->tail = 0;
    fifo->n_overflows = 0;
    fifo->max_count = 0;

    return true;
}

/**
 * @brief Put the new data into fifo
 * @param fifo  Fifo pointer
 * @param data  New data
 * @return true (or 1) if it's okay, false (or 0) if't the fifo was already full
 */
bool fifo_push(Fifo *fifo, uint8_t data)
{
    if (fifo == NULL) {
        return false;
    }

    // fifo is full
    if (fifo->count == fifo->size) {
        fifo->n_overflows++;
        return false;
    }

    fifo->ptrBuffer[fifo->head] = data;
    if (fifo->head < (fifo->size - 1)) {
        fifo->head++;
    } else {
        fifo->head = 0;
    }

    fifo->count++;
    if (fifo->count > fifo->max_count) {
        fifo->max_count = fifo->count;
    }


    return true;
}

/**
 * @brief Pull the first element out
 *
 * Before reading it's better to check count by fifo_getCount() to be sure that any values exist.
 *
 * @param fifo Fifo pointer
 * @return Data. If the fifo is empty it return also a zero value
 */
uint8_t fifo_pull(Fifo *fifo)
{
    if (fifo == NULL || fifo->ptrBuffer == NULL) {
        return 0;
    }

    if (fifo->count == 0) {
        return 0;
    }

    uint8_t dataToPull = fifo->ptrBuffer[fifo->tail];
    if (fifo->tail < (fifo->size - 1)) {
        fifo->tail++;
    } else {
        fifo->tail = 0;
    }
    fifo->count--;
    return dataToPull;
}

/**
 * @brief Return size of the fifo buffer
 * @param fifo  Fifo pointer
 * @return  Size
 */
uint32_t fifo_getSize(Fifo *fifo)
{
    if (fifo == NULL) {
        return 0;
    }

    return fifo->size;
}

/**
 * @brief Return current count of the data at the fifo
 * @param fifo  Fifo pointer
 * @return  Count of the data
 */
uint32_t fifo_getCount(Fifo *fifo)
{
    if (fifo == NULL) {
        return  0;
    } else {
        return  fifo->count;
    }
}
