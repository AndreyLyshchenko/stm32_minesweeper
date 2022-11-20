#include "display.h"
#include "spi.h"

void display_fill(uint8_t filler)
{

    GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
    for (uint8_t i = 0; i < 8; i++)
    {
        GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

        SPI1_Write(0xB0|i);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

        SPI1_Write(0x00);				// Seting column lower bit 
        SPI1_Write(0x10);				// Seting column upper bit
        while (SPI1->SR & SPI_SR_BSY);

        for(uint8_t j = 0; j < 132; j++)
        {
            GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
            SPI1_Write(filler);			 // Turning off pixels
            while (SPI1->SR & SPI_SR_BSY);
        }
    }
    GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection
}

void put_pixel(uint8_t x, uint8_t y, uint8_t state)
{
    uint8_t x_up,x_low,page_no,page_pos;
    if (state==0 || state==1)
    {
        x_up = x >> 4;
        x_low = x & 0b00001111;  

        page_no = y/8;
        page_pos=0;
        page_pos = 1<<y%8;

        GPIOA->BSRR = GPIO_ODR_ODR4 << 16U; // Selecting display (CS=0) 
        GPIOA->BSRR = GPIO_ODR_ODR3 << 16U; //Selecting sending of command (A0=0)

        SPI1_Write(0xB0|page_no);		// Seting page address ((0xb0) command code + (0b0000<=i<=0b0111) page adress)

 
        SPI1_Write(0x00|x_low);
        SPI1_Write(0x10|x_up);
       
        // SPI1_Write(0x00|x_low);				// Seting column lower bit 
        // SPI1_Write(0x10|x_up);				// Seting column upper bit
        while (SPI1->SR & SPI_SR_BSY);

        GPIOA->BSRR = GPIO_ODR_ODR3; // Selecting sending of data
        SPI1_Write(page_pos);			 // Turning off pixels
        while (SPI1->SR & SPI_SR_BSY);

        GPIOA->BSRR = GPIO_ODR_ODR4; // Ending display selection

        
    } 
}