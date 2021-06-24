# Circle buffer

Simple, **not thread-safe** circle buffer implementation in C, though tested. The project is built to be used within various MCU firmwares.

## Tests
The unit-tests are based on CppUTest 3.8.

Installing:

    apt install cpputest libcpputest-dev

Building:

    cd test
    cmake ./
    make

Running:

    ./AllTests