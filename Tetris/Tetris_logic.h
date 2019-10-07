#ifndef __TETRIS_LOGIC_H__
#define __TETRIS_LOGIC_H__

typedef enum item_flag {
    DEACTIVATE = 0,
    ACTIVATE
} item_flag_enum;

typedef enum item_edge {
    EDGE_UP,
    EDGE_DOWN,
    EDGE_LEFT,
    EDGE_RIGHT
} item_edge_enum;

extern void logic_init(void);
extern void idle_callback(void);
extern Tetris_config get_config(void);

#endif
