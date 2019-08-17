#ifndef GUI_MANAGER_H_
#define GUI_MANAGER_H_
#include <stdbool.h>
#include <SDL_events.h>
#include <SDL_messagebox.h>
#include "GUI_SettingsWin.h"
#include "GUI_LoadWin.h"
#include "GUI_GameWin.h"
#include "GUI_MainWin.h"
#include "GUI_Common.h"
#define NUM_OF_SLOTS 5
typedef enum{
	MAIN_WINDOW_ACTIVE,
	GAME_WINDOW_ACTIVE,
	SETTINGS_WINDOW_ACTIVE,
	LOAD_WINDOW_ACTIVE,
	SAVE_WINDOW_ACTIVE,
}ACTIVE_WINDOW;


typedef struct {
	SettingsWin* settingsWin;
	LoadWin* loadWin;
	GameWin* gameWin;
	MainWin* mainWin;
	ACTIVE_WINDOW activeWin;
} GuiManager;
typedef enum{
	MANAGER_QUIT,
	MANAGER_NONE,
	MANAGER_UPDATE,
}MANAGER_EVENET;


GuiManager* managerCreate();

void managerDestroy(GuiManager* src);

void managerDraw(GuiManager* src);
MANAGER_EVENET handleManagerDueToLoadEvent(GuiManager* src,LOAD_EVENT event);
MANAGER_EVENET handleManagerDueToGameEvent(GuiManager* src,GAME_EVENT event);
MANAGER_EVENET managerHandleEvent(GuiManager* src, SDL_Event* event);
MANAGER_EVENET handleManagerDueToMainEvent(GuiManager* src,MAIN_EVENT event);
MANAGER_EVENET handleManagerDueToSettingsEvent(GuiManager* src,SETTINGS_EVENT event);

#endif
