#include "mainmenu.h"

void CloseMenu(int numberItems, MENU *menu, ITEM **items)
{
   unpost_menu(menu);
   free_menu(menu);

   for (int i = 0; i < numberItems; ++i)
   {
      free_item(items[i]);
   }
}

int MainMenu(int numberItems, char **choices)
{
   int input, value;
   MENU *menu;
   ITEM **items = (ITEM **)SafeMalloc(sizeof(**items) * numberItems);
   ITEM *current;

   for (int i = 0; i < numberItems; ++i)
   {
      items[i] = new_item(choices[i], "");
   }
   items[numberItems] = (ITEM *)NULL;

   menu = new_menu((ITEM **)items);
   post_menu(menu);
   refresh();

   // Menu Loop
   while (1)
   {
      input = getch();

      switch (input)
      {
         case KEY_DOWN:
            menu_driver(menu, REQ_DOWN_ITEM);
            break;
         case KEY_UP:
            menu_driver(menu, REQ_UP_ITEM);
            break;
         case 10: /* Enter key */
            current = current_item(menu);
            value = item_index(current);
            CloseMenu(numberItems, menu, items);
            return value;
      }
   }
}
