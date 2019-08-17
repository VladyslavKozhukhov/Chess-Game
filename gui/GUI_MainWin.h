#ifndef GUI_MAINWIN_H_
#define GUI_MAINWIN_H_
#include "GUI_SimpleButton.h"
#include <stdio.h>
#include <stdbool.h>
typedef enum {
	MAIN_EXIT,MAIN_LOAD,
	MAIN_START,
	MAIN_INVALID_ARGUMENT,
	MAIN_NONE,
} MAIN_EVENT;

typedef struct {
	SDL_Window* mainWindow;
	Widget** widgets;
	SDL_Renderer* mainRenderer;
	int numOfWidgets;
	int check;
	bool first;
} MainWin;

MainWin* mainWinCreate();
Widget** createMainWinWidgets(SDL_Renderer* renderer);
void mainWinDraw(MainWin* src);
void mainWindowHide(MainWin* src);
void mainWindowShow(MainWin* src);
void mainWinDestroy(MainWin* src);
void mainWinWidgetsDestroy(Widget** widgets);
MAIN_EVENT mainWinHandleEvent(MainWin* src, SDL_Event* event);


#endif
