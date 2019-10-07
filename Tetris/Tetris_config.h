#ifndef __TETRIS_CONFIG_H__
#define __TETRIS_CONFIG_H__

#define MAX_ROW (48 + 4)
#define MAX_COL 32

typedef enum GAME_STATUS {
    GAME_STATUS_MENU = 0,
    GAME_STATUS_RUN,
    GAME_STATUS_PAUSE,
    GAME_STATUS_OVER,
    GAME_STATUS_EXIT,
    GAME_STATUS_MAX
} game_status_enum;

typedef enum PAGE_MENU_STATUS {
    PAGE_MENU_STATUS_RESUME = 0,
    PAGE_MENU_STATUS_START,
    PAGE_MENU_STATUS_HELP,
    PAGE_MENU_STATUS_EXIT,
    PAGE_MENU_STATUS_MAX
} page_menu_status_enum;

typedef enum PAGE_GAME_STATUS {
    PAGE_GAME_STATUS_RUN,
    PAGE_GAME_STATUS_PAUSE,
    PAGE_GAME_STATUS_MAX
} page_game_status_enum;

typedef enum GAME_LEVEL {
    GAME_LEVEL_1 = 1,
    GAME_LEVEL_2,
    GAME_LEVEL_3,
    GAME_LEVEL_4,
    GAME_LEVEL_5,
    GAME_LEVEL_6,
    GAME_LEVEL_7,
    GAME_LEVEL_8,
    GAME_LEVEL_9,
    GAME_LEVEL_10,
    GAME_LEVEL_MAX
} game_level_enum;

typedef enum GAME_ITEM {
    GAME_ITEM_SQUARE = 0,
    GAME_ITEM_Z,
    GAME_ITEM_BACK_Z,
    GAME_ITEM_L,
    GAME_ITEM_BACK_L,
    GAME_ITEM_T,
    GAME_ITEM_I,
    GAME_ITEM_MAX
} game_item_enum;

typedef enum GAME_ITEM_STATUS {
    GAME_ITEM_STATUS_1 = 0,
    GAME_ITEM_STATUS_2,
    GAME_ITEM_STATUS_3,
    GAME_ITEM_STATUS_4,
    GAME_ITEM_STATUS_MAX
} game_item_status_enum;

typedef struct unit {
    U8 color:4;
    U8 filled:1;
    U8 status:1;
    U8 reserve:2;
} unit_block;

typedef struct config {
	U16 game_status:5;
	U16 page_status:5;
	U16 current_level:6;
	U8 current_item:4;
	U8 current_item_status:3;
	U8 current_item_flag:1;
	U8 next_item:4;
	U8 next_item_status:3;
	U8 next_item_flag:1;
	U8 current_row;
	S8 current_col;
	U8 max_row;
	U8 max_col;
	unit_block matrix[MAX_ROW][MAX_COL];
	U32 current_score;
	U32 highest_score;
} Tetris_config;








#endif
