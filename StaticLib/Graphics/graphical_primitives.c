#include "graphical_primitives.h"

uint8_t Bit_map[128][8];
uint8_t Board[128][8];
uint8_t Game_UI[128][8];
uint8_t Menu_UI[128][8];
uint16_t Page_queue[QUEUE_LENGTH];

///@param filler 8-bit vertical pattern, most significant bit is a physically lower one
void display_fill(uint8_t filler)
{
    uint8_t page_number =0b000; //0b111 (7) max
    GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
    for (uint8_t i = 0; i < DISPLAY_PAGE_COUNT; i++)
    {
        page_number = i;
        GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

        SPI1_Write(0xB0|i);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

        SPI1_Write(0x00);				// Seting column lower bit 
        SPI1_Write(0x10);				// Seting column upper bit
        while (SPI1->SR & SPI_SR_BSY);  
        uint8_t x_pos = 0b00000000; //0b01111111 (128) max

        for(uint8_t j = 0; j < DISPLAY_WIDTH; j++)
        {
            x_pos=j;
            GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
            SPI1_Write(filler);			 // Turning off pixels
            while (SPI1->SR & SPI_SR_BSY);
            Bit_map[x_pos][page_number] = filler;            
        }
    }
    GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
}

 
/// @param state 1 - on, 0 - off
/// @param virtual if 0 - PAGE, containing pixel, will be updated immediately
void put_pixel(uint8_t x, uint8_t y, uint8_t state, uint8_t virtual)
{
    uint8_t x_up,x_low,page_number,page_pos;
    if (state==0 || state==1)
    {
        page_number = y/8;
        page_pos = 0;
        page_pos = 1<<(y%8);
        if (state==0)
        {
            Bit_map[x][page_number] &=~page_pos;
        }
            else
            {
                Bit_map[x][page_number] |=page_pos; 
            }
        if (!virtual)   // Drawing right now
        {
            x_up = x >> 4;          // Splitting column address between two address registers
            x_low = x & 0b00001111; // 

            GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
            GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

            SPI1_Write(0xB0|page_number);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

            SPI1_Write(0x00|x_low);
            SPI1_Write(0x10|x_up);

            while (SPI1->SR & SPI_SR_BSY);

            GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
            SPI1_Write(Bit_map[x][page_number]);	// Drawin page on display
            while (SPI1->SR & SPI_SR_BSY);

            GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
        }
            else 
            {
                // Putting info about page into the queue (to draw page later on)
                // This info contains X and Y page coordinates + special marker 
                uint16_t page_flag = 0;
                page_flag |= x<<3;
                page_flag |= page_number;
                page_flag |= 1<<11; // to prevent ignoring (0,0) address 
                for (uint16_t i = 0; i < QUEUE_LENGTH; i++)
                {
                    if (Page_queue[i] != 0)
                    {
                        if (Page_queue[i] == page_flag) // There is no need to mark this page for drawing
                        {                               // if we already done this before
                            break;
                        }
                    } 
                        else
                        {
                            Page_queue[i] = page_flag;
                            break;
                        }
                }
            }
    } 
}

///@brief Drawing marked pages  
void draw_changes(void)
{
    if (Page_queue[0]!=0)
    {
        GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
        for (uint16_t i = 0; i < QUEUE_LENGTH; i++)
        {
            if (Page_queue[i]!=0) // If we have something to draw
            {
                GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

                uint8_t column_number = Page_queue[i]>>3;
                uint8_t page_number = Page_queue[i] & 0b0000000000000111;

                uint8_t x_up = column_number >> 4;          // Splitting column address between two address registers
                uint8_t x_low = column_number & 0b00001111; // 

                SPI1_Write(0xB0|page_number);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

                SPI1_Write(0x00|x_low);
                SPI1_Write(0x10|x_up);

                while (SPI1->SR & SPI_SR_BSY);

                GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
                SPI1_Write(Bit_map[column_number][page_number]);			 // Drawing page
                while (SPI1->SR & SPI_SR_BSY); 

                Page_queue[i]=0;   
            } 
                else
                {
                    break;
                }    
        }
        GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
    }
}
/// @param state 0 - black line, 1 - white line
/// @param virtual if 0 - line will be drawn immediately
void line(int x1, int y1, int x2, int y2, uint8_t state, uint8_t virtual)
{
    int buf;

    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    
    int error = 0;
    // While using Bresenham's line algorithm we need to ceep in mind 8 cases:
    // *      II    *    III    *
    //   I  *       *       *  IV
    //          *       *
    // *    *   *   *   *   *   *
    //   VIII   *       *   V
    //      *  VII  *    VI *
    // *            *           *


    if (deltax>=deltay)
        {
        if (x1>x2)
        {
            buf = x2;
            x2 = x1;
            x1 = buf;
            buf = y2;
            y2=y1;
            y1=buf;
        }
        
        int deltaerr = (deltay + 1);
        int y = y1;
        int diry = y2 - y1;
        if (diry > 0)
        { 
            diry = 1;
        }   
        if (diry < 0)
        { 
            diry = -1;
        }   
        for (int x = x1; x <= x2;x++)
        {
            put_pixel(x,y,state,virtual);
            error = error + deltaerr;
            if (error >= (deltax + 1))
            {
                y = y + diry;
                error = error - (deltax + 1);
            }
        }
    }
        else
        {
            if (y1>y2)
            {
                buf = y2;
                y2 = y1;
                y1 = buf;
                buf = x2;
                x2=x1;
                x1=buf;
            }

            int deltaerr = (deltax + 1);
            int x = x1;
            int dirx = x2 - x1;
            if (dirx > 0)
            { 
                dirx = 1;
            }   
            if (dirx < 0)
            { 
                dirx = -1;
            }   
            for (int y = y1; y <= y2;y++)
            {
                put_pixel(x,y,state,virtual);
                error = error + deltaerr;
                if (error >= (deltay + 1))
                {
                    x = x + dirx;
                    error = error - (deltay + 1);
                }
            }
        }       
 
}

