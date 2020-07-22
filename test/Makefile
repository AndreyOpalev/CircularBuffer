#Set this to @ to keep the makefile quiet
.SILENT:

#---- Outputs ----#
COMPONENT_NAME = fifo
#CPPUTEST_LIB_DIR = build/libs

#--- Inputs ----#
CPPUTEST_HOME = cpputest-3.8

CPPUTEST_USE_VPATH := Y

SRC_DIRS = ../ \

SRC_FILES = ../fifo.c \

TEST_SRC_DIRS = \
. \

INCLUDE_DIRS = . \
$(CPPUTEST_HOME)/include \
../ \

#Настройки компилятора
CPPUTEST_WARNINGFLAGS += -Wall -Wswitch-enum -Wmissing-declarations -Wpedantic

CPPUTEST_CXXFLAGS = -std=c++11 \

CPPUTEST_CFLAGS = -std=c11 \

CPPUTEST_CPPFLAGS = \
-Wno-attributes \
-O0 \

CPPUTEST_LDFLAGS = \

LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

CPPUTEST_ENABLE_DEBUG = Y

CPPUTEST_USE_EXTENSIONS = Y

CPPUTEST_USE_GCOV = Y

CPPUTEST_USE_MEM_LEAK_DETECTION = N

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

all2:
	$(MAKE) -v
