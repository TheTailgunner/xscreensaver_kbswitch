/* kblayout.c --- provides some functions to manage keyboard layouts;
 * Copyright (c) Nickolaev Vladislav, 2015 <nvladislav9@gmail.com>
 */

#ifndef __XSCREENSAVER_KBLAYOUT_H__
#define __XSCREENSAVER_KBLAYOUT_H__

#include <X11/XKBlib.h>

struct kb_data
{
	unsigned cur_kbgroup;
	char *kblayout_name;
	int xkb_event_type;
};

unsigned get_current_kbgroup(Display *disp);
char *get_current_kblayout_name(Display *disp);
void set_next_kblayout(Display *disp, struct kb_data *data);
Bool initalize_xkblib(Display *disp, struct kb_data *data);

#endif /* __XSCREENSAVER_KBLAYOUT_H__ */
