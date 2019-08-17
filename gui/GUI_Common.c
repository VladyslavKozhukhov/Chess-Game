#include "GUI_Common.h"

SDL_Rect* copyRect(SDL_Rect* src){
	if(src == NULL){
		return NULL;
	}
	SDL_Rect* res = malloc(sizeof(SDL_Rect));
	if(res==NULL){
		return NULL;
	}
	res->h = src->h;
	res->w = src->w;
	res->x = src->x;
	res->y = src->y;
	return res;
}



	int countSavedGames() {
		int counter = 0;

		if (access(SLOT0, F_OK) != -1)
			counter++;
		else
			return counter;
		if (access(SLOT1, F_OK) != -1)
			counter++;
		else
			return counter;
		if (access(SLOT2, F_OK) != -1)
			counter++;
		else
			return counter;
		if (access(SLOT3, F_OK) != -1)
			counter++;
		else
			return counter;
		if (access(SLOT4, F_OK) != -1)
			counter++;
		else
			return counter;

		return counter;
	}

	void promoteSlots() {
		int numUsedslots = countSavedGames();
		int index = numUsedslots - 1;
		if (numUsedslots == 5) {
			remove(SLOT4);
			index--;
		}
		if (index >= 3) {
			rename(SLOT3, SLOT4);
			index--;
		}
		if (index >= 2) {
			rename(SLOT2, SLOT3);
			index--;
		}
		if (index >= 1) {
			rename(SLOT1, SLOT2);
			index--;
		}
		if (index >= 0) {
			rename(SLOT0, SLOT1);
			index--;
		}
	}





