
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Type_define.h"
#include "Tetris_config.h"
#include "Tetris_logic.h"
#include "Tetris_operation.h"

static Tetris_config config;

static U8 loop_times[GAME_LEVEL_MAX] = {
    0,
    20,
    18,
    16,
    14,
    12,
    10,
    9,
    8,
    7,
    6
};

void logic_init(void)
{
    memset(&config, 0, sizeof(Tetris_config));
    config.game_status = GAME_STATUS_MENU;
    config.page_status = PAGE_MENU_STATUS_START;
    config.current_level = GAME_LEVEL_1;
    config.current_score = 0;
    {
        FILE* fptr = fopen("Tetris.ini", "rb");
        if (fptr == NULL)
        {
            config.highest_score = 0;
        }
        else
        {
            fread(&config.highest_score, sizeof(config.highest_score), 1, fptr);
        }
    }
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

int random(U8 range)
{
    return (clock() * 47 + 23) % range;
}

static void generate_block(U8 item_index, U8 item_status)
{
    switch(item_index)
    {
        case GAME_ITEM_SQUARE:
            break;
        case GAME_ITEM_Z:
            break;
        case GAME_ITEM_BACK_Z:
            break;
        case GAME_ITEM_L:
            break;
        case GAME_ITEM_BACK_L:
            break;
        case GAME_ITEM_T:
            break;
        case GAME_ITEM_I:
            break;
    }
}

static void generate_next_item()
{
    if (config.next_item_flag == DEACTIVATE)
    {
        config.next_item = random(GAME_ITEM_MAX);
        config.next_item_status = random(GAME_ITEM_STATUS_MAX);
        config.next_item_flag = ACTIVATE;
    }
}

static U8 current_edge_check(U8 edge)
{
    U8 ret = 0;
    
    return ret;
}

static void current_item_run(U8 command)
{
    static U8 counter = 0;
    if (config.current_item_flag == ACTIVATE)
    {
        if (counter >= loop_times[config.current_level])
        {
            config.current_row++;
        }
        if (command == KEY_COMMAND_UP)
        {
            config.current_item_status++;
            config.current_item_status %= GAME_ITEM_STATUS_MAX;
        }
        else if (command == KEY_COMMAND_LEFT)
        {
            config.current_col--;
            if (!current_edge_check(EDGE_LEFT))
            {
                config.current_col++;
            }
        }
        else if (command == KEY_COMMAND_RIGHT)
        {
            config.current_col++;
            if (!current_edge_check(EDGE_RIGHT))
            {
                config.current_col--;
            }
        }
        else if (command == KEY_COMMAND_DOWN)
        {
            
        }
        counter++;
    }
    else
    {
        if (config.next_item_flag == ACTIVATE)
        {
            config.current_item_flag = ACTIVATE;
            config.current_item = config.next_item;
            config.current_item_status = config.next_item_status;
            config.next_item_flag = DEACTIVATE;
        }
    }
}

static void game_run_logic(U8 command)
{
    generate_next_item();
    current_item_run(command);
}

static void game_pause_logic(U8 command)
{
    
}

static void game_over_logic(U8 command)
{
    if (config.current_score > config.highest_score)
    {
        FILE* fptr = fopen("Tetris.ini", "wb");
        config.highest_score = config.current_score;
        fwrite(&config.highest_score, sizeof(config.highest_score), 1, fptr);
    }
    if (command == KEY_COMMAND_ENTER)
    {
        config.game_status = GAME_STATUS_MENU;
    }
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
            game_pause_logic(command);
            break;
        case GAME_STATUS_OVER:
            game_over_logic(command);
            break;
        case GAME_STATUS_EXIT:
            break;
    }
}
