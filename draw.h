#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include "board.h"
#include "piece.h"
#include "GLCD.h" 

#define BLOCK_SIZE 16

void	draw_rect(int px, int py, int width, int height, unsigned short color);
void	draw_fillRect(int px, int py, int width, int height, unsigned short color);

void	draw_block(int px, int py, unsigned short color);

void	draw_previewPiece(Piece* piece);
int	draw_board(Board* previousBoard, Board* board);
void draw_forceBoard(Board* board);

void	draw_initialGui(void);
void	draw_score(int score);
void	draw_level(int level);

#endif
