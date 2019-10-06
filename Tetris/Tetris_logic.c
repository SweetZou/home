
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Type_define.h"
#include "Tetris_config.h"
#include "Tetris_logic.h"
#include "Tetris_operation.h"

static Tetris_config config;

void logic_init(void)
{
    memset(&config, 0, sizeof(Tetris_config));
    config.game_status = GAME_STATUS_MENU;
    config.page_status = PAGE_MENU_STATUS_START;
    config.current_level = GAME_LEVEL_1;
}

Tetris_config get_config(void)
{
    return config;
}

static void game_menu_logic(U8 command)
{
    if (command == KEY_COMMAND_UP)
    {
        config.page_status--;
        if (config.page_status < PAGE_MENU_STATUS_START)
        {
            config.page_status = PAGE_MENU_STATUS_START;
        }
    }
    else if (command == KEY_COMMAND_DOWN)
    {
        config.page_status++;
        if (config.page_status > PAGE_MENU_STATUS_EXIT)
        {
            config.page_status = PAGE_MENU_STATUS_EXIT;
        }
    }
    else if (command == KEY_COMMAND_ENTER)
    {
        if (config.page_status == PAGE_MENU_STATUS_START)
        {
            config.game_status = GAME_STATUS_RUN;
        }
    }
}

static void game_run_logic(U8 command)
{
    printf("game is running.\n");
}

void idle_callback(void)
{
    U8 command = pop_key_command();
    printf("%-10ld - game status is %d.\n", clock(), config.game_status);
	switch (config.game_status)
    {
        case GAME_STATUS_MENU:
            game_menu_logic(command);
            break;
        case GAME_STATUS_RUN:
            game_run_logic(command);
            break;
        case GAME_STATUS_PAUSE:
            break;
        case GAME_STATUS_OVER:
            break;
        case GAME_STATUS_EXIT:
            break;
    }
}
