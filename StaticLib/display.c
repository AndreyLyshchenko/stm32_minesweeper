#include "display.h"
#include "spi.h"

static uint8_t Bit_map[128][8];

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

void put_pixel(uint8_t x, uint8_t y, uint8_t state)
{
    uint8_t x_up,x_low,page_number,page_pos;
    if (state==0 || state==1)
    {
        x_up = x >> 4;
        x_low = x & 0b00001111;  

        page_number = y/8;
        page_pos = 0;
        page_pos = 1<<y%8;
        if (state==0)
        {
            Bit_map[x][page_number] &=~page_pos;
        }
        else
        {
            Bit_map[x][page_number] |=page_pos; 
        }
        
        GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
        GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

        SPI1_Write(0xB0|page_number);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

        SPI1_Write(0x00|x_low);
        SPI1_Write(0x10|x_up);
       
        // SPI1_Write(0x00|x_low);				// Seting column lower bit 
        // SPI1_Write(0x10|x_up);				// Seting column upper bit
        while (SPI1->SR & SPI_SR_BSY);

        GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
        SPI1_Write(Bit_map[x][page_number]);			 // Turning off pixels
        while (SPI1->SR & SPI_SR_BSY);

        GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection

        
    } 
}