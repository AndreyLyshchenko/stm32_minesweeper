#include "display.h"
#include "spi.h"

static uint8_t Bit_map[128][8];
static uint16_t Page_queue[QUEUE_LENGTH];


void display_fill(uint8_t filler)
{
    uint8_t page_number =0b000; //0b111 (7) max
    GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
    for (uint8_t i = 0; i < 8; i++)
    {
        page_number = i;
        GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

        SPI1_Write(0xB0|i);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

        SPI1_Write(0x00);				// Seting column lower bit 
        SPI1_Write(0x10);				// Seting column upper bit
        while (SPI1->SR & SPI_SR_BSY);  
        uint8_t x_pos = 0b00000000; //0b01111111 (128) max

        for(uint8_t j = 0; j < 128; j++)
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
        if (!virtual)
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
            SPI1_Write(Bit_map[x][page_number]);			 // Turning off pixels
            while (SPI1->SR & SPI_SR_BSY);

            GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
        }
            else 
            {
                uint16_t page_flag = 0;
                page_flag |= x<<3;
                page_flag |= page_number;
                page_flag |= 1<<11; // to prevent ignoring (0,0) address 
                for (int i = 0; i < QUEUE_LENGTH; i++)
                {
                    if (Page_queue[i] != 0)
                    {
                        if (Page_queue[i] == page_flag)
                        {
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

void draw_changes(void)
{
    if (Page_queue[0]!=0)
    {
        GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
        for (int i = 0; i < QUEUE_LENGTH; i++)
        {
            if (Page_queue[i]!=0)
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
                SPI1_Write(Bit_map[column_number][page_number]);			 // Turning off pixels
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

