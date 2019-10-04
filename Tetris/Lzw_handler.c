
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Type_define.h"
#include "Lzw_handler.h"

lzw_item* dictionary_init(void)
{
    lzw_item* head = (lzw_item*)malloc(lzw_item);
    lzw_item* current = head;
    lzw_item* tail = NULL;
    int i = 1;
    head->key = 0;
    head->value = (U8*)malloc(sizeof(U8));
    memcpy(head->value, 0, 1);
    head->length = 1;
    head->next = NULL;
    for ( ; i < 256; i++)
    {
        tail = (lzw_item*)malloc(lzw_item);
        tail->key = i;
        tail->value = (U8*)malloc(sizeof(U8));
        memcpy(tail->value, i, 1);
        tail->length = 1;
        tail->next = NULL;
        current->next = tail;
        current = tail;
    }
    
    return head;
}

BOOL dictionary_value_check(lzw_item* head, U8* value, int length)
{
    while (TRUE)
    {
        int compare = length == head->length;
        if (compare != 0)
        {
            compare = memcmp(head->value, value, length)
            if (compare == 0)
            {
                return TRUE;
            }
        }
        if (head->next != NULL)
        {
            head = head->next;
        }
        else
        {
            break;
        }
    }
    tail = (lzw_item*)malloc(lzw_item);
    tail->key = head->key + 1;
    tail->value = (U8*)malloc(length);
    memcpy(tail->value, value, length);
    tail->next = NULL;
    head->next = tail;
    
    return FALSE;
}

char* lzw_encode(char* plaintext)
{
    
}

char* lzw_decode(char* ciphertest)
{
    
}

#if 0
void LZWEncode(FILE *fp, BITFILE *bf)
{
    int character;
    int string_code;
    int index;
    unsigned long file_length;
 
    fseek(fp, 0, SEEK_END);  //文件指针定位到输入文件最后
    file_length = ftell(fp);  //得到输入文件大小
    fseek(fp, 0, SEEK_SET);  //文件指针定位到输入文件起始处
    BitsOutput(bf, file_length, 4*8);  /*将输入文件的大小写入输出文件中，4*8代表file_length是32位数字*/
    InitDictionary();  //初始化字典，设置各根节点
    string_code = -1;  //初始化前缀
    while(EOF!=(character=fgetc(fp)))
    {	//扫描输入文件，得到各字符
		/*判断(string_code，character)是否在字典中，如果在则返回对应编码，否则返回-1*/
        index = InDictionary(character, string_code);
        if( 0<=index)
        {	// (string_code，character)在字典中
            string_code = index;  //将(string_code，character)对应的编码作为前缀
        }
        else
        {	//(string_code，character)不在字典中
            output(bf, string_code);	//输出前缀
            if(MAX_CODE > next_code)
            {  //字典空间充足时
                //将(string_code，character)添加到字典中
                AddToDictionary(character, string_code);
            }
            string_code = character;  //将新字符做为前缀
        }
    }
    output(bf, string_code);  //输入文件扫描完毕，将最后未输出的前缀输出
}

void InitDictionary(void)
{  //初始化字典，将0-255根节点初始化
    int i;
 
    for(i=0; i<256; i++)
    {  //下标值为ASCII码值
        dictionary[i].suffix = i;  //根的后缀字符为对应ASCII码
        dictionary[i].parent = -1;  //前缀字符长度为0，没有前缀
        dictionary[i].firstchild = -1;  //暂时没有第一个孩子
        dictionary[i].nextsibling = i+1;	 /*下一个兄弟根节点下标为下一个ASCII码值*/
    }
    dictionary[255].nextsibling = -1;  //最后一个根节点没有下一个兄弟
    next_code = 256;  //为全局变量，标记下一个编码为256
}

