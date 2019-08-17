#include "GUI_PieceButton.h"

Widget* createPB(SDL_Renderer* windowRender, SDL_Rect* location,const char* image,bool show) {
	if (windowRender == NULL || location == NULL || image == NULL ) {
		return NULL ;
	}

	Widget* res = (Widget*) malloc(sizeof(Widget));
	PieceButton* data = (PieceButton*) malloc(sizeof(PieceButton));
	SDL_Surface* ls = SDL_LoadBMP(image);
	SDL_SetColorKey(ls, SDL_TRUE,SDL_MapRGB(ls->format, 40, 0, 40));
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(windowRender,ls);
	if (res == NULL || data == NULL || ls == NULL|| buttonTexture == NULL) {
		free(res);
		free(data);
		SDL_FreeSurface(ls);
		SDL_DestroyTexture(buttonTexture);
		return NULL ;
	}
	SDL_FreeSurface(ls);
	data->buttonTexture = buttonTexture;
	data->location = copyRect(location);
	data->windowRenderer = windowRender;
	data->show=show;
	res->destroyWidget = destroyPB;
	res->drawWidget = drawPB;
	res->handleEvent = handlePBEvenet;
	res->data = data;
	return res;
}
void destroyPB(Widget* src) {
	if (src == NULL ) {
		return;
	}
	PieceButton* castData = (PieceButton*) src->data;
	free(castData->location);
	SDL_DestroyTexture(castData->buttonTexture);
	free(castData);
	free(src);
}

int handlePBEvenet(Widget* src, SDL_Event* event) {
	if (src == NULL || event == NULL) {
		return 0; //Better to return an error value
	}
	PieceButton* castData = (PieceButton*) src->data;
	if(castData->show==false){
		return 0;
	}
	if (event->type == SDL_MOUSEMOTION||event->type == SDL_MOUSEBUTTONDOWN||event->type == SDL_MOUSEBUTTONUP) {
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;
		if (SDL_PointInRect(&point, castData->location)) {
			return 1;
		}
	}
	return 0;
}

void drawPB(Widget* src) {
	if (src == NULL ) {
		return;
	}
	PieceButton* castData = (PieceButton*) src->data;
	if(castData->show==true){
		SDL_RenderCopy(castData->windowRenderer, castData->buttonTexture, NULL,	castData->location);
	}
	else{
	}
}
