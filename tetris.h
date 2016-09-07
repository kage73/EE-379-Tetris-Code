#ifndef TETRIS_H
#define TETRIS_H

#include "board.h"
#include "piece.h"
#include "point.h"

#define WAIT_TIME_DROP 1000


int tetris_hasLost(void);

void	tetris_newTetris(void);

void	tetris_update(void);
void	tetris_render(void);

void	tetris_addToScore(void);

void 	tetris_initPieces(void);

void	tetris_randPiece(Piece* piece);

#endif
