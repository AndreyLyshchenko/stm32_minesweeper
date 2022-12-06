#include "buttons.h"

extern bool terminator;

int BtnClick(char IO_Port, int IO_Pin, char IO_Mode, uint32_t DefaultDelay, uint32_t HoldDelay) {
    int ErrCode = 0;
    GPIO_TypeDef* Port;
    int PortCode,PinCode,ModeCode,FunctionCode;
    uint32_t Pin = 0x0000;

    if (!LinkArrayIsSet) 
    {
        InitializingLinkArray();
        LinkArrayIsSet = true;
    }

    switch (IO_Port)
    {
    case 'A':
        Port = GPIOA;
        PortCode = 0b00000000;
        break;
    
    case 'B':
        Port = GPIOB;
        PortCode = 0b00010000;
        break;

    case 'C':
        Port = GPIOC;
        PortCode = 0b00100000;
        break;        
    
    default:
        ErrCode = 1;
        return ErrCode;
    }

    if (IO_Pin <= 15 && IO_Pin >=0)
     {
        Pin |= (1<<IO_Pin);
        PinCode = IO_Pin;
    } else 
    {
        ErrCode = 2;
        return ErrCode;
    }

    if (ErrCode==0)
    {
        bool IsPressed = Port->IDR & Pin; //0 - Pressed, 1 - Not Pressed
        if (!IsPressed) 
        {
            switch (IO_Mode)
            {
            case 'D':
                ModeCode = 0b00000000;
                FunctionCode = PortCode+ModeCode+PinCode;
                ErrCode = 7;
                FunctionLink[FunctionCode]();
                while (!IsPressed)
                {
                   IsPressed = Port->IDR & Pin; 
                   delay_us(DefaultDelay);
                }            
                break;
                
            case 'U':
                ModeCode = 0b01000000;
                FunctionCode = PortCode+ModeCode+PinCode;
                ErrCode=8;
                while (!IsPressed)
                {
                    IsPressed = Port->IDR & Pin; 
                    delay_us(DefaultDelay);
                }
                FunctionLink[FunctionCode]();
                
            case 'H':
                ModeCode = 0b10000000;
                FunctionCode = PortCode+ModeCode+PinCode;
                ErrCode = 9;
                while (!IsPressed)
                {
                    FunctionLink[FunctionCode]();                 
                    IsPressed = Port->IDR & Pin; 
                    delay_us(HoldDelay);
                }

                break;                                
            default:
                ErrCode = 3;
                return ErrCode;
            }
        }

       
    } else 
    {
        return ErrCode;
    }
    
return ErrCode;
}

void transfer_control_to_buttons()
{
    // All "button press" events organized in hierarchial order because of their mutual exclusiveness

	// Function BtnCLick is triggering Click event, according to its input data:
	// Port, Pin, ClickMode(OnPress -"D", OnRelease - "U", While holding -"H"), 
	// Defalut delay (for "D" and "U" mode) and Hold delay (for "H" mode).
	// Integer, returned by function, provides information about internal errors.
	// ErrCodes 7,8,9 are indicating successfull event generatin after corresponding button was pressed,
	// 0 - corresponding button was not pressed.

	while (1)
	{
		if (BtnClick('A',8,'D',10000,10000)==7){} // MID BUTTON	
		else if (BtnClick('B',12,'D',10000,10000)==7){} // UP BUTTON
			else if (BtnClick('B',13,'D',10000,10000)==7){} // DOWN BUTTON
				else if (BtnClick('B',14,'D',10000,10000)==7){} // LEFT BUTTON
					else if (BtnClick('B',15,'D',10000,10000)==7){} // RIGHT BUTTON
						else
						{
                            if (terminator!=true)
                            {
                                delay_us(333); // NOTHING
                            }
                            else
                            {
                                return;
                            }			
						}
	}
}

