

#include <stdlib.h>
#include <string.h>
#include "Type_define.h"
#include "Tetris_config.h"
#include "Tetris_logic.h"

static Tetris_config config;

void logic_init(void)
{
    memset(&config, 0, sizeof(Tetris_config));
}

Tetris_config get_config(void)
{
    return config;
}

void idle_callback(void)
{
	switch (config.game_status)
    {
        case GAME_STATUS_READY:
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
