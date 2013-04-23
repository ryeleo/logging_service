CC=$(CROSS_COMPILE)gcc
CFLAGS= -g -Wall
INCLUDE=/usr/local/android-ndk/platforms/android-14/arch-arm/usr/include
CLIBS=/usr/local/android-ndk/platforms/android-14/arch-arm/usr/lib/libc.so

default: logging_service.h
	$(CC) $(CFLAGS) -L$(CLIBS) -I$(INCLUDE) logging_service.c main.c -o logging_service

clean:
	rm *.o logging_serice