void InitializingLinkArray() 
{
    // DOWN
    // PORT A        
    FunctionLink[0b00000000] = ButtonClick_A_0_Down;
    FunctionLink[0b00000001] = ButtonClick_A_1_Down;
    FunctionLink[0b00000010] = ButtonClick_A_2_Down; 
    FunctionLink[0b00000011] = ButtonClick_A_3_Down;
    FunctionLink[0b00000100] = ButtonClick_A_4_Down;
    FunctionLink[0b00000101] = ButtonClick_A_5_Down;
    FunctionLink[0b00000110] = ButtonClick_A_6_Down;
    FunctionLink[0b00000111] = ButtonClick_A_7_Down;
    FunctionLink[0b00001000] = ButtonClick_A_8_Down;
    FunctionLink[0b00001001] = ButtonClick_A_9_Down;
    FunctionLink[0b00001010] = ButtonClick_A_10_Down;
    FunctionLink[0b00001011] = ButtonClick_A_11_Down;
    FunctionLink[0b00001100] = ButtonClick_A_12_Down;
    FunctionLink[0b00001101] = ButtonClick_A_13_Down;
    FunctionLink[0b00001110] = ButtonClick_A_14_Down;
    FunctionLink[0b00001111] = ButtonClick_A_15_Down;
                                 
    // DOWN 
    // PORT B
    FunctionLink[0b00010000] = ButtonClick_B_0_Down;
    FunctionLink[0b00010001] = ButtonClick_B_1_Down;
    FunctionLink[0b00010010] = ButtonClick_B_2_Down;
    FunctionLink[0b00010011] = ButtonClick_B_3_Down;
    FunctionLink[0b00010100] = ButtonClick_B_4_Down;
    FunctionLink[0b00010101] = ButtonClick_B_5_Down;
    FunctionLink[0b00010110] = ButtonClick_B_6_Down;
    FunctionLink[0b00010111] = ButtonClick_B_7_Down;
    FunctionLink[0b00011000] = ButtonClick_B_8_Down;
    FunctionLink[0b00011001] = ButtonClick_B_9_Down;
    FunctionLink[0b00011010] = ButtonClick_B_10_Down;
    FunctionLink[0b00011011] = ButtonClick_B_11_Down;
    FunctionLink[0b00011100] = ButtonClick_B_12_Down;
    FunctionLink[0b00011101] = ButtonClick_B_13_Down;
    FunctionLink[0b00011110] = ButtonClick_B_14_Down;
    FunctionLink[0b00011111] = ButtonClick_B_15_Down;
                                  
    //DOWN
    //PORT C
    FunctionLink[0b00100000] = ButtonClick_C_0_Down;
    FunctionLink[0b00100001] = ButtonClick_C_1_Down;
    FunctionLink[0b00100010] = ButtonClick_C_2_Down;
    FunctionLink[0b00100011] = ButtonClick_C_3_Down;
    FunctionLink[0b00100100] = ButtonClick_C_4_Down;
    FunctionLink[0b00100101] = ButtonClick_C_5_Down;
    FunctionLink[0b00100110] = ButtonClick_C_6_Down;
    FunctionLink[0b00100111] = ButtonClick_C_7_Down;
    FunctionLink[0b00101000] = ButtonClick_C_8_Down;
    FunctionLink[0b00101001] = ButtonClick_C_9_Down;
    FunctionLink[0b00101010] = ButtonClick_C_10_Down;
    FunctionLink[0b00101011] = ButtonClick_C_11_Down;
    FunctionLink[0b00101100] = ButtonClick_C_12_Down;
    FunctionLink[0b00101101] = ButtonClick_C_13_Down;
    FunctionLink[0b00101110] = ButtonClick_C_14_Down;
    FunctionLink[0b00101111] = ButtonClick_C_15_Down; 
    
    //UP
    //PORT A
    FunctionLink[0b01000000] = ButtonClick_A_0_Up;
    FunctionLink[0b01000001] = ButtonClick_A_1_Up;
    FunctionLink[0b01000010] = ButtonClick_A_2_Up;
    FunctionLink[0b01000011] = ButtonClick_A_3_Up;
    FunctionLink[0b01000100] = ButtonClick_A_4_Up;
    FunctionLink[0b01000101] = ButtonClick_A_5_Up;
    FunctionLink[0b01000110] = ButtonClick_A_6_Up;
    FunctionLink[0b01000111] = ButtonClick_A_7_Up;
    FunctionLink[0b01001000] = ButtonClick_A_8_Up;
    FunctionLink[0b01001001] = ButtonClick_A_9_Up;
    FunctionLink[0b01001010] = ButtonClick_A_10_Up;
    FunctionLink[0b01001011] = ButtonClick_A_11_Up;
    FunctionLink[0b01001100] = ButtonClick_A_12_Up;
    FunctionLink[0b01001101] = ButtonClick_A_13_Up;
    FunctionLink[0b01001110] = ButtonClick_A_14_Up;
    FunctionLink[0b01001111] = ButtonClick_A_15_Up; 
    
    //UP
    //PORT B
    FunctionLink[0b01010000] = ButtonClick_B_0_Up;
    FunctionLink[0b01010001] = ButtonClick_B_1_Up;
    FunctionLink[0b01010010] = ButtonClick_B_2_Up;
    FunctionLink[0b01010011] = ButtonClick_B_3_Up;
    FunctionLink[0b01010100] = ButtonClick_B_4_Up;
    FunctionLink[0b01010101] = ButtonClick_B_5_Up;
    FunctionLink[0b01010110] = ButtonClick_B_6_Up;
    FunctionLink[0b01010111] = ButtonClick_B_7_Up;
    FunctionLink[0b01011000] = ButtonClick_B_8_Up;
    FunctionLink[0b01011001] = ButtonClick_B_9_Up;
    FunctionLink[0b01011010] = ButtonClick_B_10_Up;
    FunctionLink[0b01011011] = ButtonClick_B_11_Up;
    FunctionLink[0b01011100] = ButtonClick_B_12_Up;
    FunctionLink[0b01011101] = ButtonClick_B_13_Up;
    FunctionLink[0b01011110] = ButtonClick_B_14_Up;
    FunctionLink[0b01011111] = ButtonClick_B_15_Up;
    
    //UP
    //PORT C
    FunctionLink[0b01100000] = ButtonClick_C_0_Up;
    FunctionLink[0b01100001] = ButtonClick_C_1_Up;
    FunctionLink[0b01100010] = ButtonClick_C_2_Up;
    FunctionLink[0b01100011] = ButtonClick_C_3_Up;
    FunctionLink[0b01100100] = ButtonClick_C_4_Up;
    FunctionLink[0b01100101] = ButtonClick_C_5_Up;
    FunctionLink[0b01100110] = ButtonClick_C_6_Up;
    FunctionLink[0b01100111] = ButtonClick_C_7_Up;
    FunctionLink[0b01101000] = ButtonClick_C_8_Up;
    FunctionLink[0b01101001] = ButtonClick_C_9_Up;
    FunctionLink[0b01101010] = ButtonClick_C_10_Up;
    FunctionLink[0b01101011] = ButtonClick_C_11_Up;
    FunctionLink[0b01101100] = ButtonClick_C_12_Up;
    FunctionLink[0b01101101] = ButtonClick_C_13_Up;
    FunctionLink[0b01101110] = ButtonClick_C_14_Up;
    FunctionLink[0b01101111] = ButtonClick_C_15_Up;

    //HOLD
    //PORT A
    FunctionLink[0b10000000] = ButtonClick_A_0_Hold;
    FunctionLink[0b10000001] = ButtonClick_A_1_Hold;
    FunctionLink[0b10000010] = ButtonClick_A_2_Hold;
    FunctionLink[0b10000011] = ButtonClick_A_3_Hold;
    FunctionLink[0b10000100] = ButtonClick_A_4_Hold;
    FunctionLink[0b10000101] = ButtonClick_A_5_Hold;
    FunctionLink[0b10000110] = ButtonClick_A_6_Hold;
    FunctionLink[0b10000111] = ButtonClick_A_7_Hold;
    FunctionLink[0b10001000] = ButtonClick_A_8_Hold;
    FunctionLink[0b10001001] = ButtonClick_A_9_Hold;
    FunctionLink[0b10001010] = ButtonClick_A_10_Hold;
    FunctionLink[0b10001011] = ButtonClick_A_11_Hold;
    FunctionLink[0b10001100] = ButtonClick_A_12_Hold;
    FunctionLink[0b10001101] = ButtonClick_A_13_Hold;
    FunctionLink[0b10001110] = ButtonClick_A_14_Hold;
    FunctionLink[0b10001111] = ButtonClick_A_15_Hold;
        
    //HOLD
    //PORT B
    FunctionLink[0b10010000] = ButtonClick_B_0_Hold;
    FunctionLink[0b10010001] = ButtonClick_B_1_Hold;
    FunctionLink[0b10010010] = ButtonClick_B_2_Hold;
    FunctionLink[0b10010011] = ButtonClick_B_3_Hold;
    FunctionLink[0b10010100] = ButtonClick_B_4_Hold;
    FunctionLink[0b10010101] = ButtonClick_B_5_Hold;
    FunctionLink[0b10010110] = ButtonClick_B_6_Hold;
    FunctionLink[0b10010111] = ButtonClick_B_7_Hold;
    FunctionLink[0b10011000] = ButtonClick_B_8_Hold;
    FunctionLink[0b10011001] = ButtonClick_B_9_Hold;
    FunctionLink[0b10011010] = ButtonClick_B_10_Hold;
    FunctionLink[0b10011011] = ButtonClick_B_11_Hold;
    FunctionLink[0b10011100] = ButtonClick_B_12_Hold;
    FunctionLink[0b10011101] = ButtonClick_B_13_Hold;
    FunctionLink[0b10011110] = ButtonClick_B_14_Hold;
    FunctionLink[0b10011111] = ButtonClick_B_15_Hold;
    
    //HOLD
    //PORT C
    FunctionLink[0b10100000] = ButtonClick_C_0_Hold;
    FunctionLink[0b10100001] = ButtonClick_C_1_Hold;
    FunctionLink[0b10100010] = ButtonClick_C_2_Hold;
    FunctionLink[0b10100011] = ButtonClick_C_3_Hold;
    FunctionLink[0b10100100] = ButtonClick_C_4_Hold;
    FunctionLink[0b10100101] = ButtonClick_C_5_Hold;
    FunctionLink[0b10100110] = ButtonClick_C_6_Hold;
    FunctionLink[0b10100111] = ButtonClick_C_7_Hold;
    FunctionLink[0b10101000] = ButtonClick_C_8_Hold;
    FunctionLink[0b10101001] = ButtonClick_C_9_Hold;
    FunctionLink[0b10101010] = ButtonClick_C_10_Hold;
    FunctionLink[0b10101011] = ButtonClick_C_11_Hold;
    FunctionLink[0b10101100] = ButtonClick_C_12_Hold;
    FunctionLink[0b10101101] = ButtonClick_C_13_Hold;
    FunctionLink[0b10101110] = ButtonClick_C_14_Hold;
    FunctionLink[0b10101111] = ButtonClick_C_15_Hold;                                             

}