int InDictionary(int character, int string_code)
{
    int sibling;
 
    /*string_code小于0说明该字符是文件第一个字符，一定有对应根节点并存在于字典中，所以返回(string_code，character)的编码---character的ASCII码*/
    if(0>string_code)
        return character;
 
    //自左向右遍历string_code节点的所有孩子（第一个孩子的所有兄弟）
    //以string_code的第一个孩子为长兄
    sibling = dictionary[string_code].firstchild;
 
    while(-1<sibling)
    {  //sibling等于-1说明所有兄弟遍历结束
 
        /*如果找到一个兄弟的后缀是character，则返回(string_code，character)的编码¬---该兄弟的下标*/
        if(character == dictionary[sibling].suffix)
            return sibling;
 
        //如果该兄弟的后缀不是该字符，则寻找下一个兄弟
        sibling = dictionary[sibling].nextsibling;
    }
 
    /*所有兄弟的后缀均不等于该字符，说明(string_code，character)不在字典中，返回-1*/
    return -1;
}

void AddToDictionary(int character, int string_code)
{
    int firstsibling, nextsibling;
    if( 0>string_code)
        return;
    dictionary[next_code].suffix = character;  //新节点的后缀为该字符
    dictionary[next_code].parent = string_code;  //新节点的母亲为该前缀
    dictionary[next_code].nextsibling = -1; //新节点下一个兄弟暂时不存在，设为-1
    dictionary[next_code].firstchild = -1;  //新节点第一个孩子暂时不存在，设为-1
    firstsibling = dictionary[string_code].firstchild;
   
	//下面设置新节点的兄弟关系
	 if( -1<firstsibling)
     {	//新节点的母亲原本有孩子
        nextsibling = firstsibling;
		//循环找到最后一个兄弟
        while(-1<dictionary[nextsibling].nextsibling ) 
            nextsibling = dictionary[nextsibling].nextsibling;
 
		//把新节点设为最后一个兄弟的下一个兄弟
        dictionary[nextsibling].nextsibling = next_code;
    }
    else
    {  //新节点的母亲原本没有孩子
		//把新节点设为母亲的第一个孩子
        dictionary[string_code].firstchild = next_code;    
    }
    next_code ++;  //下一个编码增加1
}

BITFILE *OpenBitFileOutput(char *filename)
{  //参数是文件名
    BITFILE *bf;
    bf = (BITFILE *)malloc(sizeof(BITFILE));
    if(NULL == bf) return NULL;
	//如果参数是NULL，则文件指向屏幕
    if(NULL == filename)
        bf->fp = stdout;
    else
        bf->fp = fopen(filename, "wb");  //以二进制只写的方式打开文件
    if(NULL == bf->fp)
        return NULL;
    bf->mask = 0x80;  //初始化掩码为1000 0000
    bf->rack = 0;  //初始化rack为0
    return bf;
}

void BitsOutput(BITFILE *bf, unsigned long code, int count)
{
    unsigned long mask;
 
	/*output宏定义缺省count为16。count为16时，mask为1000 0000 0000 0000。count为32时，mask为1000 0000 0000 0000 0000 0000 0000 0000*/
    mask = 1L << (count-1);
    while( 0 != mask)
    {  /*mask为0时，说明code共count位数字输出完毕，lzw是等长码*/
		/*按位输出code*/
        BitOutput(bf, (int)(0==(code&mask)?0:1));
        mask >>= 1;  //掩码向右移位
    }
}  //注：不同于huffman编码，huffman编码是不等长码，lzw可以看成是等长码，这里编码长度是16位

void BitOutput(BITFILE *bf, int bit)
{
	/*如果bit为1，则在rack下一个未写码位置由0变为1。如果bit为0，则rack不作处理，mask直接向右移位，代表下一个未写码位置为0*/
    if(0 != bit)
        bf->rack |= bf->mask;
    bf->mask >>= 1;
 
    /*每次mask移位后，都要判断mask是否溢出为0。若溢出，则代表成功累计写入八位，即该字节已写满。直接输出rack后，rack初始化为0，mask初始化为1000 0000*/
	if(0 == bf->mask)
    { 
        fputc(bf->rack, bf->fp);
        bf->rack = 0;
        bf->mask = 0x80;
    }
}

void CloseBitFileOutput(BITFILE *bf)
{
    //如果还存在为输出的二进制数，则直接输出
    if( 0x80 != bf->mask)
        fputc(bf->rack, bf->fp);
    fclose(bf->fp);  //关闭二进制输出文件
    free(bf);  //释放输出结构体的内存
}

