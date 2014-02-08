#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define len(X) (sizeof X / sizeof X[0])

typedef struct {
	char *command;
	unsigned int mod;
	KeySym key;
} Key;

#include "keys.h"

int main() {
	Display*    dpy     = XOpenDisplay(0);
	Window      root    = DefaultRootWindow(dpy);
	unsigned int i = 0;

	for(i = 0; i < len(hotkeys); i++) {
		XGrabKey(dpy,  XKeysymToKeycode(dpy,hotkeys[i].key), hotkeys[i].mod, root, False, GrabModeAsync, GrabModeAsync);
	}

	XSelectInput(dpy, root, KeyPressMask );
	while(1)	{
		XEvent ev;
		XNextEvent(dpy, &ev);

		if(ev.type == KeyPress) {
			//ripped out of dwm
			XKeyEvent *kev = &ev.xkey;
			KeySym keysym = XKeycodeToKeysym(dpy, (KeyCode)kev->keycode, 0);
			for(i = 0; i < len(hotkeys); i++) {
				if(keysym == hotkeys[i].key && hotkeys[i].mod == kev->state) {
					printf("executing '%s'\n", hotkeys[i].command);
					system(hotkeys[i].command);
				}
			}
		}
	}

	XCloseDisplay(dpy);
	return 0;
}
