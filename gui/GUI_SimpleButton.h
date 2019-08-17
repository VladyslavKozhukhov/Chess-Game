#ifndef GUI_SIMPLEBUTTON_H_
#define GUI_SIMPLEBUTTON_H_

#include "GUI_Common.h"
#include "Widget.h"
#include <stdbool.h>
#define BUTTON_WIDTH 240
#define BUTTON_HEIGTH 70
#define BUTTON_SHIFT 30

  typedef struct simplebutton_type{
	SDL_Texture* buttonTexture;
	SDL_Renderer* windowRenderer;
		SDL_Rect* location;
		bool active;
		bool show;
	SDL_Texture* buttonPressedTexture;

}SimpleButton;

Widget* createSB(SDL_Renderer* windowRender, SDL_Rect* location,const char* image,const char* imagepressed,bool show);//,const char* imagepressed
void destroySB(Widget*);
int handleSBEvenet(Widget* src, SDL_Event* event);
void drawSB(Widget* src);
#endif
