CC =gcc
CFLAGS = -O3 -s -mtune=native -Wall -Wextra
CLIBS = -X11

hotkey: hotkey.c
	$(CC) -o hotkey -c hotkey.c  $(CFLAGS)

clean:
	rm hotkey
