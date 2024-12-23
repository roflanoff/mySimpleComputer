.PHONY: all clean

TARGET= mt_lib.a

SRC= $(wildcard *.c)
OBJ= $(patsubst %.c, %.o, $(SRC))

all: $(TARGET)
	
$(TARGET): $(OBJ)
	ar rcs $@ $^

%.o : %.c
	gcc -Wall -MMD -c $^ -o $@ -I ..
