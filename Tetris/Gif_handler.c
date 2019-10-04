
#include <stdio.h>
#include <memory.h>
#include "Type_define.h"
#include "Gif_handler.h"

static void get_gif_header(FILE* gif_file, gif_struct* gif)
{
	fread(&gif->gif_header, sizeof(gif->gif_header), 1, gif_file)
}

static void get_gif_screen_info(FILE* gif_file, gif_struct* gif)
{
	fread(&gif->stream.screen_descriptor, sizeof(gif->stream.screen_descriptor), gif_file)
}

static void get_gif_global_color_table(FILE* gif_file, gif_struct* gif)
{
	int color_count = 2 << gif->stream.screen_descriptor.pixel;
    gif->stream.global_color_table = (gif_color*)malloc(sizeof(gif_color) * color_count);
    fread(&gif->stream.global_color_table, sizeof(gif_color) * color_count, gif_file)
}

gif_struct* get_gif_info(char* gif_path)
{
	gif_struct* gif = (gif_struct*)malloc(sizeof(gif_struct));
	FILE* gif_file = fopen(gif_path, "rb");
	get_gif_header(gif_file, gif);
	get_gif_screen_info(gif_file, gif);
    get_gif_global_color_table(gif_file, gif);

	return gif
}

