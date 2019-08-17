#include "GUI_MainWin.h"

MainWin* mainWinCreate() {
	MainWin* res = NULL;
	res = (MainWin*) calloc(sizeof(MainWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	res->mainWindow = SDL_CreateWindow("Chess_Game: Main Menu", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED,
			500,500 , SDL_WINDOW_OPENGL  );

	if (res->mainWindow == NULL ) {
		mainWinDestroy(res);
		printf("Can not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->mainWindow, -1,SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		mainWinDestroy(res);
		printf("Can not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->widgets=createMainWinWidgets(res->mainRenderer);
	if (res->widgets==NULL ) {
		mainWinDestroy(res);
		printf("Can not create widgets: %s\n", SDL_GetError());
		return NULL ;
	}
	res->numOfWidgets=3;
	res->first=true;
	return res;
}
Widget** createMainWinWidgets(SDL_Renderer* renderer) {
	int i;
	if (renderer == NULL ) {
		return NULL ;
	}
	Widget** widgets = calloc(3,sizeof(Widget*));
	if (widgets == NULL ) {
		return NULL ;
	}
	SDL_Rect newgameR = { .x =125, .y = 50, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect loadR = { .x = 125, .y = 160, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	SDL_Rect quitR = { .x = 125, .y = 270, .h = BUTTON_HEIGTH, .w = BUTTON_WIDTH };
	widgets[0] = createSB(renderer, &newgameR, "./gui/images/buttons/newgame.bmp",NULL,true);
	widgets[1] = createSB(renderer, &loadR, "./gui/images/buttons/load.bmp",NULL,true);
	widgets[2] = createSB(renderer, &quitR, "./gui/images/buttons/quit.bmp",NULL,true);
	for(i=0;i<3;i++){
		if(widgets[i]==NULL){
			mainWinWidgetsDestroy(widgets);
			break;
		}
	}
	return widgets;
}
void mainWinDraw(MainWin* src) {
	int i;
	if(src==NULL){
		return;
	}
	SDL_SetRenderDrawColor(src->mainRenderer, 40, 40, 40, 40);
	SDL_RenderClear(src->mainRenderer);
	for (i=0; i < src->numOfWidgets; i++) {
		(src->widgets[i])->drawWidget(src->widgets[i]);
	}
	SDL_RenderPresent(src->mainRenderer);
}
void mainWinDestroy(MainWin* src) {
	if (!src) {
		return;
	}
	mainWinWidgetsDestroy(src->widgets);
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->mainWindow != NULL ) {
		SDL_DestroyWindow(src->mainWindow);
	}
	free(src);
}
void mainWinWidgetsDestroy(Widget** widgets){
	int i;
	for(i=0;i<3;i++){
		if(widgets[i]!=NULL){
			destroyWidget(widgets[i]); //NULL SAFE
		}
	}
	free(widgets);
}
MAIN_EVENT mainWinHandleEvent(MainWin* src, SDL_Event* event) {
	if (!event) {
		return MAIN_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (src->widgets[0]->handleEvent(src->widgets[0],event)==1) {
			return MAIN_START;
		} else if (src->widgets[1]->handleEvent(src->widgets[1],event)==1) {
			return MAIN_LOAD;
		}else if (src->widgets[2]->handleEvent(src->widgets[2],event)==1){
			return MAIN_EXIT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return MAIN_EXIT;
		}
		break;
	default:
		return MAIN_NONE;
	}
	return MAIN_NONE;
}

void mainWindowHide(MainWin* src) {
	SDL_HideWindow(src->mainWindow);
}

void mainWindowShow(MainWin* src) {
	SDL_ShowWindow(src->mainWindow);
}
