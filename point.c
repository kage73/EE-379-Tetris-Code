#include "point.h"

void	point_lcdRotate(int* xDst, int* yDst, int x, int y) {
	*xDst = LCD_WIDTH - y;
	*yDst = x;
}
