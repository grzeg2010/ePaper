/*****************************************************************************
* | File      	:   EPD_3in0g_test.c
* | Author      :   Waveshare team
* | Function    :   3inch e-paper (G) test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-07-15
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_3in0g.h"
#include "time.h"

int EPD_3in0g_test(void)
{
    printf("EPD_3IN0G_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_3IN0G_Init();

    printf("Black \r\n");
    EPD_3IN0G_Clear(EPD_3IN0G_WHITE); // WHITE
    DEV_Delay_ms(2000);

    //Create a new image cache
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_3IN0G_WIDTH % 4 == 0)? (EPD_3IN0G_WIDTH / 4 ): (EPD_3IN0G_WIDTH / 4 + 1)) * EPD_3IN0G_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_3IN0G_WIDTH, EPD_3IN0G_HEIGHT, 0, EPD_3IN0G_WHITE);
    Paint_SetScale(4);

#if 1   // show bmp
    printf("show BMP-----------------\r\n");
    EPD_3IN0G_Init();
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
		Paint_DrawBitMap(gImage_3in0g);
    EPD_3IN0G_Display(BlackImage);
    DEV_Delay_ms(2000);

#endif

#if 1   // Drawing on the image
    //1.Select Image
    EPD_3IN0G_Init();
    printf("SelectImage:BlackImage\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(0x55);

    // 2.Drawing on the image
    printf("Drawing:BlackImage\r\n");
    Paint_DrawPoint(10, 80, Red_4Color, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, Yellow_4Color, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, Black_4Color, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, Red_4Color, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, Red_4Color, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 70, 70, 120, Yellow_4Color, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, Yellow_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(45, 95, 20, Black_4Color, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(105, 95, 20, Black_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, Red_4Color, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, Yellow_4Color, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_EN(10, 0, "Red, yellow, white and black", &Font16, Red_4Color, Yellow_4Color);
    Paint_DrawString_EN(10, 35, "Four color e-Paper", &Font12, Yellow_4Color, Black_4Color);
    Paint_DrawString_CN(10, 125, "΢ѩ����", &Font24CN, Red_4Color, White_4Color);
    Paint_DrawNum(10, 50, 123456, &Font12, Red_4Color, White_4Color);

    printf("EPD_Display\r\n");
    EPD_3IN0G_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1   // Drawing on the image
    //1.Select Image
    EPD_3IN0G_Init();
    printf("SelectImage:BlackImage\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(0x55);

    // 2.Drawing on the image
    printf("Drawing:BlackImage\r\n");
    Paint_DrawRectangle(1, 1, 167, 86, Red_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(1, 314, 167, 399, Yellow_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawRectangle(59, 1, 109, 399, Black_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    printf("EPD_Display\r\n");
    EPD_3IN0G_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

#if 1   // Drawing on the image
    //1.Select Image
    EPD_3IN0G_Init();
    printf("SelectImage:BlackImage\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(0x55);

    int wNumber, lNumber;
    wNumber = (EPD_3IN0G_WIDTH/80)==0 ? (EPD_3IN0G_WIDTH/80) : (EPD_3IN0G_WIDTH/80)+1;
    lNumber = (EPD_3IN0G_HEIGHT/20)==0 ? (EPD_3IN0G_HEIGHT/20) : (EPD_3IN0G_HEIGHT/20)+1;
    // 2.Drawing on the image
    printf("Drawing:BlackImage\r\n");
    for(int j=0; j<lNumber; j++) {
        if(j%2 == 0) {
            for(int i=0; i<wNumber; i++) {
                Paint_DrawRectangle(1+i*80, 1+j*20, 20+i*80, 20+j*20, Red_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                Paint_DrawRectangle(21+i*80, 1+j*20, 40+i*80, 20+j*20, Yellow_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                Paint_DrawRectangle(41+i*80, 1+j*20, 60+i*80, 20+j*20, White_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                Paint_DrawRectangle(61+i*80, 1+j*20, 80+i*80, 20+j*20, Black_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            }
        }

        else {
            for(int i=0; i<wNumber; i++) {
                Paint_DrawRectangle(1+i*80, 1+j*20, 20+i*80, 20+j*20, White_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                Paint_DrawRectangle(21+i*80, 1+j*20, 40+i*80, 20+j*20, Black_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                Paint_DrawRectangle(41+i*80, 1+j*20, 60+i*80, 20+j*20, Red_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
                Paint_DrawRectangle(61+i*80, 1+j*20, 80+i*80, 20+j*20, Yellow_4Color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
            }
        }

    }

    printf("EPD_Display\r\n");
    EPD_3IN0G_Display(BlackImage);
    DEV_Delay_ms(3000);
#endif

    EPD_3IN0G_Init();
    printf("Clear...\r\n");
    EPD_3IN0G_Clear(EPD_3IN0G_WHITE);

    printf("Goto Sleep...\r\n");
    EPD_3IN0G_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;
}

