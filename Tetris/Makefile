
Target = Generated/Tetris.exe

Source = Tetris_main.c Tetris_logic.c Tetris_display.c Tetris_operation.c Bmp.c
Object = $(Source:.c=.o)

CC = gcc
CCFLAGS = -g -Wall
LIBs = GL/freeglut.lib GL/OpenGL32.Lib
RM = rm

vpath %.o Generated/

all: $(Target)
$(Target): $(Object)
	$(CC) $(CCFLAGS) $^ $(LIBs) -o $@

%.o: %.c
	$(CC) $(CCFLAGS) -c $^ -o Generated/$@

.PHONY: clean
clean: 
	-$(RM) Generated/*.o Generated/*.exe
	