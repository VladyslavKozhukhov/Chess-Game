#ifndef PARSER_H_
#define PARSER_H_
#include "AlphaBetaMinimax.h"
typedef enum command_e{
	GAME_MODE,
	DIFFICULTY,
	USER_COLOR,
	LOAD,
	DEFAULT,
	PRINT_SETTINGS,
	QUIT,
	RESTART,
	UNDO_MOVE,
	START,
	MOVE,
	SAVE,
	INVALID_LINE,
	GET_MOVES,
	CASTLE
} COMMAND_GAME;


typedef struct{
	COMMAND_GAME cmd;
	bool validArg;
	int arg;
	bool validIntArg;
	bool validStrArg;
	Move move;
	char* str;
} Command;

Command gameSetting(Settings* settings);
Command userInput(Game* game);
bool parserIsInt(const char* str);
Command parserPraseLine(const char* str);

#endif
