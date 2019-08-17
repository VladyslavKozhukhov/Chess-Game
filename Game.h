#ifndef GAME_H_
#define GAME_H_
#include "ArrayList.h"
#include "settings.h"
#define HISTORY_SIZE 6
#define CHANGE_FOR_PRINT 65

typedef enum game_chess {
	INVALID_MOVE,
	INVALID_ARGUMENT,
	NO_HISTORY,
	SUCCESS,
	CHECK,
	TIE,
	CHECKMATE,
	CONTINUE
} CHESSMESSAGE;

typedef struct game_t {
	Settings set;
	Piece* gameBoard[8][8];
	Player* player1;
	Player* player2;
	char curPlayer;
	ArrayList* history;
}Game;
/*
 * create new game
 */
Game* gameCreate(int historySize);
/*
 * initalize new game with settings
 */
Game* gameInitalize(Game* game,Settings settings);
/*
 * Copy Game
 */
Game* gameCopy(Game* game);
/*
 * destroy chess game
 */
void gameDestroy(Game* game);
/*
 * Set move(ai)
 */
CHESSMESSAGE gameSetMove(Game* game, Move move);

int gameSetMoveAux(Game* game,Move* move);
/*
 * check if move is valid
 */
bool gameIsValidMove(Game* game,Move* move);
/*
 * check if fake move is valid
 */
bool gameFakeMove(Game* game, Move move);
/*
 * Undo
 */
CHESSMESSAGE gameUndoPrevMove(Game* game);
/*
 * undo last move
 */
void undoLastMove(Game* game);
void undoLastMoveAux(Game* game,Move* move);
/*
 * change turn
 */
void changeTurn(Game* game);
/*
 * print board
 */
CHESSMESSAGE printGameBoard(Game* game);
/*
 * get current player
 */
Player* gameGetCurPlayer(Game* game);
CHESSMESSAGE checkWinnerOrTie(Game* game);
void insertMoves(Game* game,Move move,ArrayList* moves);
void updateMove(Game* game,ArrayList* moves,Piece* piece,int x,int y,int i,int j);
bool gameCheck(Game* game);
bool gameCheckmate(Game* game);
/*
 * threads
 */
bool gameBlockThreat(Game* game,Piece* king,Piece* kingthreat);
Piece* threatDiagToLeftUpBishop(Game* game,int i,int j,char type);
Piece* threatByRook(Game* game,int i,int j,char type);
Piece* threatUpRook(Game* game,int i,int j,char type);
Piece* threatDownRook(Game* game,int i,int j,char type);
Piece* threatLeftRook(Game* game,int i,int j,char type);
Piece* threatRightRook(Game* game,int i,int j,char type);
bool gameBlockThreatQueen(Game* game,Piece* king,Piece* kingthreat);
Piece* threatDiagToRightDownBishop(Game* game,int i,int j,char type);
Piece* threatByKnight(Game* game,int i,int j,char type);
Piece* threatKnightHelper(Game* game,int i,int j,char type);
void printArrayListForGetMoves(ArrayList* arraylist,Game* game,int x,int y);
Piece* threatDiagToRightUpBishop(Game* game,int i,int j,char type);
Piece* threatDiagToLeftDownBishop(Game* game,int i,int j,char type);
bool gameTie(Game* game);
Piece* findThreatBasic(Game* game,int i,int j,int sum1,int sum2,char type);
Piece* threatBasic(Game* game,Move move);
Piece* findThreatBasic(Game* game,int i,int j,int sum1,int sum2,char type);

bool indexIsValid(int x,int y);
Piece* threatByQueen(Game* game,int i,int j,char type);
Piece* threatByKing(Game* game,int i,int j,char type);
Piece* findThreat(Game* game,int i,int j,int sum1,int sum2,char type);
Piece* gameThreat(Game* game,int i,int j);
Piece* threatByPawn(Game* game,int i,int j,char type);
Piece* threatByWhitePawn(Game* game,int i,int j,char type);
Piece* threatByBlackPawn(Game* game,int i,int j,char type);
Piece* threatByBishop(Game* game,int i,int j,char type);
bool gameBlockThreatBishop(Game* game,Piece* king,Piece* kingthreat);
bool gameBlockThreatRook(Game* game,Piece* king,Piece* kingthreat);


#endif
