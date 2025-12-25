CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = programSort

all: $(TARGET)

$(TARGET): main.o count.o mergeSort.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

count.o: count.c
	$(CC) $(CFLAGS) -c count.c -o count.o

mergeSort.o: mergeSort.s
	$(CC) -c mergeSort.s -o mergeSort.o

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run