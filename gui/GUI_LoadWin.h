#ifndef GUI_LOADWIN_H_
#define GUI_LOADWIN_H_
#include<stdbool.h>
#include <stdio.h>
#include "GUI_SimpleButton.h"

typedef enum {
	LOAD_EVENT_SLOT_1,
	LOAD_EVENT_SLOT_2,
	LOAD_EVENT_SLOT_3,
	LOAD_EVENT_SLOT_4,
	LOAD_EVENT_SLOT_5,
	LOAD_EVENT_QUIT,
	LOAD_EVENT_BACK,
	LOAD_EVENT_START,
	LOAD_EVENT_INVALID_ARGUMENT,
	LOAD_EVENT_NONE,
	LOAD_EVENT_UPDATE,
} LOAD_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Widget** widgets;
	int numOfWidgets;
	bool first;
	int slot_num;
	bool legalload;
}LoadWin;

void loadWinDraw(LoadWin*);
LoadWin* loadWinCreate();
Widget** createLoadWinWidgets(SDL_Renderer* renderer);
void loadWinDestroy(LoadWin*);
char* getFilePath(int file_num);
bool CheckPath(char* path);
void loadWinWidgetsDestroy(Widget** widgets);
LOAD_EVENT loadWinHandleEvent(LoadWin* src, SDL_Event* event);


#endif
