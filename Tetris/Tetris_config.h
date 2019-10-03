#ifndef __TETRIS_CONFIG_H__
#define __TETRIS_CONFIG_H__

#define MAX_ROW 48
#define MAX_COL 32

typedef struct config {
	U8 current_level;
	U8 current_item;
	U8 current_row;
	U8 current_col;
	U8 next_item;
	U8 max_row;
	U8 max_col;
	U8 reserve;
	U8 matrix[MAX_ROW][MAX_COL];
	U32 current_score;
	U32 high_score[10];
} Tetris_config;








#endif
