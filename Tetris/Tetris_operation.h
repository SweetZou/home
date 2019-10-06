#ifndef __TETRIS_OPERATION_H__
#define __TETRIS_OPERATION_H__

typedef enum KEY_COMMAND {
    KEY_COMMAND_INVALID = 0,
    KEY_COMMAND_UP,
    KEY_COMMAND_DOWN,
    KEY_COMMAND_LEFT,
    KEY_COMMAND_RIGHT,
    KEY_COMMAND_ENTER,
    KEY_COMMAND_MAX
} key_command_enum;

#define KEY_COMMAND_DEPTH 10

#define KEY_CODE_W 0x0077
#define KEY_CODE_UP 0x0065
#define KEY_CODE_A 0x0061
#define KEY_CODE_LEFT 0x0064
#define KEY_CODE_D 0x0064
#define KEY_CODE_RIGHT 0x0066
#define KEY_CODE_S 0x0073
#define KEY_CODE_DOWN 0x0067
#define KEY_CODE_ENTER 0x000D

extern void keyboard_callback(U8 key, S32 x, S32 y);

extern void specialkey_callback(S32 key, S32 x, S32 y);

extern void operation_init(void);

extern U8 pop_key_command(void);

#endif
