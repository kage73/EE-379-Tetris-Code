#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

#define EMPTY 0
#define NON_EMPTY 1

typedef struct {
	int data[BOARD_WIDTH*BOARD_HEIGHT];
} Board;

void	board_newBoard(Board* board);

void	board_copyBoard(Board* dst, Board* src);

void	board_setBlock(Board* board, int x, int y, int set);
int		board_getBlock(Board* board, int x, int y);

void	board_addPieceToBoard(Board* board, Piece* piece, int x, int y);
void	board_removePieceFromBoard(Board* board, Piece* piece, int x, int y);
void	board_movePiece(Board* board, Piece* piece, int x0, int y0, int x, int y);

int		board_firstFullRow(Board* board);
void	board_removeRow(Board* board, int row);

int		board_isCollidingPiece(Board* board, Piece* piece, int x, int y);
int		board_isCollidingLeftRight(Piece* piece, int x, int y);
int		board_isCollidingBottom(Piece* piece, int x, int y);


#endif
