#ifndef WIDGET_H_
#define WIDGET_H_
#include <SDL.h>
#include <SDL_video.h>
#include<SDL_mouse.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct widget_t Widget;
struct widget_t {
	void (*drawWidget)(Widget*);
	int (*handleEvent)(Widget*, SDL_Event*);
	void (*destroyWidget)(Widget*);
	void* data;
	bool canPush;

};


void destroyWidget(Widget* src);

#endif

