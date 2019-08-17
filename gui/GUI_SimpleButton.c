#include <stdlib.h>
#include <stdio.h>
#include "GUI_SimpleButton.h"

Widget* createSB(SDL_Renderer* windowRender, SDL_Rect* location,const char* image,const char* imagepressed,bool show){
	if (windowRender == NULL || location == NULL || image == NULL ) {
		return NULL ;
	}
	Widget* res = (Widget*) malloc(sizeof(Widget));
	SimpleButton* data = (SimpleButton*) malloc(sizeof(SimpleButton));
	SDL_Surface* ld = SDL_LoadBMP(image);
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,ld);
	if(imagepressed==NULL){
		data->buttonPressedTexture = NULL;
		data->active=true;
	}
	else{
		SDL_Surface* tmp = SDL_LoadBMP(imagepressed); ;
		SDL_Texture* buttonPressedTexture = SDL_CreateTextureFromSurface(windowRender,tmp);
		SDL_FreeSurface(tmp);
		data->buttonPressedTexture = buttonPressedTexture;
		data->active=false;
		if(buttonPressedTexture==NULL){
			free(res);
			free(data);
			SDL_FreeSurface(tmp);
			SDL_DestroyTexture(buttonTexture);
			return NULL ;
		}
	}
	if (res==NULL||data==NULL||ld==NULL||buttonTexture==NULL){
		free(res);
		free(data);
		SDL_FreeSurface(ld);
		SDL_DestroyTexture(buttonTexture);
		return NULL ;
	}
	SDL_FreeSurface(ld);
	data->buttonTexture = buttonTexture;
	data->location = copyRect(location);
	data->windowRenderer = windowRender;
	data->show=show;
	res->destroyWidget = destroySB;
	res->drawWidget = drawSB;
	res->handleEvent = handleSBEvenet;
	res->data = data;
	return res;
}
void destroySB(Widget* src) {
	if (src==NULL){
		return;
	}
	SimpleButton* castData =(SimpleButton*) src->data;
	free(castData->location);
	SDL_DestroyTexture(castData->buttonTexture);
	SDL_DestroyTexture(castData->buttonPressedTexture);
	free(castData);
	free(src);
}

int handleSBEvenet(Widget* src, SDL_Event* event) {
	if (src == NULL || event == NULL) {
		return 0; //Better to return an error value
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	if(castData->show==false){
		return 0;
	}
	if (event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, castData->location)) {
			return 1;
		}
	}
	return 0;
}

void drawSB(Widget* src) {
	if (src==NULL){
		return;
	}
	SimpleButton* castData = (SimpleButton*) src->data;
	if(castData->show==true){
		if(castData->buttonPressedTexture==NULL){
			SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,	castData->location);
		}
		else{
			if(castData->active==true){
				SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,	castData->location);
			}
			else{
				SDL_RenderCopy(castData->windowRenderer, castData->buttonPressedTexture, NULL,	castData->location);
			}
		}

	}
}
