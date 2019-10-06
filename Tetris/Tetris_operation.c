
#include <stdio.h>
#include "Type_define.h"
#include "Tetris_operation.h"

static U8 key_command_queue[KEY_COMMAND_DEPTH];
static U8 queue_head = 0;
static U8 queue_tail = 0;

void operation_init(void)
{
    int i;
    for (i = 0; i < KEY_COMMAND_DEPTH; i++)
    {
        key_command_queue[i] = KEY_COMMAND_INVALID;
    }
}

U8 pop_key_command(void)
{
    U8 command = key_command_queue[queue_head];
    if (command != KEY_COMMAND_INVALID)
    {
        key_command_queue[queue_head] = KEY_COMMAND_INVALID;
        queue_head++;
        queue_head %= KEY_COMMAND_DEPTH;
    }
    return command;
}

static void push_key_command(U8 command)
{
    if ((queue_tail == queue_head) && (key_command_queue[queue_head] != KEY_COMMAND_INVALID))
    {
        //queue is full
    }
    else
    {
        key_command_queue[queue_tail] = command;
        queue_tail++;
        queue_tail %= KEY_COMMAND_DEPTH;
    }
}

void keyboard_callback(U8 key, S32 x, S32 y)
{
    //printf("key code is 0x%04X.\n", key);
	if (key == KEY_CODE_W)
    {
        push_key_command(KEY_COMMAND_UP);
    }
    else if (key == KEY_CODE_A)
    {
        push_key_command(KEY_COMMAND_LEFT);
    }
    else if (key == KEY_CODE_D)
    {
        push_key_command(KEY_COMMAND_RIGHT);
    }
    else if (key == KEY_CODE_S)
    {
        push_key_command(KEY_COMMAND_DOWN);
    }
    else if (key == KEY_CODE_ENTER)
    {
        push_key_command(KEY_COMMAND_ENTER);
    }
}

void specialkey_callback(S32 key, S32 x, S32 y)
{
    //printf("special key code is 0x%04X.\n", key);
	if (key == KEY_CODE_UP)
    {
        push_key_command(KEY_COMMAND_UP);
    }
    else if (key == KEY_CODE_LEFT)
    {
        push_key_command(KEY_COMMAND_LEFT);
    }
    else if (key == KEY_CODE_RIGHT)
    {
        push_key_command(KEY_COMMAND_RIGHT);
    }
    else if (key == KEY_CODE_DOWN)
    {
        push_key_command(KEY_COMMAND_DOWN);
    }
}
