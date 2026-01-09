CC = gcc
CFLAGS = -Wall -O2

# Numele executabilului
TARGET = steiner_solver

# Fișiere obiect
OBJS = main.o utils.o exact.o metric.o greedy.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

exact.o: exact.c utils.h
	$(CC) $(CFLAGS) -c exact.c

metric.o: metric.c utils.h
	$(CC) $(CFLAGS) -c metric.c

greedy.o: greedy.c utils.h
	$(CC) $(CFLAGS) -c greedy.c

clean:
	rm -f $(OBJS) $(TARGET)