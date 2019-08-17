#ifndef GUI_GAMEWIN_H_
#define GUI_GAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "GUI_Common.h"
#include "GUI_SimpleButton.h"
#include "GUI_PieceButton.h"
#include "../mainAux.h"

typedef enum {
	GAME_EVENT_TIE,
	GAME_EVENT_UNDO,
	GAME_EVENT_RESET,
	GAME_EVENT_SAVE,
	GAME_EVENT_LOAD,
	GAME_EVENT_MAIN_MENU,
	GAME_EVENT_EXIT,
	GAME_EVENT_INVALID_ARGUMENT,
	GAME_EVENT_NONE,
	GAME_EVENT_UPDATE,
} GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	bool first;
	bool saved;
	bool backmain;
	ArrayList* moves;
	Game* game;
	Widget** widgets;
	int numOfWidgets;

}GameWin;

GameWin* gameWinCreate();
Widget** iniatGameWinWidgets(SDL_Renderer* renderer,Game* game);
void gameWinDraw(GameWin*,bool update);
void gameWinDestroy(GameWin*);
void gameWindowHide(GameWin* src);
void gameWindowShow(GameWin* src);
void gameWinWidgetsDestroy(Widget** widgets,Game* game);
GAME_EVENT gameWinHandleEvent(GameWin* src, SDL_Event* event);


#endif
