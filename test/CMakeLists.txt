cmake_minimum_required(VERSION 3.12)
project (CircularBuf_TEST)

find_library(CPPUTEST_LIB CppUTest REQUIRED)
find_library(CPPUTESTEXT_LIB CppUTestExt REQUIRED)

if(NOT CPPUTEST_LIB)
  message(FATAL_ERROR "CppUTest library not found")
endif()

if(NOT CPPUTESTEXT_LIB)
  message(FATAL_ERROR "CppUTestExt library not found")
endif()

enable_language(C)
enable_language(CXX)

# add preprocess macro definitions

# include project source
include_directories(
  ${PROJECT_SOURCE_DIR}/../src
)

# include mocks only for test code

# add project libraries
add_library(circularbuf_lib
            ../src/circular_buf.c
            )

add_executable(AllTests
               AllTests.cpp
               TEST_circular_buf.cpp
               )

target_link_libraries(AllTests CppUTest CppUTestExt circularbuf_lib)
