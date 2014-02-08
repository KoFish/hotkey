CC =gcc
CFLAGS = -O3 -s -mtune=native -Wall -Wextra
CLIBS = -lX11

hotkey: hotkey.c keys.h
	$(CC) hotkey.c -o hotkey   $(CFLAGS) $(CLIBS)

clean:
	rm hotkey
