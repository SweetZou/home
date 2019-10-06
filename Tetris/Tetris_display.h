#ifndef __TETRIS_DISPLAY_H__
#define __TETRIS_DISPLAY_H__

typedef enum resource_id {
    RES_PHONE = 0,
    RES_TETRIS_BG,
    RES_TETRIS_GM_TITLE,
    RES_TETRIS_GM_MENU_BG,
    RES_TETRIS_GM_MENU_START,
    RES_TETRIS_GM_MENU_HELP,
    RES_TETRIS_GM_MENU_EXIT,
    RES_TETRIS_GM_MAIN,
    RES_TETRIS_GM_BOTTEM,
    RES_TETRIS_GM_BLOCK,
    RES_TETRIS_GM_NUMBER,
    RES_TETRIS_BTN_PAUSE,
    RES_TETRIS_BTN_ENSURE,
    RES_TETRIS_BTN_CANCEL,
    RES_MAX
} Resource_enum;

extern void display_init(void);
extern void display_callback(void);

#endif
