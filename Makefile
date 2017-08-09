#################################################################
# Makefile for libserial (serial/rs232 communication in Linux)
# Author: Anatolii MAKHORT
# e-mail: anmakhort@gmail.com
#################################################################

CC = gcc
STANDART = -std=gnu89
CFLAGS = -Wall -Wextra -Werror -O3 -pipe
DEBUG =
INCLUDES = -I/usr/include -I/usr/include/linux -I/include
LDFLAGS =
LIBS =

TEST_TARGET = test/test
TEST_SOURCES = test/test.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

TARGET_SUBST = serial
TARGET = libserial
TARGET_STATIC_LIB = $(TARGET).a
TARGET_SHARED_LIB = $(TARGET).so

SOURCES = serial.c

OBJECTS = $(SOURCES:.c=.o)

RM = rm -fr

.PHONY: all, run, distclean, objclean, clean

all: $(TARGET_STATIC_LIB) $(TARGET_SHARED_LIB) $(TEST_TARGET)

$(TARGET_STATIC_LIB): $(OBJECTS)
	@ar rc $(TARGET_STATIC_LIB) $(OBJECTS)
	@ranlib $(TARGET_STATIC_LIB)
	@echo "\033[32m  ✔ \033[0m\033[1;31m" $(TARGET_STATIC_LIB) "\033[0m"

$(TARGET_SHARED_LIB): $(OBJECTS)
	@$(CC) -shared -Wl,-soname,$(TARGET_SHARED_LIB).1 -o $(TARGET_SHARED_LIB).1.0.1 $(OBJECTS)
	@echo "\033[32m  ✔ \033[0m\033[1;31m" $(TARGET_SHARED_LIB).1.0.1 "\033[0m"

$(TEST_TARGET): $(TEST_OBJECTS) $(TARGET_STATIC_LIB)
	@$(CC) -o $(TEST_TARGET) $(TEST_OBJECTS) -L./ -lserial
	@echo "\033[34m  ✔ \033[0m\033[1;35m" $(TEST_TARGET) "\033[0m"

$(TEST_OBJECTS): $(TEST_SOURCES)
	@$(CC) $(STANDART) $(CFLAGS) $(DEBUG) -c $(TEST_SOURCES) -o $(TEST_OBJECTS)
	@echo "\033[32m  ✔ \033[0m\033[1;33m" $< "\033[0m->\033[1;36m" $@ "\033[0m"

%.o: %.c
	@$(CC) $(STANDART) $(CFLAGS) -fPIC $(DEBUG) -c $< -o $@
	@echo "\033[32m  ✔ \033[0m\033[1;33m" $< "\033[0m->\033[1;36m" $@ "\033[0m"

distclean:
	@$(RM) $(TEST_TARGET) *.so.1* *.a

objclean:
	@$(RM) $(OBJECTS) $(TEST_OBJECTS)

clean: distclean objclean
