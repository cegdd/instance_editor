#ifndef BOUTONH
#define BOUTONH

#include "data.h"
#include "console.h"
#include "LIBcegdd_ui.h"

enum{B_NEW_PROJECT, B_QUITTER, B_LOAD_PROJECT, B_SAVE_PROJECT, B_LOAD_MAP, B_PLAYER_START, B_SLIDE_CREATURE, B_SLIDE_CLOSE, B_NEW_CREATURE, B_DELETE_CREATURE_MOB};

void BT_event(int i, struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);

void BT_update_loop(struct CONSOLE *console, struct DIVERSsysteme *systeme, struct UI *ui, struct DATA *data);


#endif
