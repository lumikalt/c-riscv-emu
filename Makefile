CC = gcc
TARGET = risci

OPTLVL = 3
CFLAGS = -Wall -Wextra -Wimplicit-fallthrough=0

$(TARGET):
	$(CC) main.c src/*.c -o $(TARGET) $(CFLAGS) -O$(OPTLVL)

clean:
	rm -rf ./$(TARGET)
