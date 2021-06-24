#include "CppUTest/TestHarness.h"

extern "C"
{
#include "circular_buf.h"
}

TEST_GROUP(CircBufTest)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(CircBufTest, InitWithNullPointer)
{
	// This test does not work properly. It needs ptrFifo initialized with Null.
	CircBuf *ptr = NULL;
	bool ret = circbuf_init(ptr, 0, 0);
	CHECK_FALSE(ret);
}

TEST(CircBufTest, InitWithNullPointerBuffer)
{
	CircBuf circbuf;
	bool ret = circbuf_init(&circbuf, 0, 0);
	CHECK_FALSE(ret);
}

TEST(CircBufTest, InitWithZeroSize)
{
	CircBuf circbuf;
	uint8_t buffer[1];
	bool ret = circbuf_init(&circbuf, buffer, 0);
	CHECK_FALSE(ret);
}

TEST(CircBufTest, InitIsOk)
{
	CircBuf circbuf;
	uint8_t buffer[1];
	bool ret = circbuf_init(&circbuf, buffer, 1);
	CHECK(ret);
}

TEST(CircBufTest, GetSizeRight)
{
    CircBuf circbuf;
    uint8_t buffer[1];
    circbuf_init(&circbuf, buffer, 1);
    uint32_t size = circbuf_getSize(&circbuf);
    CHECK_EQUAL(1, size);
}

TEST(CircBufTest, PushIntoNullPointerFifo)
{
    CircBuf *ptrFifo = NULL;
    bool ret = circbuf_push(ptrFifo, 0xAA);
    CHECK_FALSE(ret);
}

TEST(CircBufTest, PushDataIfFifoIsEmpty)
{
    CircBuf circbuf;
    uint8_t buffer[2];
    circbuf_init(&circbuf, buffer, 2);
    bool ret = circbuf_push(&circbuf, 0xAA);
    CHECK(ret);
}

TEST(CircBufTest, PushDataIfFifoIsFull)
{
    CircBuf circbuf;
    uint8_t buffer[1];
    circbuf_init(&circbuf, buffer, 1);
    bool ret = circbuf_push(&circbuf, 0xAA);
    CHECK(ret);
    CHECK_FALSE(circbuf_push(&circbuf, 0xBB));
    CHECK_EQUAL(0xAA, circbuf_pull(&circbuf));
}

TEST(CircBufTest, JustPushAllOfData)
{
    CircBuf circbuf;
    uint8_t buffer[100];
    circbuf_init(&circbuf, buffer, 100);
    bool ret;
    for (int i = 0; i < 100; ++i) {
        ret = circbuf_push(&circbuf, i);
        CHECK(ret);
    }
}

TEST(CircBufTest, PullFromEmptyFifo)
{
    CircBuf circbuf;
    uint8_t buffer[1];
    circbuf_init(&circbuf, buffer, 1);
    uint8_t data = circbuf_pull(&circbuf);
    CHECK_EQUAL(0, data);
}

TEST(CircBufTest, PullRegularWay)
{
    CircBuf circbuf;
    uint8_t buffer[2];
    circbuf_init(&circbuf, buffer, 2);
    uint8_t data = 0xAA;
    circbuf_push(&circbuf, data);
    CHECK_EQUAL(data, circbuf_pull(&circbuf));
}

TEST(CircBufTest, VerifyCount)
{
    CircBuf circbuf;
    uint8_t buffer[10];
    circbuf_init(&circbuf, buffer, 10);
    for (uint8_t i = 0; i < 10; ++i) {
        CHECK_EQUAL(i, circbuf_getCount(&circbuf));
        circbuf_push(&circbuf, 1);
    }

    for (uint8_t i = 0; i < 10; ++i) {
        CHECK_EQUAL(10u - i, circbuf_getCount(&circbuf));
        circbuf_pull(&circbuf);
    }
}

TEST(CircBufTest, MultipleFifos)
{
    CircBuf circbuf1;
    uint8_t buffer1[10];
    circbuf_init(&circbuf1, buffer1, 10);

    CircBuf circbuf2;
    uint8_t buffer2[5];
    circbuf_init(&circbuf2, buffer2, 5);

    circbuf_push(&circbuf1, 0xA0);
    circbuf_push(&circbuf2, 0xB0);
    circbuf_push(&circbuf1, 0xA1);
    circbuf_push(&circbuf1, 0xA2);
    circbuf_push(&circbuf2, 0xB1);
    circbuf_push(&circbuf2, 0xB5);

    CHECK_EQUAL(0xA0, circbuf_pull(&circbuf1));
    CHECK_EQUAL(0xA1, circbuf_pull(&circbuf1));
    CHECK_EQUAL(0xA2, circbuf_pull(&circbuf1));

    CHECK_EQUAL(0xB0, circbuf_pull(&circbuf2));
    CHECK_EQUAL(0xB1, circbuf_pull(&circbuf2));
    CHECK_EQUAL(0xB5, circbuf_pull(&circbuf2));
}