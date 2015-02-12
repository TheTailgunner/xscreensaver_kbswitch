#include "kblayout.h"

unsigned get_current_kbgroup(Display *disp)
{
	XkbStateRec state;
    XkbGetState(disp, XkbUseCoreKbd, &state);
    return state.group;
}

char *get_current_kblayout_name(Display *disp)
{
	static char kbl_id[4];
	XkbDescPtr kb;
	const char *current_kbl_name = NULL;

	kb = XkbGetKeyboard(disp, XkbAllComponentsMask, XkbUseCoreKbd);
	current_kbl_name = XGetAtomName(disp, kb->names->groups[get_current_kbgroup(disp)]);
	strncpy(kbl_id, current_kbl_name, 3);
	kbl_id[3] = '\0';

	return kbl_id;
}

void set_next_kblayout(Display *disp, struct kb_data *data)
{
	unsigned ckb;
	
	ckb = get_current_kbgroup(disp);
	if (XkbLockGroup(disp, XkbUseCoreKbd, ( XkbMaxKbdGroup == ckb ? ckb = 0 : ++ckb )))
	{
		data->cur_kbgroup = ckb;
		data->kblayout_name = get_current_kblayout_name (disp);
	}
}

Bool initalize_xkblib(Display *disp, struct kb_data *data)
{
	if (XkbQueryExtension(disp, NULL, &(data->xkb_event_type), NULL, 
						  NULL, NULL))
	{
		XkbSelectEventDetails(disp, XkbUseCoreKbd, XkbStateNotify,
							  XkbAllStateComponentsMask, XkbGroupStateMask);
		data->cur_kbgroup = get_current_kbgroup (disp);
		data->kblayout_name = get_current_kblayout_name (disp);
		return True;
	}
	return False;
}
