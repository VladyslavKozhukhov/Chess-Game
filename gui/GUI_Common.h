#ifndef GUI_COMMON_H_
#define GUI_COMMON_H_
#include "../mainAux.h"
#include <SDL.h>
#include <SDL_video.h>
#include <unistd.h>

#define SLOT0 "./gui/files/0.xml"
#define SLOT1 "./gui/files/1.xml"
#define SLOT2 "./gui/files/2.xml"
#define SLOT3 "./gui/files/3.xml"
#define SLOT4 "./gui/files/4.xml"

SDL_Rect* copyRect(SDL_Rect* src);

int countSavedFiles();
void promoteSlots();

#endif
