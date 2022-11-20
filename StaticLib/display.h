#define display_H
#include <stm32f10x.h>

void display_fill(uint8_t filler);
void put_pixel(uint8_t x, uint8_t y, uint8_t state);