CC = gcc
CFLAG = -g -std=gnu11
OBJS = list.o test.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAG) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAG) -c $<

format:
	clang-format -i *.c
	clang-format -i *.h
clean:
	$(RM) $(OBJS) $(TARGET) experiment
