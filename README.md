# Stm32 Minesweeper 
## Что внутри?
Этот репозиторий содержит реализацию игры "Сапёр" на микроконтроллере [STM32F103C8](https://www.st.com/en/microcontrollers-microprocessors/stm32f103c8.html).
Код написан на языке Си стандарта C17.
## В проекте использовались:
* Arm Toolchain: arm-none-eabi-gcc;
* Gdb-multiarch debugger;
* Cmake & make;
* Build-essential;
* St-link utility for Linux.


## Использованная периферия:
* Программатор ST-LINK V2;
* Дисплей GMG12864-06D;
* Кнопка на 6 состояний.

## Реализация
<details>
  <summary>Gif с геймплеем</summary>

   ![gameplay](https://s3.gifyu.com/images/3fps.gif)

</details>

<details>
  <summary>Изображения</summary>

   ![main_screen](/Sources/img/IMG_0314.jpg)
   ![board](/Sources/img/IMG_0316.jpg)
   ![mine](/Sources/img/IMG_0319.JPG)
   ![lose](/Sources/img/IMG_0320.JPG)
   ![guesses](/Sources/img/IMG_0326.JPG)
   ![mistake](/Sources/img/IMG_0330.JPG)
   ![win](/Sources/img/IMG_0331.JPG)
   ![set](/Sources/img/IMG_0332.jpg)
</details>
