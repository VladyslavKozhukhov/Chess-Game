#ifndef GUI_SettingsWin_H_
#define GUI_SettingsWin_H_
#include "../settings.h"
#include "GUI_SimpleButton.h"

typedef enum {
	SETTINGS_EVENT_ONE_PLAYER,
	SETTINGS_EVENT_TWO_PLAYERS,
	SETTINGS_EVENT_NEXT,
	SETTINGS_EVENT_START,
	SETTINGS_EVENT_BACK,
	SETTINGS_NOOB,
	SETTINGS_EASY,
	SETTINGS_MODERATE,
	SETTINGS_HARD,
	SETTINGS_WHITE_COLOR,
	SETTINGS_BLACK_COLOR,
	SETTINGS_EVENT_QUIT,
	SETTINGS_EVENT_INVALID_ARGUMENT,
	SETTINGS_EVENT_NONE,
	SETTINGS_EVENT_UPDATE,
} SETTINGS_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	Widget** widgets;
	int numOfWidgets;
	bool first;
	Settings settings;
}SettingsWin;

SettingsWin* settingsWinCreate();
Widget** createSettingsWinWidgets(SDL_Renderer* renderer);
void settingsWinDraw(SettingsWin*);
void settingsWinHide(SettingsWin* src);
void settingsWinShow(SettingsWin* src);
void settingsWinDestroy(SettingsWin*);
void settingsWinWidgetsDestroy(Widget** widgets);
SETTINGS_EVENT settingsWinHandleEvent(SettingsWin* src, SDL_Event* event);

#endif
