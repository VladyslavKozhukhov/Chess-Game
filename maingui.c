#include "maingui.h"
#include "SDL.h"
int maingui() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	GuiManager* manager = managerCreate();
	if (manager == NULL ) {
		SDL_Quit();
		return 0;
	}
	SDL_Event event;
	while (true) {
		SDL_WaitEvent(&event);
		MANAGER_EVENET handle =managerHandleEvent(manager, &event);
		if (handle == MANAGER_QUIT) {
			printf("Exit");
			break;
		}
		if(handle==MANAGER_UPDATE){
			managerDraw(manager);
		}
	}
	managerDestroy(manager);
	SDL_Quit();
	return 0;
}