void LZWDecode(BITFILE *bf, FILE *fp)
{
    int character;  /*当新读取的编码不存在于字典中时，character为旧编码last_code的首字母。当新读取的编码字典中存在时，character为新编码new_code的首字母*/
    int new_code, last_code;
    int phrase_length;  //输出字符串的长度
    unsigned long file_length;  //输出文件长度
 
    file_length = BitsInput(bf, 4*8);  /*输入文件起始处存储输出文件的大小，存储为unsigned int类型，占32位*/
    if( -1 == file_length)
        file_length = 0;
    InitDictionary();  //初始化字典，设置0-256根节点
    last_code = -1;  //开始时旧编码处空缺，故设置last_code为-1
    while(0<file_length)
    {  //是否读取到最后一个编码
        new_code = input(bf);  //以16位读取新编码
        if(new_code >= next_code)
        {   //字典中没有新编码
            d_stack[0] = character;  /*character为旧编码last_code的首字母，将其放置在栈数组顶部d_stack[0]*/
            /*遍历旧编码last_code所在树，将last_code对应字符串放置于d_stack栈数组中。前缀放于栈底方向，后缀位于d_stack[1]。得到字符总数，即要输出字符串的长度*/
            phrase_length = DecodeString(1, last_code);
        }
        else
        {  //字典中有新编码
            /*遍历新编码new_code所在树，将new_code对应字符串放置于d_stack栈数组中。前缀放于栈底方向，后缀位于栈顶d_stack[0]。得到字符总数，即要输出字符串的长度*/
            phrase_length = DecodeString(0, new_code);
        }
 
        /*当新读取的编码不存在于字典中时，character为旧编码last_code的首字母。当新读取的编码字典中存在时，character为新编码new_code的首字母*/
        character = d_stack[phrase_length-1];
 
        /*当新读取的编码不存在于字典中时，输出(旧编码last_code对应字符串，last_code对应首字母)。当新读取的编码存在于字典中时，输出新编码new_code对应字符串*/
        while(0<phrase_length)
        {
            phrase_length --;
            fputc(d_stack[phrase_length], fp);
            file_length--;
        }
 
        /*当新读取的编码不存在于字典中时，将(last_code对应字符串，last_code对应首字母)}添加到字典中。当新读取的编码存在于字典中时，将(last_code对应字符串，new_code对应首字母)添加到字典中。*/
        if(MAX_CODE>next_code)
        {  
            AddToDictionary(character, last_code);
        }
 
		//新编码变为旧编码
        last_code = new_code;
    }
}

unsigned long BitsInput(BITFILE *bf, int count){
    unsigned long mask;
    unsigned long value;
	/*假设count为16，则mask为1000 0000 0000 0000*/
    mask = 1L << (count-1);
    value = 0L;  //初始化value为0
	/*mask由1000 0000 0000 0000向右移位至溢出为0时循环结束，取得16位的等长码*/
    while(0!=mask)
    {
        /*输出文件中下一位为1时，value相应位置变为1。为0时，不作操作，直接跳至下一位*/
        if(1 == BitInput(bf))
            value |= mask;  //value在mask所表示位置的二进制数字变为1
        mask >>= 1;  //mask所表示位置向右一位
    }
    return value;
}

int BitInput(BITFILE *bf)
{
    int value;
 
    if(0x80 == bf->mask)
    {  //mask为1000 0000时，从文件中得到一字节数据
        bf->rack = fgetc(bf->fp);
        if(EOF == bf->rack)
        {  //确保成功得到数据
            fprintf(stderr, "Read after the end of file reached\n");
            exit(-1);
        }
    }
    value = bf->mask & bf->rack;  //取得mask所表示位置的二进制数字
    bf->mask >>= 1;  //mask所表示位置向右一位
	/*若掩码溢出为0，则mask重新变为1000 0000*/
    if(0==bf->mask)
        bf->mask = 0x80;
    return((0==value)?0:1);  //value为0时返回0，为非零值时返回1
}

int DecodeString(int start, int code)
{
    int count;  //count标记数组下标
    count = start;
    while(0<=code)
    {  //code为-1时，到达树根，循环结束
        d_stack[count] = dictionary[code].suffix;  /*将下标为code节点中的后缀字母放置于数组相应位置*/
        code = dictionary[code].parent;  //节点上移至母节点处
        count ++;  //数组下标增加1
    }
    return count;
}
#endif
