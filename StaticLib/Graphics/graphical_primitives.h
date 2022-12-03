#ifndef graphical_primitives_H
    #define graphical_primitives_H
    #include <stm32f10x.h>
    #include <stdlib.h>
    #include "../constant_set.h"
    #include "../spi.h"

    void display_fill(uint8_t filler);
    void put_pixel(uint8_t x, uint8_t y, uint8_t state, uint8_t virtual);
    void draw_changes(void);
    void line(int x1, int y1, int x2, int y2, uint8_t state, uint8_t virtual);
    void rectangle(int x1,int y1, int x2, int y2, uint8_t border_state, uint8_t filler,  uint8_t virtual);
    void copy_map(uint8_t  array_a[128][8], uint8_t  array_b[128][8]);
    void load_map(uint8_t  array_a[128][8], uint8_t  array_b[128][8]);
    void load_image_from_array(uint8_t *image, uint8_t top_left_x, uint8_t top_left_y, uint8_t bottom_right_x, uint8_t bottom_right_y);

#endif