#ifndef GUI_PIECEBUTTON_H_
#define GUI_PIECEBUTTON_H_

#include "Widget.h"
#include <stdbool.h>
#include "GUI_Common.h"
#include <stdio.h>

typedef struct piecebutton_type{
	SDL_Renderer* windowRenderer;
		SDL_Rect* location;
		bool show;
	SDL_Texture* buttonTexture;

}PieceButton;
Widget* createPB(SDL_Renderer* windowRender, SDL_Rect* location,const char* image,bool show);//,const char* imagepressed
void destroyPB(Widget*);

int handlePBEvenet(Widget* src, SDL_Event* event);

void drawPB(Widget* src);

#endif /* PIECEBUTTON_H_ */
