CC = gcc
CFLAGS = -Wall -Wextra -I libs/nmea

test_nmea: tests/test_nmea.c libs/nmea/nmea.c libs/nmea/nmea.h
	$(CC) $(CFLAGS) tests/test_nmea.c libs/nmea/nmea.c -o test_nmea

test: test_nmea
	./test_nmea

clean:
	rm -f test_nmea