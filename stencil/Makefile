CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic -std=gnu99 -Werror

all: cosmic_monkey cosmic_monkey_debug

cosmic_monkey: cosmic_monkey.c
	$(CC) $(CFLAGS) $< -o $@

cosmic_monkey_debug: cosmic_monkey.c
	$(CC) $(CFLAGS) -DDEBUG -g $< -o $@

clean:
	rm -f cosmic_monkey cosmic_monkey_debug

.PHONY: all clean
