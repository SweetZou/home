
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Type_define.h"
#include "Tetris_config.h"
#include "Tetris_display.h"
#include "Tetris_logic.h"
#include "Bmp.h"

const GLfloat Pi = 3.1415926536f;

static BmpData bmp[RES_MAX];

static BmpData screen_bmp;


static void screen_bmp_init()
{
    memset(&screen_bmp, 0, sizeof(BmpData));
    screen_bmp.Width = bmp[RES_PHONE].Width;
    screen_bmp.Height = bmp[RES_PHONE].Height;
	screen_bmp.DataLen = bmp[RES_PHONE].DataLen;
	
	//读取像素数据
	screen_bmp.PixelData = (GLubyte*)malloc(screen_bmp.DataLen);
	if(screen_bmp.PixelData == NULL)
	{
		exit(1);
	}
    memcpy(&screen_bmp.PixelData[0], &bmp[RES_PHONE].PixelData[0], screen_bmp.DataLen);
}

void display_init(void)
{
    memset(&bmp[RES_PHONE], 0, sizeof(BmpData));
    BmpInit("Resource/phone_320_480.bmp", &bmp[RES_PHONE]);
	BmpToRGB(&bmp[RES_PHONE]);
    
    memset(&bmp[RES_TETRIS_BG], 0, sizeof(BmpData));
    BmpInit("Resource/gm_bg.bmp", &bmp[RES_TETRIS_BG]);
	BmpToRGB(&bmp[RES_TETRIS_BG]);
    
    memset(&bmp[RES_TETRIS_GM_TITLE], 0, sizeof(BmpData));
    BmpInit("Resource/gm_title.bmp", &bmp[RES_TETRIS_GM_TITLE]);
	BmpToRGB(&bmp[RES_TETRIS_GM_TITLE]);
    
    memset(&bmp[RES_TETRIS_GM_MENU_BG], 0, sizeof(BmpData));
    BmpInit("Resource/gm_menu_bg.bmp", &bmp[RES_TETRIS_GM_MENU_BG]);
	BmpToRGB(&bmp[RES_TETRIS_GM_MENU_BG]);
    
    memset(&bmp[RES_TETRIS_GM_MENU_START], 0, sizeof(BmpData));
    BmpInit("Resource/gm_menu_start.bmp", &bmp[RES_TETRIS_GM_MENU_START]);
	BmpToRGB(&bmp[RES_TETRIS_GM_MENU_START]);
    
    memset(&bmp[RES_TETRIS_GM_MENU_HELP], 0, sizeof(BmpData));
    BmpInit("Resource/gm_menu_help.bmp", &bmp[RES_TETRIS_GM_MENU_HELP]);
	BmpToRGB(&bmp[RES_TETRIS_GM_MENU_HELP]);
    
    memset(&bmp[RES_TETRIS_GM_MENU_EXIT], 0, sizeof(BmpData));
    BmpInit("Resource/gm_menu_exit.bmp", &bmp[RES_TETRIS_GM_MENU_EXIT]);
	BmpToRGB(&bmp[RES_TETRIS_GM_MENU_EXIT]);
    
    memset(&bmp[RES_TETRIS_GM_MAIN], 0, sizeof(BmpData));
    BmpInit("Resource/gm_main.bmp", &bmp[RES_TETRIS_GM_MAIN]);
	BmpToRGB(&bmp[RES_TETRIS_GM_MAIN]);
    
    memset(&bmp[RES_TETRIS_GM_BOTTEM], 0, sizeof(BmpData));
    BmpInit("Resource/gm_bottem.bmp", &bmp[RES_TETRIS_GM_BOTTEM]);
	BmpToRGB(&bmp[RES_TETRIS_GM_BOTTEM]);
    
    memset(&bmp[RES_TETRIS_GM_BLOCK], 0, sizeof(BmpData));
    BmpInit("Resource/gm_block.bmp", &bmp[RES_TETRIS_GM_BLOCK]);
	BmpToRGB(&bmp[RES_TETRIS_GM_BLOCK]);
    
    memset(&bmp[RES_TETRIS_GM_NUMBER], 0, sizeof(BmpData));
    BmpInit("Resource/gm_number.bmp", &bmp[RES_TETRIS_GM_NUMBER]);
	BmpToRGB(&bmp[RES_TETRIS_GM_NUMBER]);
    
    memset(&bmp[RES_TETRIS_BTN_PAUSE], 0, sizeof(BmpData));
    BmpInit("Resource/btn_pause.bmp", &bmp[RES_TETRIS_BTN_PAUSE]);
	BmpToRGB(&bmp[RES_TETRIS_BTN_PAUSE]);
    
    memset(&bmp[RES_TETRIS_BTN_ENSURE], 0, sizeof(BmpData));
    BmpInit("Resource/btn_ensure.bmp", &bmp[RES_TETRIS_BTN_ENSURE]);
	BmpToRGB(&bmp[RES_TETRIS_BTN_ENSURE]);
    
    memset(&bmp[RES_TETRIS_BTN_CANCEL], 0, sizeof(BmpData));
    BmpInit("Resource/btn_cancel.bmp", &bmp[RES_TETRIS_BTN_CANCEL]);
	BmpToRGB(&bmp[RES_TETRIS_BTN_CANCEL]);
    
    screen_bmp_init();
}

