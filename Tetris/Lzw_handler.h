#ifndef __LZW_HANDLER_H__
#define __LZW_HANDLER_H__
 
typedef struct key_value lzw_item;

struct key_value{
    S32 key;
    U8* value;
    S32 length;
    lzw_item* next;
};

extern char* lzw_encode(char* plaintext);

extern char* lzw_decode(char* ciphertest);


#endif
