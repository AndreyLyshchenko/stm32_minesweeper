#include "logic.h"

void end_dialog_item_select(void);
void draw_restart_select(void);
void draw_menu_select(void);
void change_selected_dialog_item(void);
uint8_t dialog_selector;
bool restart_flag;


void create_end_dialog_window(void)
{
	if (win_flag)
	{
		load_image_from_array(game_end_win,30,12,127-30,64-14);
	}
	else
	{
		load_image_from_array(game_end_loose,30,12,127-30,64-14);
	}
	copy_map(Board,Bit_map);
	draw_changes();
    dialog_selector = 0;
    ending_dialog = true;
    end_dialog_item_select();
    transfer_control_to_buttons();
}

void end_dialog_item_select(void)
{
    load_map(Bit_map,Board);
    if (dialog_selector == 0) 
    {
        draw_restart_select();
    }
    else 
    {
        draw_menu_select();
    }
    draw_changes();
}

void end_dialog_click_mid(void)
{
 if (dialog_selector == 0)
    {
        restart_flag = true;
    }
    terminator = true;
}

void change_selected_dialog_item(void)
{
    dialog_selector = !dialog_selector;
    copy_map(Board,Bit_map);
    if ( dialog_selector == 0)
    {
        draw_restart_select();
    }
    else
    {
        draw_menu_select();
    }
    draw_changes();
}

void end_dialog_click_up(void)
{
    change_selected_dialog_item();
}
void end_dialog_click_down(void)
{
    change_selected_dialog_item();
}

void draw_restart_select()
{
    rectangle(43,26,43+41,26+9,CL_WHITE,NO_FILL,VIRTUAL);
    rectangle(43,26+11,43+41,26+9+11,CL_BLACK,NO_FILL,VIRTUAL);
}

void draw_menu_select()
{
    rectangle(43,26,43+41,26+9,CL_BLACK,NO_FILL,VIRTUAL);
    rectangle(43,26+11,43+41,26+9+11,CL_WHITE,NO_FILL,VIRTUAL);
}


void end_dialog_click_left(void)
{
    //
}
void end_dialog_click_right(void)
{
    //
}