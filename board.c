#include "board.h"
#include "piece.h"
#include "GLCD.h"

void	board_newBoard(Board* board) {
	int i;
	for(i = 0; i < BOARD_WIDTH*BOARD_HEIGHT; i++) {
		board->data[i] = EMPTY;
		GLCD_SetBackColor(Black);
	}
}

void	board_copyBoard(Board* dst, Board* src) {
	int i;
	for(i = 0; i < BOARD_WIDTH*BOARD_HEIGHT; i++) {
		dst->data[i] = src->data[i];
	}
}

void	board_setBlock(Board* board, int x, int y, int set) {
	board->data[BOARD_WIDTH*y + x] = set;
}

int		board_getBlock(Board* board, int x, int y) {
	return board->data[BOARD_WIDTH*y + x];
}

void	board_addPieceToBoard(Board* board, Piece* piece, int x, int y) {
	int i, j;
	for(j = 0; j < piece->height; j++) {
		for(i = 0; i < piece->width; i++) {
			if(piece_getBlock(piece, i, j) == NON_EMPTY) {
				board_setBlock(board, x+i, y+j, NON_EMPTY); 
			}
		}
	}
}

void	board_removePieceFromBoard(Board* board, Piece* piece, int x, int y) {
	int i, j;
	for(j = 0; j < piece->height; j++) {
		for(i = 0; i < piece->width; i++) {
			if(piece_getBlock(piece, i, j) == NON_EMPTY) {
				board_setBlock(board, x+i, y+j, EMPTY); 
			}
		}
	}
}
void	board_movePiece(Board* board, Piece* piece, int x0, int y0, int x, int y) {
	board_removePieceFromBoard(board, piece, x0, y0);
	board_addPieceToBoard(board, piece, x, y);
}

int		board_firstFullRow(Board* board) {
	int i, j;
	for(j = 0; j < BOARD_HEIGHT; j++) {
		int isFull = 1;
		for(i = 0; i < BOARD_WIDTH; i++) {
			if(board_getBlock(board, i, j) == EMPTY) {
				isFull = 0;
				continue;
			}
		}
		if(isFull) {
			return j;
		}
	}
	return -1;
}

void	board_removeRow(Board* board, int row) {
	int i, j;

	for(i = 0; i < BOARD_WIDTH; i++) {
		board_setBlock(board, i, row, EMPTY);
	}


	for(j = row; j > 0; j--) {
		for(i = 0; i < BOARD_WIDTH; i++) {
			int upper = board_getBlock(board, i, j-1);
			board_setBlock(board, i, j, upper);
		}
	}


	for(i = 0; i < BOARD_WIDTH; i++) {
		board_setBlock(board, i, 0, EMPTY);
	}
}

int		board_isCollidingPiece(Board* board, Piece* piece, int x, int y) {
	int i, j;
	for(j = 0; j < piece->height; j++){
		for(i = 0; i < piece->width; i++) {
			if(piece_getBlock(piece, i, j) == NON_EMPTY && board_getBlock(board, x+i, y+j) == NON_EMPTY) {
				return 1;
			}
		}
	}

	return 0;
}

int		board_isCollidingLeftRight(Piece* piece, int x, int y) {
	return (x < 0 || x + piece->width > BOARD_WIDTH);
}
int		board_isCollidingBottom(Piece* piece, int x, int y) {
	return (y + piece->height > BOARD_HEIGHT);
}
