/*****************************************************************************
* | File      	:   EPD_4in01f.c
* | Author      :   Waveshare team
* | Function    :   4.01inch F e-paper test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2020-11-06
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
#include "EPD_4in01f.h"
#include "EPD_Test.h"
#include <time.h> 

void PrintData(int x_pos) {
    GUI_ReadBmp_RGB_7Color("./pic/cloud_small.bmp", x_pos, 20);
    Paint_DrawString_EN(x_pos + 10, 130, "15C", &Font24, EPD_4IN01F_WHITE, EPD_4IN01F_RED);
    Paint_DrawString_EN(x_pos + 10, 160, "2 m/s", &Font24, EPD_4IN01F_WHITE, EPD_4IN01F_GREEN);
    Paint_DrawString_EN(x_pos + 10, 190, "53%", &Font24, EPD_4IN01F_WHITE, EPD_4IN01F_BLUE);
}

int Table_test(void)
{
    printf("EPD_4in01F_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_4IN01F_Init();
	struct timespec start={0,0}, finish={0,0}; 
    clock_gettime(CLOCK_REALTIME,&start);
    EPD_4IN01F_Clear(EPD_4IN01F_WHITE);
	clock_gettime(CLOCK_REALTIME,&finish);
    printf("%ld S\r\n",finish.tv_sec-start.tv_sec);
    DEV_Delay_ms(100);

    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UDOUBLE Imagesize = ((EPD_4IN01F_WIDTH % 2 == 0)? (EPD_4IN01F_WIDTH / 2 ): (EPD_4IN01F_WIDTH / 2 + 1)) * EPD_4IN01F_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    Paint_NewImage(BlackImage, EPD_4IN01F_WIDTH, EPD_4IN01F_HEIGHT, 0, EPD_4IN01F_WHITE);
    Paint_SetScale(7);

#if 0
    Paint_Clear(EPD_4IN01F_WHITE);
    printf("Drawing:BlackImage\r\n");
    Paint_DrawRectangle(10, 10, 330, 320, EPD_4IN01F_BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    EPD_4IN01F_Display(BlackImage);
    DEV_Delay_ms(10000); 
#endif

#if 1
    for(int i = 0; i < 3; i++) {
	    printf("show image for array\r\n");
	    Paint_Clear(EPD_4IN01F_WHITE);

	    //Paint_DrawRectangle(1, 1, 160, 399, EPD_4IN01F_BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	    Paint_DrawLine(160, 1, 160, 399, EPD_4IN01F_BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	    Paint_DrawLine(320, 1, 320, 399, EPD_4IN01F_BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	    Paint_DrawLine(480, 1, 480, 399, EPD_4IN01F_BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	    PrintData(20);
	    PrintData(180);
	    PrintData(340);
	    PrintData(500);

	    char *i_string = (char*)i;
	    printf("\nRepeat: ");
	    printf(i_string);

	    //Paint_DrawString_EN(305, 230, i_string, &Font24, EPD_4IN01F_BLACK, EPD_4IN01F_WHITE);

	    EPD_4IN01F_Display(BlackImage);
	    //EPD_4IN01F_Display_part(BlackImage, 0, 0, 640, 200);
	    DEV_Delay_ms(4000);
    }
#endif

#if 0
    printf("e-Paper Clear...\r\n");
    EPD_4IN01F_Clear(EPD_4IN01F_WHITE);
    DEV_Delay_ms(1000); 
#endif
	
	printf("e-Paper Sleep...\r\n");
    EPD_4IN01F_Sleep();

    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    return 0;
}
