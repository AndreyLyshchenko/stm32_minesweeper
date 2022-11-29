#ifndef buttons_H
    #define buttons_H
    #define WEAK __attribute__ ((weak))   
    #include <stm32f10x.h>
    #include <stdbool.h>
    #include "delay.h"

    static bool LinkArrayIsSet = false;

    static void (*FunctionLink[0b11111111])();

    void InitializingLinkArray();

    int BtnClick(char IO_Port, int IO_Pin, char IO_Mode, uint32_t DefaultDelay, uint32_t HoldDelay);

    // PORT A
    void WEAK ButtonClick_A_0_Down();
    void WEAK ButtonClick_A_0_Up();
    void WEAK ButtonClick_A_0_Hold();

    void WEAK  ButtonClick_A_1_Down();
    void WEAK ButtonClick_A_1_Up();
    void WEAK ButtonClick_A_1_Hold();

    void WEAK ButtonClick_A_2_Down();
    void WEAK ButtonClick_A_2_Up();
    void WEAK ButtonClick_A_2_Hold();

    void WEAK ButtonClick_A_3_Down();
    void WEAK ButtonClick_A_3_Up();
    void WEAK ButtonClick_A_3_Hold();

    void WEAK ButtonClick_A_4_Down();
    void WEAK ButtonClick_A_4_Up();
    void WEAK ButtonClick_A_4_Hold();

    void WEAK ButtonClick_A_5_Down();
    void WEAK ButtonClick_A_5_Up();
    void WEAK ButtonClick_A_5_Hold();

    void WEAK ButtonClick_A_6_Down();
    void WEAK ButtonClick_A_6_Up();
    void WEAK ButtonClick_A_6_Hold();

    void WEAK ButtonClick_A_7_Down();
    void WEAK ButtonClick_A_7_Up();
    void WEAK ButtonClick_A_7_Hold();

    void WEAK ButtonClick_A_8_Down();
    void WEAK ButtonClick_A_8_Up();
    void WEAK ButtonClick_A_8_Hold();

    void WEAK ButtonClick_A_9_Down();
    void WEAK ButtonClick_A_9_Up();
    void WEAK ButtonClick_A_9_Hold();

    void WEAK ButtonClick_A_10_Down();
    void WEAK ButtonClick_A_10_Up();
    void WEAK ButtonClick_A_10_Hold();

    void WEAK ButtonClick_A_11_Down();
    void WEAK ButtonClick_A_11_Up();
    void WEAK ButtonClick_A_11_Hold();

    void WEAK ButtonClick_A_12_Down();
    void WEAK ButtonClick_A_12_Up();
    void WEAK ButtonClick_A_12_Hold();

    void WEAK ButtonClick_A_13_Down();
    void WEAK ButtonClick_A_13_Up();
    void WEAK ButtonClick_A_13_Hold();

    void WEAK ButtonClick_A_14_Down();
    void WEAK ButtonClick_A_14_Up();
    void WEAK ButtonClick_A_14_Hold();

    void WEAK ButtonClick_A_15_Down();
    void WEAK ButtonClick_A_15_Up();
    void WEAK ButtonClick_A_15_Hold();

    // PORT B
    void WEAK ButtonClick_B_0_Down();
    void WEAK ButtonClick_B_0_Up();
    void WEAK ButtonClick_B_0_Hold();

    void WEAK ButtonClick_B_1_Down();
    void WEAK ButtonClick_B_1_Up();
    void WEAK ButtonClick_B_1_Hold();

    void WEAK ButtonClick_B_2_Down();
    void WEAK ButtonClick_B_2_Up();
    void WEAK ButtonClick_B_2_Hold();

    void WEAK ButtonClick_B_3_Down();
    void WEAK ButtonClick_B_3_Up();
    void WEAK ButtonClick_B_3_Hold();

    void WEAK ButtonClick_B_4_Down();
    void WEAK ButtonClick_B_4_Up();
    void WEAK ButtonClick_B_4_Hold();

    void WEAK ButtonClick_B_5_Down();
    void WEAK ButtonClick_B_5_Up();
    void WEAK ButtonClick_B_5_Hold();

    void WEAK ButtonClick_B_6_Down();
    void WEAK ButtonClick_B_6_Up();
    void WEAK ButtonClick_B_6_Hold();

    void WEAK ButtonClick_B_7_Down();
    void WEAK ButtonClick_B_7_Up();
    void WEAK ButtonClick_B_7_Hold();

    void WEAK ButtonClick_B_8_Down();
    void WEAK ButtonClick_B_8_Up();
    void WEAK ButtonClick_B_8_Hold();

    void WEAK ButtonClick_B_9_Down();
    void WEAK ButtonClick_B_9_Up();
    void WEAK ButtonClick_B_9_Hold();

    void WEAK ButtonClick_B_10_Down();
    void WEAK ButtonClick_B_10_Up();
    void WEAK ButtonClick_B_10_Hold();

    void WEAK ButtonClick_B_11_Down();
    void WEAK ButtonClick_B_11_Up();
    void WEAK ButtonClick_B_11_Hold();

    void WEAK ButtonClick_B_12_Down();
    void WEAK ButtonClick_B_12_Up();
    void WEAK ButtonClick_B_12_Hold();

    void WEAK ButtonClick_B_13_Down();
    void WEAK ButtonClick_B_13_Up();
    void WEAK ButtonClick_B_13_Hold();

    void WEAK ButtonClick_B_14_Down();
    void WEAK ButtonClick_B_14_Up();
    void WEAK ButtonClick_B_14_Hold();

    void WEAK ButtonClick_B_15_Down();
    void WEAK ButtonClick_B_15_Up();
    void WEAK ButtonClick_B_15_Hold();

    // PORT C
    void WEAK ButtonClick_C_0_Down();
    void WEAK ButtonClick_C_0_Up();
    void WEAK ButtonClick_C_0_Hold();

    void WEAK ButtonClick_C_1_Down();
    void WEAK ButtonClick_C_1_Up();
    void WEAK ButtonClick_C_1_Hold();

    void WEAK ButtonClick_C_2_Down();
    void WEAK ButtonClick_C_2_Up();
    void WEAK ButtonClick_C_2_Hold();

    void WEAK ButtonClick_C_3_Down();
    void WEAK ButtonClick_C_3_Up();
    void WEAK ButtonClick_C_3_Hold();

    void WEAK ButtonClick_C_4_Down();
    void WEAK ButtonClick_C_4_Up();
    void WEAK ButtonClick_C_4_Hold();

    void WEAK ButtonClick_C_5_Down();
    void WEAK ButtonClick_C_5_Up();
    void WEAK ButtonClick_C_5_Hold();

    void WEAK ButtonClick_C_6_Down();
    void WEAK ButtonClick_C_6_Up();
    void WEAK ButtonClick_C_6_Hold();

    void WEAK ButtonClick_C_7_Down();
    void WEAK ButtonClick_C_7_Up();
    void WEAK ButtonClick_C_7_Hold();

    void WEAK ButtonClick_C_8_Down();
    void WEAK ButtonClick_C_8_Up();
    void WEAK ButtonClick_C_8_Hold();

    void WEAK ButtonClick_C_9_Down();
    void WEAK ButtonClick_C_9_Up();
    void WEAK ButtonClick_C_9_Hold();

    void WEAK ButtonClick_C_10_Down();
    void WEAK ButtonClick_C_10_Up();
    void WEAK ButtonClick_C_10_Hold();

    void WEAK ButtonClick_C_11_Down();
    void WEAK ButtonClick_C_11_Up();
    void WEAK ButtonClick_C_11_Hold();

    void WEAK ButtonClick_C_12_Down();
    void WEAK ButtonClick_C_12_Up();
    void WEAK ButtonClick_C_12_Hold();

    void WEAK ButtonClick_C_13_Down();
    void WEAK ButtonClick_C_13_Up();
    void WEAK ButtonClick_C_13_Hold();

    void WEAK ButtonClick_C_14_Down();
    void WEAK ButtonClick_C_14_Up();
    void WEAK ButtonClick_C_14_Hold();

    void WEAK ButtonClick_C_15_Down();
    void WEAK ButtonClick_C_15_Up();
    void WEAK ButtonClick_C_15_Hold();

#endif