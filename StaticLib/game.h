#include <stm32f10x.h>
#include "display.h"

#define TILE_SIDE 11
#define BOARD_START_X 7
#define BOARD_START_Y 2
#define X_TILE_COUNT 10
#define Y_TILE_COUNT 5

void draw_board(void);
void select_tile (uint8_t x_number, uint8_t y_number);
void draw_mine(uint8_t x_number, uint8_t y_number);