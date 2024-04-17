CC = gcc
TARGET = risci

OPTLVL = 3
CFLAGS = -Wall -Wextra

$(TARGET):
	$(CC) main.c src/*.c -o $(TARGET) $(CFLAGS) -O$(OPTLVL)

clean:
	rm -rf ./$(TARGET)
