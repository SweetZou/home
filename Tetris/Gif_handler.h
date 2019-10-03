#ifndef __GIF_HANDLER_H__
#define __GIF_HANDLER_H__

typedef struct header {
	
} gif_header;

typedef struct stream {
	
} gif_stream;

typedef struct tail {
	
} gif_tail;

typedef struct gif {
	gif_header header;
	gif_stream stream;
	gif_tail tail;
} gif_struct;







#endif
