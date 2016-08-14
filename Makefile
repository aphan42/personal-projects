CC= g++
CFLAGS= -Wall -g -std=c++11
TARGET= main

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	rm -f $(TARGET) $(TARGET).o
