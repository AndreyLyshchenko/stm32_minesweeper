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
    void reset_map(uint8_t array[DISPLAY_WIDTH][DISPLAY_PAGE_COUNT]);
    void copy_map(uint8_t  array_a[DISPLAY_WIDTH][DISPLAY_PAGE_COUNT], uint8_t  array_b[DISPLAY_WIDTH][DISPLAY_PAGE_COUNT]);
    void load_map(uint8_t  array_a[DISPLAY_WIDTH][DISPLAY_PAGE_COUNT], uint8_t  array_b[DISPLAY_WIDTH][DISPLAY_PAGE_COUNT]);
    void load_image_from_array(const uint8_t *image, uint8_t top_left_x, uint8_t top_left_y, uint8_t bottom_right_x, uint8_t bottom_right_y);
    void load_piktogramm_from_array(struct set_info info, uint8_t position_in_set, uint8_t screen_x, uint8_t screen_y);
    void inicialise_info_about_piktogramm_arrays();
#endif