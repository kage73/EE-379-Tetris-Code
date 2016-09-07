#ifndef PIECE_H
#define PIECE_H

#define EMPTY 0
#define NON_EMPTY 1

typedef struct {
	int width, height;
	int data[6];
} Piece;

void	piece_newPiece(Piece* piece, int width, int height);

void	piece_copy(Piece* dst, Piece* src);

int		piece_getBlock(Piece* piece, int x, int y);

void	piece_rotate(Piece* piece);



void	piece_createL(Piece* piece);
void	piece_createBackL(Piece* piece);
void	piece_createZ(Piece* piece);
void	piece_createBackZ(Piece* piece);
void	piece_createT(Piece* piece);
void	piece_createLine(Piece* piece);
void	piece_createSquare(Piece* piece);

#endif
