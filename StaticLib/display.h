#define display_H
#include <stm32f10x.h>
#define VIRTUAL 1
#define REAL 0
#define QUEUE_LENGTH 1024

void display_fill(uint8_t filler);
void put_pixel(uint8_t x, uint8_t y, uint8_t state, uint8_t virtual);
void draw_changes(void);

