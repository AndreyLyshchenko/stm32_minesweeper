#include "logic.h"

void (*click_function[15])();

void initialize_click_funktions_array()
{
	click_function[0] = end_dialog_click_mid;
	click_function[1] = ingame_click_mid;
	click_function[2] = menu_click_mid;

	click_function[3] = end_dialog_click_up;
	click_function[4] = ingame_click_up;
	click_function[5] = menu_click_up;
	
	click_function[6] = end_dialog_click_down;
	click_function[7] = ingame_click_down;
	click_function[8] = menu_click_down;

	click_function[9] = end_dialog_click_left;
	click_function[10] = ingame_click_left;
	click_function[11] = menu_click_left;

	click_function[12] = end_dialog_click_right;
	click_function[13] = ingame_click_right;
	click_function[14] = menu_click_right;
}

void use_click_function(uint8_t pressed_button)
{
	if (game_started)
	{
		if (ending_dialog)
		{
			// End dialog
			click_function[pressed_button]();
		}
		else
		{
			// Ingame
			click_function[pressed_button+1]();
		}
	}
	else
	{
		// Menu
		click_function[pressed_button+2]();
	}
}

void ButtonClick_A_8_Down() //mid
{
	use_click_function(CLICK_MID);
}

void ButtonClick_B_12_Down() //up
{	
	use_click_function(CLICK_UP);
}

void ButtonClick_B_13_Down() //down
{	
	use_click_function(CLICK_DOWN);
}
void ButtonClick_B_14_Down() //left
{	
	use_click_function(CLICK_LEFT);
}
void ButtonClick_B_15_Down() //right
{	
	use_click_function(CLICK_RIGHT);
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