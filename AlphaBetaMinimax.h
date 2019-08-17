#ifndef ALPHABETAMINIMAX_H_
#define ALPHABETAMINIMAX_H_
#include "Game.h"
/**
 *	Calculates the scoring of the game-board, according to the pieces of each user at the game.
 *	@param game - the current game, first - symbol of the player that called the function.
 *	@return
 *	the score, according to the score function from the instructions
 */
int gamescore(Game* game,char first);
/**
 *	bestmove alpha beta minimax
 */
int alphabeta(Game* game,int alpha,int beta,int max_player,char first,int depth);
/**
 *	suggest best move to ai
 */
Move chooseBestMove(Game* game,int depth);
/**
 *  max between x and y.
 */
int max(int x,int y);
/**
 * 	min between x and y.
 */
int min(int x, int y);
#endif
