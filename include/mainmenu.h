#ifndef MAINMENU_H
#define MAINMENU_H

#include <menu.h>
#include "utils.h"

enum {START_GAME, QUIT_GAME};

void CloseMenu(int numberItems, MENU *menu, ITEM **items);
int MainMenu(int numberItems, char **choices);

#endif /* MAINMENU_H */
