#include "piece.h"

void	piece_newPiece(Piece* piece, int width, int height) {
	int i;
	piece->width = width;
	piece->height = height;
	
	
	for(i = 0; i < 6; i++) {
		piece->data[i] = EMPTY;
	}
}

void	piece_copy(Piece* dst, Piece* src) {
	int i;
	dst->width = src->width;
	dst->height = src->height;

	for(i = 0; i < 6; i++) {
		dst->data[i] = src->data[i];
	}
}

int		piece_getBlock(Piece* piece, int x, int y) {
	return piece->data[piece->width*y + x];
}

void	piece_rotate(Piece* piece) {
	int temp;
	int newData[6];
	int i, j, count = 0;
	for(i = piece->width-1; i >= 0; i--) {
		for(j = 0; j < piece->height; j++) {
			newData[count] = piece_getBlock(piece, i, j);
			count++;
		}
	}

	for(i = 0; i < 6; i++) {
		piece->data[i] = newData[i];
	}

	temp = piece->width;
	piece->width = piece->height;
	piece->height = temp;
}



void	piece_createL(Piece* piece) {
	piece->width = 3;
	piece->height = 2;
	piece->data[0] = NON_EMPTY;
	piece->data[1] = NON_EMPTY;
	piece->data[2] = NON_EMPTY;
	piece->data[3] = NON_EMPTY;
	piece->data[4] = EMPTY;
	piece->data[5] = EMPTY;
}

void	piece_createBackL(Piece* piece) {
	piece->width = 3;
	piece->height = 2;
	piece->data[0] = EMPTY;
	piece->data[1] = EMPTY;
	piece->data[2] = NON_EMPTY;
	piece->data[3] = NON_EMPTY;
	piece->data[4] = NON_EMPTY;
	piece->data[5] = NON_EMPTY;
}

void	piece_createZ(Piece* piece) {
	piece->width = 3;
	piece->height = 2;
	piece->data[0] = NON_EMPTY;
	piece->data[1] = NON_EMPTY;
	piece->data[2] = EMPTY;
	piece->data[3] = EMPTY;
	piece->data[4] = NON_EMPTY;
	piece->data[5] = NON_EMPTY;
}

void	piece_createBackZ(Piece* piece) {
	piece->width = 3;
	piece->height = 2;
	piece->data[0] = EMPTY;
	piece->data[1] = NON_EMPTY;
	piece->data[2] = NON_EMPTY;
	piece->data[3] = NON_EMPTY;
	piece->data[4] = NON_EMPTY;
	piece->data[5] = EMPTY;
}

void	piece_createT(Piece* piece) { 
	piece->width = 3;
	piece->height = 2;
	piece->data[0] = EMPTY;
	piece->data[1] = NON_EMPTY;
	piece->data[2] = EMPTY;
	piece->data[3] = NON_EMPTY;
	piece->data[4] = NON_EMPTY;
	piece->data[5] = NON_EMPTY;
}

void	piece_createLine(Piece* piece) {
	piece->width = 1;
	piece->height = 4;
	piece->data[0] = NON_EMPTY;
	piece->data[1] = NON_EMPTY;
	piece->data[2] = NON_EMPTY;
	piece->data[3] = NON_EMPTY;
	piece->data[4] = EMPTY;
	piece->data[5] = EMPTY;
}

void	piece_createSquare(Piece* piece) {
	piece->width = 2;
	piece->height = 2;
	piece->data[0] = NON_EMPTY;
	piece->data[1] = NON_EMPTY;
	piece->data[2] = NON_EMPTY;
	piece->data[3] = NON_EMPTY;
	piece->data[4] = EMPTY;
	piece->data[5] = EMPTY;
}
