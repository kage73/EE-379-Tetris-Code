#include "tetris.h"
#include "GLCD.h"
#include "controls.h"
#include "draw.h"
#include "board.h"

#include <time.h> 
#include <stdlib.h>  

int score, level, numRows;

Board previousBoard;
Board board;

int x, y;
Piece activePiece;
Piece nextPiece;

Piece pieces[7];

int scoreFlag;
int levelFlag;
int previewFlag;
int loseFlag;


int leftLock;
int rightLock;
int downLock;
int rotateLock;

int waitTime;
int waitCount;

void 	tetris_initPieces() {
	piece_createL(pieces + 0);
	piece_createBackL(pieces + 1);
	piece_createZ(pieces + 2);
	piece_createBackZ(pieces + 3);
	piece_createLine(pieces + 4);
	piece_createSquare(pieces + 5);
	piece_createT(pieces + 6);
}

void	tetris_randPiece(Piece* piece) {
	int index = rand() % 7;
	piece_copy(piece, pieces + index);
}

void	tetris_newTetris() {
	score = 0;
	level = 1;
	numRows = 0;

	board_newBoard(&previousBoard);	
	board_newBoard(&board);

	tetris_randPiece(&activePiece);
	tetris_randPiece(&nextPiece);

	x = BOARD_WIDTH/2 - 1;
	y = 0;

	scoreFlag = 0;
	levelFlag = 0;
	previewFlag = 0;
	loseFlag = 0;
	
	leftLock = 0;
	rightLock = 0;
	downLock = 0;
	rotateLock = 0;

	waitTime = 10000;
	waitCount = 0;

	GLCD_Clear(Black);

	draw_initialGui();
	draw_score(score);
	draw_level(level);
	draw_previewPiece(&nextPiece);

	board_addPieceToBoard(&board, &activePiece, x, y);
	draw_forceBoard(&board);
}

void	tetris_update() {
	int actualTime;
	
	if(controls_isJoystickLeftPressed() && !leftLock) {
		board_removePieceFromBoard(&board, &activePiece, x, y);
		if(!board_isCollidingPiece(&board, &activePiece, x-1, y) &&
			!board_isCollidingLeftRight(&activePiece, x-1, y)) {
			x = x - 1;
		}
		board_addPieceToBoard(&board, &activePiece, x, y);
		leftLock = 1;
	}
	
	if(!controls_isJoystickLeftPressed() && leftLock) {
		leftLock = 0;
	}

	if (controls_isJoystickRightPressed() && !rightLock) {
		board_removePieceFromBoard(&board, &activePiece, x, y);
		if(!board_isCollidingPiece(&board, &activePiece, x+1, y) &&
			!board_isCollidingLeftRight(&activePiece, x+1, y)) {
			x = x + 1;
		}
		board_addPieceToBoard(&board, &activePiece, x, y);
		
		rightLock = 1;
	}
	
	if(!controls_isJoystickRightPressed() && rightLock) {
		rightLock = 0;
	}

	if (controls_isJoystickUpPressed() && !rotateLock) {
		Piece rotPiece;
		board_removePieceFromBoard(&board, &activePiece, x, y);
		piece_copy(&rotPiece, &activePiece);
		piece_rotate(&rotPiece);

		if(!board_isCollidingPiece(&board, &rotPiece, x, y) &&
			!board_isCollidingLeftRight(&rotPiece, x, y) &&
			!board_isCollidingBottom(&rotPiece, x, y)) {

			piece_copy(&activePiece, &rotPiece);
		}

		board_addPieceToBoard(&board, &activePiece, x, y);
		
		rotateLock = 1;
	}
	
	if (!controls_isJoystickUpPressed() && rotateLock) {
		rotateLock = 0;
	}

	if(controls_isJoystickDownPressed()) {
		actualTime = 1000;
	}else {
		actualTime = waitTime;
	}

	if(waitCount >= actualTime){
		board_removePieceFromBoard(&board, &activePiece, x, y);
		if(!board_isCollidingPiece(&board, &activePiece, x, y+1) &&
			!board_isCollidingBottom(&activePiece, x, y+1)) {
				board_addPieceToBoard(&board, &activePiece, x, y+1);
				y = y+1;
		} else {
			int row;
			board_addPieceToBoard(&board, &activePiece, x, y);
			row = board_firstFullRow(&board);
			while ( row > -1 ) {
				board_removeRow(&board, row);
				tetris_addToScore();
				row = board_firstFullRow(&board);
			}

			piece_copy(&activePiece, &nextPiece);
			tetris_randPiece(&nextPiece);
			x = BOARD_WIDTH/2 - 1;
			y = 0;
			previewFlag = 1;
			if(board_isCollidingPiece(&board, &activePiece, x, y)) {
				loseFlag = 1;
			}
		}
		waitCount = 0;
	} else {
		waitCount++;
	}
}


void	tetris_render() {
	int changed = draw_board(&previousBoard, &board);

	if(changed) {
		board_copyBoard(&previousBoard, &board);
	}	
	
	if(scoreFlag) {
		draw_score(score);
		scoreFlag = 0;
	}
	
	if(levelFlag) {
		draw_level(level);
		levelFlag = 0;
	}

	if(previewFlag) {
		draw_previewPiece(&nextPiece);
		previewFlag = 0;
	}
}

void tetris_addToScore() {
	int previousLevel;
	numRows++;
	score += 10*level ;
	
	previousLevel = level;
	level = (numRows / 10) + 1;
	if(level != previousLevel){
		levelFlag = 1;
		if(waitTime - WAIT_TIME_DROP >= 1000){
			waitTime -= WAIT_TIME_DROP;
		}
	}
	scoreFlag = 1;
}

int tetris_hasLost(void){
	return loseFlag;
}