void display_deinit(void)
{
    int i;
    for (i = 0; i < RES_MAX; i++)
    {
        BmpDestroy(&bmp[i]);
    }
    BmpDestroy(&screen_bmp);
}

static void display_bmp_add(BmpData* bmp, int offset_x, int offset_y)
{
    int x, y;
    int bmp_data_pointer = 0;
    for (y = 0; (y < bmp->Height) && (y + offset_y < screen_bmp.Height); y++)
    {
        for (x = 0; (x < bmp->Width) && (x + offset_x < screen_bmp.Width); x++)
        {
            if ((bmp->PixelData[bmp_data_pointer] == 255)
                && (bmp->PixelData[bmp_data_pointer + 1] == 255)
                && (bmp->PixelData[bmp_data_pointer + 2] == 255))
            {
                //nothing to do
            }
            else
            {
                memcpy(&screen_bmp.PixelData[((y + offset_y) * screen_bmp.Width + x + offset_x) * 3],
                       &bmp->PixelData[bmp_data_pointer],
                       3);
            }
            bmp_data_pointer += 3;
        }
        bmp_data_pointer = (bmp_data_pointer + 3) & ~3;
    }
}

static void display_gm_menu(U8 page_status)
{
    display_bmp_add(&bmp[RES_TETRIS_BG],
                    0,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_BG].Height);
	display_bmp_add(&bmp[RES_TETRIS_GM_TITLE],
                    (320 - bmp[RES_TETRIS_GM_TITLE].Width) >> 1,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_GM_TITLE].Height - 71);
	display_bmp_add(&bmp[RES_TETRIS_GM_MENU_BG],
                    (320 - bmp[RES_TETRIS_GM_MENU_BG].Width) >> 1,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_GM_MENU_BG].Height - 156);
    {
        int offset_y = 0;
        if (page_status != PAGE_MENU_STATUS_START)
        {
            offset_y = bmp[RES_TETRIS_GM_MENU_START].Height >> 1;
        }
        BmpData* normal_part = get_sub_bmp(&bmp[RES_TETRIS_GM_MENU_START],
                                           0,
                                           offset_y,
                                           bmp[RES_TETRIS_GM_MENU_START].Width,
                                           bmp[RES_TETRIS_GM_MENU_START].Height >> 1);
        display_bmp_add(normal_part,
                        (320 - normal_part->Width) >> 1,
                        SCREEN_HEIGHT - normal_part->Height - 200);
        BmpDestroy(normal_part);
    }
    {
        int offset_y = 0;
        if (page_status != PAGE_MENU_STATUS_HELP)
        {
            offset_y = bmp[RES_TETRIS_GM_MENU_HELP].Height >> 1;
        }
        BmpData* normal_part = get_sub_bmp(&bmp[RES_TETRIS_GM_MENU_HELP],
                                           0,
                                           offset_y,
                                           bmp[RES_TETRIS_GM_MENU_HELP].Width,
                                           bmp[RES_TETRIS_GM_MENU_HELP].Height >> 1);
        display_bmp_add(normal_part,
                        (320 - normal_part->Width) >> 1,
                        SCREEN_HEIGHT - normal_part->Height - 250);
        BmpDestroy(normal_part);
    }
    {
        int offset_y = 0;
        if (page_status != PAGE_MENU_STATUS_EXIT)
        {
            offset_y = bmp[RES_TETRIS_GM_MENU_EXIT].Height >> 1;
        }
        BmpData* normal_part = get_sub_bmp(&bmp[RES_TETRIS_GM_MENU_EXIT],
                                           0,
                                           offset_y,
                                           bmp[RES_TETRIS_GM_MENU_EXIT].Width,
                                           bmp[RES_TETRIS_GM_MENU_EXIT].Height >> 1);
        display_bmp_add(normal_part,
                        (320 - normal_part->Width) >> 1,
                        SCREEN_HEIGHT - normal_part->Height - 300);
        BmpDestroy(normal_part);
    }
	BmpDraw(&screen_bmp);
}

static void display_gm_run(Tetris_config* config)
{
    display_bmp_add(&bmp[RES_TETRIS_BG],
                    0,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_BG].Height);
    display_bmp_add(&bmp[RES_TETRIS_GM_MAIN],
                    18,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_GM_MAIN].Height - 40);
    display_bmp_add(&bmp[RES_TETRIS_GM_BOTTEM],
                    0,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_BG].Height);
    display_bmp_add(&bmp[RES_TETRIS_BTN_PAUSE],
                    18,
                    SCREEN_HEIGHT - bmp[RES_TETRIS_BG].Height + 7);
    BmpDraw(&screen_bmp);
}

void display_callback(void)
{
	Tetris_config config = get_config();
    //printf("Game status: %d.\n", config.game_status);
    
    glClear(GL_COLOR_BUFFER_BIT);
	switch (config.game_status)
    {
        case GAME_STATUS_MENU:
            display_gm_menu(config.page_status);
            break;
        case GAME_STATUS_RUN:
            display_gm_run(&config);
            break;
        case GAME_STATUS_PAUSE:
            break;
        case GAME_STATUS_OVER:
            break;
        case GAME_STATUS_EXIT:
            break;
    }
	glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}

