HEADERS = ./src/httplib.h ./src/libducklet.h ./src/ducklettypes.h
SOURCES = $(HEADERS:.h=.c)
TMP = $(SOURCES:.c=.o)
OBJECTS = $(TMP:src=obj)
CC = clang
CFLAGS = -g -Wall -O3

ducklet: ./src/ducklet.c $(HEADERS) $(SOURCES) $(OBJECTS)
	$(CC) $(CFLAGS) ./src/ducklet.c -lglib-2.0 $(OBJECTS) -o ducklet

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

install_duckletc: duckletc
	cp duckletc /usr/local/bin/duckletc

clean:
	rm $(OBJECTS) ducklet

test.log: ducklet
	curl -d "message body" http://localhost:5000/index.html > test.log

test: ducklet
	./ducklet ./test_site/ &
	firefox "localhost:5000/index"