/// @param border_state 0 - black, 1 - white 
/// @param filler 0 - black, 1 - white, everything else - no fill
/// @param virtual  if 0 - line will be drawn immediately 
void rectangle(int x1,int y1, int x2, int y2, uint8_t border_state, uint8_t filler,  uint8_t virtual)
{
    if (x1>x2)
    {
        int buf;
        buf = x1;
        x1 = x2;
        x2 = buf;
    }

    if (y1>y2)
    {
        int buf;
        buf = y1;
        y1 = y2;
        y2 = buf;
    }
    line(x1,y1,x2,y1,border_state,virtual);
    line(x2,y1,x2,y2,border_state,virtual);
    line(x2,y2,x1,y2,border_state,virtual);
    line(x1,y2,x1,y1,border_state,virtual);

    if ((filler == 0) || (filler==1))
    {
        if (((x2-x1) > 0) || ((y2-y1) > 0))
        {
            for (int i = x1+1 ; i < x2; i++)
            {
                line(i,y1+1,i,y2-1,filler,virtual);
            }        
        }
    }
}

 void reset_map(uint8_t array[DISPLAY_WIDTH][DISPLAY_PAGE_COUNT])
 {
    for (int i = 0; i < DISPLAY_WIDTH; i++)
    {
        for (int j = 0; j < DISPLAY_PAGE_COUNT; j++)
        {
            array[i][j] = 0x00;
        }
    } 
 }

/// @brief Copying bitmap from array_b to array_a WITHOUT redrawing of screen
void copy_map(uint8_t  array_a[128][8], uint8_t  array_b[128][8])
{
    for (int i = 0; i < DISPLAY_WIDTH; i++)
    {
        for (int j = 0; j < DISPLAY_PAGE_COUNT; j++)
        {
            array_a[i][j] = array_b[i][j];
        }
    }
}

/// @brief Copying bitmap from array_b to array_a WITH redrawing of screen
void load_map(uint8_t  array_a[128][8], uint8_t  array_b[128][8])
{
    for (int i = 0; i < QUEUE_LENGTH; i++) // Unimplemented changes are no longer our concern
    {
        if (Page_queue[i] != 0)
        {
            Page_queue[i]=0;
        } 
            else
            {
                break;
            }
    }
    for (uint8_t i = 0; i < DISPLAY_WIDTH; i++)
    {
        for (int j = 0; j < DISPLAY_PAGE_COUNT; j++)
        {
            {
                GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
                GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

                SPI1_Write(0xB0|j);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

                SPI1_Write(0x00|(i & 0b00001111));
                SPI1_Write(0x10|(i>>4));

                while (SPI1->SR & SPI_SR_BSY);

                GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
                SPI1_Write(array_b[i][j]);			 
                while (SPI1->SR & SPI_SR_BSY);

                GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
            }    
            array_a[i][j] = array_b[i][j];
        }
    }
}


/// @image Array must be uint8_t (char) type and have folloving structure: 
/// For image[8][2] = {1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,}:
/// Array must be organized as:  Array[] = {0xF0, 0x0F};
void load_image_from_array(const uint8_t *image, uint8_t top_left_x, uint8_t top_left_y, uint8_t bottom_right_x, uint8_t bottom_right_y)
{
    for (uint8_t y = top_left_y; y < (bottom_right_y+1); y++)
    { 
        for (uint8_t x = top_left_x; x < (bottom_right_x+1); x++)
        {
            put_pixel(x,y, (0b10000000 & (*(image + (x/8)+(y*16)) << (x%8)))>>7,VIRTUAL);
        }
    }
}

void load_piktogramm_from_array(struct set_info info, uint8_t position_in_set, uint8_t screen_x, uint8_t screen_y)
{
    for (uint8_t x = 0; x < info.x_size; x++)
    {
        for (uint8_t y = 0; y < info.y_size; y++)
        {
            put_pixel(screen_x+x-1,screen_y+y-1,(((*(info.pointer+((x/8)+(y*info.item_count)+position_in_set)))>>(7-(x%8)))&0b1),VIRTUAL);
        }
    }
    
}

void inicialise_info_about_graphic_arrays()
{
    ingame_piktogramms.item_count = 6;
    ingame_piktogramms.x_size = 7;
    ingame_piktogramms.y_size =7;
    ingame_piktogramms.pointer = game_piktogramms;

    ingame_numbers.item_count = 9;
    ingame_numbers.x_size = 7;
    ingame_numbers.y_size =7;
    ingame_numbers.pointer = game_numbers;

    menu_difficulty.item_count = 3*5;
    menu_difficulty.x_size = 40;
    menu_difficulty.y_size = 8;
    menu_difficulty.pointer = difficulties_set; 
}