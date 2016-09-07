#include "draw.h"
#include "board.h"
#include "GLCD.h"
#include "point.h"
#include "lpc17xx.h"
#include <stdio.h>

#define PREVIEW_PIECE_X 170
#define PREVIEW_PIECE_Y 16

void	draw_rect(int px, int py, int width, int height, unsigned short color) {
	//int i, j;
	//GLCD_SetTextColor(color);
	draw_fillRect(px,py,width,height,color);
	draw_fillRect(px+1,py+1,width-2,height-2,Black);
	
	/*for(j = 0; j < width; j++) {
		for(i = 0; i < height; i++) {
	
			if( i == 0 || i == width-1 || j == 0 || j == height-1){
				int x, y;
				point_lcdRotate(&x, &y, i+px, j+py);
				GLCD_PutPixel(x, y);
			}
		}
	}*/
}



void	draw_fillRect(int px, int py, int width, int height, unsigned short color) {
	int i, j;
	GLCD_SetTextColor(color);
	for(j = 0; j < height; j++) {
		for(i = 0; i < width; i++) {
			int x, y;
			point_lcdRotate(&x, &y, i+px, j+py);
			GLCD_PutPixel(x, y);
		}
	}
}

void	draw_block(int px, int py, unsigned short color) {
	int pad = 2;
	draw_fillRect(px + pad, py + pad, BLOCK_SIZE - 2*pad, BLOCK_SIZE - 2*pad, color);
}




int		draw_board(Board* previousBoard, Board* board) {
	int hasChanged = 0;
	int i, j;
	for(j = 0; j < BOARD_HEIGHT; j++) {
		for(i = 0; i < BOARD_WIDTH; i++) {
			if(board_getBlock(previousBoard, i, j) != board_getBlock(board, i, j)) {
				hasChanged = 1;
				if(board_getBlock(board, i, j) == NON_EMPTY) {
					draw_block(i*BLOCK_SIZE, j*BLOCK_SIZE, Green);
				} else {
					draw_block(i*BLOCK_SIZE, j*BLOCK_SIZE, Black);
				}
			}
		}
	}

	return hasChanged;
}
void draw_forceBoard(Board* board){
	int i, j;
	for(j = 0; j < BOARD_HEIGHT; j++) {
		for(i = 0; i < BOARD_WIDTH; i++) {
				if(board_getBlock(board, i, j) == NON_EMPTY) {
					draw_block(i*BLOCK_SIZE, j*BLOCK_SIZE, Green);
				} else {
					draw_block(i*BLOCK_SIZE, j*BLOCK_SIZE, Black);
				}
		}
	}
}

void	draw_previewPiece(Piece* piece) {
	int i, j;
	
	draw_rect(PREVIEW_PIECE_X, PREVIEW_PIECE_Y, 3*BLOCK_SIZE, 4*BLOCK_SIZE, White);
	
	
	for(j = 0; j < piece->height; j++) {
		for(i = 0; i < piece->width; i++) {
			if(piece_getBlock(piece, i, j) == NON_EMPTY) {
				draw_block(i*BLOCK_SIZE + PREVIEW_PIECE_X, j*BLOCK_SIZE + PREVIEW_PIECE_Y, Green);
			} else {
				draw_block(i*BLOCK_SIZE + PREVIEW_PIECE_X, j*BLOCK_SIZE + PREVIEW_PIECE_Y, Black);
			}
		}
	}
}

void	draw_initialGui() {
	draw_rect(0, 0, BOARD_WIDTH*BLOCK_SIZE, BOARD_HEIGHT*BLOCK_SIZE, White);
	draw_rect(PREVIEW_PIECE_X, PREVIEW_PIECE_Y, 3*BLOCK_SIZE, 4*BLOCK_SIZE, White);

	GLCD_SetTextColor(White);
	GLCD_DisplayString(8, 0, "SCORE:"); 
	GLCD_DisplayString(9, 0, "LEVEL:"); 
}
void	draw_score(int score) {
	char text[10];
	//draw_fillRect(0, 0, 0, 0, Black); 
	GLCD_SetTextColor(White);
	
	
	sprintf(text, "%d", score);
	GLCD_DisplayString(8, 6, (uint8_t*)text);
}

void	draw_level(int level) {
	char text[10];
	//draw_fillRect(0, 0, 0, 0, Black); 
	GLCD_SetTextColor(White);
	
	
	sprintf(text, "%d", level);
	GLCD_DisplayString(9, 6, (uint8_t*)text);
}
