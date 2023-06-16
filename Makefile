CC = g++
CFLAGS = -std=c++23 -Wall

TARGET = indexador

all: $(TARGET)

$(TARGET): main.cpp Indexador.cpp Indexador.h
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp Indexador.cpp

clean:
	rm -f $(TARGET)