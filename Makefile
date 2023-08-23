CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89
SOURCES = main.c shell.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = hsh

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

