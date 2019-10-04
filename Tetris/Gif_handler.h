#ifndef __GIF_HANDLER_H__
#define __GIF_HANDLER_H__

#pragma pack (１)
typedef struct header {
	S8 signature[3];
	S8 version[3];
} gif_header;

typedef struct descriptor {
	S16 width;
	S16 heigth;
	U8 pixel:3;
	U8 sort_flag:1;
	U8 color_resolution:3;
	U8 global_color_table_flag:1;
	U8 background_color;
	U8 pixel_aspect_ratio;
} gif_logic_screen_descriptor;

typedef struct color {
	U8 red;
	U8 green;
	U8 blue;
} gif_color;

typedef struct image_descriptor {
	U8 start_flag;
	gif_color* local_color_table;
	U16 offset_x;
	U16 offset_y;
	U16 width;
	U16 height;
	U8 pixel:3;
	U8 reserve:2;
	U8 sort_flag:1;
	U8 interlace_flag:1;
	U8 local_color_table_flag:1;
} gif_image_descriptor;

typedef struct data_block {
	U8* data;
} gif_data_block;

typedef struct image_stream {
	U8 lzw_code_length;
	gif_data_block* blocks;
} gif_image_stream;

typedef struct render_type {
	U8 extension_introducer;
	U8 graphic_control_label;
	U8 block_size;
	U8 transparent_flag:1;
	U8 input_flag:1;
	U8 disposol_method:3;
	U8 reserve:3;
	U16 delay;
	U8 transparent_color_index;
	U8 block_terminator;
} gif89a_render_type;

typedef struct comment_extension {
	U8 extension_introducer;
	U8 comment_label;
	gif_data_block* blocks;
	U8 block_terminator;
} gif89a_comment_extension;

typedef struct image_data {
	gif_image_descriptor descriptor;
	gif_image_stream image_stream;
} gif_image_data;

typedef struct data_stream {
	gif_logic_screen_descriptor screen_descriptior;
	gif_color* global_color_table;
	gif_image_descriptor image_descriptor;
	gif_image_data image_data;
} gif_data_stream;

typedef struct tail {
	
} gif_tail;

typedef struct gif {
	gif_header header;
	gif_data_stream stream;
	gif_tail tail;
} gif_struct;

#pragma pack ()

#endif

