/*****
*	Copyright (c) 2017 Bashlykov Sergey
*	All rights reserved.
*
*******************************************
*
*  Use menu( char *item[],  unsigned int count_item )
*  Where "item" is array of items for menu
*	And "count_item" is count of items of menu
*	For UNIX
*
*******************************************/

#include "string.h"
#include "curses.h"
#include "wchar.h"
#include "locale.h"

#define PRINT( val ) wprintf(L"\n\r %s\n\r", val);


/*** DRAWS A BORDER AROUND THE ITEM ***/
void frame(char *item)
{

    int i, len;
    len = strlen(item);
    wprintf(L"┌");
    for( i=0; i<len; i++ ) wprintf(L"─");
    wprintf(L"┐");
    wprintf(L"\n\r│"); wprintf(L"%s", item ); wprintf(L"│\n\r");
    wprintf(L"└");
    for( i=0; i<len; i++ ) wprintf(L"─");
    wprintf(L"┘");
}

/*** SHOWS THE CURRENT ITEM IN THE FRAME AND ALL OTHER ITEMS***/
unsigned int  menu_items(  char *item[],
                        unsigned int cur_item,
                        unsigned int count_item,
                        unsigned int ch )
{
    unsigned int i;

    if ( (ch == DOWN ) && ( cur_item != (count_item - 1) ) )
          cur_item++;
    else if ( (ch == UP) &&  ( cur_item != 0 ) )
          cur_item--;
    else if ( ( ch == DOWN ) && ( cur_item == (count_item - 1) ) )
            cur_item = 0;
    else if ( ( ch == UP ) && ( cur_item == 0 ) )
            cur_item = count_item - 1;

    for ( i = 0; i < count_item; i ++ )
    {
        if ( i == cur_item )
        {
            frame( item[ cur_item ] );
        }
        else
        {
            PRINT( item[i] );
        }
    }

    return cur_item;
}


void menu( char *item[],  unsigned int count_item )
{

    unsigned int crtl, ch = 0,
                cur_item = 0;

    menu_items( item, cur_item, count_item, 0);


    while ( 1 )
    {
	crtl = getch();
	if ( crtl == 27 )
	{
	    crtl = getch();
	    if ( crtl == 91 )
	    {
		ch = getch();
		clear(); 
		refresh();
    		cur_item = menu_items( item, cur_item, count_item, ch );
		PRINT("");
	    }
	}
	
    }
}

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    WINDOW *wnd;

    wnd = initscr(); // curses call to initialize window
    cbreak(); // curses call to set no waiting for Enter key
    noecho(); // curses call to set no echoing
    clear(); // curses call to clear screen, send cursor to position (0,0)
    refresh(); // curses call to implement all changes since last refresh


    char *item[] = { "item1", "item2",  "item3", "item4", "item5", "item6", "item7" };
    unsigned int count = sizeof(item) / sizeof(item[0]);

    menu( item,  count );
    endwin(); // curses call to restore the original window and leave

    return 0;
}

