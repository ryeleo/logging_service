#CC=$(CROSS_COMPILE)gcc
CC=gcc
#CC=/usr/local/android_ndk/toolchains/arm-linux-androideabi-4.6/prebuilt/linux-x86/bin/arm-linux-androideabi-gcc
CFLAGS= -g -Wall
#INCLUDE=/usr/local/android-ndk/platforms/android-14/arch-arm/usr/include
#CLIBS=/usr/local/android-ndk/platforms/android-14/arch-arm/usr/lib/libc

default: logging_service.h
	$(CC) $(CFLAGS) -L$(CLIBS) -I$(INCLUDE) logging_service.c main.c -o logging_service

clean:
	rm *.o logging_serice
