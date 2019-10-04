
#include <stdio.h>
#include "Type_define.h"
#include "Tetris_config.h"
#include "Tetris_display.h"
#include "Tetris_logic.h"
#include "Bmp.h"

void display_init(void)
{
    
}

static void display_gm_ready(void)
{
    BmpData bmp = { NULL, 0, 0, 0 };
    BmpInit("Resource\\gm_bg.bmp", &bmp);
	BmpToRGB(&bmp);
	BmpRmNevus(&bmp);
    glClear(GL_COLOR_BUFFER_BIT);
	BmpDraw(&bmp);
	glFlush();
}

void display_callback(void)
{
	Tetris_config config = get_config();
    printf("Game status: %d\n.", config.game_status);
	switch (config.game_status)
    {
        case GAME_STATUS_READY:
            display_gm_ready();
            break;
        case GAME_STATUS_START:
            break;
        case GAME_STATUS_PAUSE:
            break;
        case GAME_STATUS_OVER:
            break;
        case GAME_STATUS_EXIT:
            break;
    }
}

