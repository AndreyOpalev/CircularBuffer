#include "CppUTest/TestHarness.h"
#include "../fifo.c"

TEST_GROUP(FifoTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

// DONE
TEST(FifoTest, InitWithNullPointer) 
{
	// This test does not work properly. It needs ptrFifo initialized with Null. 
	Fifo *ptrFifo = NULL;
	// Fifo *ptrFifo;

	bool ret = fifo_init(ptrFifo, 0, 0);
	CHECK_FALSE(ret);
}

// DONE
TEST(FifoTest, InitWithNullPointerBuffer)
{
	Fifo fifo;
	bool ret = fifo_init(&fifo, 0, 0);
	CHECK_FALSE(ret);
}

// DONE
TEST(FifoTest, InitWithZeroSize)
{
	Fifo fifo;
	uint8_t buffer[1];
	bool ret = fifo_init(&fifo, buffer, 0);
	CHECK_FALSE(ret);
}

// DONE
TEST(FifoTest, InitIsOk)
{
	Fifo fifo;
	uint8_t buffer[1];
	bool ret = fifo_init(&fifo, buffer, 1);
	CHECK(ret);
}

// DONE
TEST(FifoTest, GetSizeRight)
{
    Fifo fifo1;
    uint8_t buffer1[1];
    fifo_init(&fifo1, buffer1, 1);
    uint32_t size = fifo_getSize(&fifo1);
    CHECK_EQUAL(1, size);
}

// DONE
TEST(FifoTest, PushIntoNullPointerFifo)
{
    Fifo *ptrFifo = NULL;
    bool ret = fifo_push(ptrFifo, 0xAA);
    CHECK_FALSE(ret);
}

// DONE
TEST(FifoTest, PushDataIfFifoIsEmpty)
{
    Fifo fifo;
    uint8_t buffer[2];
    fifo_init(&fifo, buffer, 2);
    bool ret = fifo_push(&fifo, 0xAA);
    CHECK(ret);
}

// DONE
TEST(FifoTest, PushDataIfFifoIsFull)
{
    Fifo fifo;
    uint8_t buffer[1];
    fifo_init(&fifo, buffer, 1);
    bool ret = fifo_push(&fifo, 0xAA);
    CHECK(ret);
    CHECK_FALSE(fifo_push(&fifo, 0xBB));
    CHECK_EQUAL(0xAA, fifo_pull(&fifo));
}

// DONE
TEST(FifoTest, JustPushAllOfData)
{
    Fifo fifo;
    uint8_t buffer[100];
    fifo_init(&fifo, buffer, 100);
    bool ret;
    for (int i = 0; i < 100; ++i) {
        ret = fifo_push(&fifo, i);
        CHECK(ret);
    }
}

// DONE
TEST(FifoTest, PullFromEmptyFifo)
{
    Fifo fifo;
    uint8_t buffer[1];
    fifo_init(&fifo, buffer, 1);
    uint8_t data = fifo_pull(&fifo);
    CHECK_EQUAL(0, data);
}

// DONE
TEST(FifoTest, PullRegularWay)
{
    Fifo fifo;
    uint8_t buffer[2];
    fifo_init(&fifo, buffer, 2);
    uint8_t data = 0xAA;
    fifo_push(&fifo, data);
    CHECK_EQUAL(data, fifo_pull(&fifo));
}

// Done
TEST(FifoTest, VerifyCount)
{
    Fifo fifo;
    uint8_t buffer[10];
    fifo_init(&fifo, buffer, 10);
    for (uint8_t i = 0; i < 10; ++i) {
        CHECK_EQUAL(i, fifo_getCount(&fifo));
        fifo_push(&fifo, 1);
    }

    for (uint8_t i = 0; i < 10; ++i) {
        CHECK_EQUAL(10u - i, fifo_getCount(&fifo));
        fifo_pull(&fifo);
    }
}

//Done
TEST(FifoTest, MultipleFifos)
{
    Fifo fifo1;
    uint8_t buffer1[10];
    fifo_init(&fifo1, buffer1, 10);

    Fifo fifo2;
    uint8_t buffer2[5];
    fifo_init(&fifo2, buffer2, 5);

    fifo_push(&fifo1, 0xA0);
    fifo_push(&fifo2, 0xB0);
    fifo_push(&fifo1, 0xA1);
    fifo_push(&fifo1, 0xA2);
    fifo_push(&fifo2, 0xB1);
    fifo_push(&fifo2, 0xB5);

    CHECK_EQUAL(0xA0, fifo_pull(&fifo1));
    CHECK_EQUAL(0xA1, fifo_pull(&fifo1));
    CHECK_EQUAL(0xA2, fifo_pull(&fifo1));

    CHECK_EQUAL(0xB0, fifo_pull(&fifo2));
    CHECK_EQUAL(0xB1, fifo_pull(&fifo2));
    CHECK_EQUAL(0xB5, fifo_pull(&fifo2));

}

